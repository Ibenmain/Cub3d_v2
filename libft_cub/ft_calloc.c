/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 15:08:28 by ibenmain          #+#    #+#             */
/*   Updated: 2021/12/04 16:12:42 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*val;
	size_t	i;

	i = 0;
	val = (void *)malloc(count * size);
	if (!val)
		return (0);
	ft_bzero(val, count * size);
	return (val);
}
