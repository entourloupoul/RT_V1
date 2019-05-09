/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_no_signe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:51:07 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:33:39 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_fill_str_ll(char *str, long long n1, int len)
{
	str[len - 1] = '\0';
	len = len - 2;
	while (n1 != 0)
	{
		str[len] = 48 + n1 % 10;
		n1 = n1 / 10;
		len--;
	}
}

static int	ft_len_str_ll(long long n1)
{
	int	len;

	len = 1;
	if (n1 == 0)
		len++;
	while (n1 != 0)
	{
		n1 = n1 / 10;
		len++;
	}
	return (len);
}

char		*ft_lltoa_no_signe(long long n)
{
	char	*str;
	int		len;

	if (n < 0)
		n = -n;
	len = ft_len_str_ll(n);
	if (!(str = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	ft_fill_str_ll(str, n, len);
	return (str);
}
