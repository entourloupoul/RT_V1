/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 08:40:07 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:50:07 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned long	i;
	unsigned long	len;
	unsigned long	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < size)
		i++;
	if (i == size)
		return (size + ft_strlen(src));
	i = 0;
	len = ft_strlen(dst);
	while (src[j] != '\0' && j < size - len - 1)
	{
		dst[len + j] = src[j];
		j++;
	}
	dst[len + j] = '\0';
	return (len + ft_strlen(src));
}
