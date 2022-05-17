/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:39:31 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/17 21:40:57 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//utilise pour tester la mlx et le makefile avant d'avoir un vrai main

#include "header.h"
#include <stdio.h>

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

//distance check must remin at > 0 for shadow raycast
int	sphere_inter(t_sphere sphere, t_ray ray, double *inter)
{
	double	a;
	double	b;
	double	c;
	double	inters[2];
	t_vec	co;

	co = dif(ray.origin, sphere.center);
	a = sqrd_mag(ray.dir);
	b = 2 * dot(co, ray.dir);
	c = sqrd_mag(co) - sphere.radius * sphere.radius;
	if (solve_2nd_degree(a, b, c, inters))
	{
		if (inters[0] > 0)
			*inter = inters[0];
		else if (inters[1] > 0)
			*inter = inters[1];
		return (inters[0] > 0 || inters[1] > 0);
	}
	return (0);
}

//inter = intersections
//on_viewport is a 2d vector
//no need to clamp scalar product when passing it to mult_color
//my_light_intensity	= 1.0 / sqrd(dist + 1)
static t_col	 render_pix(t_ray cam_ray, t_sphere sphere, t_light light)
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

static void render_img(t_col *img)
{
	int	x;
	int	y;
	t_ray	cam_ray;
t_sphere	sphere;
t_camera	cam;
t_light	light;

light.pos = new_v(-5, 8, 10);
sphere.center = new_v(0, 0, 15);
sphere.radius = 5;
cam.dir = new_v(0, 0, 1);
cam.pos = new_v(0, 0, 0);
cam.fov = 70.0;
	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			cam_ray = mk_camray(cam, x, y);
			img[x + y * WIN_WIDTH] = render_pix(cam_ray, sphere, light);
		}
	}
}

int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		dump;
	t_col	*img;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	img_ptr = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img = (t_col *)mlx_get_data_addr(img_ptr, &dump, &dump, &dump);
	render_img(img);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	mlx_destroy_image(mlx_ptr, img_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	free(mlx_ptr);
}
