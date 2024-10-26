/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/26 21:03:29 by nghaddar         ###   ########.fr       */
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

typedef struct 			s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*Next;
	struct s_token	*Prev;
}						t_token;

typedef struct 			s_token_list
{
	struct s_token *First;
	struct s_token *Last;
	unsigned int		size;
}						t_token_list;

// tokenList & token utils
t_token_list	*init_token_list();
void			free_token_list(t_token_list *TokenListToFree);
t_token			*create_token(const char *value, t_token_type type);
void			add_token(t_token_list *TokenList, t_token *NewToken);

t_token_list	*lexer(char *input, t_shell *shell);
//lexer utils1
void			handle_pipe(char *input, unsigned int *i, t_token_list *TokenList);
void			handle_rout(char *input, unsigned int *i, t_token_list *TokenList);
void			handle_rin(char *input, unsigned int *i, t_token_list *TokenList);
void			handle_single_quote(char *input, unsigned int *i, t_token_list*TokenList);
void			handle_double_quote(char *input, unsigned int *i, t_token_list*TokenList);
//lexer utils2
void			handle_cmd_arg(char *input, unsigned int *i, t_token_list *TokenList);
t_token			*create_token(const char *value, t_token_type type);
void			add_token(t_token_list *TokenList, t_token *new_token);
void			handle_and(unsigned int *i, t_token_list *TokenList);
void			handle_wildcards(unsigned int *i, t_token_list *TokenList);
//lexer utils3
void			handle_expand(char *input, unsigned int *, t_token_list *TokenList, t_shell *shell);

#endif