/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:58:00 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/05 17:58:01 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "digest.h"
#include "sha512.h"
#include "sha512_algo.h"
#include "sha512_print.h"

void	bind_sha512_args(t_context *ctx)
{
	ctx->args[0].value = &ctx->algo_ctx.digest.print;
	ctx->args[0].exec_after = digest_stdin_cmd;
	ctx->args[1].value = &ctx->algo_ctx.digest.quiet;
	ctx->args[2].value = &ctx->algo_ctx.digest.reverse;
	ctx->args[3].value = &ctx->algo_ctx.digest.string;
	ctx->args[3].exec_after = digest_string_cmd;
	ctx->algo_ctx.digest.algo_fn = sha512_algo;
	ctx->algo_ctx.digest.print_fn = sha512_hash_print;
	ctx->cmd = digest_cmd;
}
