/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:12:14 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/09 21:34:41 by fflamion         ###   ########.fr       */
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
// 			perror("minishell");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	return (pid);
// }
// executor_utils3.c

pid_t create_child_process(t_ast_node *node)
{
    pid_t pid;
    struct sigaction sa_default;

    pid = fork();
    if (pid == 0)
    {
        set_signals_for_child(&sa_default);
        handle_redirections(node);
        if (execvp(node->argv[0], node->argv) == -1)
        {
            if (errno == ENOENT)
            {
                ft_putstr_fd("minishell: command not found: ", 2);
                ft_putstr_fd(node->argv[0], 2);
                ft_putstr_fd("\n", 2);
                exit(127);
            }
            else
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(node->argv[0], 2);
                ft_putstr_fd(": ", 2);
                ft_putstr_fd(strerror(errno), 2);
                ft_putstr_fd("\n", 2);
                exit(126);
            }
        }
    }
    return (pid);
}
