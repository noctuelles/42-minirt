/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:16:58 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/16 20:11:50 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_PARSER_H
# define MINIRT_PARSER_H

#include "minirt_lexer.h"
#include "minirt_types.h"

typedef enum e_parser_errcode
{
	E_NO,
	E_INVALID_VALUE,
	E_VALUE_INVALID_CHARS,
	E_RGB_INVALID_VALUE,
	E_EXPECTED_COMMA,
	E_EXPECTED_IDENTIFIER,
	E_EXPECTED_VALUE,
	E_OUT_OF_RANGE,
	E_MALLOC,
	E_EXPECTED_NEWLINE
}				t_parser_errcode;

typedef enum e_value_type
{
	V_RGB,
	V_RANGE
}			t_value_type;

# define STR_INVALID_VALUE       "invalid value '%s'"
# define STR_RGB_INVALID_VALUE   "invalid value '%s'"
# define STR_VALUE_INVALID_CHARS "invalid value '%s': value can only contains digits."
# define STR_RGB_INVALID_RANGE   "invalid value '%s': must be within 0-255 range."
# define STR_RATIO_INVALID_RANGE "invalid value '%s': must be within 0.0-0.1 range."
# define STR_EXPECTED_COMMA      "expected comma after value '%s'"
# define STR_EXPECTED_IDENTIFIER "expected identifier"
# define STR_EXPECTED_VALUE      "expected value after '%s'"
# define STR_OUT_OF_RANGE        "value out of range '%s'"
# define STR_EXPECTED_NEWLINE    "expected newline after '%s'"

typedef struct e_parser
{
	t_list	*list_tkns;
	t_list	*list_objs;
	t_token	*curr_tkn;
	int		errcode;
}				t_parser;

void	consume(t_parser *parser, size_t n);
void	*check_rgb_component(t_parser *parser, char c, char *value,
		uint32_t *rgb);
void	*set_parser_errcode(t_parser *parser, t_parser_errcode errcode);
bool	is_an_identifier(t_parser *parser);

t_ambiant_light	*parse_ambiant_light(t_parser *parser);

#endif
