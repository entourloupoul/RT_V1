/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:26:00 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/10 14:04:46 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	rtv1_atoi(char *str, double *d)
{
	int		i;
	long	a;
	long	coeff;

	a = 0;
	coeff = 1;
	if (str == NULL)
		return (0);
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (ft_isdigit(str[i]) == 0 && (i != 0 || (i == 0 && str[i] != '+'
						&& str[i] != '-')))
			return (0);
		a = str[i] == '+' ? a : a + coeff * (str[i] - 48);
		a = str[i] == '-' ? -(a - coeff * (str[i] - 48)) : a;
		coeff = coeff * 10;
		if (a > 2147483648 || (a == 2147483648 && str[0] != '-')\
				|| coeff > 100000000000)
			return (0);
		i--;
	}
	*d = (double)a;
	return (1);
}
