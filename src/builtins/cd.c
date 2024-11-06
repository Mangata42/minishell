/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:29:27 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/06 22:17:29 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(char **args, t_sh *shell)
{
	char	*path;
	char	*old_pwd;
	char	current_pwd[PATH_MAX];

	if (!args[1])
	{
		path = get_env_value("HOME", shell->envp);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else
		path = args[1];
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (ft_putstr_fd("minishell: cd: error getting current directory\n",
				2), 1);
	if (chdir(path) == -1)
	{
		free(old_pwd);
		return (ft_putstr_fd("minishell: cd: ", 2), ft_putstr_fd(path, 2),
			ft_putstr_fd(": No such file or directory\n", 2), 1);
	}
	if (!getcwd(current_pwd, PATH_MAX))
	{
		free(old_pwd);
		return (ft_putstr_fd("minishell: cd: error getting new directory\n", 2),
			1);
	}
	free(old_pwd);
	return (0);
}
