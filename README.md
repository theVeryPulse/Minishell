# Minishell

Minishell is a simple shell program written in C, providing a basic command-line interface for users to interact with their operating system. It supports various built-in commands and allows users to execute external programs as well.

## Features

- **Command Execution:** Execute shell commands and external programs.
- **Argument Expansion** Expands environment variables such s `$PATH`, single quoted argument to literal string, double quoted argument to environment variable expanded string.
- **Built-in Commands:** Supports a variety of built-in commands, including `cd`, `echo`, `env`, `exit`, `export`, `pwd`, and `unset`.
- **Command Line Editing:** Utilizes readline library for command line editing and history functionality.
- **Signal Handling:** Handles signals include `Ctrl+C` [SIGINT] and `Ctrl+\` [SIGQUIT].
- **Input/Output Redirection:** Supports input/output redirection with `<`: input redirect, `>`: output redirect, `>>`: output redirect append, `<<`: heredoc.
- **Pipes:** Allows piping of commands using `|` operator.
- **Working history** Use arrow `↑` and `↓` to browse through history and retry commands.

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/theVeryPulse/Minishell.git
    ```
2. Navigate into the cloned directory:
   ```bash
   cd Minishell
   ```
3. Compile the program using make:
    ```bash
    make
    ```
4. Run the minishell executable:
    ```bash
    ./minishell
    ```

## Usage
Once the minishell program is running, you can interact with it using various commands and features:

**Built-in Commands**

 - `cd`: Change directory
    ```minishell
    cd /path/to/directory
    cd - # Goes back to previous directory
    ```
 - `echo`: Print arguments to standard output.
    ```minishell
    echo $PATH
    echo $?
    echo '$USER 123' "$USER 123"
    ```
 - `env`: Without arguments: print environment variables; with arguments: run program in modified environment (see `man env`).
    ```minishell
    env # prints all environment variables
    env PATH= ls # Set PATH to empty in a environment copy, then try running ls.
    ```
 - `exit`: Exit minishell
    ```minishell
    exit # return the value of the latest recorded exit status
    exit 123 # return specified value
    ```
 - `export`: Add or modify environment variable values.
    ```minishell
    export PATH=
    export a=1
    ```
 - `pwd`: Print current directory.
 - `unset`: Remove environment variable.

**External Commands**

Execute any external program by typing its name. Minishell searches for executable according to the PATH variable. 
```minishell
ls -l
```

**Input/Output Redirection**

Use `<`, `>`, `<<`, `>>` operators for input and output redirections.
```minishell
cat < input.txt > output.txt
cat <<end >output1.txt | cat <<end >output2.txt
```

**Piping**

Pipe multiple commands together using the `|` operator. When there are pipes, all commands will be executed in child processes.
```minishell
ls -l | grep .txt
cat file.txt | wc -l
```

## Contributors
- [theVeryPulse](https://github.com/theVeryPulse)
- [pejasco](https://github.com/pejasco)
