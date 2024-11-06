/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:13:29 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/06 22:13:35 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

typedef struct s_var
{
	char	*title;
	char	*value;
	size_t	index;
}			t_var;

typedef struct s_shell
{
	int		exit_status;
	t_var	*env;
	char	**envp;
	size_t	env_size;
}			t_sh;

void		update_exit_status(t_sh *shell, int status);
void		initialize_shell(t_sh *shell, char **envp);
char		*get_env_value(const char *name, char **envp);
void		free_shell(t_sh *shell);
#endif
