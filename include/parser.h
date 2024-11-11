/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:43:43 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/11 05:43:01 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "shell.h"
# include "lexer.h"

int		parser(t_t_list *token_list);

//utils
int		verif_pipe(t_token *pipe_token);
int		verif_rparen(t_token *par_token);

#endif
