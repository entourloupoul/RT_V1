/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_create_final.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 16:30:17 by pmasson           #+#    #+#             */
/*   Updated: 2019/06/03 14:43:37 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <math.h>
static int	rtv1_set_fov(t_cam *cam)
{
	double	ratio;

	if (cam->width <= 0 || cam->length <= 0)
		return (ft_msg_int(2, "Error, width/length can't be 0 or less.\n", -1));
	ratio = (double)cam->length / (double)cam->width;
	cam->n = 1;
	cam->l = 2 * tan(45 * M_PI / 180);
	cam->r = cam->l / ratio;
	return (1);
}

static int	rtv1_calc_surf2(t_scene *scene, t_cam *cam1, int x, int y, t_ray *ray)
{
/*	ray->vec[0] = -cam1->w[0]
		+ cam1->l * ((double)x / (double)cam1->length - 0.5) * cam1->u[0]
		+ cam1->r * (0.5 - (double)y / (double)cam1->width) * cam1->v[0];
	ray->vec[1] = -cam1->w[1]
		+ cam1->l * ((double)x / (double)cam1->length - 0.5) * cam1->u[1]
		+ cam1->r * (0.5 - (double)y / (double)cam1->width) * cam1->v[1];
	ray->vec[2] = -cam1->w[2]
		+ cam1->l * ((double)x / (double)cam1->length - 0.5) * cam1->u[2]
		+ cam1->r * (0.5 - (double)y / (double)cam1->width) * cam1->v[2];
*/	if (rtv1_get_color(scene, ray) <= 0)
		return (ft_msg_int(2, "No, color here.\n", 0));
	*((unsigned int *)(scene->picture->surface->pixels
				+ 4 * x + 4 * y * cam1->length)) = (unsigned int)ray->color;
	return (1);
}

static int	rtv1_calc_surf(t_scene *scene, t_cam *cam1)
{
	int	x;
	int	y;
	t_ray	ray[1];

	ft_bzero(ray, sizeof(t_ray));
	ray->source[0] = (double)scene->cam->coord[0];
	ray->source[1] = (double)scene->cam->coord[1];
	ray->source[2] = (double)scene->cam->coord[2];
	x = 0;
	y = 0;
	while (y < scene->cam->width)
	{
		x = 0;
		ray->vec[0] = -cam1->w[0]
			+ cam1->l * ((double)x / (double)cam1->length - 0.5) * cam1->u[0]
			+ cam1->r * (0.5 - (double)y / (double)cam1->width) * cam1->v[0];
		ray->vec[1] = -cam1->w[1]
			+ cam1->l * ((double)x / (double)cam1->length - 0.5) * cam1->u[1]
			+ cam1->r * (0.5 - (double)y / (double)cam1->width) * cam1->v[1];
		ray->vec[2] = -cam1->w[2]
			+ cam1->l * ((double)x / (double)cam1->length - 0.5) * cam1->u[2]
			+ cam1->r * (0.5 - (double)y / (double)cam1->width) * cam1->v[2];
		while (x < scene->cam->length)
		{
			rtv1_calc_surf2(scene, scene->cam, x, y, ray);
			ray->vec[0] = ray->vec[0] + cam1->l * ((double)1 / (double)cam1->length) * cam1->u[0];
			ray->vec[1] = ray->vec[1] + cam1->l * ((double)1 / (double)cam1->length) * cam1->u[1];
			ray->vec[2] = ray->vec[2] + cam1->l * ((double)1 / (double)cam1->length) * cam1->u[2];
			x++;
		}
		y++;
	}
	return (0);
}


int	rtv1_create_final(t_scene *scene)
{
	if (rtv1_set_cam_vec(scene->cam) < 0)
		return (-1);
	if (rtv1_set_fov(scene->cam) < 0)
		return (-1);
	if (rtv1_calc_surf(scene, scene->cam) < 0)
		return (-1);
	return (1);
}
