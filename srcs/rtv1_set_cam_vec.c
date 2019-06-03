/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_set_cam_vec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:18:49 by pmasson           #+#    #+#             */
/*   Updated: 2019/05/24 14:11:07 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <math.h>

static int	rtv1_special_coord2(t_cam *cam)
{
	double	a;

	if (cam->coord[1] == 1 || cam->coord[1] == -1)
	{
		a = cam->coord[1];
		cam->u[0] = -a;
		cam->v[2] = 1;
		cam->w[1] = a;
		return (1);
	}
	if (cam->coord[2] == 1 || cam->coord[2] == -1)
	{
		a = cam->coord[2];
		cam->u[0] = 1;
		cam->v[1] = -a;
		cam->w[2] = a;
		return (1);
	}
	return (0);
}

static int	rtv1_special_coord(t_cam *cam)
{
	int	i;
	double	a;

	i = 0;
	while (i < 3)
	{
			cam->u[i] = 0;
			cam->v[i] = 0;
			cam->w[i] = 0;
			i++;
	}
	if (cam->coord[0] == 1 || cam->coord[0] == -1)
	{
		a = cam->coord[0];
		cam->u[1] = a;
		cam->v[2] = 1;
		cam->w[0] = a;
		return (1);
	}
	return (rtv1_special_coord2(cam));
}

static int		rtv1_get_w(t_cam *cam)
{
	double	norm;

	norm = sqrt(pow(cam->coord[0], 2) + pow(cam->coord[1], 2)
			+ pow(cam->coord[2], 2));
	if (norm != 0)
	{
		cam->w[0] = cam->coord[0] / norm;
		cam->w[1] = cam->coord[1] / norm;
		cam->w[2] = cam->coord[2] / norm;
		return (1);
	}
	else
	{
		cam->w[2] = 1;
		cam->v[1] = 1;
		cam->u[0] = 1;
		return (0);
	}
}

static int		rtv1_get_u(t_cam *cam)
{
	double	norm;

	if (cam->w[0] == 0)
	{
		cam->u[0] = cam->w[1] >= 0 ? -1 : 1;
		return (1);
	}
	cam->u[1] = cam->w[0] >= 0 ? -1 : 1;
	if (cam->w[1] == 0)
		return (1);
	cam->u[0] = -cam->w[1] / cam->w[0] * cam->u[1];
	norm = sqrt(pow(cam->u[0], 2) + pow(cam->u[1], 2));
	cam->u[0] = cam->u[0] / norm;
	cam->u[1] = cam->u[1] / norm;
	return (1);
}

int		rtv1_set_cam_vec(t_cam *cam)
{
	if (!(cam->w = (double *)malloc(sizeof(double) * 3)))
		return (-1);
	if (!(cam->u = (double *)malloc(sizeof(double) * 3)))
	{
		free(cam->w);
		cam->w = NULL;
		return (-1);
	}
	if (!(cam->v = (double *)malloc(sizeof(double) * 3)))
	{
		free(cam->w);
		cam->w = NULL;
		free(cam->u);
		cam->u = NULL;
		return (-1);
	}
	if (rtv1_special_coord(cam) == 0)
	{
		if (rtv1_get_w(cam) == 1)
		{
			if (rtv1_get_u(cam) < 0 || rtv1_set_cam_vec2(cam) < 0)
				return (-1);
		}
	}
	return (1);
}
