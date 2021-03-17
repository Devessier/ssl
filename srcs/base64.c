/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:17:14 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/17 12:46:47 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "base64.h"

t_arg		g_base64_arguments[] = {
	{
		.type = ARG_NOOP,
		.name = "e",
		.description = "encodes input (default)"
	},
	{
		.type = ARG_NOOP,
		.name = "d",
		.description = "decodes input"
	},
	{
		.type = ARG_STRING,
		.name = "i",
		.description = "input file (default: stdin)"
	},
	{
		.type = ARG_STRING,
		.name = "o",
		.description = "output file (default: stdout)"
	},
	{
		.type = ARG_POSITIVE_INTEGER,
		.name = "b",
		.description = "break encoded string into num character lines"
	},
	{
		.type = ARG_END
	}
};

static void	activate_encoding_mode(t_context *ctx)
{
	ctx->algo_ctx.base64.is_encoding = true;
}

static void	activate_decoding_mode(t_context *ctx)
{
	ctx->algo_ctx.base64.is_encoding = false;
}

void		bind_base64_args(t_context *ctx)
{
	ctx->algo_ctx.base64.is_encoding = true;
	ctx->args[0].exec_after = activate_encoding_mode;
	ctx->args[1].exec_after = activate_decoding_mode;
	ctx->args[2].value = &ctx->algo_ctx.base64.input_file;
	ctx->args[3].value = &ctx->algo_ctx.base64.output_file;
	ctx->args[4].value = &ctx->algo_ctx.base64.line_break;
	ctx->cmd = base64_cmd;
}

void		base64_log_command_usage(t_context *ctx)
{
	(void)ctx;

	ft_putf_fd(STDERR_FILENO
		, "usage: ft_ssl base64 [-ed] [-b num] [-i in_file] [-o out_file]\n");
}

void						base64_cmd(t_context *ctx)
{
	if (ctx->algo_ctx.base64.is_encoding)
		base64_encode_cmd(ctx);
	else
		base64_decode_cmd(ctx);
}
