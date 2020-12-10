/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:28:48 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/10 16:59:12 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ssl.h"
#include "usage.h"

void			print_usage(void)
{
	write(STDERR_FILENO,
		"usage: ft_ssl command [command opts] [command args]\n", 52);
}

static void		print_available_commands_for_algo_type(t_algo_type type)
{
	t_algo_desc	*desc;

	desc = g_algorithms;
	while (desc->algo != ALGO_INVALID)
	{
		if (desc->type == type)
			ft_putf_fd(STDERR_FILENO, "%s\n", desc->name);
		desc++;
	}
}

static void		print_available_commands(void)
{
	const t_algo_type_desc	descs[] = {
		{ ALGO_STANDARD, "Standard" },
		{ ALGO_DIGEST, "Message Digest" },
		{ ALGO_CIPHER, "Cipher" },
		{ ALGO_TYPE_NONE, NULL },
	};
	const int				descs_len = 3;
	t_algo_type_desc		*desc;
	int						index;

	desc = (t_algo_type_desc *)descs;
	index = 0;
	while (desc->type != ALGO_TYPE_NONE)
	{
		ft_putf_fd(STDERR_FILENO, "%s commands:\n", desc->name);
		print_available_commands_for_algo_type(desc->type);
		if (index < descs_len - 1)
			ft_putchar_fd('\n', STDERR_FILENO);
		desc++;
		index++;
	}
}

void			print_unavailable_command_usage(const char *invalid_command)
{
	ft_putf_fd(2, "ft_ssl: Error: '%s' is an invalid command.\n\n"
		, invalid_command);
	print_available_commands();
}
