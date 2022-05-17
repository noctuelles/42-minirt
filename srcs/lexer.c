/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:54:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/17 14:18:28 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_lexer.h"
#include <stdlib.h>

static void	*quit(t_lexer *lexer, t_lexer_errcode errcode)
{
	ft_lstclear(&lexer->list_tkns, free_token);
	if (errcode == E_LEX_TOO_MUCH_AMLIGHT)
		print_error_line_nbr(STR_TOO_MUCH_AMLIGHT, lexer->line_nbr);
	else if (errcode == E_LEX_TOO_MUCH_CAMERA)
		print_error_line_nbr(STR_TOO_MUCH_CAMERA, lexer->line_nbr);
	else if (errcode == E_LEX_TOO_MUCH_LIGHT)
		print_error_line_nbr(STR_TOO_MUCH_LIGHT, lexer->line_nbr);
	else if (errcode == E_LEX_MALLOC)
		print_error_function(STR_FUNCTION_MALLOC);
	lexer->errcode = errcode;
	return (NULL);
}

static void	*finish_line(t_lexer *lexer)
{
	if (lexer->declared_ambiant_light > 1)
		return (quit(lexer, E_LEX_TOO_MUCH_AMLIGHT));
	else if (lexer->declared_camera > 1)
		return (quit(lexer, E_LEX_TOO_MUCH_CAMERA));
	else if (lexer->declared_light > 1)
		return (quit(lexer, E_LEX_TOO_MUCH_LIGHT));
	if (lexer->prev != lexer->line)
	{
		if (add_token_to_list(lexer, (char *) lexer->line,
				lexer->line - lexer->prev, T_VALUE) == NULL)
			return (quit(lexer, E_LEX_MALLOC));
	}
	lexer->line_nbr++;
	lexer->line = lexer->file_content[lexer->line_nbr];
	return (lexer);
}

t_list	*lex_file(t_lexer *lexer)
{
	while (lexer->file_content[lexer->line_nbr] != NULL)
	{
		lexer->prev = lexer->line;
		while (*lexer->line != '\0')
		{
			lexer->tkn = search_known_token(lexer->line);
			if (lexer->tkn.type != T_NULL)
			{
				if (lexer->line != lexer->prev)
				{
					if (add_token_to_list(lexer, (char *) lexer->prev,
							lexer->line - lexer->prev, T_VALUE) == NULL)
						return (quit(lexer, E_LEX_MALLOC));
				}
				if (add_known_token_to_list(lexer) == NULL)
					return (quit(lexer, E_LEX_MALLOC));
			}
			else
				lexer->line++;
		}
		if (!finish_line(lexer))
			return (NULL);
	}
	return (lexer->list_tkns);
}

t_list	*lex_from_file(const char *filename)
{
	t_lexer	lexer = {0};
	size_t			i;

	lexer.file_content = read_file(filename);
	if (!lexer.file_content)
		return (NULL);
	lexer.line = *lexer.file_content;
	lexer.list_tkns = lex_file(&lexer);
	i = 0;
	while (lexer.file_content[i] != NULL)
		free(lexer.file_content[i++]);
	free(lexer.file_content);
	return (lexer.list_tkns);
}

/* char *translate(t_token_type type)
{
	if (type == 0)
		return ("T_AMBIANT_LIGHT");
	if (type == 1)
		return ("T_CAMERA");
	if (type == 2)
		return ("T_LIGHT");
	if (type == 3)
		return ("T_SPHERE");
	if (type == 4)
		return ("T_PLAN");
	if (type == 5)
		return ("T_CYLINDER");
	if (type == 6)
		return ("T_VALUE");
	if (type == 7)
		return ("T_NEWLINE");
	if (type == 8)
		return ("T_COMMA");
	return ("NULL");
}

void	print_tokens(t_list *tkns)
{
	for (t_list *elem = tkns; elem; elem = elem->next)
	{
		t_token *tkn = elem->content;

		printf("<%s> ", translate(tkn->type));
		if (tkn->type == T_NEWLINE)
			printf("\n");
	}
}

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		t_list	*test_list = lex_from_file(argv[1]);
		if (test_list)
		{
			print_tokens(test_list);
		}
	}
}*/
