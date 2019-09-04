/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_shade_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:03:11 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/04 16:14:19 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** on cherche le point c ten que ac perpendiculaire a bc
** (a point du ray, b centre du cyl)
*/

void	rtv1_shade_cylinder_calc_norm(double u, t_ray *ray, t_obj *obj,
		t_fvec3d *norm)
{
	double	p;

	p = (obj->u.cylinder.axis.x * (ray->obj.pos.x
			- obj->u.cylinder.center.x) + obj->u.cylinder.axis.y
			* (ray->obj.pos.y - obj->u.cylinder.center.y)
			+ obj->u.cylinder.axis.z * (ray->obj.pos.z
			- obj->u.cylinder.center.z)) / u;
	norm->x = ray->obj.pos.x - (obj->u.cylinder.center.x
			+ p * obj->u.cylinder.axis.x);
	norm->y = ray->obj.pos.y - (obj->u.cylinder.center.y
			+ p * obj->u.cylinder.axis.y);
	norm->z = ray->obj.pos.z - (obj->u.cylinder.center.z
			+ p * obj->u.cylinder.axis.z);
}

void	rtv1_shade_cylinder(t_obj *obj, t_ray *ray)
{
	t_fvec3d	norm;
	double		length;
	double		u;
	double		shade;

	if ((u = sqrt(pow(obj->u.cylinder.axis.x, 2)
					+ pow(obj->u.cylinder.axis.y, 2)
					+ pow(obj->u.cylinder.axis.z, 2))) == 0)
		return ;
	rtv1_shade_cylinder_calc_norm(u, ray, obj, &norm);
	length = sqrt(norm.x * norm.x + norm.y * norm.y + norm.z * norm.z);
	if (length == 0)
		return ;
	norm.x = norm.x / length;
	norm.y = norm.y / length;
	norm.z = norm.z / length;
	shade = norm.x * ray->obj.dir.x + norm.y * ray->obj.dir.y
		+ norm.z * ray->obj.dir.z;
	if (shade <= 0)
		shade = 0;
	ray->shade = shade;
}
