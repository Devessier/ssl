/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 00:24:10 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/07 16:59:18 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <unistd.h>
#include <stdbool.h>
#include "libft.h"
#include "ssl.h"
#include "md5.h"
#include "sha224.h"
#include "sha256.h"
#include "sha512.h"
#include "algo_ctx.h"

t_algo_desc				g_algorithms[] = {
	{
		.algorithm = ALGO_MD5,
		.name = "md5",
		.name_capital = "MD5",
		.type = ALGO_DIGEST,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_SHA224,
		.name = "sha224",
		.name_capital = "SHA224",
		.type = ALGO_DIGEST,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_SHA256,
		.name = "sha256",
		.name_capital = "SHA256",
		.type = ALGO_DIGEST,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_SHA512,
		.name = "sha512",
		.name_capital = "SHA512",
		.type = ALGO_DIGEST,
		.arguments = NULL
	},
	{
		.algorithm = 0,
		.name = NULL,
		.type = ALGO_TYPE_NONE,
		.arguments = NULL
	},
};

t_algo					algo_name_to_algo(const char *algo_name)
{
	t_algo_desc		*algo_desc;

	algo_desc = g_algorithms;
	while (algo_desc->name != NULL)
	{
		if (ft_strcmp(algo_desc->name, algo_name) == 0)
			return (algo_desc->algorithm);
		algo_desc++;
	}
	return (ALGO_INVALID);
}

static t_algo_desc		*get_algo_desc(t_algo algo)
{
	t_algo_desc		*algo_desc;

	algo_desc = g_algorithms;
	while (algo_desc->name != NULL)
	{
		if (algo_desc->algorithm == algo)
			return (algo_desc);
		algo_desc++;
	}
	return (NULL);
}

static void				bind_args_to_algo_context(t_context *ctx)
{
	if (ctx->algo == ALGO_MD5)
		bind_md5_args(ctx);
	else if (ctx->algo == ALGO_SHA256)
		bind_sha256_args(ctx);
	else if (ctx->algo == ALGO_SHA224)
		bind_sha224_args(ctx);
	else if (ctx->algo == ALGO_SHA512)
		bind_sha512_args(ctx);
}

void					init_cmd(t_context *ctx, t_algo algo)
{
	const t_algo_desc	*algo_desc = get_algo_desc(algo);

	*ctx = (t_context) {
		.algo = algo,
		.algo_name = algo_desc->name,
		.algo_name_capital = algo_desc->name_capital,
		.usage = get_algo_usage(algo),
		.args = get_algo_arguments(algo),
		.remaining_args = NULL,
	};
	bind_args_to_algo_context(ctx);
}
