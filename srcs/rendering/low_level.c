/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_level.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:32:37 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/18 23:51:12 by maabidal         ###   ########.fr       */
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
		hit->albedo = 0x00601A5F;
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

/*
int	plane_ray_cast(t_plane plane, t_ray ray)
{

}

int	cylinder_ray_cast(t_sphere cylinder, t_ray ray)
{

}

int	2nd_degree_shape_ray_cast(t_??, t_ray ray)
{

}
*/
