/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:38:05 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/10 19:11:20 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ssl.h"
#include "sha256.h"

t_arg	g_sha256_arguments[] = {
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
	}
};

void	bind_sha256_args(t_context *ctx)
{
	ctx->args[0].value = &ctx->algo_ctx.sha256.print;
	ctx->args[1].value = &ctx->algo_ctx.sha256.quiet;
	ctx->args[2].value = &ctx->algo_ctx.sha256.reverse;
	ctx->args[3].value = &ctx->algo_ctx.sha256.string;
	ctx->args[3].exec_after = sha256_cmd;
	ctx->cmd = sha256_cmd;
}

void	sha256_cmd(t_context *ctx)
{
	printf("algo name: %s\n", ctx->algo_name);
}
