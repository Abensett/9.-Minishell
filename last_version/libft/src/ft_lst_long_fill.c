/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_long_fill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:11:24 by abensett          #+#    #+#             */
/*   Updated: 2021/12/10 12:18:49 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../libft.h"

t_list	*ft_lst_long_fill(int ac, char **list)
{
	t_list	*stack;
	int		i;

	i = 1;
	stack = NULL;
	if (ac == 1)
	{
		write(1, "ERROR", 5);
		exit(42);
	}
	while (i < ac)
		ft_lstadd_back(&stack, ft_lstnew((void *) ft_atol(list[i++])));
	return (stack);
}
