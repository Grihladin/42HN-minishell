<div align="center">

# <img src="https://github.com/Grihladin/42-project-badges/blob/main/badges/minishelle.png" width="150" height="150"> 

</div>

Minishell ([42Heilbronn](https://www.42heilbronn.de/en/) project) is a simple shell implementation that recreates basic bash functionality. The program demonstrates process management, signal handling, and command parsing while providing a fully functional command-line interface.

## 🐚 Shell Features

Minishell implements core shell functionality including command execution, piping, redirection, and built-in commands. It handles environment variables, signal management, and provides a readline-based interactive prompt.

## 🛠️ Implementation

- **Command Parsing**: Tokenization and AST-based command parsing
- **Process Management**: Fork/exec model for command execution
- **Signal Handling**: Proper SIGINT and SIGQUIT handling
- **Pipe Support**: Multi-command pipelines with proper file descriptor management
- **Redirection**: Input/output redirection with heredoc support
- **Built-ins**: Implementation of essential shell built-in commands
- **Environment**: Variable expansion and environment management

## ⚡ Key Components

- **AST Parser**: Abstract Syntax Tree for complex command structures
- **Expansion Engine**: Variable and quote expansion system
- **Execution Engine**: Process management and command execution
- **Signal System**: Non-blocking signal handling for interactive use
- **Memory Management**: Robust cleanup and leak prevention

## 📦 Installation

**Requirements:**
- macOS
- Homebrew (macOS)
- Miniconda (automatically installed if missing)

> **⚠️ If Miniconda was just installed, you need to restart your terminal before running `make`!**

```bash
git clone https://github.com/Grihladin/42HN-minishell.git
cd 42HN-minishell
make
```
## 🚀 Usage

```bash
./minishell
```

Once running, minishell provides an interactive shell prompt:

```bash
⚡️ minishell ⚡️ ➜ echo "Hello, World!"
Hello, World!
⚡️ minishell ⚡️ ➜ ls -la | grep minishell
-rwxr-xr-x  1 user  staff  123456 Jul  6 12:00 minishell
⚡️ minishell ⚡️ ➜ exit
```

## 🎯 Supported Features

### Shell Operations
- **Command Execution**: External program execution with PATH resolution
- **Pipelines**: Multi-command pipes (`cmd1 | cmd2 | cmd3`)
- **Redirections**: 
  - Input redirection (`< file`)
  - Output redirection (`> file`)
  - Append redirection (`>> file`)
  - Heredoc (`<< delimiter`)
- **Variable Expansion**: `$VAR` and `$?` (exit status)
- **Quote Handling**: Single and double quotes with proper expansion
- **Signal Handling**: Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT)

## 🚨 Error Handling

Minishell handles various error conditions gracefully:

- **Syntax Errors**: Invalid command syntax
- **File Errors**: Permission denied, file not found
- **Memory Errors**: Allocation failures with cleanup
- **Signal Handling**: Proper cleanup on interruption
- **Process Errors**: Fork/exec failures

## 📁 Project Structure

```
42HN-minishell/
├── inc/                           # Header files
│   └── minishell.h                # Main header with all declarations
├── src/                           # Source files
│   ├── main.c                     # Program entry point
│   ├── ast_tree/                  # Abstract Syntax Tree implementation
│   │   ├── ast_build.c            # AST construction
│   │   ├── ast_nodes.c            # Node creation and management
│   │   └── ast_utils.c            # AST utility functions
│   ├── builtins/                  # Built-in command implementations
│   │   ├── ft_cd/                 # Change directory command
│   │   ├── ft_echo/               # Echo command
│   │   ├── ft_env/                # Environment commands
│   │   ├── ft_exit/               # Exit command
│   │   ├── ft_export/             # Export command
│   │   ├── ft_pwd/                # Print working directory
│   │   └── ft_unset/              # Unset command
│   ├── execute/                   # Command execution engine
│   │   ├── execute.c              # Main execution logic
│   │   ├── execute_pipe.c         # Pipeline execution
│   │   ├── execute_redirect.c     # Redirection handling
│   │   └── execute_tree.c         # AST traversal and execution
│   ├── expansion/                 # Variable and quote expansion
│   │   ├── expansion.c            # Main expansion logic
│   │   ├── expansion_get_var.c    # Variable resolution
│   │   ├── expansion_heredoc.c    # Heredoc expansion
│   │   └── expansion_quotes.c     # Quote processing
│   ├── signals/                   # Signal handling
│   │   ├── sig_actions.c          # Main signal setup
│   │   ├── sig_actions_here_doc.c # Heredoc signals
│   │   └── sig_actions_quit.c     # Quit signal handling
│   └── utils/                     # Utility functions
│       ├── init.c                 # Initialization
│       ├── tokenization.c         # Input tokenization
│       ├── user_input.c           # Input handling
│       ├── prompt.c               # Prompt display
│       ├── here_doc.c             # Heredoc implementation
│       ├── pipes.c                # Pipe utilities
│       ├── get_path.c             # PATH resolution
│       ├── env_to_array.c         # Environment conversion
│       ├── free_vars.c            # Memory cleanup
│       └── utils*.c               # Various utilities
├── libft/                         # Custom C library (submodule)
├── get_next_line/                 # Line reading utility (submodule)
├── Makefile                       # Build configuration
└── README.md                      # Documentation
```

---

### Made with ❤️ by [psenko](https://github.com/plavik) and [mratke](https://github.com/Grihladin) - 42 Heilbronn
