/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflamion <fflamion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:20:10 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/06 20:24:07 by fflamion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char *buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
		return (EXIT_FAILURE);
	
	printf("%s\n", buffer);
	return (EXIT_SUCCESS);
}