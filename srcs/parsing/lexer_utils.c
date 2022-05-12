/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:56:35 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/07 17:59:56 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt_lexer.h"
#include <stdlib.h>

t_token	set_token(char *str, t_token_type type)
{
	t_token	tkn;

	tkn.value = str;
	tkn.type = type;
	if (str)
		tkn.len = ft_strlen(str);
	return (tkn);
}

t_token	*new_token(char *str, size_t len, t_token_type type)
{
	t_token	*tkn;

	tkn = malloc(sizeof(t_token));
	if (!tkn)
		return (NULL);
	tkn->value = str;
	tkn->len = len;
	tkn->type = type;
	return (tkn);
}

void	free_token(void *token)
{
	t_token	*tkn;

	tkn = token;
	if (tkn->type == T_VALUE)
		free(tkn->value);
	free(tkn);
}

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
