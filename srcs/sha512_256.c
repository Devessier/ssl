/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_256.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:33:54 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 02:50:37 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "digest.h"
#include "sha512_256.h"
#include "sha512_256_algo.h"
#include "sha512_256_print.h"

void	bind_sha512_256_args(t_context *ctx)
{
	ctx->args[0].value = &ctx->algo_ctx.digest.print;
	ctx->args[0].exec_after = digest_stdin_cmd;
	ctx->args[1].value = &ctx->algo_ctx.digest.quiet;
	ctx->args[2].value = &ctx->algo_ctx.digest.reverse;
	ctx->args[3].value = &ctx->algo_ctx.digest.string;
	ctx->args[3].exec_after = digest_string_cmd;
	ctx->algo_ctx.digest.algo_fn = sha512_256_algo;
	ctx->algo_ctx.digest.print_fn = sha512_256_hash_print;
	ctx->cmd = digest_cmd;
}
