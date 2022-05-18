/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:11:55 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/18 16:36:07 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_parser.h"
#include <errno.h>
#include <stdlib.h>

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

static t_list	*get_obj(t_parser *parser, t_token_type type)
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

static void	*quit(t_list **tkns, t_parser *parser, t_parser_errcode errcode)
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
	ft_lstclear(tkns, free_token);
	return (NULL);
}

static t_list	*parse_from_tkns(t_list *list_tkns)
{
	t_parser	parser;
	t_list		*elem;

	ft_memset(&parser, 0, sizeof(t_parser));
	parser.list_tkns = list_tkns;
	parser.curr_tkn = list_tkns->content;
	while (parser.list_tkns)
	{
		if (!is_an_identifier(&parser))
			return (quit(&list_tkns, &parser, E_EXPECTED_IDENTIFIER));
		elem = get_obj(&parser, parser.curr_tkn->type);
		if (!elem)
			return (quit(&list_tkns, &parser, E_KEEP));
		ft_lstadd_back(&parser.list_objs, elem);
		parser.line_nbr++;
	}
	ft_lstclear(&list_tkns, free_token);
	return (parser.list_objs);
}

t_list	*parse_scene(const char *filename)
{
	t_list	*tkns;
	t_list	*objs;

	tkns = lex_from_file(filename);
	if (!tkns)
		return (NULL);
	objs = parse_from_tkns(tkns);
	if (!objs)
		return (NULL);
	else
		return (objs);
}
