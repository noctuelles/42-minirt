/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:21:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/18 15:28:58 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_parser.h"
#include "minirt_types.h"
#include <stdlib.h>

t_object	*parse_ambiant_light(t_parser *parser)
{
	t_object	*ambiant_object;
	t_object	obj;
	char		*tkn_value;

	obj.type = OBJ_AM_LIGHT;
	if (!check_type(parser, T_VALUE, &tkn_value, true))
		return (set_parser_errcode(parser, E_EXPECTED_VALUE));
	if (!check_double_value(parser, tkn_value, &obj.ratio, set_range(0, 1)))
		return (NULL);
	if (!parse_rgb(parser, &obj.rgb))
		return (NULL);
	ambiant_object = ft_calloc (1, sizeof(t_object));
	if (!ambiant_object)
		return (set_parser_errcode(parser, E_MALLOC));
	ambiant_object->ratio = obj.ratio;
	ambiant_object->rgb = obj.rgb;
	return (ambiant_object);
}

t_object	*parse_camera(t_parser *parser)
{
	t_object	*camera;
	t_object	obj;
	char		*tkn_value;

	obj.type = OBJ_CAMERA;
	if (!parse_coords(parser, &obj.coord, set_range(0.0, 0.0)))
		return (NULL);
	if (!parse_coords(parser, &obj.vec, set_range(-1.0, 1.0)))
		return (NULL);
	if (!check_type(parser, T_VALUE, &tkn_value, true))
		return (NULL);
	if (ft_stronly_digits(tkn_value))
	{
		obj.fov = ft_atoi(tkn_value);
		if (!(obj.fov >= FOV_MIN && obj.fov <= FOV_MAX))
			return (set_parser_errcode(parser, E_INVALID_RANGE));
	}
	else
		return (set_parser_errcode(parser, E_INVALID_VALUE));
	camera = ft_calloc(1, sizeof(t_object));
	if (!camera)
		return (set_parser_errcode(parser, E_MALLOC));
	*camera = obj;
	return (camera);
}

t_object	*parse_light(t_parser *parser)
{
	t_object	*light;
	t_object	obj;
	char		*tkn_value;

	obj.type = OBJ_LIGHT;
	if (!parse_coords(parser, &obj.coord, set_range(0.0, 0.0)))
		return (NULL);
	if (!check_type(parser, T_VALUE, &tkn_value, true))
		return (set_parser_errcode(parser, E_EXPECTED_VALUE));
	if (!check_double_value(parser, tkn_value, &obj.ratio, set_range(0, 1)))
		return (NULL);
	if (!parse_rgb(parser, &obj.rgb))
		return (NULL);
	light = ft_calloc(1, sizeof(t_object));
	if (!light)
		return (set_parser_errcode(parser, E_MALLOC));
	*light = obj;
	return (light);
}

t_object	*parse_sphere(t_parser *parser)
{
	t_object	*sphere;
	t_object	obj;
	char		*tkn_value;

	obj.type = OBJ_SPHERE;
	if (!parse_coords(parser, &obj.coord, set_range(0.0, 0.0)))
		return (NULL);
	if (!check_type(parser, T_VALUE, &tkn_value, true))
		return (set_parser_errcode(parser, E_EXPECTED_VALUE));
	if (!check_double_value(parser, tkn_value, &obj.diameter, set_range(0, 0)))
		return (NULL);
	if (!parse_rgb(parser, &obj.rgb))
		return (NULL);
	if (obj.diameter < 0)
		return (set_parser_errcode(parser, E_INVALID_RANGE));
	sphere = ft_calloc(1, sizeof(t_object));
	if (!sphere)
		return (set_parser_errcode(parser, E_MALLOC));
	*sphere = obj;
	return (sphere);
}

t_object	*parse_plan(t_parser *parser)
{
	t_object	*plan;
	t_object	obj;

	obj.type = OBJ_PLAN;
	if (!parse_coords(parser, &obj.coord, set_range(0.0, 0.0)))
		return (NULL);
	if (!parse_coords(parser, &obj.vec, set_range(-1.0, 1.0)))
		return (NULL);
	if (!parse_rgb(parser, &obj.rgb))
		return (NULL);
	plan = ft_calloc(1, sizeof(t_object));
	if (!plan)
		return (set_parser_errcode(parser, E_MALLOC));
	*plan = obj;
	return (plan);
}
