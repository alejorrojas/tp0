# Sistemas Operativos - TP0

## ¿De qué trata?

El TP0 es una práctica inicial para empezar a familiarizarse con algunas de las herramientas necesarias para el trabajo práctico cuatrimestral de la materia Sistemas Operativos.

Es un ejercicio corto y sirve como base para empezar el TP cuatrimestral.

## Consigna

Podés encontrar la consigna en el siguiente [link].

[link]: https://faq.utnso.com.ar/tp0-enunciado

<br/>
<br/>
<br/>



## Module Runner Script for testing 

This project contains a script (`run-modules.sh`) that automates the process of building and running four modules (`kernel`, `cpu`, `memoria`, and `filesystem`) concurrently in the same machine. Each module is run in a separate terminal window.

### How to Run

Follow these steps to execute the script:

1. **Navigate to the project directory**:
    ```bash
    cd tp-2024-2c-Undefined/
    ```

2. **Make the script executable**:
    ```bash
    chmod +x run-modules.sh
    ```

3. **Run the script**:
    ```bash
    ./run-modules.sh
    ```

   This will:
   - Open four terminal windows, each running a different module.
   - Each terminal window will perform the following for each module:
     - Clean the build (`make clean`).
     - Build the module (`make`).
     - Execute the module binary (`./bin/{module}`).

### How to Kill All Open Terminals

If you want to close all the terminals opened by the script, run the following command in your main terminal:

4. **Kill all `xterm` processes**:
    ```bash
    pkill xterm
    ```

This will terminate all the `xterm` windows that were opened by the script.
