/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_get_scene1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 09:23:14 by pmasson           #+#    #+#             */
/*   Updated: 2019/07/25 15:18:17 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include "libft.h"
#include <stdlib.h>
#include "get_next_line.h"

static int	rtv1_get_cam(t_rt *rt, char **nb, int *count, char *line)
{
	int	ret;
	double		vec[3];
	t_fvec3d	*save;

	ft_bzero(vec, sizeof(double) * 3);
	if (ft_strncmp(line , "pos=", 4) == 0)
		save = &(rt->cam.pos);
	else
		save = &(rt->cam.rot);
	ret = 1;
	while (ret == 1 && nb[*count] != NULL && *count < 3)
	{
		ret = rtv1_atoi(nb[*count], &vec[*count]);
		*count = *count + 1;
	}
	save->x = vec[0];
	save->y = vec[1];
	save->z = vec[2];
	rt->cam.px_screen_size.x = 1024;
	rt->cam.px_screen_size.y = 1024;
	return (ret);
}


static int	rtv1_get_coord(t_rt *rt, char *line, int *step)
{
	char	**nb;
	int		ret;
	int		count;
	
	count = 0;
	ret = 1;
	if (ft_strncmp(line, "pos=", 4) != 0 && ft_strncmp(line, "rot=", 4) != 0)
		return (ft_msg_int(2, "Error, problem in cam/light coord.\n", -1));
	if (!(nb = ft_strsplit(line + 4, ',')))
		return (ft_msg_int(2, "Error, failed split.\n", -1));
	if (*step == 3)
		ret = rtv1_get_cam(rt, nb, &count, line);
	if (*step == 4)
		ret = rtv1_get_light(rt, nb, &count, line);
	if ((count != 3 || (count == 3 && nb[count] != NULL)) || ret != 1)
	{
		rtv1_free_tab(nb);
		return  (ft_msg_int(2, "Error, cam/light problem.\n", -1));
	}
	rtv1_free_tab(nb);
	*step = 6;
	return (0);
}	

static int	rtv1_manage_cls(t_rt *rt, char *line, int *step)
{
	if ((*step == 2 || *step == 6) && ft_strcmp(line, "camera") == 0)
		*step = 3;
	else if ((*step == 2 || *step == 6) && ft_strcmp(line, "light") == 0)
		*step = 4;
	else if (ft_strcmp(line, "objects") == 0)
		*step = 10;
	else if ((*step == 2 || *step == 6) && ft_strncmp(line, "shadows=", 8) == 0)
	{
		rt->shadows = ft_strcmp(line + 8, "on") == 0 ? 1 : rt->shadows;
		rt->shadows = ft_strcmp(line + 8, "yes") == 0 ? 1 : rt->shadows;
		rt->shadows = ft_strcmp(line + 8, "off") == 0 ? 0 : rt->shadows;
		rt->shadows = ft_strcmp(line + 8, "no") == 0 ? 0 : rt->shadows;
	}
	else if (*step == 3 || *step == 4)
		return (rtv1_get_coord(rt, line, step));
	else if (*step >= 10)
		return (rtv1_get_obj(rt, line));
	if (*step < 3)
		return (ft_msg_int(2, "Error, wrong syntax in scene.\n", -1));
	return (0);
}


static int	rtv1_manage_line(t_rt *rt, char *line, int *step)
{
	if (*step == 0 && ft_strcmp(line, "scene") != 0)
		return (ft_msg_int(2, "Error, must start with <scene>.\n", -1));
	else if (*step == 0)
		*step = 1;
	else if (*step == 1)
	{
		if (ft_strncmp(line, "name=", 5) != 0)
			return (ft_msg_int(2, "Error, name should be here.\n", -1));
		if (!(rt->name = ft_strdup(line + 5)))
			return (ft_msg_int(2, "Error, failed dup name scene.\n", -1));
		*step = 2;
	}
	else if (*step > 1)
	{
		if (rtv1_manage_cls(rt, line, step) < 0)
			return (-1);
	}
	return (0);
}

int	rtv1_get_scene(t_rt *rt, int fd)
{
	char	*line;
	char	*tmp;
	int		end;
	int		step;

	step = 0;
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
			end = rtv1_manage_line(rt, tmp, &step);
		free(tmp);
		free(line);
	}
	if (end < 0)
		return (-1);
	return (1);
}
