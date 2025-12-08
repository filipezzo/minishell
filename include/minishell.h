#ifndef MINISHELL_H
#define MINISHELL_H

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

#endif