# MiniShell

MiniShell is a simple command-line shell written in C. It allows you to execute commands by entering them into the shell prompt. The shell searches for the executable in the system `PATH` and runs it if found.

## Features

- Supports executing commands by searching in the system `PATH`.
- Continues to prompt for new commands until the user exits.
- Supports basic command-line parameters.
- Exits the shell gracefully with the command `leave`.

## Getting Started

### Prerequisites

- A C compiler (e.g., `gcc`)
- A Unix-like operating system (Linux, macOS, etc.)

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/avihai119/minishell.git
    cd minishell
    ```

2. Compile the shell:
    ```sh
    gcc -o minishell minishell.c
    ```

3. Run the shell:
    ```sh
    ./minishell
    ```

## Usage

1. Start the shell by running the compiled executable:
    ```sh
    ./minishell
    ```

2. Enter any command you would like to run. For example:
    ```sh
    > ls -l
    > echo "Hello, World!"
    ```

3. To exit the shell, type:
    ```sh
    > leave
    ```

## Code Overview

The main logic of the shell is in the `minishell.c` file. Here is a brief overview of its structure:

- The `main` function enters an infinite loop, continuously prompting the user for commands.
- Commands are read using `fgets`, and the newline character is removed.
- If the command is `leave`, the shell exits.
- The shell uses `fork` to create a child process to execute the command.
- The `execv` function is used to run the command, searching each directory in the system `PATH`.
- If the command is not found, an error message is displayed.

## Example

```sh
Enter command: > ls -l
total 64
-rwxr-xr-x  1 user user  16784 Jul  4 10:20 minishell
-rw-r--r--  1 user user   1232 Jul  4 10:20 minishell.c

Enter command: > echo "Hello, World!"
Hello, World!

Enter command: > leave
