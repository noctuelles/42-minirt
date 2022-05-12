/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:54:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/07 18:23:30 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_lexer.h"
#include <stdlib.h>

t_token	*add_token_to_list(t_lexer *lexer, char *value, size_t len,
		t_token_type type)
{
	char	*str;
	t_list	*elem;
	t_token	*tkn;

	str = value;
	if (type == T_VALUE)
	{
		str = ft_strndup(value, len);
		if (!str)
			return (NULL);
	}
	tkn = new_token(str, len, type);
	if (!tkn)
	{
		if (str != value)
			free(str);
		return (NULL);
	}
	elem = ft_lstnew(tkn);
	if (!elem)
	{
		free_token(tkn);
		return (NULL);
	}
	ft_lstadd_back(&lexer->list_tkns, elem);
	return (tkn);
}

void	*add_known_token_to_list(t_lexer *lexer)
{
	lexer->line += lexer->tkn.len;
	if (lexer->tkn.type == T_AMBIANT_LIGHT)
		lexer->declared_ambiant_light++;
	if (lexer->tkn.type == T_CAMERA)
		lexer->declared_camera++;
	if (lexer->tkn.type == T_LIGHT)
		lexer->declared_light++;
	if (lexer->tkn.type != T_BREAK)
	{
		if (add_token_to_list(lexer, lexer->tkn.value, lexer->tkn.len,
					lexer->tkn.type) == NULL)
			return (NULL);
	}
	lexer->prev = lexer->line;
	return (lexer);
}

t_list	*lex_file(char **file)
{
	t_lexer	lexer = {0};

	lexer.line = *file;
	while (*file != NULL)
	{
		lexer.prev = lexer.line;
		while (*lexer.line != '\0')
		{
			lexer.tkn = search_known_token(lexer.line);
			if (lexer.tkn.type != T_NULL)
			{
				if (lexer.line != lexer.prev)
				{
					if (add_token_to_list(&lexer, (char *) lexer.prev,
							lexer.line - lexer.prev, T_VALUE) == NULL)
					{
					}
				}
				if (add_known_token_to_list(&lexer) == NULL)
				{

				}
			}
			else
				lexer.line++;
		}
		if (lexer.prev != lexer.line)
		{
			if (add_token_to_list(&lexer, (char *) lexer.line,
					lexer.line - lexer.prev, T_VALUE) == NULL)
			{
			}
		}
		file++;
		lexer.line = *file;
	}
	return (lexer.list_tkns);
}

char *translate(t_token_type type)
{
	if (type == 0)
		return ("T_AMBIANT_LIGHT");
	if (type == 1)
		return ("T_CAMERA");
}

int main(int argc, char **argv)
{
	char **file = read_file(argv[1]);
	t_list *list = lex_file(file);

	for (t_list *elem = list; elem; elem = elem->next)
	{
		t_token *tkn = elem->content;
		printf("<%d> : \"%s\"\n", tkn->type, tkn->value);
	}
}
