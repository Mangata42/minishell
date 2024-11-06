/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:14:04 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/06 22:17:39 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(char **args)
{
	int		i;
	int		n_flag;
	char	*str;

	n_flag = 0;
	i = 1;
	while (args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		str = args[i] + 1;
		while (*str == 'n')
			str++;
		if (*str == '\0')
			n_flag = 1;
		else
			break ;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
