/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:56:35 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/17 14:04:25 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt_lexer.h"
#include <stdlib.h>

t_token	search_known_token(const char *str)
{
	if (ft_strncmp(str, STR_SPHERE, 2) == 0)
		return (set_token(STR_SPHERE, T_SPHERE));
	if (ft_strncmp(str, STR_PLAN, 2) == 0)
		return (set_token(STR_PLAN, T_PLAN));
	if (ft_strncmp(str, STR_CYLINDER, 2) == 0)
		return (set_token(STR_CYLINDER, T_CYLINDER));
	if (ft_strncmp(str, STR_AMBIANT_LIGHT, 1) == 0)
		return (set_token(STR_AMBIANT_LIGHT, T_AMBIANT_LIGHT));
	if (ft_strncmp(str, STR_CAMERA, 1) == 0)
		return (set_token(STR_CAMERA, T_CAMERA));
	if (ft_strncmp(str, STR_LIGHT, 1) == 0)
		return (set_token(STR_LIGHT, T_LIGHT));
	if (ft_strncmp(str, STR_COMMA, 1) == 0)
		return (set_token(STR_COMMA, T_COMMA));
	if (ft_strncmp(str, STR_NEWLINE, 1) == 0)
		return (set_token(STR_NEWLINE, T_NEWLINE));
	if (ft_strncmp(str, STR_SPACE, 1) == 0)
		return (set_token(STR_SPACE, T_BREAK));
	if (ft_strncmp(str, STR_TAB, 1) == 0)
		return (set_token(STR_TAB, T_BREAK));
	return (set_token(NULL, T_NULL));
}

void	*add_known_token_to_list(t_lexer *lexer)
{
	lexer->line += lexer->tkn.len;
	if (lexer->tkn.type != T_BREAK)
	{
		if (lexer->tkn.type == T_AMBIANT_LIGHT)
			lexer->declared_ambiant_light++;
		if (lexer->tkn.type == T_CAMERA)
			lexer->declared_camera++;
		if (lexer->tkn.type == T_LIGHT)
			lexer->declared_light++;
		if (add_token_to_list(lexer, lexer->tkn.value, lexer->tkn.len,
					lexer->tkn.type) == NULL)
			return (NULL);
	}
	lexer->prev = lexer->line;
	return (lexer);
}

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
