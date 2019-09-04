/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_check_plane_side.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:05:09 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/04 16:23:34 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**return -1 if points are on the same side of the plane
*/

int	rtv1_check_plane_side(t_fvec3d pointa, t_plane plane, t_fvec3d pointb)
{
	double	a;
	double	b;

	a = -plane.constant - plane.equation.x * pointa.x
		- plane.equation.y * pointa.y - plane.equation.z
		* pointa.z;
	b = -plane.constant - plane.equation.x * pointb.x
		- plane.equation.y * pointb.y
		- plane.equation.z * pointb.z;
	if ((a >= 0 && b >= 0) || (a <= 0 && b <= 0))
		return (-1);
	return (1);
}
