/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:43:48 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/31 11:44:57 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "minishell.h"

typedef struct s_ast_node
{
	t_token_type		type;
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*parent;
}	t_ast_node;

typedef struct s_ast_list
{
	struct s_token		*first;
	struct s_token		*last;
	unsigned int		size;
}	t_ast_list;

//list
t_ast_node	*create_ast_node(const char *value, t_token_type type);
t_ast_list	*init_ast_list(void);
void		free_ast_list(t_ast_list *list);
void		free_ast_node(t_ast_node *node);

//
#endif