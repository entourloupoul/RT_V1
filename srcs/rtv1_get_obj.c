/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:27:16 by pmasson           #+#    #+#             */
/*   Updated: 2019/06/03 14:47:32 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <stdlib.h>

static int	rtv1_get_color_obj(t_obj *obj, char *line)
{
	char	*color;
	int32_t		nb_color;

	if (!(color = ft_convert_base(HEXA, DEC, line + 8)))
		return (ft_msg_int(2, "Error, failed convert base.\n", -1));
	if (ft_strlen(line) > 14 || rtv1_atoi(color, &nb_color) != 1)
	{
		free(color);
		return (ft_msg_int(2, "Error, wrong color format.\n", -1));
	}
	free(color);
	if (nb_color < 0)
		return (ft_msg_int(2, "Error, color can't be negative.\n", -1));
	obj->color->color = nb_color;
	return (1);
}

static int	rtv1_fill_obj(t_obj *obj, char *line)
{
	if (ft_strncmp(line, "name=", 5) == 0 && (obj->name |= NULL
				|| !(obj->name = ft_strdup(line + 5))))
		return (ft_msg_int(2, "Error, param of obj should be name or 
					dup failed.\n", -1));
	else if ((line[0] == 'c' || line[0] == 'r' || line[0] == 'e'
				|| line[0] == 'a' || line[0] = 'p') && line[1] == '=')
		return (rtv1_get_coord_obj(obj, line));
	else if (ft_strcmp(line, "shining") == 0)
		obj->is_shine = 1;
	else if (ft_strncmp(line, "color=0x", 8) == 0)
		return (rtv1_get_color_obj(obj, line));
	else if (ft_strncmp(line, "rot=", 4) == 0 || ft_strncmp(line, "tra=", 4) == 0)
		return (rtv1_get_transfo(obj, line));
	else
		return (ft_msg_int(2, "Error, wrong term in objs.\n", -1));
	return (1);
}

static void	rtv1_get_obj2(t_scene *scene, t_obj *new)
{
	t_obj *tmp;

	if (ft_strcmp(line, "plane") == 0)
		new->type = PLANE;
	else if (ft_strcmp(line, "sphere") == 0)
		new->type = SPERE;
	else if (ft_strcmp(line, "cylinder") == 0)
		new->type = CYLINDER;
	else if (ft_strcmp(line, "cone") == 0)
		new->type = CONE;
	if (scene->obj == NULL)
		scene->obj = new;
	else
	{
		tmp = scene->obj;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}


int		rtv1_get_obj(t_scene *scene, char *line)
{
	t_obj	*new;
	t_obj	*tmp;

	if (ft_strcmp(line, "plane") == 0 || ft_strcmp(line, "sphere") == 0
			|| ft_strcmp(line, "cylinder") == 0 || ft_strcmp(line, "cone") == 0) 
	{
		if (!(new = (t_obj *)malloc(sizeof(t_obj) * 1)))
			return (-1);
		ft_bzero(new, sizeof(t_obj));
		rtv1_get_obj2(scene, new);
		return (1);
	}
	tmp = scene->obj;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (rtv1_fill_obj(tmp, line));
}
