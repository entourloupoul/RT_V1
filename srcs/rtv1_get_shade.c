/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_shade.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:56:40 by pmasson           #+#    #+#             */
/*   Updated: 2019/08/12 19:02:44 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>
#include <stdio.h>
static int	rtv1_check_plane_side(t_rt *rt, t_obj *obj)
{
	double	a;
	double	b;

	/* si return 1 la lumiere esr de l'autre cote du plan, sinon non*/
	a = -obj->u.plane.constant - obj->u.plane.equation.x * rt->cam.pos.x
		- obj->u.plane.equation.y * rt->cam.pos.y - obj->u.plane.equation.z
		* rt->cam.pos.z;
	b = -obj->u.plane.constant - obj->u.plane.equation.x * rt->lights->pos.x
		- obj->u.plane.equation.y * rt->lights->pos.y
		- obj->u.plane.equation.z * rt->lights->pos.z;
	if ((a >= 0 && b >= 0) || (a <= 0 && b <= 0))
		return (-1);
	return (1);
}

static void	rtv1_shade_plane(t_rt *rt, t_obj *obj, t_ray *ray)
{
	ray->shade = obj->u.plane.norm.x * ray->obj.dir.x + obj->u.plane.norm.y
		* ray->obj.dir.y + obj->u.plane.norm.z * ray->obj.dir.z;
	if (ray->shade <= 0)
	{
		if (rtv1_check_plane_side(rt, obj) > 0)
			ray->shade = 0;
		else
		{
			obj->u.plane.norm.x = -obj->u.plane.norm.x;
			obj->u.plane.norm.y = -obj->u.plane.norm.y;
			obj->u.plane.norm.z = -obj->u.plane.norm.z;
			ray->shade = obj->u.plane.norm.x * ray->obj.dir.x
				+ obj->u.plane.norm.y * ray->obj.dir.y
				+ obj->u.plane.norm.z * ray->obj.dir.z;
		}
	}
	return;
}

static void	rtv1_shade_sphere(t_obj *obj, t_ray *ray)
{
	t_fvec3d	norm;
	double	length;

	norm.x = -obj->u.sphere.center.x + ray->obj.pos.x;
	norm.y = -obj->u.sphere.center.y + ray->obj.pos.y;
	norm.z = -obj->u.sphere.center.z + ray->obj.pos.z;
	length = sqrt(norm.x * norm.x + norm.y * norm.y + norm.z * norm.z);
	if (length == 0)
		return ;
	norm.x = norm.x / length;
	norm.y = norm.y / length;
	norm.z = norm.z / length;
	ray->shade = norm.x * ray->obj.dir.x + norm.y * ray->obj.dir.y
		+ norm.z * ray->obj.dir.z;
	//printf("shade:%f\n", ray->shade);
	if (ray->shade <= 0)
		ray->shade = 0;
}

/*
//on cherche le point c ten que ac perpendiculaire a bc (a point du ray, b centre du cyl)
*/

static void	rtv1_shade_cylinder(t_obj *obj, t_ray *ray)
{
	t_fvec3d	norm;
	double	length;
	double	u;

	if ((u = sqrt(pow(obj->u.cylinder.axis.x, 2)
					+ pow(obj->u.cylinder.axis.y, 2)
					+ pow(obj->u.cylinder.axis.z, 2))) == 0)
		return ;
	length = (obj->u.cylinder.axis.x * (ray->obj.pos.x
			- obj->u.cylinder.center.x) + obj->u.cylinder.axis.y
			* (ray->obj.pos.y - obj->u.cylinder.center.y)
			+ obj->u.cylinder.axis.z * (ray->obj.pos.z
			- obj->u.cylinder.center.z)) / u;
	norm.x = ray->obj.pos.x - (obj->u.cylinder.center.x
			+ length * obj->u.cylinder.axis.x);
	norm.y = ray->obj.pos.y - (obj->u.cylinder.center.y
			+ length * obj->u.cylinder.axis.y);
	norm.z = ray->obj.pos.z - (obj->u.cylinder.center.z
			+ length * obj->u.cylinder.axis.z);
	length = sqrt(norm.x * norm.x + norm.y * norm.y + norm.z * norm.z);
	if (length == 0)
		return ;
	norm.x = norm.x / length;
	norm.y = norm.y / length;
	norm.z = norm.z / length;
	ray->shade = norm.x * ray->obj.dir.x + norm.y * ray->obj.dir.y
		+ norm.z * ray->obj.dir.z;
	if (ray->shade <= 0)
		ray->shade = 0;
}


int	rtv1_get_shade(t_rt *rt, t_obj *obj, t_ray *ray, t_obj *save)
{
	if (obj == NULL)
		return (1);
	ray->ambient = AMBIENT;
	//printf("amb:%f\n", ray->ambient);	
	if (obj->type == PLANE)
		rtv1_shade_plane(rt, obj, ray);
	if (obj->type == SPHERE)
		rtv1_shade_sphere(obj, ray);
	if (obj->type == CYLINDER)
		rtv1_shade_cylinder(obj, ray);
	if (ray->dist >= 0)
	{
//		puts("ici0");
		if (save->type == PLANE)
		{
			if (rtv1_check_plane_side(rt, save) > 0)
			{
//				puts("coucou");
				ray->shade = 0;
			}
		}
		else
		{
//			puts("not ok");
			ray->shade = 0;
		}
	}
	ray->color.p.r = (int8_t)round((double)ray->color.p.r
				* (ray->ambient + (1 - ray->ambient) * ray->shade));
	ray->color.p.g = (int8_t)round((double)ray->color.p.g
				* (ray->ambient + (1 - ray->ambient) * ray->shade));
	ray->color.p.b = (int8_t)round((double)ray->color.p.b
				* (ray->ambient + (1 - ray->ambient) * ray->shade));
	return (1);
}



