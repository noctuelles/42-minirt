/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:15:43 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/18 16:31:18 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_PARSER_H
# define MINIRT_PARSER_H

# include "minirt_lexer.h"
# include "minirt_types.h"

/******************************************************************************
 *                                  Macros                                    *
 *****************************************************************************/

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

/******************************************************************************
 *                              Typedef & Enum                                *
 *****************************************************************************/

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

typedef struct e_parser
{
	t_list	*list_tkns;
	t_list	*list_objs;
	char	*last_tkn_value;
	t_token	*curr_tkn;
	int		errcode;
	size_t	line_nbr;
}				t_parser;

/******************************************************************************
 *                            Functions Prototype                             *
 *****************************************************************************/

/* parsing_utils.c */

void		consume(t_parser *parser, size_t n);
void		*set_parser_errcode(t_parser *parser, t_parser_errcode errcode);
bool		is_an_identifier(t_parser *parser);
const char	*get_parser_err_msg(t_parser_errcode errcode);

/* parsing.c */

t_list	*parse_scene(const char *filename);

/* parsing_objs.c */

t_object	*parse_ambiant_light(t_parser *parser);
t_object	*parse_camera(t_parser *parser);
t_object	*parse_light(t_parser *parser);
t_object	*parse_sphere(t_parser *parser);
t_object	*parse_plan(t_parser *parser);

/* parsing_objs_2.c */

t_object	*parse_cylinder(t_parser *parser);

/* parsing_objs_utils.c */

void		*check_rgb_component(t_parser *parser, char c, char *value,
				uint32_t *rgb);
void		*check_double_value(t_parser *parser, char *str, double *value,
				t_range range);
void		*check_type(t_parser *parser, t_token_type type, char **tkn_value,
				bool do_consume);
void		*parse_rgb(t_parser *parser, uint32_t *rgb);
void		*parse_coords(t_parser *parser, t_coord3d *coord, t_range range);

static inline t_range	set_range(double r1, double r2)
{
	t_range	range;

	range.r1 = r1;
	range.r2 = r2;
	return (range);
}

#endif
