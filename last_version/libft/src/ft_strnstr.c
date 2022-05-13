/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 09:07:10 by abensett          #+#    #+#             */
/*   Updated: 2021/11/12 17:31:56 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	int		i;
	int		d;
	int		f;

	if (little[0] == '\0')
		return ((char *) big);
	i = 0;
	while (big[i] && n != 0)
	{
		if (n < ft_strlen(little))
			return (NULL);
		d = 0;
		f = i;
		while (big[f] == little[d] && big[f] && little[d])
		{
			d++;
			f++;
		}
		if (little[d] == '\0')
			return ((char *) big + i);
		n--;
		i++;
	}
	return (NULL);
}
