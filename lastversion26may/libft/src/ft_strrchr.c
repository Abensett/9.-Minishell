/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:28:38 by abensett          #+#    #+#             */
/*   Updated: 2021/11/12 17:32:00 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*i;

	i = ft_strchr(str, '\0');
	while (i >= str)
	{
		if (*i == (unsigned char)c)
			return ((char *)i);
		i--;
	}
	return (NULL);
}
