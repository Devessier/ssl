/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 00:24:10 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 14:12:56 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "libft.h"
#include "usage.h"
#include "args.h"
#include "ssl.h"
#include "md5.h"
#include "sha224.h"
#include "sha256.h"
#include "sha384.h"
#include "sha512.h"
#include "sha512_224.h"
#include "sha512_256.h"
#include "hmac_sha256.h"
#include "base64.h"
#include "des.h"
#include "algo_ctx.h"

t_algo_desc				g_algorithms[] = {
	{
		.algorithm = ALGO_MD5,
		.name = "md5",
		.name_capital = "MD5",
		.type = ALGO_DIGEST,
		.bind_args = bind_md5_args,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_SHA224,
		.name = "sha224",
		.name_capital = "SHA224",
		.type = ALGO_DIGEST,
		.bind_args = bind_sha224_args,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_SHA256,
		.name = "sha256",
		.name_capital = "SHA256",
		.type = ALGO_DIGEST,
		.bind_args = bind_sha256_args,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_SHA384,
		.name = "sha384",
		.name_capital = "SHA384",
		.type = ALGO_DIGEST,
		.bind_args = bind_sha384_args,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_SHA512,
		.name = "sha512",
		.name_capital = "SHA512",
		.type = ALGO_DIGEST,
		.bind_args = bind_sha512_args,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_SHA512_224,
		.name = "sha512224",
		.name_capital = "SHA512224",
		.type = ALGO_DIGEST,
		.bind_args = bind_sha512_224_args,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_SHA512_256,
		.name = "sha512256",
		.name_capital = "SHA512256",
		.type = ALGO_DIGEST,
		.bind_args = bind_sha512_256_args,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_HMAC_SHA256,
		.name = "hmac-sha256",
		.name_capital = "HMAC-SHA256",
		.type = ALGO_DIGEST,
		.bind_args = bind_hmac_sha256_args,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_BASE64,
		.name = "base64",
		.name_capital = "BASE64",
		.type = ALGO_CIPHER,
		.bind_args = bind_base64_args,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_DES,
		.name = "des",
		.name_capital = "DES",
		.type = ALGO_CIPHER,
		.bind_args = bind_des_args,
		.arguments = NULL
	},
	{
		.algorithm = ALGO_DES_ECB,
		.name = "des-ecb",
		.name_capital = "DES-ECB",
		.type = ALGO_CIPHER,
		.bind_args = bind_des_args,
		.arguments = NULL
	},
	{
		.algorithm = 0,
		.name = NULL,
		.type = ALGO_TYPE_NONE,
		.bind_args = NULL,
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
	algo_desc->bind_args(ctx);
}

t_error					ssl_exec(int argc, char **argv)
{
	const char	*command_name = *argv;
	t_algo		algo;
	t_context	ctx;
	ssize_t		parsed_args;

	if (ft_strcmp(argv[0], "help") == 0)
	{
		print_available_commands();
		return (E_SUCCESS);
	}
	algo = algo_name_to_algo(command_name);
	if (algo == ALGO_INVALID)
	{
		print_unavailable_command_usage(command_name);
		return (E_FAILURE);
	}
	init_cmd(&ctx, algo);
	if ((parsed_args = parse_args(&ctx, ++argc, ++argv)) == -1)
		return (E_FAILURE);
	ctx.cmd(&ctx);
	return (E_SUCCESS);
}
