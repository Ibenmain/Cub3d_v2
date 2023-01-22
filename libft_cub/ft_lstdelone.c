/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:58:28 by ibenmain          #+#    #+#             */
/*   Updated: 2021/12/03 23:31:02 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del)
		free(lst);
	else if (lst)
	{
		del(lst->content);
		free(lst);
	}
}
