/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac_sha256.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:56:15 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 14:16:10 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "hmac_sha256_algo.h"

static void		hmac_sha256_print(t_context *ctx)
{
	(void)ctx;
	ft_putf("print hmac sha256\n");
}

static void		hmac_sha256_cmd(t_context *ctx)
{
	const char	*string = ctx->algo_ctx.hmac.string;
	const char	*key = ctx->algo_ctx.hmac.key;
	t_reader	reader;

	if (string == NULL)
		return ft_putf_fd(STDERR_FILENO
			, "invalid string to hash\n");
	if (key == NULL)
		return ft_putf_fd(STDERR_FILENO
			, "invalid key\n");
	reader = create_reader_buffer((char *)string, ft_strlen(string));
	hmac_sha256_algo(ctx, &reader);
	hmac_sha256_print(ctx);
}

void	bind_hmac_sha256_args(t_context *ctx)
{
	ctx->args[0].value = &ctx->algo_ctx.hmac.string;
	ctx->args[1].value = &ctx->algo_ctx.hmac.key;
	ctx->cmd = hmac_sha256_cmd;
}
