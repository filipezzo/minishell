/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 09:05:43 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/13 22:24:45 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700
# define _GNU_SOURCE
# define BUFSIZE 1024
# define PATH_MAX 4096

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_signal_status;

typedef enum e_type
{
	WORD,
	COMMAND,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	SUBSHELL,
	LEFT_PAREN,
	RIGHT_PAREN,
	PIPE,
	BACKGROUND,
	SEPARATOR,
	AND,
	OR,
}	t_type;

typedef enum e_mstype
{
	INT_T,
	LONG_T,
	UINT_T,
	ULONG_T,
	FLOAT_T,
	DOUBLE_T,
	CHAR_T,
	STRING_T,
	LEXTOKEN_T,
	LEXSIG_T,
	ASTREE_T,
	DLIST_T,
	BNODE_T,
	TNODE_T,
	REDIRECTION_T,
	COMMAND_T,
}	t_mstype;

typedef enum e_sig
{
	STATE_PROMPT,
	STATE_EXEC,
	STATE_HEREDOC
}	t_sig;

typedef struct s_redir
{
	t_mstype		mstype;
	t_type			type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	t_mstype		mstype;
	char			**args;
	t_redir			*redirections;
	pid_t			pid;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_prompt
{
	char			*user;
	char			*host;
	char			*home;
	char			*dir;
	char			*type;
	char			*display;
}					t_prompt;

typedef struct s_shell
{
	int				exit_status;
	t_env			*env_list;
	t_cmd			*cmd_list;
	int				saved_stdin;
	int				saved_stdout;
	pid_t			last_pid;
}					t_shell;

typedef struct s_astree
{
	t_mstype		mstype;
	struct s_tnode	*root;
	struct s_tnode	*entry;
}					t_astree;

typedef struct s_lextoken
{
	enum e_mstype	mstype;
	enum e_type		type;
	char			*content;
}					t_lextoken;

typedef struct s_lexsig
{
	t_mstype		mstype;
	t_type			type;
	char			*sign;
	size_t			size;
}					t_lexsig;

typedef struct s_tnode
{
	t_mstype		mstype;
	t_type			type;
	void			*data;
	void			*origin;
	struct s_tnode	*branch;
	struct s_tnode	*left;
	struct s_tnode	*right;
	void			(*destroy)(void *data);
	void			(*print)(void *data, int fd);
}					t_tnode;

char		**env_list_to_array(t_env *env_list);
void		init_env(t_shell *shell, char **envp);
int			is_command_builtin(const char *command_name);
int			redirect_input(const char *filename);
int			redirect_output(const char *filename);
int			redirect_append(const char *filename);
int			builtin_cd(t_shell *shell, char **args);
int			builtin_echo(t_cmd *cmd);
int			builtin_env(t_env *list, char **args);
int			builtin_exit(t_shell *shell, char **args);
int			builtin_export(t_shell *shell, char **args);
int			builtin_pwd(void);
int			builtin_unset(t_env **env_list, char **args);
int			run_builtin(t_shell *shell, t_cmd *cmd);
int			is_command_builtin(const char *cmd);
void		init_signals(void);
void		set_signals_exec(void);
void		set_signals_child(void);
void		set_signals_heredoc(void);
void		free_env_node(t_env *node);
char		*get_env_value(t_env *env, char *key);
void		free_shell(t_shell *shell);
int			is_valid_env_key(char *str);
void		update_or_create_node(t_env **head, char *key, char *value);
int			count_list_elements(t_env *list);
void		free_shell(t_shell *shell);
int			handling_builtin_error_args(char **args, char *builtin, int option);
void		free_full_matrix(char **arr);
void		executor(t_shell *shell);
void		execute_external(t_shell *shell, t_cmd *cmd);
void		run_ast(t_shell *shell, t_tnode *node);
int			redirect_input(const char *filename);
int			redirect_output(const char *filename);
int			redirect_append(const char *filename);
int			apply_redirect(t_cmd *cmd);
int			is_command_builtin(const char *command_name);
int			builtin_echo(t_cmd *cmd);
int			builtin_unset(t_env **env_list, char **args);
int			builtin_export(t_shell *shell, char **args);
char		*find_command_path(t_shell *shell, char *cmd);
void		free_env_node(t_env *node);
int			is_valid_env_key(char *str);
void		update_or_create_node(t_env **head, char *key, char *value);
int			count_list_elements(t_env *list);
t_bool		lex_isjump(char c);
void		init_mock_env(t_shell *shell);
char		*build_prompt(t_prompt *prompt);
char		*build_user_pmt(char **crr);
char		*build_host_pmt(char **crr);
char		*build_home_pmt(char **crr);
char		*build_dir_pmt(char *home, char **crr);
char		*build_type_pmt(char *user, char **crr);
t_dlist		*lexer(char *in, t_lexsig **siglexer);
t_lexsig	**init_lexer_config(void);
void		free_lexer_config(t_lexsig **sigs);
t_bool		syntax_analyze(t_dlist *tokens);
t_bool		syntax_check_lside(t_dlist *tokens, t_type type);
t_bool		syntax_check_adjacency(t_dlist *tokens, t_type type);
t_bool		syntax_check_balance(t_dlist *tokens, t_type left, t_type right);
t_bool		syntax_check_redir(t_dlist *tokens);
t_bool		syntax_err_msg(char *msg, char *oper);
t_bool		syntax_err_smsg(char *msg);
t_astree	*parser(t_dlist *tokens);
t_tnode		*parse_and_or(t_astree *tree, t_bnode **cursor);
t_tnode		*parse_pipeline(t_astree *tree, t_bnode **cursor);
t_tnode		*parse_command(t_astree *tree, t_bnode **cursor);
t_tnode		*parse_redir(t_tnode *node, t_bnode **cursor);
t_tnode		*parse_subshell(t_astree *tree, t_bnode **cursor);
void		print_string(void *ptr, int fd);
void		destroy_string_lst(char **list);
t_astree	*new_astree(void);
void		destroy_astree(void *ptr);
void		print_astree(void *ptr, int fd);
t_tnode		*get_entry_astree(t_astree *tree);
t_tnode		*new_tnode(void *origin, void *data);
void		destroy_tnode(void *ptr);
t_bool		new_lextoken(t_lextoken **new, t_type type, char *content);
void		destroy_lextoken(void *ptr);
t_lextoken	*get_lextoken(void *ptr);
t_lextoken	*bnode_to_lextoken(t_bnode *node);
void		next_lextoken(t_bnode **cursor);
t_redir		*new_redir(t_type type);
void		destroy_redir(void *ptr);
void		destroy_lst_redir(void *ptr);

// Command ---------------------------------------------------------------------
t_cmd		*new_cmd(void);
void		destroy_cmd(void *ptr);
t_cmd		*get_cmd(void *ptr);
t_cmd		*set_arg_cmd(t_cmd *cmd, char *src);
void		print_cmd(void *ptr, int fd);

// Prompt ----------------------------------------------------------------------
t_prompt	*new_prompt(void);
void		destroy_prompt(void *ptr);
// =================================================================== Structure

#endif
