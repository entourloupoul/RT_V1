/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:05:02 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:56:47 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_fill_str_ull(char *str, unsigned long long n1, int len)
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

static int	ft_len_str_ull(unsigned long long n1)
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

char		*ft_ulltoa(unsigned long long n)
{
	char	*str;
	int		len;

	len = ft_len_str_ull(n);
	if (!(str = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	ft_fill_str_ull(str, n, len);
	return (str);
}
