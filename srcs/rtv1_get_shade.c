/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_shade.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:56:40 by pmasson           #+#    #+#             */
/*   Updated: 2019/06/03 09:41:40 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <math.h>
#include <stdio.h>
static int	rtv1_check_plane_side(t_scene *scene, t_ray *ray, t_obj *obj)
{
	double	a;
	double	b;

	/* si return 1 la lumiere esr de l'autre cote du plan, sinon non*/
	a = -obj->data[3] - obj->data[0] * ray->source[0]
		- obj->data[1] * ray->source[1] - obj->data[2] * ray->source[2];
	b = -obj->data[3] - obj->data[0] * scene->light->coord[0]
		- obj->data[1] * scene->light->coord[1]
		- obj->data[2] * scene->light->coord[2];
	if ((a >= 0 && b >= 0) || (a <= 0 && b <= 0))
		return (-1);
	return (1);
}

static void	rtv1_shade_sphere(t_scene *scene, t_obj *obj, t_ray *ray)
{
	double	norm[3];
	double	length;

	(void)scene;
	norm[0] = -(double)obj->data[0] + ray->source[0];
	norm[1] = -(double)obj->data[1] + ray->source[1];
	norm[2] = -(double)obj->data[2] + ray->source[2];
	length = sqrt(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
	if (length == 0)
		return ;
	norm[0] = norm[0] / length;
	norm[1] = norm[1] / length;
	norm[2] = norm[2] / length;
	length = sqrt(ray->vec[0] * ray->vec[0] + ray->vec[1] * ray->vec[1]
			+ ray->vec[2] * ray->vec[2]);
	if (length == 0)
		return ;
	ray->vec[0] = ray->vec[0] / length;
	ray->vec[1] = ray->vec[1] / length;
	ray->vec[2] = ray->vec[2] / length;
	ray->shade = norm[0] * ray->vec[0] + norm[1] * ray->vec[1]
		+ norm[2] * ray->vec[2];
	if (ray->shade <= 0)
		ray->shade = 0;
	if (ray->shade > 1)
		printf("shade:%f\n", ray->shade);
}


int	rtv1_get_shade(t_scene *scene, t_obj *obj, t_ray *ray, t_obj *save)
{
	ray->ambient = 0.2;
	if (obj->type == 2)
		rtv1_shade_sphere(scene, obj, ray);
	if (obj->type == 1)
		ray->shade = 1;
	if (ray->t >= 0)
	{
		if (save->type != 1)
		{
			if (rtv1_check_plane_side(scene, ray, save) > 0)
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



