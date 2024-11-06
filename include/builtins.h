/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:04:50 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/06 22:12:55 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"
# include <limits.h>

// utils
t_var	*copy_env(t_sh *shell);

int		ft_echo(char **args);
int		ft_cd(char **args, t_sh *shell);
int		ft_pwd(void);
int		ft_export(char **args, t_sh *shell);
int		ft_unset(char **args, t_sh *shell);
int		ft_env(t_sh *shell);
int		ft_exit(char **args);

#endif
