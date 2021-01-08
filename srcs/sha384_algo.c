/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:34:22 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 01:04:39 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "sha2.h"
#include "sha384.h"
#include "sha384_algo.h"
#include "sha512_algo.h"
#include "algo_rotate.h"

static void		sha384_init(t_sha384_algo_context *ctx)
{
	*ctx = (t_sha384_algo_context) {
		.buffer_length = 0,
		.intermediate_hash[0] = 0xcbbb9d5dc1059ed8,
		.intermediate_hash[1] = 0x629a292a367cd507,
		.intermediate_hash[2] = 0x9159015a3070dd17,
		.intermediate_hash[3] = 0x152fecd8f70e5939,
		.intermediate_hash[4] = 0x67332667ffc00b31,
		.intermediate_hash[5] = 0x8eb44a8768581511,
		.intermediate_hash[6] = 0xdb0c2e0d64f98fa7,
		.intermediate_hash[7] = 0x47b5481dbefa4fa4,
		.binary_length = 0,
	};
	ft_bzero(ctx->buffer, sizeof(ctx->buffer));
}

static void		fill_hash(t_sha384_algo_context *ctx
	, uint8_t hash[SHA384_HASH_SIZE])
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
		hash[index + 32] = (ctx->intermediate_hash[4] >> (56 - index * 8))
			& 0x00000000000000ff;
		hash[index + 40] = (ctx->intermediate_hash[5] >> (56 - index * 8))
			& 0x00000000000000ff;
		index++;
	}
}

void			sha384_final(t_sha384_algo_context *ctx
	, uint8_t hash[SHA384_HASH_SIZE])
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

void			sha384_algo(t_context *ctx, t_reader *reader)
{
	t_sha384_algo_context	algo_ctx;
	ssize_t					buffer_length;
	uint8_t					*hash;

	sha384_init(&algo_ctx);
	hash = ctx->algo_ctx.digest.algo_ctx.sha384.hash;
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
	sha384_final(&algo_ctx, hash);
}
