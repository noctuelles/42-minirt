/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_lexer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:22:59 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/18 15:25:01 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_LEXER_H
# define MINIRT_LEXER_H

# include "libft.h"
# include <stdint.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdbool.h>

/******************************************************************************
 *                                  Macros                                    *
 *****************************************************************************/

# define STR_AMBIANT_LIGHT    "A"
# define STR_CAMERA           "C"
# define STR_LIGHT            "L"
# define STR_COMMA            ","
# define STR_NEWLINE          "\n"
# define STR_TAB              "\t"
# define STR_SPACE            " "
# define STR_SPHERE           "sp"
# define STR_PLAN             "pl"
# define STR_CYLINDER         "cy"

# define STR_ERROR                  "Error\n"
# define STR_INVALID_FILE_EXTENSION "invalid file extension"
# define STR_ERROR_FILE_READ        "an error occured during file reading"
# define STR_EMPTY_FILE             "empty file"

# define STR_TOO_MUCH_AMLIGHT       "minirt: line %u: ambiant light cannot be \
declared more than once.\n"
# define STR_TOO_MUCH_CAMERA        "minirt: line %u: camera cannot be \
declared more than once.\n"
# define STR_TOO_MUCH_LIGHT         "minirt: line %u: light cannot be \
declared more than once.\n"

# define STR_FILE_EXTENSION         ".rt"

# define STR_FUNCTION_READ          "read"
# define STR_FUNCTION_OPEN          "open"
# define STR_FUNCTION_MALLOC        "malloc"

/******************************************************************************
 *                              Typedef & Enum                                *
 *****************************************************************************/

typedef enum e_token_type
{
	T_AMBIANT_LIGHT,
	T_CAMERA,
	T_LIGHT,
	T_SPHERE,
	T_PLAN,
	T_CYLINDER,
	T_VALUE,
	T_NEWLINE,
	T_COMMA,
	T_BREAK,
	T_NULL
}				t_token_type;

typedef struct e_token
{
	t_token_type	type;
	size_t			len;
	char			*value;
}				t_token;

typedef enum e_lexer_errcode
{
	E_LEX_TOO_MUCH_AMLIGHT,
	E_LEX_TOO_MUCH_CAMERA,
	E_LEX_TOO_MUCH_LIGHT,
	E_LEX_MALLOC
}			t_lexer_errcode;

typedef struct e_lexer
{
	char				**file_content;
	t_list				*list_tkns;
	t_token				tkn;
	const char			*line;
	const char			*prev;
	unsigned int		declared_ambiant_light;
	unsigned int		declared_camera;
	unsigned int		declared_light;
	size_t				line_nbr;
	t_lexer_errcode		errcode;
}				t_lexer;

/******************************************************************************
 *                            Functions Prototype                             *
 *****************************************************************************/

/* file.c */

char	**read_file(const char *filename);

/* file_utils.c */

size_t	get_file_nbr_lines(int fd);

/* io_utils.c */

void	*print_error(const char *error_msg);
void	*print_error_function(const char *function);
void	*print_error_line_nbr(const char *error_msg, size_t line_nbr);
void	*print_parser_errmsg(const char *error_msg, size_t line_nbr,
			const char *tkn_value);

/* tokens.c */

t_token	set_token(char *str, t_token_type type);
t_token	*new_token(char *str, size_t len, t_token_type type);
void	free_token(void *token);

/* lexer_utils.c */

void	*add_known_token_to_list(t_lexer *lexer);
t_token	search_known_token(const char *str);
t_token	*add_token_to_list(t_lexer *lexer, char *value, size_t len,
			t_token_type type);

#endif
