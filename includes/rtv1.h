/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:39:26 by pmasson           #+#    #+#             */
/*   Updated: 2019/07/11 13:07:49 by pmasson          ###   ########.fr       */
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
	double	*norm;
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
typedef struct	s_cam
{
	int	*coord;
	double	*w;
	double	*u;
	double	*v;
	double	n;
	double	l;
	double	r;
	int	length;
	int	width;
}				t_cam;
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
	t_cam	*cam;
	char	done;
	int		shadows;
	char	tobj;
	t_light	*light;
	t_obj	*obj;
	t_picture	*picture;
}				t_scene;
typedef struct	s_ray
{
	double	source[6];
	double	vec[6];
	int		hits;
	double	t;
	double	ambient;
	double	shade;
	int		color;
}				t_ray;
typedef struct	s_terms
{
	double	i;
	double	j;
	double	k;
	double	l;
	double	m;
	double	n;
}				t_terms;
int		rtv1_get_scene(t_scene *scene, int fd);
void	rtv1_free_tab(char **tab);
int		rtv1_atoi(char *str, int *d);
int		rtv1_check_param(char *line);
int		rtv1_get_light(t_scene *scene, char **nb, int *i, char *line);
int		rtv1_get_obj(t_scene *scene, char *line);
int		rtv1_get_coord_obj(t_obj *obj, char *line);
void	rtv1_free_scene(t_scene **scene);
int		rtv1_create_final(t_scene *scene);
int		rtv1_set_cam_vec(t_cam *cam);
int		rtv1_set_cam_vec2(t_cam *cam);
int		rtv1_get_color(t_scene *scene, t_ray *ray);
double	rtv1_check_inter_sphere(t_obj *obj, t_ray *ray, int s);
double	rtv1_check_inter_plane(t_obj *obj, t_ray *ray, int s);
int		rtv1_get_shade(t_scene *scene, t_obj *obj, t_ray *ray, t_obj *save);
double	rtv1_solve_2_deg(double det, double a, double b);
double	rtv1_check_inter_cylinder(t_obj *obj, t_ray *ray, int s);
# endif
