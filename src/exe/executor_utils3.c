/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:12:14 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/12 04:00:56 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	w_c(pid_t pid, t_sh *shell, struct sigaction *orig_int,
		struct sigaction *orig_quit)
{
	int					status;
	struct sigaction	sa_ignore;

	set_signals_for_parent(&sa_ignore);
	waitpid(pid, &status, 0);
	update_exit_status(shell, status);
	res_sig(orig_int, orig_quit);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	return (shell->exit_status);
}

void	handle_exec_error(t_ast_node *node, t_sh *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->argv[0], 2);
	free_ast(node);
	free_shell(shell);
	if (errno == ENOENT)
	{
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(126);
}

char	*find_executable_path(char *command, t_sh *shell)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	path_env = get_env_value(shell, "PATH");
	paths = ft_split(path_env, ':');
	full_path = NULL;
	if (!paths)
		return (NULL);
	while (paths[i] != NULL)
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

void	execute_child(t_ast_node *node, struct sigaction *sa_default,
		t_sh *shell)
{
	char	*path;

	set_signals_for_child(sa_default);
	handle_redirections(node);
	path = find_executable_path(node->argv[0], shell);
	if (!path)
	{
		handle_exec_error(node, shell);
		free_shell(shell);
		free_ast(node);
		exit(127);
	}
	if (execve(path, node->argv, shell->envp) == -1)
	{
		free(path);
		handle_exec_error(node, shell);
	}
	free(path);
	free_shell(shell);
	free_ast(node);
	exit(0);
}

pid_t	create_child_process(t_ast_node *node, t_sh *shell)
{
	pid_t				pid;
	struct sigaction	sa_default;

	pid = fork();
	if (pid == 0)
		execute_child(node, &sa_default, shell);
	return (pid);
}

// void	execute_child(t_ast_node *node, struct sigaction *sa_default,
// 		t_sh *shell)
// {
// 	set_signals_for_child(sa_default);
// 	handle_redirections(node);
// 	if (execvp(node->argv[0], node->argv) == -1)
// 		handle_exec_error(node, shell);
// }

// pid_t	create_child_process(t_ast_node *node)
// {
// 	pid_t				pid;
// 	struct sigaction	sa_default;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		set_signals_for_child(&sa_default);
// 		handle_redirections(node);
// 		if (execvp(node->argv[0], node->argv) == -1)
// 		{
// 			if (errno == ENOENT)
// 			{
// 				ft_putstr_fd("minishell: ", 2);
// 				ft_putstr_fd(node->argv[0], 2);
// 				ft_putstr_fd(": command not found", 2);
// 				ft_putstr_fd("\n", 2);
// 				exit(127);
// 			}
// 			else
// 			{
// 				ft_putstr_fd("minishell: ", 2);
// 				ft_putstr_fd(node->argv[0], 2);
// 				ft_putstr_fd(": ", 2);
// 				ft_putstr_fd(strerror(errno), 2);
// 				ft_putstr_fd("\n", 2);
// 				exit(126);
// 			}
// 		}
// 	}
// 	return (pid);
// }
