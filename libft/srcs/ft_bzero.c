/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:07:59 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:37:37 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned long	i;
	unsigned char	*s1;
	unsigned char	c2;

	i = 0;
	c2 = 0;
	s1 = (unsigned char *)s;
	if (n == 0)
		return ;
	while (i < n)
	{
		s1[i] = c2;
		i++;
	}
}
