/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 19:17:20 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "shell.h"

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIRECTION_IN,
	TOKEN_REDIRECTION_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_VARIABLE,
	TOKEN_STRING,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_EOF,
	TOKEN_WILDCARDS,
	TOKEN_EXPAND
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_token_list
{
	t_token				*token;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}	t_token_list;

t_token_list	*lexer(char *input, t_shell *shell);
//utils1
void			handle_pipe(char *input, int *i, t_token_list **tokens);
void			handle_rout(char *input, int *i, t_token_list **tokens);
void			handle_rin(char *input, int *i, t_token_list **tokens);
void			handle_single_quote(char *input, int *i, t_token_list **tokens);
void			handle_double_quote(char *input, int *i, t_token_list **tokens, t_shell *shell);
//utils2
void			handle_cmd_arg(char *input, int *i, t_token_list **tokens);
t_token			*create_token(const char *value, t_token_type type);
void			add_token(t_token_list **tokens, t_token *new_token);
void			handle_and(char *input, int *i, t_token_list **tokens);
void			handle_wildcards(char *input, int *i, t_token_list **tokens);
//utils3S
void			handle_expand(char *input, int *i, t_token_list **tokens, t_shell *shell);

#endif