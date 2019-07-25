/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_coord_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:32:24 by pmasson           #+#    #+#             */
/*   Updated: 2019/07/25 15:31:24 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

static int	rtv1_get_rp_obj(t_obj *obj, char **nb)
{
	int	i;
	double vec;
	double	*save;	

	vec = 0;
	i = 0;
	while (nb[i] != NULL && i < 3 && rtv1_atoi(nb[i], &vec) == 1)
		i++;
	if (i != 1 || (i == 1 && nb[i] != NULL))
		return (ft_msg_int(2, "Error, a or c wrong.\n", -1));
	if (obj->type == SPHERE)
		save = &(obj->u.sphere.radius);
	if (obj->type == CYLINDER)
		save = &(obj->u.cylinder.radius);
	if (obj->type == CONE)
		save = &(obj->u.cone.phy);
	*save = vec;
	return (1);
}

static int	rtv1_get_ac_obj(t_obj *obj, char **nb, char c)
{
	int	i;
	double vec[3];
	t_fvec3d	*save;	

	ft_bzero(vec, sizeof(double) * 3);
	i = 0;
	while (nb[i] != NULL && i < 3 && rtv1_atoi(nb[i], &vec[i]) == 1)
		i++;
	if (i != 3 || (i == 3 && nb[i] != NULL))
		return (ft_msg_int(2, "Error, a or c wrong.\n", -1));
	if (obj->type == SPHERE)
		save = &(obj->u.sphere.center);
	if (obj->type == CYLINDER)
		save = c == 'c' ? &(obj->u.cylinder.center) : &(obj->u.cylinder.axis);
	if (obj->type == CONE)
		save = c == 'c' ? &(obj->u.cone.center) : &(obj->u.cone.axis);
	save->x = vec[0];
	save->y = vec[1];
	save->z = vec[2];
	return (1);
}


static int	rtv1_get_scc_coord(t_obj *obj, char **nb, char *line)
{
	int	ret;

	ret = 0;
	if (obj->type == SPHERE && line[0] != 'c' && line[0] != 'r')
		return (ft_msg_int(2, "Error, wrong type of coord in sphere.\n", -1));
	if (obj->type == CYLINDER && line[0] != 'c' && line[0] != 'a'
			&& line[0] != 'r')
		return (ft_msg_int(2, "Error, wrong type of coord in cyl.\n", -1));
	if (obj->type == CONE && line[0] != 'c' && line[0] != 'a' && line[0] != 'p')
		return (ft_msg_int(2, "Error, wrong type of coord in cone.\n", -1));
	if (line[0] == 'c' || line[0] == 'a')
		ret = rtv1_get_ac_obj(obj, nb, line[0]);
	if (line[0] == 'r' || line[0] == 'p')
		ret = rtv1_get_rp_obj(obj, nb);
	return (1);
}

static int	rtv1_get_plane_coord(t_obj *obj, char **nb, char *line)
{
	double	eq[4];
	int		i;
	double	length;

	if (line[0] != 'e')
		return (ft_msg_int(2, "Error, no equation in plane.\n", -1));
	ft_bzero(eq, sizeof(double) * 4);
	i = 0;
	while (nb[i] != NULL && i < 4 && rtv1_atoi(nb[i], &eq[i]) == 1)
		i++;
	if (i != 4 || (i == 4 && nb[i] != NULL))
		return (ft_msg_int(2, "Error, plane equation wrong.\n", -1));
	obj->u.plane.equation.x = eq[0];
	obj->u.plane.equation.y = eq[1];
	obj->u.plane.equation.z = eq[2];
	obj->u.plane.constant = eq[3];
	length = sqrt(eq[0] * eq[0] + eq[1] * eq[1] + eq[2] * eq[2]);
	if (length == 0)
		return (1);
	obj->u.plane.norm.x = eq[0] / length;
	obj->u.plane.norm.y = eq[1] / length;
	obj->u.plane.norm.z = eq[2] / length;
	return (1);
}

int	rtv1_get_coord_obj(t_obj *obj, char *line)
{
	char	**nb;
	int		ret;

	ret = 0;
	if (!(nb = ft_strsplit(line + 2, ',')))
		return (ft_msg_int(2, "Error, failed split obj.\n", -1));
	if (obj->type == PLANE)
		ret = rtv1_get_plane_coord(obj, nb, line);
	else
		ret = rtv1_get_scc_coord(obj, nb, line);
	rtv1_free_tab(nb);
	if (ret < 0)
		return (-1);
	return (1);
}
