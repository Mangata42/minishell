/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:53:15 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/19 17:20:56 by nghaddar         ###   ########.fr       */
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
		free_ast(node);
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
		free_ast(node);
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
			handle_redir_heredoc(redir);
		redir = redir->left;
	}
}
// void	handle_redir_heredoc(t_ast_node *node)
// {
// 	char	*line;
// 	int		fd;
// 	char	*delimiter;

// 	// Créer un fichier temporaire pour le heredoc
// 	fd = open("/tmp/heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("minishell: heredoc");
// 		exit(EXIT_FAILURE);
// 	}
// 	delimiter = node->filename;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	close(fd);
// 	// Réouvrir le fichier pour la lecture
// 	fd = open("/tmp/heredoc_tmp", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("minishell: heredoc");
// 		exit(EXIT_FAILURE);
// 	}
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// 	unlink("/tmp/heredoc_tmp"); // Supprimer le fichier temporaire
// }