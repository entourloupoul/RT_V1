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

static void	rtv1_get_norm(t_obj *obj)
{
	double	length;

	obj->norm[0] = (double)obj->data[0];
	obj->norm[1] = (double)obj->data[1];
	obj->norm[2] = (double)obj->data[2];
	length = sqrt(obj->norm[0] * obj->norm[0] + obj->norm[1] * obj->norm[1]
			+ obj->norm[2] * obj->norm[2]);
	if (length == 0)
		return ;
	obj->norm[0] = obj->norm[0] / length;
	obj->norm[1] = obj->norm[1] / length;
	obj->norm[2] = obj->norm[2] / length;
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
	if (obj->type == 1)
		rtv1_get_norm(obj);
	return (1);
}


