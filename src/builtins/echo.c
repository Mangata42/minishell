/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:14:04 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/12 15:21:00 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_n_flag(char **args, int *i)
{
	char	*str;
	int		n_flag;

	n_flag = 0;
	while (args[*i] && !ft_strncmp(args[*i], "-n", 2))
	{
		str = args[*i] + 1;
		while (*str == 'n')
			str++;
		if (*str == '\0')
			n_flag = 1;
		else
			break ;
		(*i)++;
	}
	return (n_flag);
}

int	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	if (!args[i])
		return (ft_putchar_fd('\n', STDOUT_FILENO), 0);
	n_flag = check_n_flag(args, &i);
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
// int	ft_echo(char **args)
// {
// 	int		i;
// 	int		n_flag;
// 	char	*str;

// 	n_flag = 0;
// 	i = 1;
// 	while (args[i] && !ft_strncmp(args[i], "-n", 2))
// 	{
// 		str = args[i] + 1;
// 		while (*str == 'n')
// 			str++;
// 		if (*str == '\0')
// 			n_flag = 1;
// 		else
// 			break ;
// 		i++;
// 	}
// 	while (args[i])
// 	{
// 		write(1, args[i], ft_strlen(args[i]) + 1);
// 		if (args[i + 1])
// 			write(1, (const void *)' ', 2);
// 		i++;
// 	}
// 	if (!n_flag)
// 		write(1, (const void *)'\n', 2);
// 	return (0);
// }

// int	is_n_option(const char *str)
// {
// 	int	i;

// 	i = 2;
// 	if (str[0] != '-' || str[1] != 'n')
// 		return (0);
// 	while (str[i] == 'n')
// 		i++;
// 	return (str[i] == '\0');
// }

// char	**check_option(char **args, int *n_flag)
// {
// 	*n_flag = 0;
// 	while (*args && is_n_option(*args))
// 	{
// 		*n_flag = 1;
// 		args++;
// 	}
// 	return (args);
// }

// int	ft_echo(char **args)
// {
// 	int		n_flag;
// 	size_t	total_len;
// 	size_t	pos;
// 	size_t	len;
// 	char	**start;
// 	char	*buffer;
// 	char	**tmp;

// 	total_len = 0;
// 	pos = 0;
// 	if (!args || !*args)
// 		return (write(1, "\n", 1) != 1);
// 	args++;
// 	start = check_option(args, &n_flag);
// 	tmp = start;
// 	while (*tmp)
// 	{
// 		total_len += ft_strlen(*tmp);
// 		tmp++;
// 	}
// 	if (!n_flag)
// 		total_len++;
// 	buffer = malloc(total_len + 1);
// 	if (!buffer)
// 		return (1);
// 	while (*start)
// 	{
// 		len = ft_strlen(*start);
// 		ft_memcpy(buffer + pos, *start, len);
// 		pos += len;
// 		start++;
// 	}
// 	if (!n_flag)
// 		buffer[pos++] = '\n';
// 	buffer[pos] = '\0';
// 	write(1, buffer, pos);
// 	free(buffer);
// 	return (0);
// }
