/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:46:24 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/09 20:40:36 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verif_pipe(t_token *pipe_token)
{
	t_token_type	p_type;
	int				check_mask;

	if (!pipe_token->index || !pipe_token->next)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	p_type = pipe_token->prev->type;
	check_mask = (TOKEN_COMMAND | TOKEN_VARIABLE | TOKEN_STRING 
		| TOKEN_ARGUMENT | TOKEN_EXPAND | TOKEN_RPAREN);
	if (!(p_type & check_mask))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	verif_rparen(t_token *par_token)
{
	if (par_token->prev->type == TOKEN_LPAREN)
	{
		printf("minishell: syntax error near unexpected token : `)'\n");
		return (1);
	}
	return (0);
}