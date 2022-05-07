/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:38:25 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/07 16:24:38 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt_lexer.h"
#include "ft_dprintf.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

void	*print_error(const char *error_msg)
{
	ft_dprintf(STDERR_FILENO, "Error\nminirt: %s.\n", error_msg);
	return (NULL);
}

void	*print_error_function(const char *function)
{
	ft_dprintf(STDERR_FILENO, "Error\nminirt: %s: %s.\n", function,
			strerror(errno));
	return (NULL);
}
