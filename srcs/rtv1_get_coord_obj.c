/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_coord_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:32:24 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/04 16:17:31 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

static int	rtv1_get_radius_angle_value(t_obj *obj, char **nb, char *line)
{
	double	value;

	value = 0;
	if (nb[0] == NULL || rtv1_atoi(nb[0], &value) != 1 || nb[1] != NULL)
		return (ft_msg_int(2, "Error in radius angle 1.\n", -1));
	if (ft_strncmp(line, "radius=", 7) == 0 && obj->type == SPHERE)
		obj->u.sphere.radius = value;
	else if (ft_strncmp(line, "radius=", 7) == 0 && obj->type == CYLINDER)
		obj->u.cylinder.radius = value;
	else if (ft_strncmp(line, "angle=", 6) == 0 && obj->type == CONE)
	{
		if (value >= 90)
			return (ft_msg_int(2, "Error, angle must be < 90 deg.\n", -1));
		obj->u.cone.angle = value;
	}
	else
		return (ft_msg_int(2, "Error, wrong association radius angle.\n", -1));
	return (1);
}

static int	rtv1_get_rot_pos_coord(t_obj *obj, char **nb, char *line)
{
	int		i;
	double	val[3];

	val[0] = 0;
	val[1] = 0;
	val[2] = 0;
	i = 0;
	while (nb[i] != NULL && i < 3 && rtv1_atoi(nb[i], &val[i]) == 1)
		i++;
	if (i != 3 || (i == 3 && nb[i] != NULL))
		return (ft_msg_int(2, "Error, wrong term in pos rot obj.\n", -1));
	if (ft_strncmp(line, "pos=", 4) == 0)
	{
		obj->pos.x = val[0];
		obj->pos.y = val[1];
		obj->pos.z = val[2];
	}
	else
	{
		obj->rot.x = val[0];
		obj->rot.y = val[1];
		obj->rot.z = val[2];
	}
	return (1);
}

int			rtv1_get_coord_obj(t_obj *obj, char *line)
{
	char	**nb;
	int		ret;
	int		shift;

	shift = 4;
	shift = ft_strncmp(line, "radius=", 7) == 0 ? 7 : shift;
	shift = ft_strncmp(line, "angle=", 6) == 0 ? 6 : shift;
	ret = 0;
	if (!(nb = ft_strsplit(line + shift, ',')))
		return (ft_msg_int(2, "Error, failed split obj.\n", -1));
	if (ft_strncmp(line, "rot=", 4) == 0 || ft_strncmp(line, "pos=", 4) == 0)
		ret = rtv1_get_rot_pos_coord(obj, nb, line);
	else
		ret = rtv1_get_radius_angle_value(obj, nb, line);
	rtv1_free_tab(nb);
	if (ret < 0)
		return (-1);
	return (1);
}
