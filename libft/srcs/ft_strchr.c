/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 08:56:45 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:47:22 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c1;
	unsigned long	i;
	unsigned long	len;
	int				pos;
	char			*s1;

	c1 = (unsigned char)c;
	len = ft_strlen(s);
	s1 = (char *)s;
	i = 0;
	pos = -1;
	while (i <= len && pos == -1)
	{
		if (s[i] == c1)
			pos = i;
		i++;
	}
	if (pos == -1)
		return (NULL);
	return (s1 + pos);
}
