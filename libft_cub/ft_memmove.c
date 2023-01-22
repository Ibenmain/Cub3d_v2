/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:13:06 by ibenmain          #+#    #+#             */
/*   Updated: 2021/11/27 22:19:11 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	i = -1;
	if (!s && !d)
		return (NULL);
	if (s <= d)
	{
		while (len != 0)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	else
	{
		while (++i < len)
		{
			d[i] = s[i];
		}
	}
	return (d);
}
