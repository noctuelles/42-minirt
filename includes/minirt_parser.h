/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:16:58 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/17 17:30:58 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_PARSER_H
# define MINIRT_PARSER_H

#include "minirt_lexer.h"
#include "minirt_types.h"

typedef enum e_parser_errcode
{
	E_KEEP,
	E_INVALID_VALUE,
	E_INVALID_RANGE,
	E_EXPECTED_COMMA,
	E_EXPECTED_IDENTIFIER,
	E_EXPECTED_VALUE,
	E_MALLOC,
	E_EXPECTED_NEWLINE
}				t_parser_errcode;

typedef enum e_value_type
{
	V_RGB,
	V_RANGE
}			t_value_type;

# define STR_INVALID_VALUE       "minirt: line %u: '%s': \
invalid value.\n"
# define STR_INVALID_RANGE       "minirt: line %u: '%s': \
invalid range.\n"
# define STR_EXPECTED_COMMA      "minirt: line %u: '%s': \
expected comma.\n"
# define STR_EXPECTED_IDENTIFIER "minirt: line %u: '%s': \
expected identifier.\n"
# define STR_EXPECTED_VALUE      "minirt: line %u: '%s': \
expected value.\n"
# define STR_EXPECTED_NEWLINE    "minirt: line %u: '%s': \
expected newline.\n"

# define FOV_MIN  0
# define FOV_MAX  180

typedef struct e_parser
{
	t_list	*list_tkns;
	t_list	*list_objs;
	char	*last_tkn_value;
	t_token	*curr_tkn;
	int		errcode;
	size_t	line_nbr;
}				t_parser;

void	consume(t_parser *parser, size_t n);
void	*check_rgb_component(t_parser *parser, char c, char *value,
		uint32_t *rgb);
void	*check_type(t_parser *parser, t_token_type type, char **tkn_value,
		bool do_consume);
void	*set_parser_errcode(t_parser *parser, t_parser_errcode errcode);
bool	is_an_identifier(t_parser *parser);

const char	*get_parser_err_msg(t_parser_errcode errcode);
t_list			*parse(t_list *list_tkns);
t_object		*parse_ambiant_light(t_parser *parser);
t_object		*parse_camera(t_parser *parser);
t_object		*parse_light(t_parser *parser);
t_object		*parse_sphere(t_parser *parser);
t_object		*parse_plan(t_parser *parser);
t_object		*parse_cylinder(t_parser *parser);

/* io_utils.c */

const char	*get_parser_errmsg(t_parser_errcode errcode);

#endif
