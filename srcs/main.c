/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:40:40 by pmasson           #+#    #+#             */
/*   Updated: 2019/08/12 19:02:41 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>

static int	rtv1_create_window(t_rt *rt, t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (ft_msg_int(2, "Error, failes init sdl2.\n", -1));
	if (!(sdl->window = SDL_CreateWindow(rt->name, 0, 0,
					sdl->size.x, sdl->size.y, 0)))
	{
		SDL_Quit();
		return (ft_msg_int(2, "Error, failed create window.\n", -1));
	}
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->window, -1, 0)))
	{
		SDL_DestroyWindow(sdl->window);
		SDL_Quit();
		return (ft_msg_int(2, "Error, failed create renderer.\n", -1));
	}
	if (!(sdl->surface = SDL_CreateRGBSurface(0, sdl->size.x, sdl->size.y,
					32, 0, 0, 0, 0)))
	{
		SDL_DestroyWindow(sdl->window);
		SDL_DestroyRenderer(sdl->renderer);
		SDL_Quit();
		return (ft_msg_int(2, "Error, failed create surface.\n", -1));
	}
	return (1);
}

static int	rtv1_quit_video(t_rt *rt, char *str, int ret)
{
	ft_putstr_fd(str, 2);
	SDL_DestroyWindow(rt->sdl.window);
	SDL_DestroyRenderer(rt->sdl.renderer);
	if (rt->sdl.texture != NULL)
		SDL_DestroyTexture(rt->sdl.texture);
	SDL_FreeSurface(rt->sdl.surface);
	SDL_Quit();
	return (ret);
}

static int	rtv1_put_on_screen(t_rt *rt)
{
	int			running;
	SDL_Event	event;

	if (!(rt->sdl.texture = SDL_CreateTextureFromSurface(rt->sdl.renderer,
					rt->sdl.surface)))
		return (rtv1_quit_video(rt, (char *)SDL_GetError(), -1));
	if (SDL_RenderCopy(rt->sdl.renderer, rt->sdl.texture, NULL, NULL) < 0)
		return (rtv1_quit_video(rt, "Error, render copy\n", -1));
	SDL_RenderPresent(rt->sdl.renderer);
	running = 1;
	while (running == 1)
	{
		while (SDL_PollEvent(&event))
		{
			if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type
						&& SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
				running = 0;
		}
	}
	return (rtv1_quit_video(rt, NULL, 1));
}




static int	rtv1_create_scene(t_rt *rt)
{
	rt->sdl.size.x = rt->cam.px_screen_size.x;
	rt->sdl.size.y = rt->cam.px_screen_size.y;
	if (rtv1_create_window(rt, &(rt->sdl)) < 0)
		return (-1);
	if (rtv1_create_final(rt) < 0)
		rtv1_quit_video(rt, NULL, -1);
	if (rtv1_put_on_screen(rt) < 0)
		return (-1);
	return (1);
}

int	main(int argc, char **argv)
{
	int	fd;
	int	ret;
	t_rt	*rt;

	ret = 0;
	if (argc != 2)
		return (ft_msg_int(1, "usage : ./rtv1 <scene file>\n", 0));
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_msg_int(2, "Error, can't open scene file", -1));
	if (!(rt = (t_rt *)malloc(sizeof(t_rt) * 1)))
	{
		close(fd);
		return (ft_msg_int(2, "Error, failed malloc rt.\n", -1));
	}
	ft_bzero(rt, sizeof(t_rt));
	if (rtv1_get_scene(rt, fd) < 0)
	{
		close(fd);
		rtv1_free_scene(&rt);
		return (-1);
	}
	close(fd);
	ret = rtv1_create_scene(rt);
	rtv1_free_scene(&rt);
	return (ret);
}
