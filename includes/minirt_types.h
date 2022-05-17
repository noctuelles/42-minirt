/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:23:32 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/17 17:43:22 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPES_H
# define MINIRT_TYPES_H

# include <stdint.h>

typedef uint32_t	t_col;

typedef struct e_coord3d
{
	double	x;
	double	y;
	double	z;
}				t_coord3d;
typedef t_coord3d	t_vec;

typedef struct	e_range
{
	double	r1;
	double	r2;
}				t_range;

typedef enum	e_object_type
{
	OBJ_AM_LIGHT,
	OBJ_CAMERA,
	OBJ_LIGHT,
	OBJ_SPHERE,
	OBJ_PLAN,
	OBJ_CYLINDER
}				t_object_type;

/*           -- Object Types and variables used --
 *
 * Ambiant light :
 *   - ratio, rgb
 * Camera :
 *   - coord, vec, fov
 * Light :
 *   - coord, ratio, rgb
 * Sphere :
 *   - coord, diameter, rgb
 * Plan :
 *   - coord, vec, rgb
 * Cylinder :
 *   - coord, vec, diameter, height, rgb
 */

typedef struct	e_object
{
	t_object_type	type;
	t_coord3d		coord;
	t_coord3d		vec;
	double			ratio;
	double			diameter;
	double			height;
	uint32_t		fov;
	uint32_t		rgb;
}				t_object;

typedef struct s_rayhit
{
	t_col	albedo;
	t_vec	point;
	t_vec	normal;
	double	dist;
}	t_rayhit;

#endif
