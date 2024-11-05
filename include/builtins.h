/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:10:57 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/06 16:05:22 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"
#include "shell.h"

int		builtin_echo(char *s, char optN);
int		builtin_cd(char *path);

// export
void	print_sorted_env(t_sh *shell);
void	mod_var(t_sh *shell, char *var_title, char *var_value);
void	add_var(t_sh *shell, char *var_title, char *var_value);
void	builtin_export(t_sh *shell, char *new_var);

// export utils 1
void	swap_values(t_var *a, t_var *b);
t_var	*remove_var(t_var *env, char *var_title);
t_var	*copy_env(t_sh *shell);
t_var	*var_exists(t_sh *shell, char *var_to_check);

// unset
void	builtin_unset(t_sh *shell, char *var_title);

// pwd
int		builtin_pwd();

// env
void	builtin_env(t_sh *shell);

// exit
void	builtin_exit(t_sh *shell, int n);


#endif