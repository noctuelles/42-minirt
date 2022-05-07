/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:23:32 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/07 15:24:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPES_H
# define MINIRT_TYPES_H

# include <stdint.h>

typedef struct e_coord3d
{
	double	x;
	double	y;
	double	z;
}				t_coord3d;

typedef struct e_ambiant_light
{
	float		ratio;
	uint32_t	rgb;
}				t_ambiant_light;

typedef struct e_camera
{
	t_coord3d	coord;
	t_coord3d	vec;
	uint8_t		fov;
}				t_camera;

typedef struct e_light
{
	t_coord3d	coord;
	float		ratio;
	uint32_t	rgb;
}				t_light;

typedef struct e_sphere
{
	t_coord3d	coord;
	double		diameter;
	uint32_t	rgb;
}				t_sphere;

typedef struct e_plan
{
	t_coord3d	coord;
	t_coord3d	vec;
	uint32_t	rgb;
}				t_plan;

typedef struct e_cylinder
{
	t_coord3d	coord;
	t_coord3d	vec;
	double		diameter;
	double		height;
	uint32_t	rgb;
}				t_cylinder;

#endif
