/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:23:15 by pmasson           #+#    #+#             */
/*   Updated: 2019/07/24 13:48:03 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <stdio.h>
static double	rtv1_check_inter(t_obj *obj, t_ray *ray, int shift)
{
	double t;

	t = -1;
	if (obj->type == 1)
		t = rtv1_check_inter_plane(obj, ray, shift);
	if (obj->type == 2)
		t = rtv1_check_inter_sphere(obj, ray, shift);
	if (obj->type == 3)
		t = rtv1_check_inter_cylinder(obj, ray, shift);
	return (t);
}

static int	rtv1_modif_ray(t_scene *scene, t_ray *ray, double t)
{
	double	length;

	if (scene->light != NULL)
	{
		ray->source[3] = ray->source[0] + t * ray->vec[0];
		ray->source[4] = ray->source[1] + t * ray->vec[1];
		ray->source[5] = ray->source[2] + t * ray->vec[2];
		ray->vec[3] = scene->light->coord[0] - ray->source[3];
		ray->vec[4] = scene->light->coord[1] - ray->source[4];
		ray->vec[5] = scene->light->coord[2] - ray->source[5];
		length = sqrt(ray->vec[3] * ray->vec[3] + ray->vec[4] * ray->vec[4]
				+ ray->vec[5] * ray->vec[5]);
		if (length == 0)
			return (ft_msg_int(2, "length = 0 rtv1_modif_ray.\n", 0));
		ray->vec[3] = ray->vec[3] / length;
		ray->vec[4] = ray->vec[4] / length;
		ray->vec[5] = ray->vec[5] / length;
	}
	return (1);
}

static int	rtv1_get_color2(t_scene *scene, t_obj *obj,
		t_ray *ray, double t)
{
	t_obj	*tmp;
	t_obj	*save;
	double	ret;

	if (t < 0)
		return (0);
	ray->color = obj->color;
	if (scene->light == NULL)
		return (1);
	rtv1_modif_ray(scene, ray, t);
	save = NULL;
	t = -1;
	tmp = scene->obj;
	while (tmp->next != NULL)
	{
		if ((ret = rtv1_check_inter(tmp, ray, 3)) >= 0)
		{
			if (tmp != obj && (t < 0 || (t > 0 && ret < t)))
			{
				t = ret;
				save = tmp;
			}
		}
		tmp = tmp->next;
	}
	ray->t = t;
	return (rtv1_get_shade(scene, obj, ray, save));
}

int	rtv1_get_color(t_scene *scene, t_ray *ray)
{
	t_obj	*tmp;
	t_obj	*save;
	double	t;
	double	ret;

	t = -1;
	save = NULL;
	tmp = scene->obj;
	while (tmp != NULL)
	{
		if ((ret = rtv1_check_inter(tmp, ray, 0)) >= 0)
		{
			if (t < 0 || (t > 0 && ret < t))
			{
				t = ret;
				save = tmp;
			}
		}
		tmp = tmp->next;
	}
	return (rtv1_get_color2(scene, save, ray, t));
}
