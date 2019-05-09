/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:58:05 by pmasson           #+#    #+#             */
/*   Updated: 2019/05/09 14:48:03 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int				ft_valid_base(const char *base)
{
	int i;
	int k;

	i = 0;
	if (base == NULL)
		return (0);
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i + 1] != '\0')
	{
		k = i + 1;
		while (base[k] != '\0')
		{
			if (base[k] == base[i] || base[k] <= 32 ||
					base[k] >= 127 || base[k] == 43 || base[k] == 45)
				return (0);
			k++;
		}
		i++;
	}
	return (1);
}

static int				ft_valid_input(const char *base, char *str)
{
	int i;
	int k;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		k = 0;
		while (str[i] != base[k] && base[k] != '\0')
			k++;
		if (base[k] == '\0')
			return (0);
		i++;
	}
	return (1);
}

static unsigned long	ft_basetol(const char *base, char *str)
{
	unsigned long		n;
	unsigned long long	ret;
	long				i;
	unsigned long		j;
	unsigned long		k;

	k = ft_strlen(base);
	i = (long)ft_strlen(str) - 1;
	n = 1;
	ret = 0;
	while (i >= 0)
	{
		j = 0;
		while (str[i] != base[j])
			j++;
		ret = ret + n * j;
		n = n * k;
		i--;
	}
	return (ret);
}

static char				*ft_ltobase(const char *base, unsigned long long n)
{
	unsigned long long	k;
	unsigned long		b;
	int					i;
	char				*new;

	b = ft_strlen(base);
	k = n;
	i = 0;
	while (n / b > 0)
	{
		n = n / b;
		i++;
	}
	i++;
	if (!(new = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	new[i] = '\0';
	while (i > 0)
	{
		i--;
		new[i] = base[k % b];
		k = k / b;
	}
	return (new);
}

char					*ft_convert_base(const char *base1,
		const char *base2, char *str)
{
	char				*ret;
	unsigned long long	l;

	if (ft_valid_base(base1) == 0)
	{
		ft_putstr("base1 is not a valid base.\n");
		return (NULL);
	}
	if (ft_valid_base(base2) == 0)
	{
		ft_putstr("base2 is not a valid base.\n");
		return (NULL);
	}
	if (ft_valid_input(base1, str) == 0)
	{
		return (NULL);
	}
	l = ft_basetol(base1, str);
	ret = ft_ltobase(base2, l);
	return (ret);
}
