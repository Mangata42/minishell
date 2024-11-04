/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:10:57 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/04 17:43:10 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"
#include "shell.h"

int		builtin_echo(char *s, char optN);
int		builtin_cd(char *path);
void	print_env(t_sh *shell);
void	add_var(t_sh *shell, char *new_var);
void	export(t_sh *shell, char *new_var);

#endif