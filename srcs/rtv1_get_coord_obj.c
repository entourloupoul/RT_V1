/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_coord_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:32:24 by pmasson           #+#    #+#             */
/*   Updated: 2019/06/03 14:56:09 by pmasson          ###   ########.fr       */
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

static int	rtv1_get_plane_coord(t_obj *obj, char **nb)
{
	double	eq[4];
	int		i;
	double	length;

	if (line[0] != 'e')
		return (ft_msg_int(2, "Error, no equation in plane.\n", -1));
	ft_bzero(eq, sizeof(double) * 4);
	i = 0;
	while (eq[i] = != NULL && i < 4 && rtv1_atoi(nb[i], &eq[i]) == 1)
		i++;
	if (i != 4 || (i == 4 && nb[i] != NULL))
		return (ft_msg_int(2, "Error, plane equation wrong.\n", -1));
	obj->u->equation->x = eq[0];
	obj->u->equation->y = eq[1];
	obj->u->equation->z = eq[2];
	obj->u->constant = eq[3];
	length = sqrt(eq[0] * eq[0] + eq[1] * eq[1] + eq[2] * eq[2]);
	if (length == 0)
		return (1);
	obj->u->norm->x = eq[0] / length;
	obj->u->norm->y = eq[1] / length;
	obj->u->norm->z = eq[2] / length;
	return (1);
}

int	rtv1_get_coord_obj(t_obj *obj, char *line)
{
	int		shift;
	char	**nb;
	int		ret;

	ret = 0;
	if (!(nb = ft_strsplit(line + 2, ',')))
		return (ft_msg_int(2, "Error, failed split obj.\n", -1));
	if (rtv1_get_coord_obj2(obj, nb, shift) != 1)
	{
		rtv1_free_tab(nb);
		return (-1);
	}
	if (obj->type == PLANE)
		ret = rtv1_get_plane_coord(obj, nb, line);
	rtv1_free_tab(nb);
	return (1);
}


