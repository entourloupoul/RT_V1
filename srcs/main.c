/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:40:40 by pmasson           #+#    #+#             */
/*   Updated: 2019/07/24 13:15:17 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include <stdio.h>
static int	rtv1_create_window(t_scene *scene, t_picture *picture)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (ft_msg_int(2, "Error, failes init sdl2.\n", -1));
	if (!(picture->window = SDL_CreateWindow(scene->name, 0, 0,
					picture->length, picture->width, 0)))
	{
		SDL_Quit();
		return (ft_msg_int(2, "Error, failed create window.\n", -1));
	}
	if (!(picture->renderer = SDL_CreateRenderer(picture->window, -1, 0)))
	{
		SDL_DestroyWindow(picture->window);
		SDL_Quit();
		return (ft_msg_int(2, "Error, failed create renderer.\n", -1));
	}
	if (!(picture->surface = SDL_CreateRGBSurface(0, picture->length,
					picture->width, 32, 0, 0, 0, 0)))
	{
		SDL_DestroyWindow(picture->window);
		SDL_DestroyRenderer(picture->renderer);
		SDL_Quit();
		return (ft_msg_int(2, "Error, failed create surface.\n", -1));
	}
	return (1);
}

static int	rtv1_quit_video(t_scene *scene, char *str, int ret)
{
	ft_putstr_fd(str, 2);
	SDL_DestroyWindow(scene->picture->window);
	SDL_DestroyRenderer(scene->picture->renderer);
	if (scene->picture->texture != NULL)
		SDL_DestroyTexture(scene->picture->texture);
	SDL_FreeSurface(scene->picture->surface);
	SDL_Quit();
	free(scene->picture);
	return (ret);
}

static int	rtv1_put_on_screen(t_scene *scene)
{
	int			running;
	SDL_Event	event;

	if (!(scene->picture->texture
				= SDL_CreateTextureFromSurface(scene->picture->renderer,
					scene->picture->surface)))
		return (rtv1_quit_video(scene, "Error texture creation", -1));
	if (SDL_RenderCopy(scene->picture->renderer,
				scene->picture->texture, NULL, NULL) < 0)
		return (rtv1_quit_video(scene, "Error, render copy\n", -1));
	SDL_RenderPresent(scene->picture->renderer);
	running = 1;
//	return (0);
	while (running == 1)
	{
		while (SDL_PollEvent(&event))
		{
			if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type
						&& SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
				running = 0;
		}
	}
	return (rtv1_quit_video(scene, NULL, 1));
}




static int	rtv1_create_scene(t_scene *scene)
{
	t_picture	*picture;

	if (!(picture = (t_picture *)malloc(sizeof(t_picture) * 1)))
		return (ft_msg_int(2, "Error, failed malloc picture.\n", -1));
	ft_bzero(picture, sizeof(t_picture));
	picture->length = scene->cam->length;
	picture->width = scene->cam->width;
	scene->picture = picture;
	if (rtv1_create_window(scene, picture) < 0)
		return (-1);
	if (rtv1_create_final(scene) < 0)
		rtv1_quit_video(scene, NULL, -1);
	if (rtv1_put_on_screen(scene) < 0)
		return (-1);
	return (1);
}

int	main(int argc, char **argv)
{
	int	fd;
	int	ret;
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
	//prendre en compte les autres argv pour changement ou changement interatcif.
	ret = rtv1_create_scene(scene);
	rtv1_free_scene(&scene);
	return (ret);
}
