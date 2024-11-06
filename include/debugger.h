/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:57:07 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/06 16:10:07 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DEBUGGER_H
# define DEBUGGER_H

# include "minishell.h"
# include "ast.h"

# define RESET	"\033[0m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"

void		print_t_list(t_t_list *list);
void		print_token_info(t_token *token, unsigned int index);
void		print_token_type(t_token_type type);

//get_info
const char	*get_type(int index);
const char	*get_color_code(int index);
int			get_token_index(t_token_type type);
const char	*get_color(int level);

//print
void		print_ast(t_ast_node *node, int level);
void		print_node_info(t_ast_node *node, int level);
void		print_node_type(t_ast_node *node);
void		print_indentation(int level);
void		print_env_debug(char **envp);
void		print_env_debug(char **envp);

#endif
