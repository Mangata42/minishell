/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:48:46 by nghaddar          #+#    #+#             */
/*   Updated: 2024/10/30 16:33:20 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Should verify command or not??
char	*findCommandLocation(char *cmd)
{
	int		execPathIndex = 0;
	char	**execPath;
	char	*execLocation = NULL;
	char	*cmdWithSlash;
	char	*cmdWithPath;
	char 	*envPath;

	cmdWithSlash = ft_strpreppend(cmd, "/");
	envPath = getenv("PATH");
	execPath = ft_split(envPath, ':');
	while (execPath[execPathIndex])
	{
		cmdWithPath = ft_strpreppend(cmdWithSlash, execPath[execPathIndex]);
		if (access(cmdWithPath, F_OK) == 0)
			break;

		execPathIndex++;
		free(cmdWithPath);
		cmdWithPath = NULL;
	}

	for (int i = 0; execPath[i]; i++)
		free(execPath[i]);
	
	free(execPath);
	free(cmdWithSlash);
	if (cmdWithPath)
		return (cmdWithPath);
		
	return (NULL);
}


int		verif_cmd(t_token *cmd_token)
{
	/*TODO : add the condition REDIR_IN -> FILE -> CMD */
	t_token_type	p_type;
	int				check_mask;

	if (!cmd_token->index)
		return (0);

	check_mask = (TOKEN_AND | TOKEN_OR | TOKEN_HEREDOC | TOKEN_PIPE);
	p_type = cmd_token->prev->type;
	if (!(check_mask & p_type)){
		printf("%s: parsing error\n", cmd_token->value);
		return (1);
	}
}

int		verif_args_set(t_token *args_token)
{
	t_token_type	p_type;
	int				variable_check_mask;

	if (!args_token->index)
	{
		printf("%s: parsing error\n", args_token->value);
		return (1);
	}
	
	p_type = args_token->prev->type;
	variable_check_mask = (TOKEN_PIPE | TOKEN_REDIRECTION_OUT | TOKEN_APPEND
							| TOKEN_COMMAND);
	if (args_token->type & (TOKEN_STRING | TOKEN_EXPAND | TOKEN_ARGUMENT 
							| TOKEN_WILDCARDS))
		if (p_type != TOKEN_COMMAND){
			printf("%s: parsing error\n", args_token->value);
			return (1);
		}
		
	if (args_token->type == TOKEN_VARIABLE && !(variable_check_mask & p_type)){
		printf("%s: parsing error\n", args_token->value);
		return (1);
	}

	return (0);
}

int		verif_pipe(t_token *pipe_token)
{
	t_token_type p_type;
	int			 check_mask;

	if (!pipe_token->index)
	{
		printf("pipe parsing error\n");
		return (1);
	}

	p_type = pipe_token->prev->type;
	check_mask = (TOKEN_COMMAND | TOKEN_VARIABLE);

	if (!(check_mask & p_type))
	{
		printf("pipe parsing error\n");
		return (1);
	}
	
	return (0);
}

int		verif_redir_in_set(t_token *redir_in_token)
{
	if (!redir_in_token->index == 0)
		return (1);
	return (0);
}

int		verif_redir_out_set(t_token *redir_out_token)
{
	t_token_type p_type;
	int			 check_mask;

	p_type = redir_out_token->type;
	check_mask = (TOKEN_ARGUMENT | TOKEN_STRING | TOKEN_WILDCARDS | TOKEN_EXPAND
					| TOKEN_COMMAND | TOKEN_VARIABLE | TOKEN_HEREDOC);
	
	if (!redir_out_token->index || !(p_type & check_mask))
	{
		printf("redirection out parse error\n");
		return (1);
	}
	return (0);
}

int		verif_operand_set(t_token *operand_token)
{
	t_token_type p_type;
	int			 check_mask;
	
	if (!operand_token->index)
	{
		printf("operand parse error\n");
		return (1);
	}
	
	p_type = operand_token->prev->type;
	check_mask = (TOKEN_ARGUMENT | TOKEN_STRING | TOKEN_WILDCARDS | TOKEN_EXPAND
					| TOKEN_COMMAND); 
	if (!(p_type & check_mask))
	{
		printf("operand parse error\n");
		return (1);
	}
	
	return (0);
}

int	parser(t_t_list *token_list)
{
	t_token *token_cursor = token_list->first;
	int		status = 0;

	while (token_cursor)
	{
		if (token_cursor->type == TOKEN_COMMAND)
			status = verif_cmd(token_cursor);
		else if (token_cursor->type & (TOKEN_ARGUMENT |TOKEN_VARIABLE
		 | TOKEN_STRING | TOKEN_EXPAND | TOKEN_WILDCARDS))
			status = verif_args_set(token_cursor);
		else if (token_cursor->type == TOKEN_PIPE)
			status = verif_pipe(token_cursor);
		else if (token_cursor->type & (TOKEN_REDIRECTION_IN | TOKEN_HEREDOC))
			status = verif_redir_in_set(token_cursor);
		else if (token_cursor->type & (TOKEN_REDIRECTION_OUT | TOKEN_APPEND))
			status = verif_redir_out_set(token_cursor);
		else if (token_cursor->type & (TOKEN_AND | TOKEN_OR))
			status = verif_operand_set(token_cursor);
		if (status)
			return (status);
		token_cursor = token_cursor->next;
	}
	return (0);
}