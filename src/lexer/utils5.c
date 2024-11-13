/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:40:08 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/13 14:33:47 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_path(char *path, char *command)
{
	char	*full_path;
	int		exists;

	full_path = ft_strjoin(path, "/");
	if (!full_path)
		return (false);
	full_path = ft_strjoin_free(full_path, command);
	if (!full_path)
		return (false);
	exists = (access(full_path, X_OK) == 0);
	free(full_path);
	return (exists);
}

bool	command_exists(char *command, t_sh *shell)
{
	char	*path;
	char	**paths;
	int		i;
	bool	found;

	path = get_env_value(shell, "PATH");
	if (!path)
		return (false);
	paths = ft_split(path, ':');
	if (!paths)
		return (false);
	i = 0;
	found = false;
	while (paths[i] && !found)
	{
		found = check_path(paths[i], command);
		i++;
	}
	ft_free_split(paths);
	return (found);
}

void	h_par(char c, uint16_t *i, t_t_list *t_list)
{
	if (c == '(')
		add_token(t_list, create_token("(", TOKEN_LPAREN));
	else if (c == ')')
		add_token(t_list, create_token(")", TOKEN_RPAREN));
	(*i)++;
}

int	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
	{
		return (match_pattern(pattern + 1, str) || (*str
				&& match_pattern(pattern, str + 1)));
	}
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}

void	expand_wildcard(const char *pattern, t_t_list *t_list)
{
	struct dirent	*entry;
	DIR				*dir;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return ;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (match_pattern(pattern, entry->d_name))
			add_token(t_list, create_token(entry->d_name, TOKEN_ARGUMENT));
		entry = readdir(dir);
	}
	closedir(dir);
}
