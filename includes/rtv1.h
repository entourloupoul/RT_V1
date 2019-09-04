/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmasson <pmasson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:39:26 by pmasson           #+#    #+#             */
/*   Updated: 2019/09/04 16:28:05 by pmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL2/SDL.h>
# include <stdint.h>
# include <stdbool.h>
# include <stddef.h>
# define AMBIENT 0.1

typedef struct	s_color
{
	uint8_t		b;
	uint8_t		g;
	uint8_t		r;
	uint8_t		a;
}				t_color;

typedef union	u_pixel
{
	uint32_t	color;
	t_color		p;
}				t_pixel;

typedef struct	s_vec2d
{
	int32_t		x;
	int32_t		y;
}				t_vec2d;

typedef struct	s_fvec2d
{
	double		x;
	double		y;
}				t_fvec2d;

typedef struct	s_vec3d
{
	int32_t		x;
	int32_t		y;
	int32_t		z;
}				t_vec3d;

typedef struct	s_fvec3d
{
	double		x;
	double		y;
	double		z;
}				t_fvec3d;

typedef struct	s_light
{
	t_fvec3d		pos;
	double			dist;
	struct s_light	*next;
}				t_light;

typedef struct	s_plane
{
	t_fvec3d	equation;
	double		constant;
	t_fvec3d	norm;
}				t_plane;

typedef struct	s_sphere
{
	t_fvec3d	center;
	double		radius;
}				t_sphere;

typedef struct	s_cylinder
{
	t_fvec3d	center;
	t_fvec3d	axis;
	double		radius;
	t_plane		plane;
}				t_cylinder;

typedef struct	s_cone
{
	t_fvec3d	center;
	t_fvec3d	axis;
	double		angle;
	t_plane		plane;
	double		mat_x[3][3];
	double		mat_y[3][3];
	double		mat_z[3][3];
}				t_cone;

typedef enum	e_obj_type
{
	PLANE,
	SPHERE,
	CYLINDER,
	CONE
}				t_obj_type;

typedef union	u_obj_union
{
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_cone		cone;
}				t_obj_union;

typedef struct	s_obj
{
	char			*name;
	bool			is_shine;
	t_pixel			color;
	t_obj_type		type;
	t_obj_union		u;
	t_fvec3d		pos;
	t_fvec3d		rot;
	struct s_obj	*next;
}				t_obj;

typedef struct	s_geo
{
	t_fvec3d	pos;
	t_fvec3d	dir;
}				t_geo;

typedef struct	s_ray
{
	t_geo		cam;
	t_geo		obj;
	double		dist;
	double		ambient;
	double		shade;
	double		final_shade;
	double		coef_shine;
	t_pixel		color;
	bool		shadows;
}				t_ray;

typedef struct	s_cam
{
	t_fvec3d	pos;
	t_fvec3d	rot;
	t_fvec3d	u;
	t_fvec3d	v;
	t_fvec3d	w;
	double		screen_normal;
	t_fvec2d	screen_ratio;
	t_fvec2d	px_screen_size;
}				t_cam;

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Surface		*surface;
	SDL_Texture		*texture;
	t_vec2d			size;
}				t_sdl;

typedef struct	s_rt
{
	char		*name;
	t_cam		cam;
	t_obj		*objs;
	t_light		*lights;
	t_sdl		sdl;
	bool		shadows;
}				t_rt;

typedef struct	s_terms
{
	double		i;
	double		j;
	double		k;
	double		l;
	double		m;
	double		n;
}				t_terms;

int				rtv1_get_scene(t_rt *rt, int fd);
void			rtv1_free_tab(char **tab);
int				rtv1_atoi(char *str, double *d);
int				rtv1_get_light(t_rt *rt, char **nb, int *i, char *line);
int				rtv1_get_obj(t_rt *rt, char *line);
int				rtv1_get_coord_obj(t_obj *obj, char *line);
void			rtv1_calc_obj(t_rt *rt);
void			rtv1_free_scene(t_rt **rt);
int				rtv1_create_final(t_rt *rt);
int				rtv1_set_cam_vec(t_cam *cam);
int				rtv1_get_color(t_rt *rt, t_ray *ray);
double			rtv1_check_inter_sphere(t_obj *obj, t_geo source);
double			rtv1_check_inter_plane(t_obj *obj, t_geo source);
int				rtv1_get_shade(t_light *light, t_obj *obj, t_ray *ray,
					t_obj *save);
double			rtv1_solve_2_deg(double det, double a, double b);
double			rtv1_check_inter_cylinder(t_obj *obj, t_geo source);
double			rtv1_check_inter_cone(t_obj *obj, t_geo source);
void			create_rot_mat(double mat[3][3], double angle, char axis);
void			dot_product_column_vec(t_fvec3d *r, double m1[3][3],
					t_fvec3d col);
int				rtv1_check_plane_side(t_fvec3d pointa, t_plane plane,
					t_fvec3d pointb);
void			rtv1_shade_cone(t_obj *obj, t_ray *ray);
double			rtv1_check_inter(t_obj *obj, t_geo source);
void			rtv1_shade_cylinder(t_obj *obj, t_ray *ray);
#endif
