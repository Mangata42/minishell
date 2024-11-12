/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:04:50 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/12 17:17:01 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"
# include <limits.h>
# include "ast.h"

// utils
t_var	*copy_env(t_sh *shell);

int		ft_echo(char **args);
int		ft_cd(char **args, t_sh *shell);
int		ft_pwd(void);
int		ft_export(char **args, t_sh *shell);
int		ft_unset(char **args, t_sh *shell);
int		ft_env(t_sh *shell);
int		ft_exit(char **args, t_sh *shell, t_ast_node *node);

// export utils
void	swap_values(t_var *a, t_var *b);
t_var	*copy_env(t_sh *shell);
t_var	*var_exists(t_sh *shell, char *var_to_check);
void	print_sorted_env(t_sh *shell);
char	**ret_env_array(t_sh *shell);

// unset utils
void	remove_var(t_sh *shell, char *var_title);

#endif
