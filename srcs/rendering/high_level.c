/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:35:04 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/19 15:30:55 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static BOOL	cast_ray(t_ray ray, t_list *objs, t_rayhit *hit)
{
	int				next;
	t_obj_interface	*interface;

	if (objs == NULL)
		return (FALSE);
	next = cast_ray(ray, objs->next, hit);
	interface = (t_obj_interface *)objs->content;
	return (interface->ray_caster(interface->obj, ray, hit) || next);
}

static t_ray new_ray(t_vec origin, t_vec direction)
{
	t_ray ray;

	ray.origin = origin;
	ray.dir = direction;
	return (ray);
}

static t_col	render_pixel(t_scene scene, t_ray cam_ray)
{
	t_rayhit	hit;
	t_vec		to_light;
	double		lighting;
	t_col		col;
	t_ray		light_ray;

	hit.t = DBL_MAX;
	if (cast_ray(cam_ray, scene.objs, &hit))
	{
		col = mult_colors(hit.albedo, scene.ambiant_light);
		to_light = dif(scene.light.pos, hit.point);
		light_ray = new_ray(hit.point, normalized(to_light));
		light_ray.origin = sum(light_ray.origin, mul_d(light_ray.dir, 0.001));
		if (!cast_ray(light_ray, scene.objs, &hit))
		{
			lighting = dot(hit.normal, normalized(to_light));
			lighting *= scene.light.intensity / sqrd(magnitude(to_light) + 1.0);
			col = add_colors(col, mult_color_scalar(hit.albedo, lighting));
		}
		return (col);
	}
	return (BLACK);
}

void	render_img(t_col *img, t_scene scene)
{
	int		x;
	int		y;
	t_ray	cam_ray;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			cam_ray = mk_camray(scene.camera, x, y);
			img[x + y * WIN_WIDTH] = render_pixel(scene, cam_ray);
		}
	}
}


/*
t_sphere	sphere;
t_camera	cam;
t_light	light;

light.pos = new_v(-5, 8, 10);
sphere.center = new_v(0, 0, 15);
sphere.radius = 5;
cam.dir = new_v(0, 0, 1);
cam.pos = new_v(0, 0, 0);
cam.fov = 70.0;
*/
