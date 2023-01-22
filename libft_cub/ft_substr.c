/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:36:42 by ibenmain          #+#    #+#             */
/*   Updated: 2021/11/23 22:15:47 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;
	size_t	i;
	char	*new;

	i = 0;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		new = malloc(1);
	else
	{
		if (len > str_len)
			len = str_len;
		new = (char *)malloc((len + 1) * sizeof(char));
		if (!new)
			return (NULL);
		while (i < len)
			new[i++] = s[start++];
	}
	new[i] = '\0';
	return (new);
}
