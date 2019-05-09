/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:49:46 by pmasson           #+#    #+#             */
/*   Updated: 2019/02/22 11:49:29 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	unsigned long	len;
	unsigned long	i;

	i = 0;
	if (s == NULL || f == NULL)
		return ;
	len = ft_strlen(s);
	while (i < len)
	{
		f(s + i);
		i++;
	}
}
