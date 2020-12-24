/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 12:30:01 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/24 14:12:15 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "digest.h"
#include "md5.h"

static bool		should_apply_reverse_mode(t_context *ctx
	, t_digest_exec_origin origin)
{
	return (ctx->algo_ctx.digest.reverse == true
		&& (origin == DIGEST_EXEC_ORIGIN_FILE
			|| origin == DIGEST_EXEC_ORIGIN_STRING));
}

void			digest_algo_exec(t_context *ctx
	, t_reader *reader, t_digest_exec_origin origin)
{
	const bool	reverse_mode = should_apply_reverse_mode(ctx, origin);

	ctx->algo_ctx.digest.algo_fn(ctx, reader);
	if (reverse_mode == true)
		ctx->algo_ctx.digest.print_fn(ctx);
	if (ctx->algo_ctx.digest.quiet == false)
	{
		if (origin == DIGEST_EXEC_ORIGIN_STRING && reverse_mode == false)
			ft_putf("%s (\"%s\") = ", ctx->algo_name_capital
				, reader->ctx.buffer.data);
		else if (origin == DIGEST_EXEC_ORIGIN_STRING && reverse_mode == true)
			ft_putf(" \"%s\"", reader->ctx.buffer.data);
		else if (origin == DIGEST_EXEC_ORIGIN_FILE && reverse_mode == false)
			ft_putf("%s (%s) = ", ctx->algo_name_capital
				, reader->ctx.fd.filename);
		else if (origin == DIGEST_EXEC_ORIGIN_FILE && reverse_mode == true)
			ft_putf(" %s", reader->ctx.fd.filename);
	}
	if (reverse_mode == false)
		ctx->algo_ctx.digest.print_fn(ctx);
	ft_putchar('\n');
}
