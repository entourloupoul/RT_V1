/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_check_inter_plane.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 18:26:19 by pmasson           #+#    #+#             */
/*   Updated: 2019/05/29 21:36:10 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	rtv1_check_inter_plane(t_obj *obj, t_ray *ray)
{
	double	t;
	double	den;
	double	num;

	den = (double)obj->data[0] * ray->vec[0] + (double)obj->data[1]
		* ray->vec[1] + (double)obj->data[2] * ray->vec[2];
	if (den == 0)
		return (-1);
	num = -(double)obj->data[3]
		- (double)obj->data[0] * ray->source[0]
		- (double)obj->data[1] * ray->source[1]
		- (double)obj->data[2] * ray->source[2];
	t = num / den;
	return (t);
}
