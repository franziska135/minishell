# Minishell

The "Minishell" project aims to create a simple shell, similar to bash, that can parse and execute commands, handle basic input/output redirections, implement environment variables, and manage signal handling. This project is implemented as part of the 42 school curriculum by Franziska Marggraf and Mohamad Zolfaghari.

## Warning for 42 Students

This repository is intended as a reference and educational tool. **42 students are strongly advised not to copy this code without fully understanding its functionality.** Plagiarism in any form is against 42's principles and could lead to serious academic consequences. Use this repository responsibly to learn and better understand how to implement similar functionalities on your own.

## Features

- **Command Prompt**: Displays a prompt when waiting for a new command.
- **Command History**: Maintains a history of commands that can be navigated.
- **Executable Search**: Searches and launches executables based on the PATH variable, or using relative or absolute paths.
- **Redirections**:
  - `<` redirects input.
  - `>` redirects output.
  - `<<` reads input until a line containing a specified delimiter.
  - `>>` redirects output in append mode.
- **Pipes**: Implements pipes (`|`) to allow the output of one command to serve as input to the next.
- **Environment Variables**: Handles expansion of environment variables that begin with `$`.
- **Exit Status**: Handles `$?` which expands to the exit status of the most recently executed foreground pipeline.
- **Signal Handling**: Implements custom behavior for `ctrl-C`, `ctrl-D`, and `ctrl-\` similar to bash:
  - `ctrl-C`: Displays a new prompt on a new line.
  - `ctrl-D`: Exits the shell.
  - `ctrl-\`: Does nothing.
- **Builtins**: Implements several built-in commands:
  - `echo` with option `-n`
  - `cd` only with a relative or absolute path
  - `pwd` without options
  - `export` without options
  - `unset` without options
  - `env` without options or arguments
  - `exit` without options

## Compilation

Clone the repository and compile the Minishell with the following commands:

```
git clone https://github.com/yourusername/minishell.git
cd minishell
make
```
## Usage

Run Minishell by executing:

```bash
./minishell
```

Once running, Minishell will display a command prompt similar to bash where you can type commands for execution.

