/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:09:34 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/06 15:45:16 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

typedef struct s_shell
{
	int		exit_status;
	char	**envp;
	size_t	env_entries;
}				t_sh;

void	update_exit_status(t_sh *shell, int status);
void	initialize_shell(t_sh *shell, char **envp);
char	*get_env_value(const char *name, char **envp);

#endif
