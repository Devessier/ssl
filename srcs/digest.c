/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:05:37 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/22 15:21:03 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"

t_arg	g_digest_arguments[] = {
	{
		.type = ARG_BOOLEAN,
		.name = "p",
		.description = "echo STDIN to STDOUT and append the checksum to STDOUT"
	},
	{
		.type = ARG_BOOLEAN,
		.name = "q",
		.description = "quiet mode"
	},
	{
		.type = ARG_BOOLEAN,
		.name = "r",
		.description = "reverse the format of the output"
	},
	{
		.type = ARG_STRING,
		.name = "s",
		.description = "print the sum of the given string"
	},
	{
		.type = ARG_END
	}
};

void	log_digest_command_usage(t_context *ctx)
{
	ft_putf_fd(STDERR_FILENO
		, "usage: ft_ssl %s [-p] [-q] [-r] [-s string] [files ...]\n"
		, ctx->algo_name);
}
