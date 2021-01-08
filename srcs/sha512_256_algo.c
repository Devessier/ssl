/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_256_algo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 02:26:19 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 02:52:59 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "sha2.h"
#include "sha512_256.h"
#include "sha512_256_algo.h"
#include "sha512_algo.h"
#include "algo_rotate.h"

static void		sha512_256_init(t_sha512_256_algo_context *ctx)
{
	*ctx = (t_sha512_256_algo_context) {
		.buffer_length = 0,
		.intermediate_hash[0] = 0x22312194fc2bf72c,
		.intermediate_hash[1] = 0x9f555fa3c84c64c2,
		.intermediate_hash[2] = 0x2393b86b6f53b151,
		.intermediate_hash[3] = 0x963877195940eabd,
		.intermediate_hash[4] = 0x96283ee2a88effe3,
		.intermediate_hash[5] = 0xbe5e1e2553863992,
		.intermediate_hash[6] = 0x2b0199fc2c85b8aa,
		.intermediate_hash[7] = 0x0eb72ddc81c52ca2,
		.binary_length = 0,
	};
	ft_bzero(ctx->buffer, sizeof(ctx->buffer));
}

/*
** We must fill 256 bits, that is, 3.5 64-bit words.
** To do that we simply fill totally 3 64-bit words
** and the first bits of a fourth 64-bit word.
*/

static void		fill_hash(t_sha512_256_algo_context *ctx
	, uint8_t hash[SHA512_256_HASH_SIZE])
{
	size_t	index;

	index = 0;
	while (index < 8)
	{
		hash[index] = (ctx->intermediate_hash[0] >> (56 - index * 8))
			& 0x00000000000000ff;
		hash[index + 8] = (ctx->intermediate_hash[1] >> (56 - index * 8))
			& 0x00000000000000ff;
		hash[index + 16] = (ctx->intermediate_hash[2] >> (56 - index * 8))
			& 0x00000000000000ff;
		hash[index + 24] = (ctx->intermediate_hash[3] >> (56 - index * 8))
			& 0x00000000000000ff;
		index++;
	}
}

void			sha512_256_final(t_sha512_256_algo_context *ctx
	, uint8_t hash[SHA512_256_HASH_SIZE])
{
	ssize_t	index;

	index = ctx->buffer_length;
	if (ctx->buffer_length < 112)
	{
		ctx->buffer[index++] = 0x80;
		while (index < 112)
			ctx->buffer[index++] = 0;
	}
	else
	{
		ctx->buffer[index++] = 0x80;
		while (index < 128)
			ctx->buffer[index++] = 0;
		sha512_transform(ctx);
		ft_bzero(ctx->buffer, 112);
	}
	ctx->binary_length += ctx->buffer_length * 8;
	index = 111;
	while (++index < 128)
		ctx->buffer[index] = ((t_uint128)ctx->binary_length
			>> ((127 - index) * 8)) & 0x000000ff;
	sha512_transform(ctx);
	fill_hash(ctx, hash);
}

void			sha512_256_algo(t_context *ctx, t_reader *reader)
{
	t_sha512_256_algo_context	algo_ctx;
	ssize_t						buffer_length;
	uint8_t						*hash;

	sha512_256_init(&algo_ctx);
	hash = ctx->algo_ctx.digest.algo_ctx.sha512_256.hash;
	while ((buffer_length = reader_read(reader
		, (char *)(algo_ctx.buffer + algo_ctx.buffer_length)
		, SHA512_BUFFER_SIZE - algo_ctx.buffer_length)) > 0)
	{
		if (reader->type == READER_TYPE_FD && reader->ctx.fd.auto_print == true)
			write(STDOUT_FILENO, algo_ctx.buffer + algo_ctx.buffer_length,
				buffer_length);
		if ((algo_ctx.buffer_length += buffer_length) == SHA512_BUFFER_SIZE)
		{
			sha512_transform(&algo_ctx);
			algo_ctx.binary_length += 1024;
			algo_ctx.buffer_length = 0;
		}
		if (reader->finished == true)
			break ;
	}
	sha512_256_final(&algo_ctx, hash);
}
