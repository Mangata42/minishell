/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:32:08 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/19 19:35:39 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int						is_builtin(char *cmd);

char	**cp_argv(t_ast_node *node)
{
	int		i;
	char	**argv;
	int		j;

	i = 0;
	while (node->argv[i])
		i++;
	argv = malloc(sizeof(char *) * (i + 1));
	if (!argv)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		if (node->argv[j])
			argv[j] = ft_strdup(node->argv[j]);
		else
			argv[j] = NULL;
		j++;
	}
	return (argv);
}

int	execute_builtin(t_ast_node *node, t_sh *shell)
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
		return (ft_exit(node->argv, shell, node));
	return (1);
}

int	execute_builtin_command(t_ast_node *node, t_sh *shell)
{
	int	original_stdin;
	int	original_stdout;
	int	status;

	original_stdin = 0;
	original_stdout = 0;
	handle_redirections(node);
	status = execute_builtin(node, shell);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	shell->exit_status = status;
	return (status);
}

typedef struct s_exec_data
{
	struct sigaction	orig_int;
	struct sigaction	orig_quit;
	pid_t				pid;
	int					status;
}						t_exec_data;

int	handle_external_command(t_ast_node *node, t_sh *shell)
{
	t_exec_data	data;

	save_og_s(&data.orig_int, &data.orig_quit);
	data.pid = create_child_process(node, shell);
	if (data.pid < 0)
	{
		perror("minishell");
		return (-1);
	}
	if (data.pid > 0)
		return (w_c(data.pid, shell, &data.orig_int, &data.orig_quit));
	return (0);
}

int	execute_command_node(t_ast_node *node, t_sh *shell)
{
	if (node->argv == NULL)
	{
		free_ast(node->root);
		free_shell(shell);
		return (-1);
	}
	if (is_builtin(node->argv[0]))
		return (execute_builtin_command(node, shell));
	return (handle_external_command(node, shell));
}

// int	execute_command_node(t_ast_node *node, t_sh *shell)
// {
// 	int					original_stdin;
// 	int					original_stdout;
// 	int					status;
// 	pid_t				pid;
// 	struct sigaction	orig_int;
// 	struct sigaction	orig_quit;

// 	if (is_builtin(node->argv[0]))
// 		return (execute_builtin_command(node, shell));
// 	else
// 	{
// 		save_og_s(&orig_int, &orig_quit);
// 		pid = create_child_process(node, shell);
// 		if (pid < 0)
// 		{
// 			perror("minishell");
// 			return (-1);
// 		}
// 		if (pid > 0)
// 			return (w_c(pid, shell, &orig_int, &orig_quit));
// 		return (0);
// 	}
// }
