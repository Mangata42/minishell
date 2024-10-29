/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:54:03 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/29 16:49:23 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc(t_token *heredoc_token, char *delimiter)
{
	int		fd;
	char	*line;

	fd = open("heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	free(heredoc_token->value);
	heredoc_token->value = ft_strdup("heredoc.txt");
}

