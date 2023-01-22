/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:17:36 by ibenmain          #+#    #+#             */
/*   Updated: 2021/12/04 15:54:08 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str_mapi;

	i = 0;
	if (!s)
		return (NULL);
	str_mapi = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str_mapi)
		return (NULL);
	while (s[i])
	{
		str_mapi[i] = f(i, s[i]);
			i++;
	}
	str_mapi[i] = '\0';
	return (str_mapi);
}
