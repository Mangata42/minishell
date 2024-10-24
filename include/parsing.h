/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:09:54 by fflamion          #+#    #+#             */
/*   Updated: 2024/10/24 14:26:43 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSING_H
#define PARSING_H

typedef struct s_sep
{
	char	*cmd;
	struct s_sep	*next;
	struct s_sep	*prev;
}	t_sep;


t_sep	*tokenizer(char *input);
void	print_list(t_sep *list);
void	free_list(t_sep *list);

#endif