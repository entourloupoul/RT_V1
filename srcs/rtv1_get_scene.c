/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_scene1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 09:23:14 by pmasson           #+#    #+#             */
/*   Updated: 2019/05/09 14:38:54 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include "libft.h"
#include <stdlib.h>
#include "get_next_line.h"

static int	rtv1_get_cam(t_scene *scene, char **nb, int *i, int shift)
{
	int	ret;

	if (scene->cam == NULL)
	{
		if (!(scene->cam = (t_camera *)malloc(sizeof(t_camera) * 1)))
			return (-1);
		if (!(scene->cam->coord = (int *)malloc(sizeof(int) * 6)))
		{
			free(scene->cam);
			scene->cam = NULL;
			return (-1);
		}
	}
	ret = 1;
	while (ret == 1 && nb[*i] != NULL && *i < 3)
	{
		ret = rtv1_atoi(nb[*i], &scene->cam->coord[*i + shift]);
		*i = *i + 1;
	}
	return (ret);
}


static int	rtv1_get_coord(t_scene *scene, char *line, int i)
{
	char	**nb;
	int		shift;
	int		ret;
	
	ret = 1;
	if (ft_strncmp(line, "t=", 2) != 0 && ft_strncmp(line, "r=", 2) != 0)
		return (ft_msg_int(2, "Error, problem in cam/light coord.\n", -1));
	if (!(nb = ft_strsplit(line + 2, ',')))
		return (ft_msg_int(2, "Error, failed split.\n", -1));
	if (scene->done == 3)
	{
		shift = line[0] == 't' ? 0 : 3;
		ret = rtv1_get_cam(scene, nb, &i, shift);
	}
	if (scene->done == 4)
		ret = rtv1_get_light(scene, nb, &i, line);
	if ((i != 3 || (i == 3 && nb[i] != NULL)) || ret != 1)
	{
		rtv1_free_tab(nb);
		return  (ft_msg_int(2, "Error, cam/light problem.\n", -1));
	}
	rtv1_free_tab(nb);
	return (0);
}	



static int	rtv1_manage_cls(t_scene *scene, char *line)
{
	if (scene->done == 2 && ft_strcmp(line, "camera") == 0)
		scene->done = 3;
	else if (scene->done < 10 && ft_strcmp(line, "light") == 0)
		scene->done = 4;
	else if (ft_strcmp(line, "objects") == 0)
		scene->done = 10;
	else if (scene->done < 10 && ft_strncmp(line, "shadows=", 8) == 0)
	{
		scene->shadows = ft_strcmp(line + 8, "on") == 0 ? 1 : scene->shadows;
		scene->shadows = ft_strcmp(line + 8, "yes") == 0 ? 1 : scene->shadows;
	}
	else if (scene->done == 3 || scene->done == 4)
		return (rtv1_get_coord(scene, line, 0));
	else if (scene->done >= 10)
		return (rtv1_get_obj(scene, line));
	if (scene->done < 3)
		return (ft_msg_int(2, "Error, wrong syntax in scene.\n", -1));
	return (0);
}


static int	rtv1_manage_line(t_scene *scene, char *line)
{
	if (scene->done == 0 && ft_strcmp(line, "scene") != 0)
		return (ft_msg_int(2, "Error, must start with <scene>.\n", -1));
	else if (scene->done == 0)
		scene->done = 1;
	else if (scene->done == 1)
	{
		if (ft_strncmp(line, "name=", 5) != 0)
			return (ft_msg_int(2, "Error, name should be here.\n", -1));
		if (!(scene->name = ft_strdup(line + 5)))
			return (ft_msg_int(2, "Error, failed dup name.\n", -1));
		scene->done = 2;
	}
	else if (scene->done > 1)
	{
		if (rtv1_manage_cls(scene, line) < 0)
			return (-1);
	}
	return (0);
}

int	rtv1_get_scene(t_scene *scene, int fd)
{
	char	*line;
	char	*tmp;
	int		end;

	line = NULL;
	end = 0;
	while (end == 0 && get_next_line(fd, &line) > 0)
	{
		if (!(tmp = ft_strtrim(line)))
		{
			free(line);
			return (ft_msg_int(2, "Error, failed trim.\n", -1));
		}
		if (tmp[0] != '}' && tmp[0] != '{')
			end = rtv1_manage_line(scene, tmp);
		free(tmp);
		free(line);
	}
	return (1);
}
