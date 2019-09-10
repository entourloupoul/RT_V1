/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_check_inter_cone.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:57:11 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/10 14:05:43 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

static void	rtv1_modif_ref(t_geo *source, t_obj *obj)
{
	source->pos.x = source->pos.x - obj->pos.x;
	source->pos.y = source->pos.y - obj->pos.y;
	source->pos.z = source->pos.z - obj->pos.z;
	dot_product_column_vec(&(source->dir), obj->u.cone.mat_x, source->dir);
	dot_product_column_vec(&(source->dir), obj->u.cone.mat_y, source->dir);
	dot_product_column_vec(&(source->dir), obj->u.cone.mat_z, source->dir);
	dot_product_column_vec(&(source->pos), obj->u.cone.mat_x, source->pos);
	dot_product_column_vec(&(source->pos), obj->u.cone.mat_y, source->pos);
	dot_product_column_vec(&(source->pos), obj->u.cone.mat_z, source->pos);
}

double		rtv1_check_inter_cone(t_obj *obj, t_geo source)
{
	double	a;
	double	b;
	double	c;
	double	det;

	rtv1_modif_ref(&source, obj);
	if ((a = pow(source.dir.x, 2) + pow(source.dir.y, 2) - pow(source.dir.z, 2)
		* pow(tan(obj->u.cone.angle * M_PI / 180), 2)) == 0)
		return (ft_msg_int(2, "Error calculating in a cone.\n", -1));
	b = 2 * (source.pos.x * source.dir.x + source.pos.y * source.dir.y
			- source.pos.z * source.dir.z * pow(tan(obj->u.cone.angle
			* M_PI / 180), 2));
	c = pow(source.pos.x, 2) + pow(source.pos.y, 2) - pow(source.pos.z, 2)
			* pow(tan(obj->u.cone.angle * M_PI / 180), 2);
	det = pow(b, 2) - 4 * a * c;
	if (det < 0)
		return (-1);
	else
		return (rtv1_solve_2_deg(det, a, b));
}
