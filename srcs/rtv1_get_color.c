/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:23:15 by pmasson           #+#    #+#             */
/*   Updated: 2019/06/03 09:41:32 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>
static double	rtv1_check_inter(t_obj *obj, t_ray *ray)
{
	double t;

	t = -1;
	if (obj->type == 1)
		t = rtv1_check_inter_plane(obj, ray);
	if (obj->type == 2)
		t = rtv1_check_inter_sphere(obj, ray);
	return (t);
}

static void	rtv1_modif_ray(t_scene *scene, t_ray *ray, double t)
{
	if (scene->light != NULL)
	{
		ray->source[0] = ray->source[0] + t * ray->vec[0];
		ray->source[1] = ray->source[1] + t * ray->vec[1];
		ray->source[2] = ray->source[2] + t * ray->vec[2];
		ray->vec[0] = scene->light->coord[0] - ray->source[0];
		ray->vec[1] = scene->light->coord[1] - ray->source[1];
		ray->vec[2] = scene->light->coord[2] - ray->source[2];
	}
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
		if ((ret = rtv1_check_inter(tmp, ray)) >= 0)
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
		if ((ret = rtv1_check_inter(tmp, ray)) >= 0)
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
