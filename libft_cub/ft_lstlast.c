/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 01:33:04 by ibenmain          #+#    #+#             */
/*   Updated: 2021/12/01 22:19:52 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (!tmp)
		return (0);
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
	}
	return (tmp);
}
