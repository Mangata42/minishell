/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:43:43 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/09 15:02:04 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

int		parser(t_t_list *token_list);

//utils
int		verif_pipe(t_token *pipe_token);
int		verif_rparen(t_token *par_token);

#endif
