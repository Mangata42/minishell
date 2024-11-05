/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 06:29:51 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/05 06:54:01 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void init_colors(t_colors *color_set)
{
	color_set->colors[0] = "\033[0;31m";
	color_set->colors[1] = "\033[1;31m";
	color_set->colors[2] = "\033[0;32m";
	color_set->colors[3] = "\033[1;32m";
	color_set->colors[4] = "\033[0;33m";
	color_set->colors[5] = "\033[1;33m";
	color_set->colors[6] = "\033[0;34m";
	color_set->colors[7] = "\033[1;34m";
	color_set->colors[8] = "\033[0;35m";
	color_set->colors[9] = "\033[1;35m";
	color_set->colors[10] = "\033[0;36m";
	color_set->colors[11] = "\033[1;36m";
	color_set->colors[12] = "\033[0;37m";
	color_set->colors[13] = "\033[1;37m";
	color_set->colors[14] = "\033[0;90m";
	color_set->colors[15] = "\033[1;90m";
	color_set->reset_color = "\033[0m";
	color_set->color_count = 16;
	color_set->index = 0;
}