
#ifndef MINISHELL_H
#define MINISHELL_H

#define BUFSIZE 1024
#define PATH_MAX 4096

#include "libft.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

extern int g_signal_status;

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

typedef enum e_sig
{
	STATE_PROMPT,
    STATE_EXEC,
    STATE_HEREDOC
}	t_sig;

typedef struct s_redir
{
	t_type type;
	char *file; // nome do arquivo
	struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
	char **args;		   // {"ls", "-la", NULL} | {"cat", "hello.txt", NULL}
	t_redir *redirections; // lista de redireções
	pid_t pid;			   // id do processo
	struct s_cmd *next;	   // prox comando do pipe
} t_cmd;

typedef struct s_job
{
	struct s_cmd *pipeline;
	t_type oper;
	struct s_job *next;
} t_job;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_prompt
{
	char	*user;
	char	*host;
	char	*home;
	char	*dir;
	char	*type;
}			t_prompt;

typedef struct s_shell
{
	int exit_status; // valor do $?
	t_env *env_list; // lista de variaveis de ambiente
	t_cmd *cmd_list; // lista dos argumentos / - >
	int saved_stdin;
	int saved_stdout;
	pid_t last_pid;
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

// init

char **env_list_to_array(t_env *env_list);
void init_env(t_shell *shell, char **envp);

// execute
int is_command_builtin(const char *command_name);
int redirect_input(const char *filename);
int redirect_output(const char *filename);
int redirect_append(const char *filename);

// builtin
int builtin_cd(t_shell *shell, char **args);
int builtin_echo(t_cmd *cmd);
int builtin_env(t_env *list, char **args);
int builtin_exit(t_shell *shell, char **args);
int builtin_export(t_shell *shell, char **args);
int builtin_pwd(void);
int builtin_unset(t_env **env_list, char **args);
int run_builtin(t_shell *shell, t_cmd *cmd);
int is_command_builtin(const char *cmd);

// SIGNALS
void init_signals(void);
void set_signals_exec(void);
void set_signals_child(void);
void set_signals_heredoc(void);

// UTILS

void free_env_node(t_env *node);
char *get_env_value(t_env *env, char *key);
void free_shell(t_shell *shell);
int is_valid_env_key(char *str);
void update_or_create_node(t_env **head, char *key, char *value);
int count_list_elements(t_env *list);
void free_shell(t_shell *shell);
int handling_builtin_error_args(char **args, char *builtin, int option);
void free_full_matrix(char **arr);

// MOCKS --- REMOVER AO FINAL DO PROJETO

void init_mock_env(t_shell *shell);

// Execute =====================================================================
void executor(t_shell *shell);
void execute_external(t_shell *shell, t_cmd *cmd);
// Redirections ----------------------------------------------------------------

int redirect_input(const char *filename);
int redirect_output(const char *filename);
int redirect_append(const char *filename);
int apply_redirect(t_cmd *cmd);

// Builtins --------------------------------------------------------------------

int is_command_builtin(const char *command_name);
int builtin_echo(t_cmd *cmd);
int builtin_unset(t_env **env_list, char **args);
int builtin_export(t_shell *shell, char **args);
// ===================================================================== Execute

// Frontend ====================================================================
void		start_prompt(t_shell *shell);
char		*build_prompt(t_prompt *prompt);
void		signal_handler_prompt(int sig);
void		setup_signals_prompt(void);

// Readline | Display Prompt ---------------------------------------------------
char		*build_user_pmt(char **crr);
char		*build_host_pmt(char **crr);
char		*build_home_pmt(char **crr);
char		*build_dir_pmt(char *home, char **crr);
char		*build_type_pmt(char *user, char **crr);

// Syntax ----------------------------------------------------------------------
t_bool	syntax_analyze(t_dlist *tokens);
t_bool	syntax_check_lside(t_dlist *tokens, t_type type);
t_bool	syntax_check_adjacency(t_dlist *tokens, t_type type);
t_bool	syntax_check_balance(t_dlist *tokens, t_type left, t_type right);
t_bool	syntax_check_redir(t_dlist *tokens);
t_bool	syntax_err_msg(char *msg, char *oper);
t_bool	syntax_err_smsg(char *msg);

// Display Prompt | Instance ---------------------------------------------------
t_prompt	*new_prompt(void);
void	destroy_prompt(void *ptr);

// ==================================================================== Frontend

// Lexer =======================================================================
// Principal Functions ---------------------------------------------------------

t_dlist *lexer(char *in, t_siglexer **siglexer);
// ======================================================================= Lexer

// UTILS =======================================================================
char *find_command_path(t_shell *shell, char *cmd);
void free_env_node(t_env *node);
int is_valid_env_key(char *str);
void update_or_create_node(t_env **head, char *key, char *value);
int count_list_elements(t_env *list);
t_bool lex_isjump(char c);
// ======================================================================= UTILS

// Instances ===================================================================
t_bool	safe_destroy(void *ptr, t_bool (*destroyer)(void *));
t_bool	safe_sdestroy(void *ptr, void (*destroyer)(void *));

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
