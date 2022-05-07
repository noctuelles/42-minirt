/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_lexer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:12:27 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/07 16:29:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_LEXER_H
# define MINIRT_LEXER_H

# include <stdint.h>
# include <sys/types.h>

# define STR_AMBIANT_LIGHT    "A"
# define STR_CAMERA           "C"
# define STR_LIGHT            "L"
# define STR_SPHERE           "sp"
# define STR_PLAN             "pl"
# define STR_CYLINDER         "cy"
# define STR_COMMA            ","

# define STR_ERROR                  "Error\n"
# define STR_OUT_OF_RANGE           "value out of range"
# define STR_INVALID_FILE_EXTENSION "invalid file extension"
# define STR_ERROR_FILE_READ        "an error occured during file reading"
# define STR_EMPTY_FILE             "empty file"
# define STR_FILE_EXTENSION         ".rt"

# define STR_FUNCTION_READ          "read"
# define STR_FUNCTION_OPEN          "open"

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_VALUE,
	T_NEWLINE,
	T_COMMA,
	T_NULL
}				t_token_type;

typedef struct e_token
{
	t_token_type	type;
	char			*value;
}				t_token;

size_t	get_file_nbr_lines(int fd);
char	**read_file(const char *filename);

void	*print_error(const char *error_msg);
void	*print_error_function(const char *function);

#endif
