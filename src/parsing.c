/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:04 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/24 14:26:18 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_list(t_sep *list)
{
	int i = 0;
	while (list)
	{
		printf("-----------------------------------\n");
		printf("| i = %d                            \n", i);
		printf("| list->cmd_sep : %s            \n", list->cmd);
		printf("-----------------------------------\n");
		list = list->next;
		i++;
	}
}

void free_list(t_sep *list)
{
	t_sep *tmp;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->cmd);
		free(tmp);
	}
}

t_sep *create_cell(char *cmd_sep)
{
	t_sep *cell = malloc(sizeof(t_sep));
	if (!cell)
		return NULL;

	cell->cmd = ft_strdup(cmd_sep);
	if (!cell->cmd)
	{
		free(cell);
		return NULL;
	}

	cell->prev = NULL;
	cell->next = NULL;
	return cell;
}

t_sep *add_cell(t_sep *list, char *cmd_sep, int pos)
{
	t_sep	*prec = NULL;
	t_sep	*cur = list;
	t_sep	*cell = create_cell(cmd_sep);
	int		i;

	i = 0;
	if (!cell)
		return NULL;
	if (list == NULL)
		return cell;
	while (i++ < pos && cur != NULL)
	{
		prec = cur;
		cur = cur->next;
	}
	prec->next = cell;
	cell->next = cur;
	return list;
}

t_sep *tokenizer(char *input)
{
	char	**token = ft_split(input, ';');
	t_sep 	*list = NULL;
	int		i;

	i = 0;
	while (token && token[i])
	{
		list = add_cell(list, token[i], i);
		i++;
	}
	i = 0;
	while (token[i++])
		free(token[i]);
	free(token);
	return list;
}
