/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:55:22 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/18 01:03:18 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "header.h"

typedef int (t_ray_caster)(void *, t_ray);

typedef struct s_scene
{
	t_list		*objs;
	t_list		*lights;
	t_camera	camera;
	t_col 		ambiant_light;
}	t_scene;

typedef struct s_obj_interface
{
	t_ray_caster	ray_caster;
	void			*obj;
}	t_obj_interface;

typedef struct e_camera
{
	t_vec		pos;
	t_vec		dir;
	t_matrix	rotation;
	uint8_t		fov;
}				t_camera;

typedef struct e_light
{
	t_vec		pos;
	double		ratio;
	t_col		rgb;
}				t_light;

typedef struct e_sphere
{
	t_vec		center;
	double		radius;
	t_col		rgb;
}				t_sphere;

typedef struct e_plan
{
	t_vec		pos;
	t_vec		vec;
	t_col		rgb;
}				t_plan;

typedef struct e_cylinder
{
	t_vec		pos;
	t_vec		vec;
	double		radius;
	double		height;
	t_col		rgb;
}				t_cylinder;
#endif
