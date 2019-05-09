/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:37:21 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:45:34 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int n)
{
	int		a;
	char	c;

	a = 1000000000;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	while (a != 1 && n / a == 0)
		a = a / 10;
	while (a != 0)
	{
		c = (n / a) + 48;
		write(1, &c, 1);
		n = n - (n / a) * a;
		a = a / 10;
	}
}
