/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 11:49:25 by abensett          #+#    #+#             */
/*   Updated: 2021/11/12 17:30:55 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		*s2;

	if (s == NULL)
		return (NULL);
	i = 0;
	s2 = (void *)s;
	while (i < n)
	{
		if (s2[i] == (char)c)
			return (&s2[i]);
		i++;
	}
	return (NULL);
}
