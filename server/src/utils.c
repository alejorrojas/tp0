#include"utils.h"

t_log* logger;

int iniciar_servidor(void)
{
    int socket_servidor;
    struct addrinfo hints, *servinfo;
    int err;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = AI_PASSIVE;     // Usar la IP del servidor

    // Obtener información de la dirección del servidor
    err = getaddrinfo(NULL, PUERTO, &hints, &servinfo);
    if (err != 0) {
        log_error(logger, "Error en getaddrinfo: %s", gai_strerror(err));
        abort(); 
    }

    // Creamos el socket
    int fd_escucha = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (fd_escucha == -1) {
        log_error(logger, "Error al crear el socket: %s", strerror(errno));
        freeaddrinfo(servinfo);
        abort(); 
    }

    // Configurar el socket para reutilizar el puerto
    err = setsockopt(fd_escucha, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int));
    if (err == -1) {
        log_error(logger, "Error en setsockopt: %s", strerror(errno));
        close(fd_escucha);
        freeaddrinfo(servinfo);
        abort(); 
    }

    // Asociar el socket al puerto especificado
    err = bind(fd_escucha, servinfo->ai_addr, servinfo->ai_addrlen);
    if (err == -1) {
        log_error(logger, "Error en bind: %s", strerror(errno));
        close(fd_escucha);
        freeaddrinfo(servinfo);
        abort(); 
    }

    // Liberar la estructura servinfo ya que no se necesita más
    freeaddrinfo(servinfo);

    // Poner el socket en modo de escucha
    err = listen(fd_escucha, SOMAXCONN);
    if (err == -1) {
        log_error(logger, "Error en listen: %s", strerror(errno));
        close(fd_escucha);
        abort(); 
    }

    // Si todo salió bien, el servidor está listo para aceptar conexiones
    log_info(logger, "Yes! Listo para escuchar a mi cliente");

    // Devolver el descriptor del socket
    return fd_escucha;
}

int esperar_cliente(int socket_servidor)
{
	// Quitar esta línea cuando hayamos terminado de implementar la funcion
	// assert(!"no implementado!");

	// Aceptamos un nuevo cliente
	int socket_cliente = accept(socket_servidor, NULL, NULL);
	log_info(logger, "Se conecto un cliente!");

	return socket_cliente;
}

int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

void recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}

t_list* recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
}
