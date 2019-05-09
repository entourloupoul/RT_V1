/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:22:24 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:43:43 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long	i;
	unsigned char	*s;
	unsigned char	c2;

	i = 0;
	c2 = (unsigned char)c;
	s = (unsigned char *)b;
	while (i < len)
	{
		s[i] = c2;
		i++;
	}
	return (b);
}
