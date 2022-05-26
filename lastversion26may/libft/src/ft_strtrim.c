/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:30:20 by abensett          #+#    #+#             */
/*   Updated: 2021/11/12 17:37:44 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_set(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (0);
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*s2;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	j = ft_strlen(s1);
	while (ft_set(s1[i], set) == 0)
		i++;
	if (i == (int) ft_strlen(s1))
	{
		s2 = ft_strdup("");
		if (!s2)
			return (NULL);
		else
			return (s2);
	}
	while (ft_set(s1[j - 1], set) == 0)
		j--;
	s2 = ft_substr(s1, i, j - i);
	return (s2);
}
