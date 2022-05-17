/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:38:25 by plouvel           #+#    #+#             */
/*   Updated: 2022/05/17 17:20:21 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt_parser.h"
#include "ft_dprintf.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

void	*print_error(const char *error_msg)
{
	ft_dprintf(STDERR_FILENO, "Error\nminirt: error: %s.\n", error_msg);
	return (NULL);
}

void	*print_error_function(const char *function)
{
	ft_dprintf(STDERR_FILENO, "Error\nminirt: %s: %s.\n", function,
			strerror(errno));
	return (NULL);
}

void	*print_error_line_nbr(const char *error_msg, size_t line_nbr)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_dprintf(STDERR_FILENO, error_msg, line_nbr + 1); 
	return (NULL);
}

void	*print_parser_errmsg(const char *error_msg, size_t line_nbr,
		const char *tkn_value)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_dprintf(STDERR_FILENO, error_msg, line_nbr + 1, tkn_value); 
	return (NULL);
}
