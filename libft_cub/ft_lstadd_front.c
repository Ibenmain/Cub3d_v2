/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:18:13 by ibenmain          #+#    #+#             */
/*   Updated: 2021/12/04 15:49:37 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			new->next = *alst;
			*alst = new;
		}
	}
}
