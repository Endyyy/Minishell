Minishell
Introduction
Minishell is a small-scale shell implementation inspired by popular Unix shells like Bash. This project is part of the curriculum at 42, designed to help students grasp important concepts of system programming, process management, file handling, and command-line parsing.

In this project, you’ll implement a basic shell that can execute commands, handle environment variables, manage input and output redirection, and more. The goal is to simulate a simplified but functional version of a shell with essential features.

Objectives
Implement a command-line interface (CLI) that can interpret and execute commands.
Manage system calls such as fork, execve, and waitpid.
Handle simple built-in commands like cd, echo, exit, etc.
Implement input and output redirection with >, >>, and <.
Manage environment variables with setenv, unsetenv, and env commands.
Handle pipes (|) for chaining commands.
Ensure that your shell can handle errors gracefully, especially invalid commands or incorrect usage of syntax.
Features
Command execution: Accepts user input, parses it, and executes corresponding commands.
Built-in commands: Implements commonly used shell built-ins like cd, exit, and echo.
Redirection: Supports file input/output redirection using > and <, as well as append redirection using >>.
Pipes: Supports pipe operations (|) to allow the output of one command to be used as the input for another.
Environment variables: Users can manage environment variables using commands like env, setenv, and unsetenv.
Error handling: Properly handles common errors like invalid commands, invalid arguments, and incorrect file redirection syntax.
Process management: Creates new processes with fork and manages their execution using execve. Waits for child processes using waitpid and handles process termination correctly.
Requirements
C Programming: The shell is written in C and requires a solid understanding of system programming concepts, such as system calls and memory management.
Unix/Linux Environment: Development should be done in a Unix-like environment (Linux, macOS, etc.) with access to the standard C libraries.
Implementation Details
Main Loop: The shell continuously prompts the user for input, parses it, and executes the corresponding commands until the user exits.
Command Parsing: The input is split into commands and arguments, which are then processed to identify built-ins or external programs.
Forking: When executing external commands, the shell forks a new process and uses execve to execute the command.
Redirection Handling: The shell handles redirections by modifying the file descriptors of processes before executing commands.
Signal Handling: Implements basic signal handling to ensure the shell behaves correctly when receiving signals like SIGINT.
