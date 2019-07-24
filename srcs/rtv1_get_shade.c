/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_shade.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:56:40 by pmasson           #+#    #+#             */
/*   Updated: 2019/07/24 14:00:55 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>
#include <stdio.h>
static int	rtv1_check_plane_side(t_scene *scene, t_ray *ray, t_obj *obj)
{
	double	a;
	double	b;

	(void)ray;
	/* si return 1 la lumiere esr de l'autre cote du plan, sinon non*/
	a = -obj->data[3] - obj->data[0] * scene->cam->coord[0]
		- obj->data[1] * scene->cam->coord[1] - obj->data[2] * scene->cam->coord[2];
	b = -obj->data[3] - obj->data[0] * scene->light->coord[0]
		- obj->data[1] * scene->light->coord[1]
		- obj->data[2] * scene->light->coord[2];
	if ((a >= 0 && b >= 0) || (a <= 0 && b <= 0))
		return (-1);
	return (1);
}

static void	rtv1_shade_plane(t_scene *scene, t_obj *obj, t_ray *ray)
{
//	double	norm[3];
//	double	length;

	(void)scene;
/*	norm[0] = obj->data[0];
	norm[1] = obj->data[1];
	norm[2] = obj->data[2];
	length = sqrt(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
	if (length == 0)
		return ;
	norm[0] = norm[0] / length;
	norm[1] = norm[1] / length;
	norm[2] = norm[2] / length;
*/	ray->shade = obj->norm[0] * ray->vec[3] + obj->norm[1] * ray->vec[4]
		+ obj->norm[2] * ray->vec[5];
	if (ray->shade <= 0)
	{
		if (rtv1_check_plane_side(scene, ray, obj) > 0)
		{
			//puts("kl");
			ray->shade = 0;
		}
		else
		{
			obj->norm[0] = -obj->norm[0];
			obj->norm[1] = -obj->norm[1];
			obj->norm[2] = -obj->norm[2];
			ray->shade = obj->norm[0] * ray->vec[3] + obj->norm[1] * ray->vec[4]
				+ obj->norm[2] * ray->vec[5];
		}
	}
	return;
}

static void	rtv1_shade_sphere(t_scene *scene, t_obj *obj, t_ray *ray)
{
	double	norm[3];
	double	length;

	(void)scene;
	norm[0] = -(double)obj->data[0] + ray->source[3];
	norm[1] = -(double)obj->data[1] + ray->source[4];
	norm[2] = -(double)obj->data[2] + ray->source[5];
	length = sqrt(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
	if (length == 0)
		return ;
	norm[0] = norm[0] / length;
	norm[1] = norm[1] / length;
	norm[2] = norm[2] / length;
	ray->shade = norm[0] * ray->vec[3] + norm[1] * ray->vec[4]
		+ norm[2] * ray->vec[5];
	if (ray->shade <= 0)
		ray->shade = 0;
}

/*
//on cherche le point c ten que ac perpendiculaire a bc (a point du ray, b centre du cyl)
*/

static void	rtv1_shade_cylinder(t_scene *scene, t_obj *obj, t_ray *ray)
{
	double	norm[3];
	double	length;
	double	u;

	(void)scene;
	if ((u = sqrt(pow((double)obj->data[4], 2) + pow((double)obj->data[5], 2)
					+ pow((double)obj->data[6], 2))) == 0)
		return ;
	length = ((double)obj->data[4] * (ray->source[3] - (double)obj->data[0])
			+ (double)obj->data[5] * (ray->source[4] - (double)obj->data[1])
			+ (double)obj->data[6] * (ray->source[5] - (double)obj->data[2]))
			/ u;
	norm[0] = ray->source[3] - ((double)obj->data[0] + length * (double)obj->data[4]);
	norm[1] = ray->source[4] - ((double)obj->data[1] + length * (double)obj->data[5]);
	norm[2] = ray->source[5] - ((double)obj->data[2] + length * (double)obj->data[6]);
	length = sqrt(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
	if (length == 0)
		return ;
	norm[0] = norm[0] / length;
	norm[1] = norm[1] / length;
	norm[2] = norm[2] / length;
	ray->shade = norm[0] * ray->vec[3] + norm[1] * ray->vec[4]
		+ norm[2] * ray->vec[5];
	if (ray->shade <= 0)
		ray->shade = 0;
}


int	rtv1_get_shade(t_scene *scene, t_obj *obj, t_ray *ray, t_obj *save)
{
	ray->ambient = 0.2;
	if (obj->type == 2)
		rtv1_shade_sphere(scene, obj, ray);
	if (obj->type == 3)
		rtv1_shade_cylinder(scene, obj, ray);
	else if (obj->type == 1)
		rtv1_shade_plane(scene, obj, ray);
	if (ray->t >= 0)
	{
//		puts("ici0");
		if (save->type == 1)
		{
			if (rtv1_check_plane_side(scene, ray, save) > 0)
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
	ray->color = ((int)round(((ray->color & 16711680) / 65536) * (ray->ambient
		+ (1 - ray->ambient) * ray->shade) * 65536) & 16711680)
		+ ((int)round(((ray->color & 65280) / 256) * (ray->ambient 
		+ (1 - ray->ambient) * ray->shade) * 256) & 65280)
		+ ((int)round((ray->color & 255) * (ray->ambient + (1 - ray->ambient)
		* ray->shade)) & 255);
	return (1);
}



