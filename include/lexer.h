/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/29 13:54:15 by fflamion         ###   ########.fr       */
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
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_token_list
{
	struct s_token		*first;
	struct s_token		*last;
	unsigned int		size;
}	t_t_list;

// T_List & token utils
t_t_list		*init_t_list(void);
void			free_token_list(t_t_list *t_list);
t_token			*create_token(const char *value, t_token_type type);
void			add_token(t_t_list *t_list, t_token *new_token);

t_t_list		*lexer(char *input, t_sh *shell);

// lexer utils1
void			h_pipe(char *input, uint16_t *i, t_t_list *t_list);
void			h_rout(char *input, uint16_t *i, t_t_list *t_list);
void			h_rin(char *input, uint16_t *i, t_t_list *t_list);
void			h_s_q(char *input, uint16_t *i, t_t_list *t_list);
void			h_d_q(char *input, uint16_t *i, t_t_list *t_list, t_sh *shell);

// lexer utils2
void			h_cmd_arg(char *input, uint16_t *i, t_t_list *t_list);
void			handle_and(uint16_t *i, t_t_list *t_list);
void			handle_wildcards(uint16_t *i, t_t_list *t_list);

// lexer utils3
void			h_exp(char *input, uint16_t *i, t_t_list *t_list, t_sh *shell);
char			*parse_env_var(char *input, uint16_t *i, t_sh *shell);

#endif
