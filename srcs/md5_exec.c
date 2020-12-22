/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:25:06 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/22 23:56:08 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "digest.h"
#include "md5.h"
#include "hexa.h"

static void		md5_hash_print(uint8_t hash[MD5_HASH_SIZE])
{
	size_t	index;

	index = 0;
	while (index < MD5_HASH_SIZE)
		print_hexa_num(STDOUT_FILENO, hash[index++]);
}

static bool		should_apply_reverse_mode(t_context *ctx
	, t_digest_exec_origin origin)
{
	return (ctx->algo_ctx.digest.reverse == true
		&& (origin == DIGEST_EXEC_ORIGIN_FILE
			|| origin == DIGEST_EXEC_ORIGIN_STRING));
}

void			md5_algo_exec(t_context *ctx
	, t_reader *reader, t_digest_exec_origin origin)
{
	const bool	reverse_mode = should_apply_reverse_mode(ctx, origin);
	uint8_t		hash[MD5_HASH_SIZE];

	md5_algo(reader, hash);
	if (reverse_mode == true)
		md5_hash_print(hash);
	if (ctx->algo_ctx.digest.quiet == false)
	{
		if (origin == DIGEST_EXEC_ORIGIN_STRING && reverse_mode == false)
			ft_putf("MD5 (\"%s\") = ", reader->ctx.buffer.data);
		else if (origin == DIGEST_EXEC_ORIGIN_STRING && reverse_mode == true)
			ft_putf(" \"%s\"", reader->ctx.buffer.data);
		else if (origin == DIGEST_EXEC_ORIGIN_FILE && reverse_mode == false)
			ft_putf("MD5 (%s) = ", reader->ctx.fd.filename);
		else if (origin == DIGEST_EXEC_ORIGIN_FILE && reverse_mode == true)
			ft_putf(" %s", reader->ctx.fd.filename);
	}
	if (reverse_mode == false)
		md5_hash_print(hash);
	ft_putchar('\n');
}
