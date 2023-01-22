/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenmain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:24:22 by ibenmain          #+#    #+#             */
/*   Updated: 2021/12/04 15:51:52 by ibenmain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int			rest;
	long int	nbr;

	nbr = n;
	if (nbr < 0)
	{
		nbr *= -1;
		write(fd, "-", 1);
	}
	rest = nbr % 10 + '0';
	nbr /= 10;
	if (nbr != 0)
		ft_putnbr_fd(nbr, fd);
	write(fd, &rest, 1);
}
