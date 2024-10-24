/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replaceSubStr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghaddar <nghaddar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:44:38 by nghaddar          #+#    #+#             */
/*   Updated: 2024/10/23 14:02:16 by nghaddar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replaceSubStr(char *s, char *toRep, char *newVal)
{
	char	*newS;
	int 	i = 0, y = 0, z = 0;

	if (!s)
		return (NULL);
	
	if (!toRep || !newVal || !ft_strlen(toRep) || !ft_strlen(newVal))
		return (s);

	if (!(newS = (char *)malloc(ft_strlen(s) + ft_strlen(newVal) + 1)))
		return (NULL);
	
	while (s[i])
	{
		if (s[i] == toRep[0])
			if (!ft_strncmp(s + i, toRep, ft_strlen(toRep)))
				{
					z = 0;
					while (newVal[z])
						newS[y++] = newVal[z++];
					i += ft_strlen(toRep);
				}
		newS[y++] = s[i++];
	}
	return (newS);
}