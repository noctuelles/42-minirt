/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 17:37:35 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/17 17:43:17 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_parser.h"
#include "minirt_types.h"

void	*check_rgb_component(t_parser *parser, char c, char *value,
		uint32_t *rgb)
{
	uint16_t	component_value;

	if (ft_strlen(value) <= 3 && ft_stronly_digits(value))
	{
		component_value = ft_atoi(value);
		if (component_value >= 0 && component_value <= 255)
		{
			if (c == 'R')
				*rgb = component_value;
			else if (c == 'G')
				*rgb |= component_value << 8;
			else if (c == 'B')
				*rgb |= component_value << 16;
		}
		else
			return (set_parser_errcode(parser, E_INVALID_RANGE));
	}
	else
		return (set_parser_errcode(parser, E_INVALID_VALUE));
	return (parser);
}

void	*check_double_value(t_parser *parser, char *str, double *value,
		t_range range)
{
	bool	is_a_dot;
	size_t	i;

	is_a_dot = false;
	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (set_parser_errcode(parser, E_INVALID_VALUE));
	while (str[i] != '\0')
	{
		if (str[i] == '.')
		{
			if (is_a_dot == false)
				is_a_dot = true;
			else
			return (set_parser_errcode(parser, E_INVALID_VALUE));
		}
		else if (!(str[i] >= '0' && str[i] <= '9'))
			return (set_parser_errcode(parser, E_INVALID_VALUE));
		i++;
	}
	*value = strtod(str, NULL);
	if ((range.r1 != range.r2) && !(*value >= range.r1 && *value <= range.r2))
		return (set_parser_errcode(parser, E_INVALID_RANGE));
	return (parser);
}

void	*check_type(t_parser *parser, t_token_type type, char **tkn_value,
		bool do_consume)
{
	if (parser->curr_tkn->type == type)
	{
		if (do_consume)
		{
			if (tkn_value)
				*tkn_value = parser->curr_tkn->value;
			consume(parser, 1);
		}
		return (parser);
	}
	if (type == T_VALUE)
		return (set_parser_errcode(parser, E_EXPECTED_VALUE));
	if (type == T_COMMA)
		return (set_parser_errcode(parser, E_EXPECTED_COMMA));
	if (type == T_NEWLINE)
		return (set_parser_errcode(parser, E_EXPECTED_NEWLINE));
	return (NULL);
}

void	*parse_rgb(t_parser *parser, uint32_t *rgb)
{
	char	*tkn_value;
	if (check_type(parser, T_VALUE, &tkn_value, true) == NULL
			|| check_rgb_component(parser, 'R', tkn_value, rgb) == NULL)
		return (NULL);
	if (check_type(parser, T_COMMA, &tkn_value, true) == NULL)
		return (NULL);
	if (check_type(parser, T_VALUE, &tkn_value, true) == NULL
			|| check_rgb_component(parser, 'G', tkn_value, rgb) == NULL)
		return (NULL);
	if (check_type(parser, T_COMMA, &tkn_value, true) == NULL)
		return (NULL);
	if (check_type(parser, T_VALUE, &tkn_value, true) == NULL
			|| check_rgb_component(parser, 'B', tkn_value, rgb) == NULL)
		return (NULL);
	return (parser);
}

void	*parse_coords(t_parser *parser, t_coord3d *coord, t_range range)
{
	char	*tkn_value;

	if (check_type(parser, T_VALUE, &tkn_value, true) == NULL
			|| check_double_value(parser, tkn_value, &coord->x, range) == NULL)
		return (NULL);
	if (check_type(parser, T_COMMA, &tkn_value, true) == NULL)
		return (NULL);
	if (check_type(parser, T_VALUE, &tkn_value, true) == NULL
			|| check_double_value(parser, tkn_value, &coord->y, range) == NULL)
		return (NULL);
	if (check_type(parser, T_COMMA, &tkn_value, true) == NULL)
		return (NULL);
	if (check_type(parser, T_VALUE, &tkn_value, true) == NULL
			|| check_double_value(parser, tkn_value, &coord->z, range) == NULL)
		return (NULL);
	return (parser);
}

bool	is_an_identifier(t_parser *parser)
{
	t_token_type	type;

	type = parser->curr_tkn->type;
	if (type == T_AMBIANT_LIGHT || type == T_CAMERA
		|| type == T_LIGHT || type == T_SPHERE
		|| type == T_PLAN || type == T_CYLINDER)
		return (true);
	else
		return (false);
}
