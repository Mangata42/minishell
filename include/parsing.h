/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/27 17:23:09 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "shell.h"

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
	t_token_type type;
	char *value;
	struct s_token *Next;
	struct s_token *Prev;
}				t_token;

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
void			h_pipe(char *input, uint16_t *i, t_token_list *TokenList);
void			h_rout(char *input, uint16_t *i, t_token_list *TokenList);
void			h_rin(char *input, uint16_t *i, t_token_list *TokenList);
void			h_s_q(char *input, uint16_t *i, t_token_list*TokenList);
void			h_d_q(char *input, uint16_t *i, t_token_list *TokenList, t_shell *shell);
//lexer utils2
void			h_cmd_arg(char *input, uint16_t *i, t_token_list *TokenList);
t_token			*create_token(const char *value, t_token_type type);
void			add_token(t_token_list *TokenList, t_token *new_token);
void			handle_and(uint16_t *i, t_token_list *TokenList);
void			handle_wildcards(uint16_t *i, t_token_list *TokenList);
//lexer utils3
void			h_exp(char *input, uint16_t *, t_token_list *TokenList, t_shell *shell);

#endif