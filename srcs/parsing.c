/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:11:55 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/17 17:06:39 by plouvel          ###   ########.fr       */
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
	if (!check_type(parser, T_NEWLINE, NULL, true))
		return (NULL);
	if (!obj)
	{
		if (errno)
			return (set_parser_errcode(parser, E_MALLOC));
		else
			return (NULL);
	}
	elem = ft_lstnew(obj);
	if (!elem)
	{
		free(obj);
		return (set_parser_errcode(parser, E_MALLOC));
	}
	return (elem);
}

static void	*quit(t_parser *parser)
{
	ft_lstclear(&parser->list_objs, free);
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
			return (set_parser_errcode(&parser, E_EXPECTED_IDENTIFIER));
		elem = get_obj(&parser, parser.curr_tkn->type);
		ft_lstadd_back(&parser.list_objs, elem);
	}
	return (parser.list_objs);
}
