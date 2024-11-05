/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:09:09 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/05 08:25:04 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_s_h(struct sigaction *sa, int signum, void (*handler)(int))
{
	sa->sa_handler = handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sigaction(signum, sa, NULL);
}

void	save_og_s(struct sigaction *orig_int, struct sigaction *orig_quit)
{
	sigaction(SIGINT, NULL, orig_int);
	sigaction(SIGQUIT, NULL, orig_quit);
}

void	res_sig(struct sigaction *orig_int, struct sigaction *orig_quit)
{
	sigaction(SIGINT, orig_int, NULL);
	sigaction(SIGQUIT, orig_quit, NULL);
}

void	set_signals_for_parent(struct sigaction *sa_ignore)
{
	set_s_h(sa_ignore, SIGINT, SIG_IGN);
	set_s_h(sa_ignore, SIGQUIT, SIG_IGN);
}

void	set_signals_for_child(struct sigaction *sa_default)
{
	set_s_h(sa_default, SIGINT, SIG_DFL);
	set_s_h(sa_default, SIGQUIT, SIG_DFL);
}