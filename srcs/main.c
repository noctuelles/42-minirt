/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:45:01 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/19 22:45:09 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

t_scene	setup_scene()
{
	t_scene		scene;

	scene.light.pos = new_v(-5, 8, 10);
	scene.light.intensity = 100;
	scene.camera.dir = new_v(0, 0, 1);
	scene.camera.pos = new_v(0, 0, 0);
	scene.camera.fov = 70.0;
	scene.ambiant_light = 0x00900A0F;

	scene.objs = malloc(sizeof(t_list));

	scene.objs->content = malloc(sizeof(t_obj_interface));
	((t_obj_interface *)scene.objs->content)->ray_caster = &sphere_raycast;
	((t_obj_interface *)scene.objs->content)->obj = malloc(sizeof(t_sphere));
	((t_sphere *)((t_obj_interface *)scene.objs->content)->obj)->center = new_v(5, -2, 15);
	((t_sphere *)((t_obj_interface *)scene.objs->content)->obj)->radius = 5;

	scene.objs->next = malloc(sizeof(t_list));
	scene.objs->next->content = malloc(sizeof(t_obj_interface));
	((t_obj_interface *)scene.objs->next->content)->ray_caster = &plane_raycast;
	((t_obj_interface *)scene.objs->next->content)->obj = malloc(sizeof(t_plane));
	((t_plane *)((t_obj_interface *)scene.objs->next->content)->obj)->pos = new_v(2, -5, 0);
	((t_plane *)((t_obj_interface *)scene.objs->next->content)->obj)->normal = new_v(1, 0, 0);
	((t_plane *)((t_obj_interface *)scene.objs->next->content)->obj)->albedo = WHITE;

	scene.objs->next->next = NULL;

	return (scene);
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

	render_img(img, setup_scene());

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	mlx_destroy_image(mlx_ptr, img_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	free(mlx_ptr);
}
