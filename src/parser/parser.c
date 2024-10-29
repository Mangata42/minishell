/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:48:46 by nghaddar          #+#    #+#             */
/*   Updated: 2024/10/29 18:21:01 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	t_token_type p_type;

	if (cmd_token->index == 0)
		return (0);

	printf("%s: parsing error\n", cmd_token->value);
	p_type = cmd_token->prev->type;
	if (p_type != TOKEN_AND
		&& p_type != TOKEN_OR
		&& p_type != TOKEN_HEREDOC
		&& p_type != TOKEN_PIPE)
		return (1);
}

int		verif_args_set(t_token *args_token)
{
	t_token_type p_type;
	int			val_to_check;
	int			val_asked;

	if (args_token->index == 0)
	{
		printf("%s: parsing error\n", args_token->value);
		return (1);
	}

	val_to_check = (TOKEN_STRING || TOKEN_EXPAND || TOKEN_ARGUMENT);
	val_asked = (TOKEN_COMMAND || TOKEN_PIPE || TOKEN_REDIRECTION_OUT || TOKEN_APPEND);
	if (val_to_check == val_asked)
		return (0)
	if (args_token->type == TOKEN_STRING && (p_type == ))
}

int	parser(t_t_list *token_list)
{
	t_token *token_cursor = token_list->first;
	int		status = 0;

	while (token_cursor)
	{
		if (token_cursor->type == TOKEN_COMMAND)
			status = verif_cmd(token_cursor);
		else if (token_cursor->type == TOKEN_ARGUMENT ||
					token_cursor->type == TOKEN_VARIABLE ||
					token_cursor->type == TOKEN_STRING ||
					token_cursor->type == TOKEN_EXPAND ||
					token_cursor->type == TOKEN_WILDCARDS)
			status = verif_args_set(token_cursor);
		// else if (token_cursor->type == TOKEN_PIPE)
		// 	status = verif_pipe(token_cursor);
		// else if (token_cursor->type == TOKEN_REDIRECTION_IN)
		// 	status = verif_redir_in(token_cursor);
		// else if (token_cursor->type == TOKEN_HEREDOC)
		// 	status = verif_heredoc(token_cursor);
		// else if (token_cursor->type == TOKEN_REDIRECTION_OUT ||
		// 			token_cursor->type == TOKEN_APPEND)
		// 	status = verif_redir_out_set(token_cursor);
		// else if (token_cursor->type == TOKEN_AND ||
		// 	token_cursor->type == TOKEN_OR)
		// 	status = verif_operand_set(token_cursor);
		if (status)
			return (status);
		token_cursor = token_cursor->next;
	}
}