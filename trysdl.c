/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trysdl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:58:47 by pmasson           #+#    #+#             */
/*   Updated: 2019/05/24 17:45:10 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include <stdio.h>

int	main(void)
{
	SDL_Window *window;
	SDL_Event event;
	int	running;
	SDL_Renderer *renderer;
	SDL_Surface *surface;
	SDL_Texture *texture;
	int x;
	int y;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("try sdl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500,0);
	if (window == NULL)
		return (0);
	running = 1;
	renderer = SDL_CreateRenderer(window, -1, 0);
	surface = SDL_CreateRGBSurface(0, 500,500,32,0,0,0,0);
	if (renderer == NULL)
		return (0);
	if (surface == NULL)
		return (0);
	x = 10;
	y = 10;
	puts("coucou");
	while (y < 100)
	{
		x = 10;
		while (x < 200)
		{
			*((unsigned int *)(surface->pixels + 4 * x + 4 * y * 500)) = 0x0000FF;
			x = x + 1;
		}
		while (x < 400)
		{
			*((unsigned int *)(surface->pixels + 4 * x + 4 * y * 500)) = 0xFF0000;
			x = x + 1;
		}
		y = y + 1;
	}
	puts("yo");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	puts("fjerkow");
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	puts("dodod");
	while (running == 1)
	{
		while (SDL_PollEvent(&event))
		{
			if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
				running = 0;
		}
	}
	puts("fuite");
	SDL_DestroyWindow(window);
	SDL_Quit();
	return(0);
}

