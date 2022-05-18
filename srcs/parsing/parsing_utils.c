/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:37:51 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/18 15:21:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_parser.h"

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

void	*set_parser_errcode(t_parser *parser, t_parser_errcode errcode)
{
	parser->errcode = errcode;
	return (NULL);
}

const char	*get_parser_err_msg(t_parser_errcode errcode)
{
	if (errcode == E_INVALID_VALUE)
		return (STR_INVALID_VALUE);
	else if (errcode ==  E_INVALID_RANGE)
		return (STR_INVALID_RANGE);
	else if (errcode == E_EXPECTED_COMMA)
		return (STR_EXPECTED_COMMA);
	else if (errcode == E_EXPECTED_IDENTIFIER)
		return (STR_EXPECTED_IDENTIFIER);
	else if (errcode == E_EXPECTED_VALUE)
		return (STR_EXPECTED_VALUE);
	else if (errcode == E_EXPECTED_NEWLINE)
		return (STR_EXPECTED_NEWLINE);
	else
		return (NULL);
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
