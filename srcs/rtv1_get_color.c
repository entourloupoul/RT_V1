/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:23:15 by pmasson           #+#    #+#             */
/*   Updated: 2019/08/12 19:02:46 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <stdio.h>
static double	rtv1_check_inter(t_obj *obj, t_geo source)
{
	double t;

	t = -1;
	if (obj->type == PLANE)
		t = rtv1_check_inter_plane(obj, source);
	if (obj->type == SPHERE)
		t = rtv1_check_inter_sphere(obj, source);
	if (obj->type == CYLINDER)
		t = rtv1_check_inter_cylinder(obj, source);
	return (t);
}

static int	rtv1_modif_ray(t_ray *ray, double t, t_light *light)
{
	double	length;

	if (light != NULL)
	{
		ray->obj.pos.x = ray->cam.pos.x + t * ray->cam.dir.x;
		ray->obj.pos.y = ray->cam.pos.y + t * ray->cam.dir.y;
		ray->obj.pos.z = ray->cam.pos.z + t * ray->cam.dir.z;
		ray->obj.dir.x = light->pos.x - ray->obj.pos.x;
		ray->obj.dir.y = light->pos.y - ray->obj.pos.y;
		ray->obj.dir.z = light->pos.z - ray->obj.pos.z;
		length = sqrt(pow(ray->obj.dir.x, 2) + pow(ray->obj.dir.y, 2)
				+ pow(ray->obj.dir.z, 2));
		if (length == 0)
			return (ft_msg_int(2, "length = 0 rtv1_modif_ray.\n", 0));
		ray->obj.dir.x = ray->obj.dir.x / length;
		ray->obj.dir.y = ray->obj.dir.y / length;
		ray->obj.dir.z = ray->obj.dir.z / length;
	}
	return (1);
}

static int	rtv1_get_color2(t_rt *rt, t_obj *obj,
		t_ray *ray, double t)
{
	t_obj	*tmp;
	t_obj	*save;
	double	ret;

	if (t < 0)
		return (0);
	ray->color.color = obj->color.color;
	if (rt->lights == NULL)
		return (1);
	rtv1_modif_ray(ray, t, rt->lights);
	save = NULL;
	t = -1;
	tmp = rt->objs;
	while (tmp != NULL && tmp->next != NULL)
	{
		if ((ret = rtv1_check_inter(tmp, ray->obj)) >= 0)
		{
			if (tmp != obj && (t < 0 || (t > 0 && ret < t)))
			{
				t = ret;
				save = tmp;
			}
		}
		tmp = tmp->next;
	}
	ray->dist = t;
	return (rtv1_get_shade(rt, obj, ray, save));
}

int	rtv1_get_color(t_rt *rt, t_ray *ray)
{
	t_obj	*tmp;
	t_obj	*save;
	double	t;
	double	ret;

	t = -1;
	save = NULL;
	tmp = rt->objs;
	while (tmp != NULL)
	{
		if ((ret = rtv1_check_inter(tmp, ray->cam)) >= 0)
		{
			if (t < 0 || (t > 0 && ret < t))
			{
				t = ret;
				save = tmp;
			}
		}
		tmp = tmp->next;
	}
	return (rtv1_get_color2(rt, save, ray, t));
}
