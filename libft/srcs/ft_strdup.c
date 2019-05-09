/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:12:31 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:49:07 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	len = ft_strlen(s1);
	if (!(dup = malloc(sizeof(*dup) * (len + 1))))
		return (NULL);
	while (i <= len)
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}
