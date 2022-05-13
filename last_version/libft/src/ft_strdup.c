/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:20:09 by abensett          #+#    #+#             */
/*   Updated: 2021/06/10 11:51:36 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char			*dup;
	unsigned int	lensrc;

	lensrc = 0;
	while (src[lensrc])
		lensrc++;
	dup = malloc(sizeof(char) * (lensrc + 1));
	if (!dup)
		return (NULL);
	dup[lensrc] = '\0';
	while (lensrc-- != 0)
		dup[lensrc] = src[lensrc];
	return (dup);
}
