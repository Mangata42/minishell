/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:14:04 by nghaddar          #+#    #+#             */
/*   Updated: 2024/10/24 14:27:06 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		builtin_echo(char *s, char optN)
{
	ft_putstr(s);
	if (!optN)
		ft_putchar('\n');
	return (0);
}