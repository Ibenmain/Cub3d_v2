/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 01:06:19 by ibenmain          #+#    #+#             */
/*   Updated: 2021/12/01 22:20:28 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		size;

	size = 0;
	tmp = lst;
	if (!tmp)
		return (0);
	else
	{
		while (tmp != NULL)
		{
			size++;
			tmp = tmp->next;
		}
	}
	return (size);
}
