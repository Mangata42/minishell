/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:43:43 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/19 13:31:47 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "shell.h"

int	parser(t_t_list *token_list);

// utils
int	verif_redir_in_out_set(t_token *redir_in_token);
int	verif_pipe(t_token *pipe_token);
int	verif_rparen(t_token *par_token);

#endif
