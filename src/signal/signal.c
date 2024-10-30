/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:34:38 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/30 17:56:50 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct s_colors
{
	const char	*colors[16];
	int			color_count;
	int			index;
}	t_colors;

void	init_colors(t_colors *color_set)
{
	color_set->colors[0] = "\033[0;31m";
	color_set->colors[1] = "\033[0;32m";
	color_set->colors[2] = "\033[0;33m";
	color_set->colors[3] = "\033[0;34m";
	color_set->colors[4] = "\033[0;35m";
	color_set->colors[5] = "\033[0;36m";
	color_set->colors[6] = "\033[1;31m";
	color_set->colors[7] = "\033[1;32m";
	color_set->colors[8] = "\033[1;33m";
	color_set->colors[9] = "\033[1;34m";
	color_set->colors[10] = "\033[1;35m";
	color_set->colors[11] = "\033[1;36m";
	color_set->colors[12] = "\033[0;90m";
	color_set->colors[13] = "\033[0;91m";
	color_set->colors[14] = "\033[0;92m";
	color_set->colors[15] = "\033[0;93m";
	color_set->color_count = 16;
	color_set->index = 0;
}

void	handle_sigint(int signum)
{
	static t_colors	color_set;
	const char		*reset_color;

	reset_color = "\033[0m";
	if (color_set.color_count == 0)
		init_colors(&color_set);
	(void)signum;
	write(1, "\n", 1);
	write(1, color_set.colors[color_set.index], 7);
	write(1, "minishell> ", 11);
	write(1, "\033[0m", 7);
	color_set.index = (color_set.index + 1) % color_set.color_count;
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}