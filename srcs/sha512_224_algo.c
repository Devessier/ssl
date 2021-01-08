/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_224_algo.c                                      :+:      :+:    :+:   */
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
#include "sha512_224.h"
#include "sha512_224_algo.h"
#include "sha512_algo.h"
#include "algo_rotate.h"

static void		sha512_224_init(t_sha512_224_algo_context *ctx)
{
	*ctx = (t_sha512_224_algo_context) {
		.buffer_length = 0,
		.intermediate_hash[0] = 0x8c3d37c819544da2,
		.intermediate_hash[1] = 0x73e1996689dcd4d6,
		.intermediate_hash[2] = 0x1dfab7ae32ff9c82,
		.intermediate_hash[3] = 0x679dd514582f9fcf,
		.intermediate_hash[4] = 0x0f6d2b697bd44da8,
		.intermediate_hash[5] = 0x77e36f7304c48942,
		.intermediate_hash[6] = 0x3f9d85a86a1d36c8,
		.intermediate_hash[7] = 0x1112e6ad91d692a1,
		.binary_length = 0,
	};
	ft_bzero(ctx->buffer, sizeof(ctx->buffer));
}

static void		fill_hash(t_sha512_224_algo_context *ctx
	, uint8_t hash[SHA512_224_HASH_SIZE])
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
		index++;
	}
	index = 0;
	while (index < 4)
	{
		hash[index + 24] = (ctx->intermediate_hash[3] >> (56 - index * 8))
			& 0x00000000000000ff;
		index++;
	}
}

void			sha512_224_final(t_sha512_224_algo_context *ctx
	, uint8_t hash[SHA512_224_HASH_SIZE])
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

void			sha512_224_algo(t_context *ctx, t_reader *reader)
{
	t_sha512_224_algo_context	algo_ctx;
	ssize_t					buffer_length;
	uint8_t					*hash;

	sha512_224_init(&algo_ctx);
	hash = ctx->algo_ctx.digest.algo_ctx.sha512_224.hash;
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
	sha512_224_final(&algo_ctx, hash);
}
