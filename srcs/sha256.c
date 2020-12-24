/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:38:05 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/24 15:43:32 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ssl.h"
#include "digest.h"
#include "sha256.h"
#include "sha256_algo.h"
#include "sha256_print.h"

void	bind_sha256_args(t_context *ctx)
{
	ctx->args[0].value = &ctx->algo_ctx.digest.print;
	ctx->args[0].exec_after = digest_stdin_cmd;
	ctx->args[1].value = &ctx->algo_ctx.digest.quiet;
	ctx->args[2].value = &ctx->algo_ctx.digest.reverse;
	ctx->args[3].value = &ctx->algo_ctx.digest.string;
	ctx->args[3].exec_after = digest_string_cmd;
	ctx->algo_ctx.digest.algo_fn = sha256_algo;
	ctx->algo_ctx.digest.print_fn = sha256_hash_print;
	ctx->cmd = digest_cmd;
}

void	sha256_cmd(t_context *ctx)
{
	printf("algo name: %s\n", ctx->algo_name);
}
