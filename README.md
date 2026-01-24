## Minishell 🐚

A minimal bash-like shell written in C, developed as part of the 42 School curriculum.

This project aims to reproduce the core behavior of a Unix shell, focusing on process creation, parsing, pipes, redirections, signals, and environment management, following strict constraints similar to a real shell.

## ✨ Features

- Interactive prompt with readline

- Command history

- Builtins: echo, cd, pwd, export, unset, env, exit

- External command execution (execve)

- Pipelines (|)

- Logical operators (&&, ||)

- Redirections: <, >, >>

- Heredoc << (pipe-based)

- Environment variables and $?

- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)


## 🧠 Project Architecture

The project is divided into two main subsystems, mirroring how a real shell works.

### 1️⃣ Parsing

Responsible for understanding user input and transforming it into executable structures.

- Lexer

- Tokenizes the input

- Handles quotes, operators, and words

- Syntax Analysis

- Validates grammar

- Detects invalid sequences

- Parser

- Builds an AST (Abstract Syntax Tree)

- Supports pipes, logical operators, and subshells

### 2️⃣ Execution

Responsible for executing the parsed structures.

- AST traversal

- Pipeline flattening

- Forking and process control

- Redirection handling

- Builtin execution in parent process when required

- External command execution in child processes

- Signal management per execution context

## 🛠️ Installation Requirements

- GCC or Clang
- Make
- Unix-like environment (Linux or macOS recommended)\
```⚠️ Windows users should use WSL or a Linux VM. ```


If you need help compiling C programs:\
[How to compile and run C programs](https://www.geeksforgeeks.org/techtips/how-to-compile-and-run-c-program-in-terminal/)

## ▶️ Usage
```bash
git clone https://github.com/filipezzo/minishell.git
cd minishell
make
./minishell
```

## 📚 Documentation - PTBR

Detailed notes and diagrams created during the development process:

- [Parsing overview](docs/frontend.tldr)
- [Execution essentials](docs/execution.tldr)

## 📌 Example
```bash
minishell$ echo hello | wc -c
6

minishell$ cat << EOF | grep a
banana
apple
EOF
banana
apple
```
## 👨‍💻 Authors

- Filipe Avanzzo - fsousa@42sp
- Mauricio Hidani - mhidani@42sp

**42 School — São Paulo**