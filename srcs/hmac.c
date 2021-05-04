/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:47:49 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 14:17:17 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"

t_arg			g_hmac_arguments[] = {
	{
		.type = ARG_STRING,
		.name = "s",
		.description = "print the hmac of the given string"
	},
	{
		.type = ARG_STRING,
		.name = "k",
		.description = "key used in hmac algorithm"
	},
	{
		.type = ARG_END
	}
};

void	hmac_log_command_usage(t_context *ctx)
{
	ft_putf_fd(STDERR_FILENO
		, "usage: ft_ssl %s [-s string] [-k key]\n", ctx->algo_name);
}
