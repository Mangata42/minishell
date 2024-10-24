/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strPreppend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:07:42 by nghaddar          #+#    #+#             */
/*   Updated: 2024/10/23 14:03:20 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strPreppend(char *str, char *toPreppend)
{
	char *newStr;
	int i = -1;
	int y = -1;

	if (!(newStr = malloc(ft_strlen(str) + ft_strlen(toPreppend) + 1)))
		return (NULL);
	
	while (toPreppend[++i])
		newStr[i] = toPreppend[i];
	while (str[++y])
		newStr[i++] = str[y];
		
	newStr[i++] = '\0';
	return (newStr);
}