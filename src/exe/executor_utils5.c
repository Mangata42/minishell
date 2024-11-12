/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:10:43 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/12 17:23:23 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_absolute_or_relative_path(char *command)
{
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	else
		return (NULL);
}

char	*build_full_path(char *dir, char *command)
{
	char	*full_path;

	full_path = ft_strjoin(dir, "/");
	if (!full_path)
		return (NULL);
	full_path = ft_strjoin_free(full_path, command);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*search_in_path(char *command, t_sh *shell)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	path_env = get_env_value(shell, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = build_full_path(paths[i], command);
		if (full_path)
		{
			ft_free_split(paths);
			return (full_path);
		}
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

char	*find_executable_path(char *command, t_sh *shell)
{
	char	*path;

	if (ft_strchr(command, '/'))
		path = check_absolute_or_relative_path(command);
	else
		path = search_in_path(command, shell);
	return (path);
}
