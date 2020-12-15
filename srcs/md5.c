/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:36:52 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/15 20:54:20 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "md5.h"

t_arg	g_md5_arguments[] = {
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

void	bind_md5_args(t_context *ctx)
{
	ctx->args[0].value = &ctx->algo_ctx.md5.print;
	ctx->args[1].value = &ctx->algo_ctx.md5.quiet;
	ctx->args[2].value = &ctx->algo_ctx.md5.reverse;
	ctx->args[3].value = &ctx->algo_ctx.md5.string;
	ctx->args[3].exec_after = md5_cmd;
	ctx->cmd = md5_cmd;
}

void	md5_cmd(t_context *ctx)
{
	(void)ctx;
	const char			buff[] = "salut petit !";
	const t_reader		reader = create_reader_buffer((char *)buff, ft_strlen(buff));

	md5_algo((t_reader *)&reader);
}
