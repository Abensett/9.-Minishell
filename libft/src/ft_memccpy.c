/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:30:12 by abensett          #+#    #+#             */
/*   Updated: 2021/11/12 17:30:54 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				len;
	unsigned char		*dest;
	unsigned char		*sourc;

	len = 0;
	dest = (unsigned char *) dst;
	sourc = (unsigned char *) src;
	while (len < n && (len == 0 || sourc[len - 1] != (unsigned char) c))
	{
		dest[len] = sourc[len];
		len++;
	}
	if (len > 0 && sourc[len - 1] == (unsigned char) c)
		return (dest + len);
	else
		return (NULL);
}
