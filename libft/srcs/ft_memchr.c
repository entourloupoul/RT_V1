/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:01:03 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:40:37 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		c1;
	unsigned char const *s2;
	unsigned long		i;
	void				*s3;

	s2 = (unsigned char const *)s;
	s3 = (void *)s;
	c1 = (unsigned char)c;
	i = 0;
	while (i < n && s2[i] != c1)
	{
		i++;
	}
	if (i == n)
		return (NULL);
	return (s3 + i);
}
