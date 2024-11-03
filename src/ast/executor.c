/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:12:34 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/03 16:56:25 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_ast(t_ast_node *node, t_sh *shell)
{
	if (!node)
		return (0);
	if (node->type == AST_COMMAND)
		return (execute_command_node(node, shell));
	else if (node->type == AST_PIPE)
		return (execute_pipe_node(node, shell));
	else if (node->type == AST_AND)
		return (execute_and_node(node, shell));
	else if (node->type == AST_OR)
		return (execute_or_node(node, shell));
	return (0);
}

int	execute_command_node(t_ast_node *node, t_sh *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		handle_redirections(node);
		if (execvp(node->argv[0], node->argv) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		update_exit_status(shell, status);
		return (shell->exit_status);
	}
	perror("minishell");
	return (-1);
}

int	execute_pipe_node(t_ast_node *node, t_sh *shell)
{
	int		pipefd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("minishell"), -1);
	pid_left = fork();
	if (pid_left == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(node->left, shell);
		exit(shell->exit_status);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(node->right, shell);
		exit(shell->exit_status);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	update_exit_status(shell, status);
	return (shell->exit_status);
}

int	execute_and_node(t_ast_node *node, t_sh *shell)
{
	int	status;

	status = execute_ast(node->left, shell);
	if (status == 0)
		return (execute_ast(node->right, shell));
	return (status);
}

int	execute_or_node(t_ast_node *node, t_sh *shell)
{
	int	status;

	status = execute_ast(node->left, shell);
	if (status != 0)
		return (execute_ast(node->right, shell));
	return (status);
}
