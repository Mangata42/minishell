/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:04:50 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/11 08:45:16 by nghaddar         ###   ########.fr       */
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

// export utils
void	free_split(char **split_str);
void	swap_values(t_var *a, t_var *b);
t_var	*copy_env(t_sh *shell);
t_var	*var_exists(t_sh *shell, char *var_to_check);
void	print_sorted_env(t_sh *shell);
// int		verify_arg(char *arg);

// unset utils
void	remove_var(t_sh *shell, char *var_title);

#endif
