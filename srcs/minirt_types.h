/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:23:32 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/17 18:19:24 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPES_H
# define MINIRT_TYPES_H

# include <stdint.h>
# include "ft_math.h"
# include "mlx_colors.h"

typedef struct e_ambiant_light
{
	float		ratio;
	uint32_t	rgb;
}				t_ambiant_light;

# define NEAR_PLANE 1
typedef struct e_camera
{
	t_vec		pos;
	t_vec		dir;
	t_matrix	rotation;
	uint8_t		fov;
}				t_camera;

typedef struct e_light
{
	t_vec	pos;
	float		ratio;
	uint32_t	rgb;
}				t_light;

typedef struct e_sphere
{
	t_vec	center;
	double		radius;
	uint32_t	rgb;
}				t_sphere;

typedef struct e_plan
{
	t_vec	pos;
	t_vec	vec;
	uint32_t	rgb;
}				t_plan;

typedef struct e_cylinder
{
	t_vec	pos;
	t_vec	vec;
	double		diameter;
	double		height;
	uint32_t	rgb;
}				t_cylinder;

typedef struct s_rayhit
{
	t_col	albedo;
	t_vec	point;
	t_vec	normal;
	double	dist;
}	t_rayhit;
#endif
