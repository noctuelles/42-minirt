/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:52:11 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/18 00:54:38 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "ft_math.h"
# include "mlx_colors.h"
# include "scene.h"

typedef struct s_rayhit
{
	t_col	col;
	t_vec	point;
	t_vec	normal;
	double	dist;
}	t_rayhit;

int		sphere_ray_cast(t_sphere sphere, t_ray ray);
void	render_img(t_col *img, t_scene scene);
#endif
