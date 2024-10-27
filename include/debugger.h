/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:57:07 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 15:48:31 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef DEBUGGER_H
#define DEBUGGER_H

#include "minishell.h"

void	print_token_list(t_token_list *list);
void	print_env(char **envp);

#endif