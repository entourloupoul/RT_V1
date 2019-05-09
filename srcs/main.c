/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:40:40 by pmasson           #+#    #+#             */
/*   Updated: 2019/05/09 15:17:54 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


#include <stdio.h>
int	main(int argc, char **argv)
{
	int	fd;
	t_scene	*scene;

	if (argc != 2)
		return (ft_msg_int(1, "usage : ./rtv1 <scene file>\n", 0));
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_msg_int(2, "Error, can't open scene file", -1));
	if (!(scene = (t_scene *)malloc(sizeof(t_scene) * 1)))
	{
		close(fd);
		return (ft_msg_int(2, "Error, failed malloc scene.\n", -1));
	}
	ft_bzero(scene, sizeof(t_scene));
	if (rtv1_get_scene(scene, fd) < 0)
	{
		close(fd);
		rtv1_free_scene(&scene);
		return (-1);
	}
	close(fd);
	rtv1_free_scene(&scene);
	//close(avant aussi);;
	/*
	printf("%s\n", scene->name);
	int i;
	i = 0;
	printf("cam: : ");
	while (i < 6)
	{
		printf("%d ", scene->cam->coord[i]);
		i++;
	}
	puts("");
	t_light *tmp;
	tmp = scene->light;
	while (tmp != NULL)
	{
		printf("light : ");
		i = 0;
		while (i < 3)
		{
			printf("%d ", tmp->coord[i]);
			i++;
		}
		puts("");
		tmp = tmp->next;
	}
	t_obj *obj;
	obj = scene->obj;
	while (obj != NULL)
	{
		printf("name : %s\ntype: %d\ndata: ", obj->name, obj->type);
		i = 0;
		while (i < 8)
		{
			printf("%d ", obj->data[i]);
			i++;
		}
		puts("");
		printf("opt: %d\n", obj->opt);
		printf("color: %X\n", obj->color);
		obj = obj->next;
	}
	free(scene->cam->coord);*/
	return (1);
}
