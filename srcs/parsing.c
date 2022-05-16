/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:11:55 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/16 20:11:49 by plouvel          ###   ########.fr       */
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
		parser->curr_tkn = parser->list_tkns->content;
	}
}

t_list	*route(t_parser *parser, t_token_type type)
{
	t_list	*elem;
	void	*obj;

	obj = NULL;
	if (type == T_AMBIANT_LIGHT)
		obj = parse_ambiant_light(parser);
	if (check_type(parser, T_NEWLINE, NULL,  false) == false)
	{
		free(obj);
		return (NULL);
	}
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

t_list	*parse(t_list *list_tkns)
{
	t_parser	parser;
	t_list		*elem;

	parser.list_tkns = list_tkns;
	parser.curr_tkn = list_tkns->content;
	while (parser.list_tkns)
	{
		if (!is_an_identifier(&parser))
			return (set_parser_errcode(&parser, E_EXPECTED_IDENTIFIER));
		elem = route(&parser, parser.curr_tkn->type);
		ft_lstadd_back(&parser.list_objs, elem);
		consume(&parser, 1);
	}
	return (parser.list_objs);
}
