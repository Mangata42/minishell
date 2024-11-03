/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:53:15 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/03 17:50:11 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redir_in(t_ast_node *node)
{
	int	fd;

	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_redir_out(t_ast_node *node, int flags)
{
	int	fd;

	fd = open(node->filename, flags, 0644);
	if (fd == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirections(t_ast_node *node)
{
	t_ast_node	*redir;

	redir = node->left;
	while (redir)
	{
		if (redir->type == AST_REDIRECTION_IN)
			handle_redir_in(redir);
		else if (redir->type == AST_REDIRECTION_OUT)
			handle_redir_out(redir, O_WRONLY | O_CREAT | O_TRUNC);
		else if (redir->type == AST_REDIRECTION_APPEND)
			handle_redir_out(redir, O_WRONLY | O_CREAT | O_APPEND);
		else if (redir->type == AST_REDIRECTION_HEREDOC)
			handle_redir_in(redir);
		redir = redir->left;
	}
}
