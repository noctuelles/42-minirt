/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:21:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/09 14:53:35 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_parser.h"
#include "minirt_types.h"
#include <stdlib.h>

bool	check_value(t_parser *parser)
{
	char	*value;
	bool	is_a_dot;

	is_a_dot = false;
	value = parser->curr_tkn->value;
	while (*value)
	{
		if (ft_isdigit(*value) == 0)
		{
			if (*value == '.')
			{
				if (!is_a_dot)
					is_a_dot = true;
				else
					return (false);
			}
			else
				return (false);
		}
		value++;
	}
	return (true);
}

void	*check_value_triplet(t_parser *parser)
{
	t_list	*save;

	save = parser->list_tkns;
	if (check_type(parser, T_VALUE, true) == NULL)
		return (NULL);
	if (check_type(parser, T_COMMA, true) == NULL)
		return (NULL);
	if (check_type(parser, T_VALUE, true) == NULL)
		return (NULL);
	if (check_type(parser, T_COMMA, true) == NULL)
		return (NULL);
	if (check_type(parser, T_VALUE, true) == NULL)
		return (NULL);
	if (check_type(parser, T_NEWLINE, true) == NULL)
		return (NULL);
	parser->list_tkns = save;
	parser->curr_tkn = parser->list_tkns->content;
	return (parser);
}

void	*check_type(t_parser *parser, t_token_type type, bool do_consume)
{
	if (parser->curr_tkn->type == type)
	{
		if (type == T_VALUE)
		{
			if (check_value(parser) == false)
				return (set_parser_errcode(parser, E_INVALID_VALUE));
		}
		if (do_consume)
			consume(parser, 1);
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

uint32_t	parse_rgb(t_parser *parser)
{
	uint32_t	rgb;

	rgb = (uint8_t) ft_atoi(parser->curr_tkn->value);
	consume(parser, 2);
	rgb = (rgb << 8) |  (uint8_t) ft_atoi(parser->curr_tkn->value);
	consume(parser, 2);
	rgb = (rgb << 8) |  (uint8_t) ft_atoi(parser->curr_tkn->value);
	consume(parser, 1);
	return (rgb);
}

t_ambiant_light	*parse_ambiant_light(t_parser *parser)
{
	t_ambiant_light	*ambiant_light;
	t_ambiant_light	obj;

	if (check_type(parser, T_VALUE, false) == false)
		return (NULL);
	obj.ratio = atof(parser->curr_tkn->value);
	if (obj.ratio < 0.0 || obj.ratio > 1.0)
		return (set_parser_errcode(parser, E_OUT_OF_RANGE));
	consume(parser, 1);
	if (check_value_triplet(parser) == NULL)
		return (NULL);
	obj.rgb = parse_rgb(parser);
	ambiant_light = malloc (sizeof(t_ambiant_light));
	if (!ambiant_light)
		return (set_parser_errcode(parser, E_MALLOC)); 
	*ambiant_light = obj;
	return (ambiant_light);
}
