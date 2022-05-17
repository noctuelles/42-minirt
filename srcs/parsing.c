/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:11:55 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/17 17:35:34 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_parser.h"
#include <errno.h>
#include <stdlib.h>

void	consume(t_parser *parser, size_t n)
{
	size_t	i;

	i = 0;
	while (i++ < n)
	{
		parser->last_tkn_value = parser->curr_tkn->value;
		parser->list_tkns = parser->list_tkns->next;
		if (parser->list_tkns)
			parser->curr_tkn = parser->list_tkns->content;
	}
}

static t_object	*get_obj_from_type(t_parser *parser, t_token_type type)
{
	t_object	*obj;

	obj = NULL;
	if (type == T_AMBIANT_LIGHT)
		obj = parse_ambiant_light(parser);
	else if (type == T_CAMERA)
		obj = parse_camera(parser);
	else if (type == T_LIGHT)
		obj = parse_light(parser);
	else if (type == T_SPHERE)
		obj = parse_sphere(parser);
	else if (type == T_PLAN)
		obj = parse_plan(parser);
	else if (type == T_CYLINDER)
		obj = parse_cylinder(parser);
	return (obj);
}

t_list	*get_obj(t_parser *parser, t_token_type type)
{
	t_list	*elem;
	void	*obj;

	consume(parser, 1);
	obj = get_obj_from_type(parser, type);
	if (!obj)
	{
		if (errno)
			return (set_parser_errcode(parser, E_MALLOC));
		else
			return (NULL);
	}
	else
	{
		if (!check_type(parser, T_NEWLINE, NULL, true))
			return (NULL);
		elem = ft_lstnew(obj);
		if (!elem)
		{
			free(obj);
			return (set_parser_errcode(parser, E_MALLOC));
		}
	}
	return (elem);
}

static void	*quit(t_parser *parser, t_parser_errcode errcode)
{
	char	*tkn_value;

	if (errcode != E_KEEP)
		parser->errcode = errcode;
	ft_lstclear(&parser->list_objs, free);
	if (parser->errcode == E_INVALID_VALUE
			|| parser->errcode == E_INVALID_RANGE)
		tkn_value = parser->last_tkn_value;
	else
		tkn_value = parser->curr_tkn->value;
	print_parser_errmsg(get_parser_err_msg(parser->errcode), parser->line_nbr,
			tkn_value);
	return (NULL);
}

t_list	*parse(t_list *list_tkns)
{
	t_parser	parser;
	t_list		*elem;

	ft_memset(&parser, 0 ,sizeof(t_parser));
	parser.list_tkns = list_tkns;
	parser.curr_tkn = list_tkns->content;
	while (parser.list_tkns)
	{
		if (!is_an_identifier(&parser))
			return (quit(&parser, E_EXPECTED_IDENTIFIER));
		elem = get_obj(&parser, parser.curr_tkn->type);
		if (!elem)
			return (quit(&parser, E_KEEP));
		ft_lstadd_back(&parser.list_objs, elem);
		parser.line_nbr++;
	}
	return (parser.list_objs);
}
