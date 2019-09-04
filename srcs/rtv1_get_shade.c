/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_shade.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:56:40 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/04 16:08:48 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	rtv1_shade_plane(t_light *light, t_obj *obj, t_ray *ray)
{
	double	shade;

	shade = obj->u.plane.norm.x * ray->obj.dir.x + obj->u.plane.norm.y
		* ray->obj.dir.y + obj->u.plane.norm.z * ray->obj.dir.z;
	if (shade <= 0)
		shade = -shade;
	if (rtv1_check_plane_side(light->pos, obj->u.plane, ray->cam.pos) > 0)
		shade = 0;
	ray->shade = shade;
}

static void	rtv1_shade_sphere(t_obj *obj, t_ray *ray)
{
	t_fvec3d	norm;
	double		length;
	double		shade;

	norm.x = -obj->u.sphere.center.x + ray->obj.pos.x;
	norm.y = -obj->u.sphere.center.y + ray->obj.pos.y;
	norm.z = -obj->u.sphere.center.z + ray->obj.pos.z;
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

int			rtv1_get_shade(t_light *light, t_obj *obj, t_ray *ray, t_obj *save)
{
	if (obj == NULL)
		return (1);
	ray->ambient = AMBIENT;
	if (obj->type == PLANE)
		rtv1_shade_plane(light, obj, ray);
	if (obj->type == SPHERE)
		rtv1_shade_sphere(obj, ray);
	if (obj->type == CYLINDER)
		rtv1_shade_cylinder(obj, ray);
	if (obj->type == CONE)
		rtv1_shade_cone(obj, ray);
	if (ray->dist >= 0 && ray->shadows == 1)
	{
		if (save != NULL && save->type == PLANE)
		{
			if (rtv1_check_plane_side(light->pos,
						save->u.plane, ray->obj.pos) > 0)
				ray->shade = 0;
		}
		else if (save != NULL)
			ray->shade = 0;
	}
	return (1);
}
