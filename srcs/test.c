/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:39:31 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/16 14:13:59 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//utilise pour tester la mlx et le makefile avant d'avoir un vrai main

#include "header.h"
#include <stdio.h>

/*
int	cast_ray(t_ray ray, t_list *i_shapes, t_rayhit *hit)
{
	int	ret;

	if (shapes == NULL)
		return (0);
	//apply transformations
	ret = i_shape->equation(ray, i_shapes->properties, hit);
	return (ret || cast_ray(raym i_saes->next, hit);
}
*/

t_ray	mk_camray(t_camera cam, t_vec on_viewport)
{
	t_ray	ray;

(void)cam;
	ray.origin.x = on_viewport.x / (double)WIN_WIDTH;
	ray.origin.y = on_viewport.y / (double)WIN_HEIGHT;
	ray.origin.z = 1.0;
	ray.dir = normalized(ray.origin);
	return (ray);
}

int	sphere_inters(t_sphere sphere, t_ray ray, double *inters)
{
	double	a;
	double	b;
	double	c;
	t_vec	co;

	co = dif(ray.origin, sphere.center);
	a = sqrd_mag(ray.dir);
	b = 2 * dot(co, ray.dir);
	c = sqrd_mag(co) - sphere.radius * sphere.radius;
	return (solve_2nd_degree(a, b, c, inters));
}

//inters = intersections
//on_viewport is a 2d vector
static t_col	 render_pix(t_vec on_viewport, t_camera cam, t_sphere sphere, t_vec light_dir)
{
	t_ray	cam_ray;
	double	inters[2];

	cam_ray = mk_camray(cam, on_viewport);
	if (sphere_inters(sphere, cam_ray, inters))
		if (inters[0] >= 0 || inters[1] >= 0)
		{

			return (BLUE);
		}
	return (BLACK);
}

static void render_img(t_col *img)
{
	int	x;
	int	y;
	t_vec	on_viewport;
	t_sphere	sphere;
	t_camera	cam;

	sphere.center = new_v(0, 0, 0);
	sphere.radius = 5;
	cam.dir = new_v(0, 0, 1);
	cam.pos = new_v(0, 0, 0);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			on_viewport.x = (double)x - (double)WIN_WIDTH / 2.0;
			on_viewport.y = (double)WIN_HEIGHT / 2.0 - (double)y;
			img[x + y * WIN_WIDTH] = render_pix(on_viewport, cam, sphere);
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
}
