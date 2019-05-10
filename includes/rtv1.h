/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:39:26 by pmasson           #+#    #+#             */
/*   Updated: 2019/05/10 17:04:35 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <SDL2/SDL.h>
# define HEXA "0123456789ABCDEF"
# define DEC "0123456789"
typedef	struct	s_obj
{
	char	*name;
	char	type;
	int		*data;
	int		opt;
	int		color;
	struct s_obj	*next;
}				t_obj;
typedef struct	s_light
{
	int		nb;
	int		*coord;
	struct s_light	*next;
}				t_light;
typedef struct	s_camera
{
	int	*coord;
	int	length;
	int	width;
}				t_camera;
typedef struct	s_picture
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	int				length;
	int				width;
}				t_picture;
typedef	struct	s_scene
{
	char	*name;
	t_camera	*cam;
	char	done;
	int		shadows;
	char	tobj;
	t_light	*light;
	t_obj	*obj;
	t_picture	*picture;
}				t_scene;
int		rtv1_get_scene(t_scene *scene, int fd);
void	rtv1_free_tab(char **tab);
int		rtv1_atoi(char *str, int *d);
int		rtv1_check_param(char *line);
int		rtv1_get_light(t_scene *scene, char **nb, int *i, char *line);
int		rtv1_get_obj(t_scene *scene, char *line);
int		rtv1_get_coord_obj(t_obj *obj, char *line);
void	rtv1_free_scene(t_scene **scene);
# endif
