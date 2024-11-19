/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:29:37 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/12 03:41:52 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("minishell");
		return (-1);
	}
	return (0);
}

void	execute_left_child(t_ast_node *node, t_sh *shell, int pipefd[2])
{
	pid_t	pid_left;

	pid_left = fork();
	if (pid_left == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(node->left, shell);
		free_ast(node->root);
		free_shell(shell);
		exit(shell->exit_status);
	}
}

void	execute_right_child(t_ast_node *node, t_sh *shell, int pipefd[2])
{
	pid_t	pid_right;

	pid_right = fork();
	if (pid_right == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(node->right, shell);
		free_ast(node->root);
		free_shell(shell);
		exit(shell->exit_status);
	}
}

int	execute_pipe_node(t_ast_node *node, t_sh *shell)
{
	int	pipefd[2];
	int	status;

	if (setup_pipe(pipefd) == -1)
		return (-1);
	execute_left_child(node, shell, pipefd);
	execute_right_child(node, shell, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	update_exit_status(shell, status);
	return (shell->exit_status);
}
