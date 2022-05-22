/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_level.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:32:37 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/22 18:44:31 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/*
BOOL	is_a_hit(double inters, t_rayhit *hit)
{
	if(*inters > 0 && *inters < hit->t)
		return (TRUE); 
	return (inters[1] > 0 && inters[1] < hit->t);
}
*/

BOOL	are_hits(double *inters, t_rayhit *hit)
{
	if(*inters > 0 && *inters < hit->t)
		return (TRUE); 
	return (inters[1] > 0 && inters[1] < hit->t);
}

BOOL	sphere_raycast(void *sphere, t_ray ray, t_rayhit *hit)
{
	double	a;
	double	b;
	double	c;
	double	inters[2];
	t_vec	co;

	co = dif(ray.origin, ((t_sphere *)sphere)->center);
	a = sqrd_mag(ray.dir);
	b = 2 * dot(co, ray.dir);
	c = sqrd_mag(co) - sqrd(((t_sphere *)sphere)->radius);
	if (solve_2nd_degree(a, b, c, inters) && are_hits(inters, hit))
	{
		if (inters[0] > 0)
			hit->t = inters[0];
		else if (inters[1] > 0)
			hit->t = inters[1];
		hit->point = sum(mul_d(ray.dir, hit->t), ray.origin);
		hit->normal = normalized(dif(hit->point, ((t_sphere *)sphere)->center));
		hit->albedo = ((t_sphere *)sphere)->albedo;
		return (TRUE);
	}
	return (FALSE);
}

//-recadrage: obtenir une valeur entre -1 et 1
//creer canvas_scale 
//-map to canvas
t_ray	mk_camray(t_camera cam, int x, int y)
{
	t_ray	ray;
	t_vec	canvas_scale;

	ray.origin.x = ((double)x - (double)HALF_WIDTH) / (double)HALF_WIDTH;
	ray.origin.y = ((double)HALF_HEIGHT - (double)y) / (double)HALF_HEIGHT;
	canvas_scale.x = tan(DEG2RAD * cam.fov);
	canvas_scale.y = canvas_scale.x * ((double)WIN_HEIGHT / (double)WIN_WIDTH);
	ray.origin = mul(ray.origin, canvas_scale);
	ray.origin.z = 1.0;
	ray.dir = normalized(ray.origin);
	return (ray);
}

#include <stdio.h>
BOOL	plane_raycast(void *plane_ptr, t_ray ray, t_rayhit *hit)
{
	double	denominator;
	double	enumerator;
	double	t;
	t_plane	plane;

	plane = *((t_plane *)plane_ptr);
	denominator = dot(plane.normal, ray.dir);
	if (denominator == 0)
		return (FALSE);
	enumerator = dot(dif(plane.pos, ray.origin), plane.normal);
	t = enumerator / denominator;
	if (t > 0 && t < hit->t)
	{
		hit->t = t;
		hit->point = sum(ray.origin, mul_d(ray.dir, t));
		hit->normal = plane.normal;
		hit->albedo = plane.albedo;
		return (TRUE);
	}
	return (FALSE);
}

static BOOL	tube_raycast(t_cylinder cylindre, t_ray ray, t_ayhit *hit)
{

}

BOOL	cylinder_raycast(void *cylinder_ptr, t_ray ray, t_rayhit *hit)
{
	t_cylinder	cylinder;
	t_rayhit	plane_hit;
	t_plane		plane;

	cylinder = *(t_cylinder *)cylinder_ptr;
	plane.normal = cylinder.dir;
	if (dot(plane.normal, ray.dir) > 0)
		plane.normal = mul_d(plane.normal, -1);
	plane.pos = sum(cylinder.pos, mul_d(plane.normal, cylinder.height));
	plane.albedo = cylinder.albedo;
	plane_hit.t = DBL_MAX;
	if (plane_raycast(&plane, ray, &plane_hit) && sqrd_dist(plane_hit.point, plane.pos) <= sqrd(cylinder.radius))
	{
		*hit = plane_hit;
		return (TRUE);
	}
	return (FALSE);
}
