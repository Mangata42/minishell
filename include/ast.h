/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:36:31 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/12 17:16:51 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

// # include "debugger.h"
# include "lexer.h"

typedef enum e_ast_node_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_REDIRECTION_IN,
	AST_REDIRECTION_OUT,
	AST_REDIRECTION_APPEND,
	AST_REDIRECTION_HEREDOC
}						t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	char				**argv;
	char				*filename;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_sh				*shell;
}						t_ast_node;

// ast_list
t_ast_node				*create_ast_node(t_ast_node_type type, t_sh *shell);
void					add_argument(t_ast_node *node, char *argument);
void					free_ast(t_ast_node *node);

// parser
t_ast_node				*ast_parser(t_t_list *token_list, t_sh *shell);
t_ast_node				*parse_parentheses(t_token **current_token,
							t_sh *shell);
t_ast_node				*parse_command(t_token **current_token, t_sh *shell);
t_ast_node				*parse_pipeline(t_token **current_token, t_sh *shell);
t_ast_node				*parse_and_or_sequence(t_token **current_token,
							t_sh *shell);

// parse_redir
void					parse_redir(t_token **curr_t, t_ast_node *cmd_node,
							t_sh *sh);
int						is_redirection_token(t_token *token);

// parse_pipeline
t_ast_node				*parse_pipeline(t_token **current_token, t_sh *shell);
t_ast_node				*parse_parentheses(t_token **current_token,
							t_sh *shell);

// execution
int						execute_ast(t_ast_node *node, t_sh *shell);
int						execute_command_node(t_ast_node *node, t_sh *shell);
int						execute_pipe_node(t_ast_node *node, t_sh *shell);
int						execute_and_node(t_ast_node *node, t_sh *shell);
int						execute_or_node(t_ast_node *node, t_sh *shell);

// executor_utils1
void					handle_redir_in(t_ast_node *node);
void					handle_redir_out(t_ast_node *node, int flags);
void					handle_redirections(t_ast_node *node);
void					handle_redir_heredoc(t_ast_node *node);

// executor_utils2
void					set_s_h(struct sigaction *sa, int signum,
							void (*handler)(int));
void					save_og_s(struct sigaction *orig_int,
							struct sigaction *orig_quit);
void					res_sig(struct sigaction *orig_int,
							struct sigaction *orig_quit);
void					set_signals_for_parent(struct sigaction *sa_ignore);
void					set_signals_for_child(struct sigaction *sa_default);

// executor_utils3
int						w_c(pid_t p, t_sh *s, struct sigaction *b,
							struct sigaction *a);
pid_t					create_child_process(t_ast_node *node, t_sh *shell);

#endif
