/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objs_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:39:59 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/18 15:25:06 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_parser.h"
#include "minirt_types.h"
#include <stdlib.h>

t_object	*parse_cylinder(t_parser *parser)
{
	t_object	*cylinder;
	t_object	obj;
	char		*tkn_value;

	obj.type = OBJ_CYLINDER;
	if (parse_coords(parser, &obj.coord, set_range(0.0, 0.0)) == NULL)
		return (NULL);
	if (parse_coords(parser, &obj.vec, set_range(-1.0, 1.0)) == NULL)
		return (NULL);
	if (check_type(parser, T_VALUE, &tkn_value, true) == NULL)
		return (set_parser_errcode(parser, E_EXPECTED_VALUE));
	if (!check_double_value(parser, tkn_value, &obj.diameter, set_range(0, 0)))
		return (NULL);
	if (check_type(parser, T_VALUE, &tkn_value, true) == NULL)
		return (set_parser_errcode(parser, E_EXPECTED_VALUE));
	if (check_double_value(parser, tkn_value, &obj.height, set_range(0, 0))
			== NULL)
		return (NULL);
	if (parse_rgb(parser, &obj.rgb) == NULL)
		return (NULL);
	cylinder = ft_calloc(1, sizeof(t_object));
	if (!cylinder)
		return (set_parser_errcode(parser, E_MALLOC)); 
	*cylinder = obj;
	return (cylinder);
}
