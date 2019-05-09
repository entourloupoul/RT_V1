/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 09:51:49 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:53:57 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned long	i;
	unsigned long	j;
	char			*str;

	i = 0;
	str = (char *)haystack;
	if (needle[0] == '\0')
		return (str);
	if (haystack[0] == '\0' && needle[0] == '\0')
		return (str);
	if (haystack[0] == '\0')
		return (NULL);
	while (haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j] != '\0'
				&& i + j < len && haystack[i + j] != '\0')
			j++;
		if ((i + j == len || haystack[i + j] == '\0') && needle[j] != '\0')
			return (NULL);
		if (needle[j] == '\0')
			return (str + i);
		i++;
	}
	return (NULL);
}
