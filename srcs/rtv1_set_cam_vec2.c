/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_set_cam_vec2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:35:46 by pmasson           #+#    #+#             */
/*   Updated: 2019/05/24 17:28:09 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <rtv1.h>
#include <stdio.h>
int	rtv1_set_cam_vec2(t_cam *cam)
{
	double	norm;

	if (cam->u[0] != 0)
	{
		cam->v[2] = 1;
		cam->v[1] = -cam->w[2]
			/ (cam->w[1] - cam->w[0] * cam->u[1] / cam->u[0]);
		cam->v[0] = -cam->u[1] * cam->v[1] / cam->u[0];
	}
	else
		return (1);
	norm = sqrt(pow(cam->v[0], 2) + pow(cam->v[1], 2) + pow(cam->v[2], 2));
	cam->v[0] = cam->v[0] / norm;
	cam->v[1] = cam->v[1] / norm;
	cam->v[2] = cam->v[2] / norm;
	//printf("u:%f,%f,%f\nv:%f,%f,%f\nw:%f,%f,%f\n", cam->u[0], cam->u[1], cam->u[2], cam->v[0], cam->v[1], cam->v[2], cam->w[0], cam->w[1], cam->w[2]);
	return (1);
}

