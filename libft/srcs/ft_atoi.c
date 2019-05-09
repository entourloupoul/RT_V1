/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:15:46 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:28:39 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_convert(const char *str, int i, int k)
{
	int a;
	int res;

	a = 1;
	res = 0;
	while (k >= 0)
	{
		res = res + a * (str[i + k] - 48);
		a = a * 10;
		k--;
	}
	return (res);
}

int			ft_atoi(const char *str)
{
	int i;
	int k;
	int res;

	i = 0;
	k = 0;
	res = 0;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\n'
			|| str[i] == '\f' || str[i] == '\v' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] < 48 || str[i + 1] > 57)
			return (0);
		i++;
	}
	while (str[i + k] >= 48 && str[i + k] <= 57)
		k++;
	if (k != 0)
		res = ft_convert(str, i, k - 1);
	if (i - 1 >= 0 && str[i - 1] == '-')
		res = -res;
	return (res);
}
