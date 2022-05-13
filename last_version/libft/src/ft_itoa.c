/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:09:12 by abensett          #+#    #+#             */
/*   Updated: 2021/11/12 17:29:57 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_lennb(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n >= 1)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*ft_makingofstr(char *str, long nbr, int len, int sign)
{
	if (nbr != 0)
		str = malloc(sizeof(char) * (len + 1));
	else
		return (str = ft_strdup("0"));
	if (!str)
		return (0);
	sign = 0;
	if (nbr < 0)
	{
		sign = -1;
		nbr = -nbr;
	}
	str[len] = '\0';
	while (--len)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (sign == -1)
		str[0] = '-';
	else
		str[0] = (nbr % 10) + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	nbr;
	int		sign;

	nbr = n;
	len = ft_lennb(nbr);
	str = 0;
	sign = 0;
	str = ft_makingofstr(str, nbr, len, sign);
	if (!str)
		return (0);
	return (str);
}
