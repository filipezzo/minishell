#ifndef MINISHELL_H
#define MINISHELL_H

#define BUFSIZE 1024
#define PATH_MAX 4096

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "libft.h"

typedef enum e_type
{
    REDIR_IN,     // <
    REDIR_OUT,    // >
    REDIR_APPEND, // >>
    REDIR_HEREDOC // <<
} t_type;

typedef struct s_redir
{
    t_type type;
    char *file; // nome do arquivo
    struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
    char **args;           // {"ls", "-la", NULL};
    t_redir *redirections; // lista de redireções
    pid_t pid;             // id do processo
    struct s_cmd *next;    // prox comando do pipe
} t_cmd;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_shell
{
    int exit_status;
    t_env *env_list; // incremente se precisar.
} t_shell;

// exemplo cat < in.txt | grep oi > out.txt

// no 1
//  args = {"cat", NULL}
//  redirects =  [type: REDIR_IN, file: "in.txt", next: NULL]
//  pid = preenchido dps do fork
//  next = &no2

// no 2
//  args = {"grep", "oi", NULL}
//  redirects =  [type: REDIR_OUT, file: "out.txt", next: NULL]
//  pid = PID DPS DO FORK
//  next = NULL

// execute
int is_command_builtin(const char *command_name);
int redirect_input(const char *filename);
int redirect_output(const char *filename);
int redirect_append(const char *filename);
void apply_redirect(t_cmd *cmd);
int builtin_echo(t_cmd *cmd);
int builtin_env(t_env *list);
int builtin_unset(t_env **env_list, char **args);
int builtin_export(t_shell *shell, char **args);
// UTILS

void free_env_node(t_env *node);
int is_valid_env_key(char *str);
void update_or_create_node(t_env **head, char *key, char *value);
int count_list_elements(t_env *list);

// MOCKS --- REMOVER AO FINAL DO PROJETO

void init_mock_env(t_shell *shell);

#endif