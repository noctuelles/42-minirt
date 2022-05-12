/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:39:31 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/12 18:08:41 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//utilise pour tester les la mlx et le makefile aant d'avoir un vrai main

#include "header.h"

int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	mlx_destroy_window(mlx_ptr, win_ptr);
}
