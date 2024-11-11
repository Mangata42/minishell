/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:32:08 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/11 02:33:30 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	execute_builtin_command(t_ast_node *node, t_sh *shell)
{
	int	original_stdin;
	int	original_stdout;
	int	status;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	handle_redirections(node);
	status = execute_builtin(node, shell);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	shell->exit_status = status;
	return (status);
}

int	execute_command_node(t_ast_node *node, t_sh *shell)
{
	int					original_stdin;
	int					original_stdout;
	int					status;
	pid_t				pid;
	struct sigaction	orig_int;
	struct sigaction	orig_quit;

	if (is_builtin(node->argv[0]))
		return (execute_builtin_command(node, shell));
	else
	{
		save_og_s(&orig_int, &orig_quit);
		pid = create_child_process(node, shell);
		if (pid < 0)
		{
			perror("minishell");
			return (-1);
		}
		if (pid > 0)
			return (w_c(pid, shell, &orig_int, &orig_quit));
		return (0);
	}
}