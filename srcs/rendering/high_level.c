/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   high_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:35:04 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/18 00:46:13 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

static void	cast_ray_through_objects(t_ray ray, t_list *objs)
{

}

static t_col	get_spot_lights_colors(t_ray ray, t_list *objs, t_list *lights)
{

}
//-recadrage: obtenir une valeur entre -1 et 1
//creer canvas_scale 
//-map to canvas
static t_ray	mk_camray(t_camera cam, int x, int y)
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


static void	render_pixel(t_scene, t_ray cam_ray)
{
	double	inter;

	if (sphere_inter(sphere, cam_ray, &inter))
	{
		t_vec	point = sum(mul_d(cam_ray.dir, inter), cam_ray.origin);
		t_vec	normal = normalized(dif(point, sphere.center));
		t_vec	point_to_light = dif(light.pos, point);
		double	dot_scalar = dot(normal, normalized(point_to_light));
		double	distance_scalar = 100.0 / sqrd(magnitude(point_to_light) + 1.0);
		t_col	point_col = mult_color_scalar(0x00601A5F, dot_scalar * distance_scalar);
		t_col	ambient_col = mult_colors(0x00601A5F, 0x00900A0F);
		return (add_colors(point_col, ambient_col));
	}
	return (BLACK);
}

void	render_img(t_col *img, t_scene scene)
{
	int	x;
	int	y;
	t_ray	cam_ray;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			cam_ray = mk_camray(cam, x, y);
			img[x + y * WIN_WIDTH] = render_pix(cam_ray, scene);
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
