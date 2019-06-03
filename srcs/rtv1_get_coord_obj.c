/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_coord_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:32:24 by pmasson           #+#    #+#             */
/*   Updated: 2019/05/29 20:32:31 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

/*
 * coord: obj->data
 * c = center
 * r = rayon
 * e = equation
 * a = axis
 * l = length
 * sphere(c,c,c,r,)
 * cylinder(c,c,c,r,a,a,a,l) (c = center of the base)
 * cone(c,c,c,r,a,a,a,l)
 * plane(e,e,e,e)*/
#include <stdio.h>
static int	rtv1_get_coord_obj2(t_obj *obj, char **nb, int s)
{
	int	i;
	int	shift;

	shift = s == 10 ? 0 : s;
	i = 0;
	while (i + shift < 8 && nb[i] != NULL)
	{
		if (rtv1_atoi(nb[i], &obj->data[i + shift]) == 0)
			return (ft_msg_int(2, "Error, wrong term in coord obj.\n", -1));
		i++;
	}
	if (s == 0 && i != 3 && obj->type != 2 && obj->type != 3 && obj->type != 4)
		return (ft_msg_int(2, "Error, wrong type of coord in object.\n", -1));
	if (s == 10 && i != 4 && obj->type != 1)
		return (ft_msg_int(2, "Error, wrong type of coord in object.\n", -1));
	if (s == 3 && i != 1 && obj->type != 2 && obj->type != 3 && obj->type != 4)
		return (ft_msg_int(2, "Error, wrong type of coord in object.\n", -1));
	if (s == 4 && i != 3 && obj->type != 3 && obj->type != 4)
		return (ft_msg_int(2, "Error, wrong type of coord in object.\n", -1));
	if (s == 7 && i != 1 && obj->type != 3 && obj->type != 4)
		return (ft_msg_int(2, "Error, wrong type of coord in object.\n", -1));
	return (1);
}

int	rtv1_get_coord_obj(t_obj *obj, char *line)
{
	int		shift;
	char	**nb;

	if (line[0] == 'c')
		shift = 0;
	if (line[0] == 'e')
		shift = 10;
	if (line[0] == 'r')
		shift = 3;
	if (line[0] == 'a')
		shift = 4;
	if (line[0] == 'l')
		shift = 7;
	if (!(nb = ft_strsplit(line + 2, ',')))
		return (ft_msg_int(2, "Error, failed split obj.\n", -1));
	if (rtv1_get_coord_obj2(obj, nb, shift) != 1)
	{
		rtv1_free_tab(nb);
		return (-1);
	}
	rtv1_free_tab(nb);
	return (1);
}


