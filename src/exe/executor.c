/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:12:34 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/07 21:03:06 by fflamion         ###   ########.fr       */
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

static int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}

static int	execute_builtin(t_ast_node *node, t_sh *shell)
{
	char	*cmd;

	cmd = node->argv[0];
	if (!ft_strcmp(cmd, "echo"))
		return (ft_echo(node->argv));
	if (!ft_strcmp(cmd, "cd"))
		return (ft_cd(node->argv, shell));
	if (!ft_strcmp(cmd, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd, "export"))
		return (ft_export(node->argv, shell));
	if (!ft_strcmp(cmd, "unset"))
		return (ft_unset(node->argv, shell));
	if (!ft_strcmp(cmd, "env"))
		return (ft_env(shell));
	if (!ft_strcmp(cmd, "exit"))
		return (ft_exit(node->argv));
	return (1);
}

int	execute_command_node(t_ast_node *node, t_sh *shell)
{
	pid_t				pid;
	struct sigaction	orig_int;
	struct sigaction	orig_quit;
	int					status;
	if (node->argv[0] && ft_isdigit(node->argv[0][0]))
	{
		shell->exit_status = 127;
		return (127);
	}
	if (is_builtin(node->argv[0]))
	{
		status = execute_builtin(node, shell);
		shell->exit_status = status;
		return (status);
	}
	save_og_s(&orig_int, &orig_quit);
	pid = create_child_process(node);
	if (pid < 0)
	{
		perror("minishell");
		return (-1);
	}
	if (pid > 0)
		return (w_c(pid, shell, &orig_int, &orig_quit));
	return (0);
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
	shell->exit_status = status;
	if (status == 0)
		return (execute_ast(node->right, shell));
	return (status);
}

int	execute_or_node(t_ast_node *node, t_sh *shell)
{
	int	status;

	status = execute_ast(node->left, shell);
	shell->exit_status = status;
	if (status != 0)
		return (execute_ast(node->right, shell));
	return (status);
}
