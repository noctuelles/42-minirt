/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:21:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/16 20:11:48 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_parser.h"
#include "minirt_types.h"
#include <stdlib.h>

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
			return (set_parser_errcode(parser, E_RGB_INVALID_VALUE));
	}
	else
		return (set_parser_errcode(parser, E_INVALID_VALUE));
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
	if (check_type(parser, T_NEWLINE, &tkn_value, true) == NULL)
		return (NULL);
	return (parser);
}

void	*parse_ratio(t_parser *parser, float *ratio)
{
	char	*tkn_value;

	if (check_type(parser, T_VALUE, &tkn_value, true) == false)
		return (NULL);
	if (ft_strlen(tkn_value) < 3)
		return (set_parser_errcode(parser, E_INVALID_VALUE));
	if (tkn_value[0] != '0' || tkn_value[0] != '1' || tkn_value[1] != '.')
		return (set_parser_errcode(parser, E_VALUE_INVALID_CHARS));
	if (ft_stronly_digits(&tkn_value[2]))
	{
		*ratio = atof(tkn_value);
		if (*ratio < 0.0 || *ratio > 1.0)
			return (set_parser_errcode(parser, E_OUT_OF_RANGE));
	}
	else
		return (set_parser_errcode(parser, E_INVALID_VALUE));
	return (parser);
}


bool	is_an_identifier(t_parser *parser)
{
	t_token_type	type;

	type = parser->curr_tkn->type;
	if (type == T_AMBIANT_LIGHT || type == T_CAMERA
		|| type == T_LIGHT || type == T_SPHERE
		|| type == T_PLAN || type == T_CYLINDER)
	{
		consume(parser, 1);
		return (true);
	}
	else
		return (false);
}

t_ambiant_light	*parse_ambiant_light(t_parser *parser)
{
	t_ambiant_light	*ambiant_light;
	t_ambiant_light	obj;

	if (parse_ratio(parser, &obj.ratio) == NULL)
		return (NULL);
	if (parse_rgb(parser, &obj.rgb) == NULL)
		return (NULL);
	ambiant_light = malloc (sizeof(t_ambiant_light));
	if (!ambiant_light)
		return (set_parser_errcode(parser, E_MALLOC)); 
	*ambiant_light = obj;
	return (ambiant_light);
}
