/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:46:34 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:56:00 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_strtrim_new(char const *s, char *new, int start, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char		*ft_strtrim(char const *s)
{
	char			*new;
	int				start;
	int				i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	if (s[i] == '\0')
		return (ft_strnew(0));
	start = i;
	while (s[i] != '\0')
		i++;
	if (i == 0)
		return (ft_strdup(s));
	i--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i--;
	if ((unsigned long)(i - start + 1) == ft_strlen(s))
		return (ft_strdup(s));
	if (!(new = (char *)malloc(sizeof(char) * (i - start + 1 + 1))))
		return (NULL);
	return (ft_strtrim_new(s, new, start, i - start + 1));
}
