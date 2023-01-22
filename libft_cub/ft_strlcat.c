/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <ibenmain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:16:02 by ibenmain          #+#    #+#             */
/*   Updated: 2023/01/05 15:28:30 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	d_len = 0;
	s_len = 0;
	i = 0;
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	while (src[i] != '\0' && i + d_len < dstsize - 1 && dstsize != 0)
	{
		dst[i + d_len] = src[i];
		i++;
		dst[i + d_len] = '\0';
	}
	if (dstsize <= d_len)
		return (s_len + dstsize);
	return (d_len + s_len);
}
