
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
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

typedef enum e_type
{
	WORD,		   // 		Word
	COMMAND,	   // 		Command
	REDIR_IN,	   // <	Redirect in
	REDIR_OUT,	   // >	Redirect out
	REDIR_APPEND,  // >>	Redirect Append
	REDIR_HEREDOC, // <<	Redirect Heredoc
	PIPE,		   // |	Pipe
	LPAREN,		   // (	Left open parentheses
	RPAREN,		   // )	Right close parentheses
	RUN_BKG,	   // &	Run in background
	CMD_SEP,	   // ;	Commands separators
	AND_IF,		   // &&	And conditional
	AND_OR,		   // ||	Or conditional
} t_type;

typedef struct s_redir
{
	t_type type;
	char *file; // nome do arquivo
	struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
	char **args;		   // {"ls", "-la", NULL};
	t_redir *redirections; // lista de redireções
	pid_t pid;			   // id do processo
	struct s_cmd *next;	   // prox comando do pipe
} t_cmd;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_shell
{
	int exit_status; // valor do $?
	t_env *env_list; // lista de variaveis de ambiente
	t_cmd *cmd_list; // lista dos argumentos
} t_shell;

typedef struct s_lex_unit
{
	enum e_type type;
	char *content;
} t_lexunit;

typedef struct s_siglexer
{
	t_type type; // Tipo de token
	char *sign;	 // Sinal
	size_t size; // Tamanho
} t_siglexer;

typedef struct s_shared_work
{
	t_siglexer **signs_lexer;
} t_shared_work;

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

// builtin
int builtin_cd(t_shell *shell, char **args);
int builtin_echo(t_cmd *cmd);
int builtin_env(t_env *list);
int builtin_exit(t_shell *shell, char **args);
int builtin_export(t_shell *shell, char **args);
int builtin_pwd();
int builtin_unset(t_env **env_list, char **args);
void run_builtin(t_shell *shell, t_cmd *cmd);
int is_command_builtin(const char *cmd);
// UTILS

void free_env_node(t_env *node);
void free_shell(t_shell *shell);
int is_valid_env_key(char *str);
void update_or_create_node(t_env **head, char *key, char *value);
int count_list_elements(t_env *list);
void free_shell(t_shell *shell);

// MOCKS --- REMOVER AO FINAL DO PROJETO

void init_mock_env(t_shell *shell);

// Execute =====================================================================
// Redirections ----------------------------------------------------------------

int redirect_input(const char *filename);
int redirect_output(const char *filename);
int redirect_append(const char *filename);
void apply_redirect(t_cmd *cmd);

// Builtins --------------------------------------------------------------------

int is_command_builtin(const char *command_name);
int builtin_echo(t_cmd *cmd);
int builtin_env(t_env *list);
int builtin_unset(t_env **env_list, char **args);
int builtin_export(t_shell *shell, char **args);
// ===================================================================== Execute

// Lexer =======================================================================
// Principal Functions ---------------------------------------------------------

t_dlist *lexer(char *in, t_siglexer **siglexer);
// ======================================================================= Lexer

// UTILS =======================================================================

void free_env_node(t_env *node);
int is_valid_env_key(char *str);
void update_or_create_node(t_env **head, char *key, char *value);
int count_list_elements(t_env *list);
t_bool lex_isjump(char c);
// ======================================================================= UTILS

// Instances ===================================================================
// Lexer Unit ------------------------------------------------------------------

t_bool new_lexunit(t_lexunit **new, t_type type, char *content);
t_bool destroy_lexunit(void *ptr);

// Signal Lexer ----------------------------------------------------------------

t_siglexer *new_siglexer(t_type type, char *sign, size_t size);
t_siglexer **new_lst_siglexer(void);
t_bool destroy_siglexer(void *ptr);
t_bool destroy_lst_siglexer(void *ptr);
// =================================================================== Instances

// MOCKS --- REMOVER AO FINAL DO PROJETO =======================================

void init_mock_env(t_shell *shell);
// ======================================= MOCKS --- REMOVER AO FINAL DO PROJETO

#endif