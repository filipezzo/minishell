/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhidani <mhidani@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 13:37:28 by mhidani           #+#    #+#             */
/*   Updated: 2026/01/04 19:00:12 by mhidani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef void	(*data_shredder)(void *ptr);
typedef size_t	(*data_print)(void *ptr, size_t col, size_t row);

typedef struct s_astree
{
	struct s_branch	*entry;
	struct s_branch	*root;
}					t_astree;

typedef struct s_branch
{
	void			*data;
	t_type			type;
	struct s_astree	*mother;
	struct s_branch	*origin;
	struct s_branch	*left;
	struct s_branch	*right;
	void			(*shredder)(void *ptr);
	size_t			(*print)(void *ptr, size_t col, size_t row);
}					t_branch;

t_astree	*astree_new(void);
t_bool		astree_destroy(t_astree *ptr, t_branch **cursor);
void		astree_print(t_branch **cursor, size_t level);
t_branch	*branch_new(void *data);
t_branch	*branch_setfuncs(t_branch *lev, data_shredder shr, data_print prt);
t_lexunit	*get_token(void *ptr);
t_cmd		*get_command(void *ptr);
t_cmd		*cmd_new(void);
t_cmd		*cmd_addarg(t_cmd *cmd, char *src);
t_bnode		*tokens_next(t_bnode **cursor);
t_bool		is_redirection(t_type type);
t_redir		*redir_new(t_type type);
t_branch	*parse_subshell(t_bnode **cursor);
t_branch	*parse_scommand(t_bnode **cursor);
t_branch	*parse_command(t_bnode **cursor);
t_branch	*parse_pipeline(t_bnode **cursor);
t_branch	*parse_expression(t_bnode **cursor);
t_branch	*parse_redirection(t_bnode **cursor, t_branch *node);
t_astree	*parser(t_dlist *tokens);
void		cmd_destroyer(void *ptr);

// ASTree ----------------------------------------------------------------------
t_astree	*astree_new(void)
{
	t_astree	*tree;

	tree = malloc(sizeof(t_astree));
	if (!tree)
		return (NULL);
	tree->entry = NULL;
	tree->root = NULL;
	return (tree);
}

t_branch	*branch_new(void *data)
{
	t_branch	*branch;

	if (!data)
		return (NULL);
	branch = malloc(sizeof(t_branch));
	if (!branch)
		return (NULL);
	branch->data = data;
	branch->type = WORD;
	branch->left = NULL;
	branch->right = NULL;
	branch->mother = NULL;
	branch->shredder = free;
	branch->print = NULL;
	return (branch);
}

t_branch	*branch_setfuncs(t_branch *lev, data_shredder shr, data_print prt)
{
	if (!lev || !shr)
		return (NULL);
	lev->shredder = shr;
	lev->print = prt;
	return (lev);
}

t_bool	astree_destroy(t_astree *tree, t_branch **cursor)
{

	if (!tree || !*cursor)
		return (FALSE);
	astree_destroy(tree, &(*cursor)->left);
	astree_destroy(tree, &(*cursor)->right);
	(*cursor)->shredder((*cursor)->data);
	free(*cursor);
	free(tree);
	return (TRUE);
}

t_lexunit	*get_token(void *ptr)
{
	t_bnode		*node;
	t_lexunit	*unit;

	if (!ptr)
		return (NULL);
	node = (t_bnode *)ptr;
	if (!node->data)
		return (NULL);
	unit = (t_lexunit *)node->data;
	return (unit);
}

t_cmd	*get_command(void *ptr)
{
	t_branch	*node;
	t_cmd		*command;

	if (!ptr)
		return (NULL);
	node = (t_branch *)ptr;
	if (!node->data)
		return (NULL);
	command = (t_cmd *)node->data;
	return (command);
}

void	shredder_lstchar(void *ptr)
{
	char	**lstchar;
	size_t	i;

	if (!ptr)
		return ;
	i = 0;
	lstchar = (char **)ptr;
	while (lstchar[i])
	{
		free(lstchar[i]);
		i++;
	}
	free(lstchar);
}

t_cmd	*cmd_new(void)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->args = NULL;
	command->redirections = NULL;
	command->pid = -1;
	command->next = NULL;
	return (command);
}

t_bnode	*tokens_next(t_bnode **cursor)
{
	if (!(*cursor)->right)
	{
		*cursor = NULL;
		return (*cursor);
	}
	*cursor = (*cursor)->right;
	return (*cursor);
}

t_redir	*redir_new(t_type type)
{
	t_redir	*redirection;

	redirection = malloc(sizeof(t_redir));
	if (!redirection)
		return (NULL);
	redirection->type = type;
	redirection->file = NULL;
	redirection->next = NULL;
	return (redirection);
}

t_cmd	*cmd_addarg(t_cmd *cmd, char *src)
{
	char	**new_args;
	size_t	i;
	size_t	size;

	if (!cmd || !src)
		return (NULL);
	size = 0;
	while (cmd->args && cmd->args[size])
		size++;
	if (size == 0)
		new_args = ft_calloc(2, sizeof(char *));
	else
		new_args = ft_calloc(size + 2, sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (cmd->args && i < size)
	{
		new_args[i] = ft_strdup(cmd->args[i]);
		i++;
	}
	new_args[size] = ft_strdup(src);
	shredder_lstchar(cmd->args);
	cmd->args = new_args;
	return (cmd);
}

t_branch	*parse_subshell(t_bnode **cursor)
{
	t_branch	*node;
	t_branch	*branch;

	tokens_next(cursor);
	branch = parse_expression(cursor);
	if (!branch)
		return (NULL);
	node = branch_new(ft_strdup("subshell"));
	node->type = SUBSHELL;
	node->left = branch;
	node->left->origin = node;
	tokens_next(cursor);
	return (node);
}

t_bool	is_redirection(t_type type)
{
	return (
		type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_APPEND
		|| type == REDIR_HEREDOC
	);
}

t_branch	*parse_redirection(t_bnode **cursor, t_branch *node)
{
	t_lexunit	*token;
	t_cmd		*command;
	t_redir		*redir;
	t_redir		*redir_cursor;

	token = get_token(*cursor);
	command = get_command(node);
	redir = redir_new(token->type);
	redir->file = ft_strdup(get_token((*cursor)->right)->content);
	tokens_next(cursor);
	if (!command->redirections)
		command->redirections = redir;
	else
	{
		redir_cursor = command->redirections->next;
		while (redir_cursor)
			redir_cursor = command->redirections->next;
		redir_cursor = redir;
	}
	tokens_next(cursor);
	return (node);
}

t_branch	*parse_scommand(t_bnode **cursor)
{
	t_branch	*node;
	t_cmd		*command;
	t_lexunit	*token;

	token = get_token(*cursor);
	node = branch_new(cmd_new());
	if (!node)
		return (NULL);
	node->type = COMMAND;
	node->shredder = cmd_destroyer;
	command = (t_cmd *)node->data;
	while (token)
	{
		if (token->type == WORD)
			cmd_addarg(command, token->content);
		else if (is_redirection(token->type))
		{
			if (!parse_redirection(cursor, node))
				return (NULL);
			token = get_token(*cursor);
			continue ;
		}
		else
			break ;
		tokens_next(cursor);
		token = get_token(*cursor);
	}
	return (node);
}

t_branch	*parse_command(t_bnode **cursor)
{
	t_lexunit	*token;

	token = get_token(*cursor);
	if (!token)
		return (NULL);
	if (token->type == LEFT_PAREN)
		return (parse_subshell(cursor));
	return (parse_scommand(cursor));
}

t_branch	*parse_pipeline(t_bnode **cursor)
{
	t_branch	*branch;
	t_branch	*node;
	t_lexunit	*token;

	branch = parse_command(cursor);
	if (!branch)
		return (NULL);
	token = get_token(*cursor);
	while (token && token->type == PIPE)
	{
		node = branch_new(ft_strdup(token->content));
		node->type = token->type;
		node->left = branch;
		node->left->origin = node;
		tokens_next(cursor);
		node->right = parse_command(cursor);
		node->right->origin = node;
		if (!node->right)
			return (NULL);
		branch = node;
		token = get_token(*cursor);
	}
	return (branch);
}

t_branch	*parse_expression(t_bnode **cursor)
{
	t_branch	*branch;
	t_branch	*node;
	t_lexunit	*token;

	branch = parse_pipeline(cursor);
	if (!branch)
		return (NULL);
	token = get_token(*cursor);
	while (token && (token->type == OR || token->type == AND))
	{
		node = branch_new(ft_strdup(token->content));
		node->type = token->type;
		tokens_next(cursor);
		node->left = branch;
		node->left->origin = node;
		node->right = parse_pipeline(cursor);
		if (!node->right)
			return (NULL);
		node->right->origin = node;
		branch = node;
		token = get_token(*cursor);
	}
	return (branch);
}

t_astree	*parser(t_dlist *tokens) // TODO: doesn't make all tree
{
	t_astree	*tree;

	tree = astree_new();
	tree->root = parse_expression(&tokens->head);
	return (tree);
}

void	astree_print(t_branch **cursor, size_t level)
{
	size_t	i;

	if (!*cursor)
		return ;
	i = 0;
	while (++i < level)
		printf("│\t");
	if ((*cursor)->origin && (*cursor)->origin->left == *cursor)
	{
		if ((*cursor)->type == COMMAND)
			printf("├ [left] %s\n", ((t_cmd *)(*cursor)->data)->args[0]);
		else
			printf("├ [left] %s\n", (char *)(*cursor)->data);
	}
	else if ((*cursor)->origin && (*cursor)->origin->left == NULL)
		printf("├ [left] NULL\n");
	else if ((*cursor)->origin && (*cursor)->origin->right == *cursor)
	{
		if ((*cursor)->type == COMMAND)
			printf("└ [right] %s\n", ((t_cmd *)(*cursor)->data)->args[0]);
		else
			printf("└ [right] %s\n", (char *)(*cursor)->data);
	}
	else if ((*cursor)->origin && (*cursor)->origin->right == NULL)
		printf("└ [right] NULL\n");
	else
		printf("[root] %s\n", (char *)(*cursor)->data);
	astree_print(&(*cursor)->left, level + 1);
	astree_print(&(*cursor)->right, level + 1);
}

t_astree	*astree_test(void)
{
	t_astree	*tree = malloc(sizeof(t_astree));

	tree->root = branch_new(ft_strdup("||"));
	tree->root->left = branch_new(ft_strdup("&&"));
	tree->root->left->origin = tree->root;
	tree->root->left->left = branch_new(ft_strdup("subshell"));
	tree->root->left->left->origin = tree->root->left;
	tree->root->left->left->left = branch_new(ft_strdup("echo start > a.txt"));
	tree->root->left->left->left->origin = tree->root->left->left;
	tree->root->left->left->right = branch_new(ft_strdup("cat < b.txt"));
	tree->root->left->left->right->origin = tree->root->left->left;
	tree->root->left->right = branch_new(ft_strdup("ls -l >> out.txt"));
	tree->root->left->right->origin = tree->root->left;
	tree->root->right = branch_new(ft_strdup("echo fail"));
	tree->root->right->origin = tree->root;
	return (tree);
}

int	main(void)
{
	char		*input = "( echo start > a.txt | cat < b.txt ) && ls -l >> out.txt || echo fail";
	t_siglexer	**sigs = new_lst_siglexer();
	t_dlist		*tokens = lexer(input, sigs);
	t_astree	*tree = parser(tokens);
	// t_astree	*tree = astree_test();

	printf("%s\n", input);
	astree_print(&tree->root, 0);

	destroy_lst_siglexer(sigs);
	ft_destroy_dlist(tokens);
	astree_destroy(tree, &tree->root);
	return (EXIT_SUCCESS);
}

/**
 *                OR (||)
 *               /       \
 *          AND (&&)     CMD
 *           /      \     echo fail
 *      SUBSHELL    CMD
 *         |        ls -l >> out.txt
 *        PIPE
 *       /    \
 *    CMD      CMD
 * echo start  cat
 *   > a.txt   < b.txt
 */
