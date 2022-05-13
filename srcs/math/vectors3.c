/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:24:49 by maabidal          #+#    #+#             */
/*   Updated: 2022/05/13 17:33:02 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_math.h"

t_vec	new_v(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
