/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 00:24:10 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/10 19:11:04 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <unistd.h>
#include <stdbool.h>
#include "libft.h"
#include "ssl.h"
#include "md5.h"
#include "sha256.h"
#include "algo_ctx.h"

t_algo_desc				g_algorithms[] = {
	{
		.algorithm = ALGO_MD5,
		.name = "md5",
		.type = ALGO_DIGEST,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_SHA256,
		.name = "sha256",
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
}

t_context				create_cmd(t_algo algo)
{
	const t_algo_desc	*algo_desc = get_algo_desc(algo);
	t_context			ctx;

	ctx = (t_context) {
		.algo = algo,
		.algo_name = algo_desc->name,
		.args = get_algo_arguments(algo),
	};
	bind_args_to_algo_context((t_context *)&ctx);
	return (ctx);
}
