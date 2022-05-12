/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:39:31 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/12 23:27:43 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//utilise pour tester les la mlx et le makefile avant d'avoir un vrai main

#include "header.h"
#include <stdio.h>

/*
typedef struct s_img
{
	t_col		*buff;
	int			bpp;
	int			line_size;
}	t_img;
*/

static void	 put_pix(t_col *img, int x, int y, t_col col)
{
	img[x + y * WIN_WIDTH] = col;
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

	for (int x = 0; x < WIN_HEIGHT; x++)
		put_pix(img, x, x, WHITE);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);

	mlx_loop(mlx_ptr);
	mlx_destroy_image(mlx_ptr, img_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
}
