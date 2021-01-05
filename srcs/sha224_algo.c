/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:33:54 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/05 17:16:51 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "sha2.h"
#include "sha224.h"
#include "sha224_algo.h"
#include "sha256_algo.h"
#include "algo_rotate.h"

static void		sha224_init(t_sha256_algo_context *ctx)
{
	*ctx = (t_sha224_algo_context) {
		.buffer_length = 0,
		.intermediate_hash[0] = 0xc1059ed8,
		.intermediate_hash[1] = 0x367cd507,
		.intermediate_hash[2] = 0x3070dd17,
		.intermediate_hash[3] = 0xf70e5939,
		.intermediate_hash[4] = 0xffc00b31,
		.intermediate_hash[5] = 0x68581511,
		.intermediate_hash[6] = 0x64f98fa7,
		.intermediate_hash[7] = 0xbefa4fa4,
		.binary_length = 0,
	};
	ft_bzero(ctx->buffer, sizeof(ctx->buffer));
}

static void		fill_hash(t_sha224_algo_context *ctx
	, uint8_t hash[SHA224_HASH_SIZE])
{
	size_t	index;

	index = 0;
	while (index < 4)
	{
		hash[index] = (ctx->intermediate_hash[0] >> (24 - index * 8))
			& 0x000000ff;
		hash[index + 4] = (ctx->intermediate_hash[1] >> (24 - index * 8))
			& 0x000000ff;
		hash[index + 8] = (ctx->intermediate_hash[2] >> (24 - index * 8))
			& 0x000000ff;
		hash[index + 12] = (ctx->intermediate_hash[3] >> (24 - index * 8))
			& 0x000000ff;
		hash[index + 16] = (ctx->intermediate_hash[4] >> (24 - index * 8))
			& 0x000000ff;
		hash[index + 20] = (ctx->intermediate_hash[5] >> (24 - index * 8))
			& 0x000000ff;
		hash[index + 24] = (ctx->intermediate_hash[6] >> (24 - index * 8))
			& 0x000000ff;
		index++;
	}
}

void			sha224_final(t_sha224_algo_context *ctx, uint8_t *hash)
{
	ssize_t	index;

	index = ctx->buffer_length;
	if (ctx->buffer_length < 56)
	{
		ctx->buffer[index++] = 0x80;
		while (index < 56)
			ctx->buffer[index++] = 0;
	}
	else
	{
		ctx->buffer[index++] = 0x80;
		while (index < 64)
			ctx->buffer[index++] = 0;
		sha256_transform(ctx);
		ft_bzero(ctx->buffer, 56);
	}
	ctx->binary_length += ctx->buffer_length * 8;
	index = 55;
	while (++index < 64)
		ctx->buffer[index] = (ctx->binary_length >> ((63 - index) * 8))
			& 0x000000ff;
	sha256_transform(ctx);
	fill_hash(ctx, hash);
}

void			sha224_algo(t_context *ctx, t_reader *reader)
{
	t_sha224_algo_context	algo_ctx;
	ssize_t					buffer_length;
	uint8_t					*hash;

	sha224_init(&algo_ctx);
	hash = ctx->algo_ctx.digest.algo_ctx.sha224.hash;
	while ((buffer_length = reader_read(reader
		, (char *)(algo_ctx.buffer + algo_ctx.buffer_length)
		, SHA256_BUFFER_SIZE - algo_ctx.buffer_length)) > 0)
	{
		if (reader->type == READER_TYPE_FD && reader->ctx.fd.auto_print == true)
			write(STDOUT_FILENO, algo_ctx.buffer + algo_ctx.buffer_length,
				buffer_length);
		if ((algo_ctx.buffer_length += buffer_length) == SHA256_BUFFER_SIZE)
		{
			sha256_transform(&algo_ctx);
			algo_ctx.binary_length += 512;
			algo_ctx.buffer_length = 0;
		}
		if (reader->finished == true)
			break ;
	}
	sha224_final(&algo_ctx, hash);
}
