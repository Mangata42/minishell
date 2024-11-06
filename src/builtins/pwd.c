/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:20:10 by nghaddar          #+#    #+#             */
/*   Updated: 2024/11/06 15:23:08 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int builtin_pwd()
{
	char *buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
		return (EXIT_FAILURE);
	
	printf("%s\n", buffer);
	return (EXIT_SUCCESS);
}