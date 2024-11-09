/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:14:04 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/09 18:52:05 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int is_n_option(const char *str) 
{
	int i = 2;

	if (str[0] != '-' || str[1] != 'n')
		return 0;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

char **check_option(char **args, int *n_flag) 
{
	*n_flag = 0;
	
	while (*args && is_n_option(*args)) {
		*n_flag = 1;
		args++;
	}
	
	return (args);
}

int ft_echo(char **args) 
{
	int		n_flag;
	size_t	total_len = 0;
	size_t	pos = 0;
	size_t	len;
	size_t	written;
	char	**start;
	char	*buffer;
	char	**tmp;
	
	if (!args || !*args)
		return (write(1, "\n", 1) != 1);	
	args++;
	start = check_option(args, &n_flag);
	tmp = start;
	while (*tmp) 
	{
		total_len += ft_strlen(*tmp);
		if (*(tmp + 1))
			total_len++;
		tmp++;
	}
	
	if (!n_flag)
		total_len++;
		
	buffer = malloc(total_len + 1);
	if (!buffer)
		return (1);
	while (*start) 
	{
		len = ft_strlen(*start);
		ft_memcpy(buffer + pos, *start, len);
		pos += len;
		if (*(start + 1)) 
			buffer[pos++] = ' ';
		start++;
	}
	
	if (!n_flag)
		buffer[pos++] = '\n';
	buffer[pos] = '\0';
	
	written = write(1, buffer, pos);
	free(buffer);
	return (written);
}