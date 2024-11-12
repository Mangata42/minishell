/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:33:17 by fflamion          #+#    #+#             */
/*   Updated: 2024/11/12 01:20:07 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct s_process_data
{
	char		*input;
	t_t_list	*t_list;
	t_sh		*shell;
}				t_process_data;

void	handle_exit_status(uint16_t *i, char *buffer, size_t *j,
		t_sh *shell)
{
	char	*env_value;
	char	*tmp;

	(*i) += 2;
	env_value = ft_itoa(shell->exit_status);
	if (!env_value)
		return ;
	tmp = env_value;
	while (*env_value && *j < 255)
		buffer[(*j)++] = *env_value++;
	free(tmp);
}

void	handle_env_var(uint16_t *i, char *buffer, size_t *j,
		t_process_data *data)
{
	char	*env_value;

	(*i)++;
	env_value = parse_env_var(data->input, i, data->shell);
	if (!env_value)
		return ;
	while (env_value && *env_value && *j < 255)
		buffer[(*j)++] = *env_value++;
}

void	process_double_quotes(uint16_t *i, char *buffer, size_t *j,
		t_process_data *data)
{
	while (data->input[*i] && data->input[*i] != '\"')
	{
		if (data->input[*i] == '$' && data->input[*i + 1] == '?')
			handle_exit_status(i, buffer, j, data->shell);
		else if (data->input[*i] == '$')
			handle_env_var(i, buffer, j, data);
		else if (*j < 255)
			buffer[(*j)++] = data->input[(*i)++];
	}
}

void	h_d_q(char *input, uint16_t *i, t_t_list *t_list, t_sh *shell)
{
	char			buffer[256];
	size_t			j;
	t_process_data	data;

	j = 0;
	data.input = input;
	data.t_list = t_list;
	data.shell = shell;
	(*i)++;
	process_double_quotes(i, buffer, &j, &data);
	buffer[j] = '\0';
	add_token(t_list, create_token(buffer, TOKEN_STRING));
	if (input[*i] == '\"')
		(*i)++;
	else
		ft_putstr_fd("Error: Missing closing double quote\n", 2);
}
