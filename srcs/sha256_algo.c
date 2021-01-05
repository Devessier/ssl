/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:34:39 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/05 12:08:19 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "sha256.h"
#include "algo_rotate.h"

static const uint32_t	g_k[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

static void		sha256_init(t_sha256_algo_context *ctx)
{
	*ctx = (t_sha256_algo_context) {
		.buffer_length = 0,
		.intermediate_hash[0] = 0x6a09e667,
		.intermediate_hash[1] = 0xbb67ae85,
		.intermediate_hash[2] = 0x3c6ef372,
		.intermediate_hash[3] = 0xa54ff53a,
		.intermediate_hash[4] = 0x510e527f,
		.intermediate_hash[5] = 0x9b05688c,
		.intermediate_hash[6] = 0x1f83d9ab,
		.intermediate_hash[7] = 0x5be0cd19,
		.binary_length = 0,
	};
	ft_bzero(ctx->buffer, sizeof(ctx->buffer));
}

uint32_t		ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ ((~x) & z));
}

uint32_t		maj(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t		bsig0(uint32_t x)
{
	return (rotr32(x, 2) ^ rotr32(x, 13) ^ rotr32(x, 22));
}

uint32_t		bsig1(uint32_t x)
{
	return (rotr32(x, 6) ^ rotr32(x, 11) ^ rotr32(x, 25));
}

uint32_t		ssig0(uint32_t x)
{
	return (rotr32(x, 7) ^ rotr32(x, 18) ^ (x >> 3));
}

uint32_t		ssig1(uint32_t x)
{
	return rotr32(x, 17) ^ rotr32(x, 19) ^ (x >> 10);
}

static void		fill_sha256_states(t_sha256_states *to_fill, uint32_t intermediate_hash[8])
{
	to_fill->a = intermediate_hash[0];
	to_fill->b = intermediate_hash[1];
	to_fill->c = intermediate_hash[2];
	to_fill->d = intermediate_hash[3];
	to_fill->e = intermediate_hash[4];
	to_fill->f = intermediate_hash[5];
	to_fill->g = intermediate_hash[6];
	to_fill->h = intermediate_hash[7];
}

static void		add_sha256_states(uint32_t intermediate_hash[8], t_sha256_states to_add)
{
	intermediate_hash[0] += to_add.a;
	intermediate_hash[1] += to_add.b;
	intermediate_hash[2] += to_add.c;
	intermediate_hash[3] += to_add.d;
	intermediate_hash[4] += to_add.e;
	intermediate_hash[5] += to_add.f;
	intermediate_hash[6] += to_add.g;
	intermediate_hash[7] += to_add.h;
}

void			sha256_transform(t_sha256_algo_context *ctx)
{
	t_sha256_states	states;
	uint32_t		words[64];
	ssize_t			index;
	uint32_t		tmp[2];

	index = -1;
	while (++index < 16)
		words[index] = ctx->buffer[index * 4] << 24
			| ctx->buffer[index * 4 + 1] << 16
			| ctx->buffer[index * 4 + 2] << 8
			| ctx->buffer[index * 4 + 3];
	index = 15;
	while (++index < 64)
		words[index] = ssig1(words[index - 2]) + words[index - 7] + ssig0(words[index - 15]) + words[index - 16];
	fill_sha256_states(&states, ctx->intermediate_hash);
	index = -1;
	while (++index < 64)
	{
		tmp[0] = states.h + bsig1(states.e) + ch(states.e, states.f, states.g) + g_k[index] + words[index];
		tmp[1] = bsig0(states.a) + maj(states.a, states.b, states.c);
		states.h = states.g;
		states.g = states.f;
		states.f = states.e;
		states.e = states.d + tmp[0];
		states.d = states.c;
		states.c = states.b;
		states.b = states.a;
		states.a = tmp[0] + tmp[1];
	}
	add_sha256_states(ctx->intermediate_hash, states);
}

static void		fill_hash(t_sha256_algo_context *ctx, uint8_t hash[SHA256_HASH_SIZE])
{
	size_t	index;

	index = 0;
	while (index < 4)
	{
		hash[index] = (ctx->intermediate_hash[0] >> (24 - index * 8)) & 0x000000ff;
		hash[index + 4] = (ctx->intermediate_hash[1] >> (24 - index * 8)) & 0x000000ff;
		hash[index + 8] = (ctx->intermediate_hash[2] >> (24 - index * 8)) & 0x000000ff;
		hash[index + 12] = (ctx->intermediate_hash[3] >> (24 - index * 8)) & 0x000000ff;
		hash[index + 16] = (ctx->intermediate_hash[4] >> (24 - index * 8)) & 0x000000ff;
		hash[index + 20] = (ctx->intermediate_hash[5] >> (24 - index * 8)) & 0x000000ff;
		hash[index + 24] = (ctx->intermediate_hash[6] >> (24 - index * 8)) & 0x000000ff;
		hash[index + 28] = (ctx->intermediate_hash[7] >> (24 - index * 8)) & 0x000000ff;
		index++;
	}
}

void			sha256_final(t_sha256_algo_context *ctx, uint8_t *hash)
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

void 			sha256_algo(t_context *ctx, t_reader *reader)
{
	t_sha256_algo_context	algo_ctx;
	ssize_t					buffer_length;
	uint8_t					*hash;

	sha256_init(&algo_ctx);
	hash = ctx->algo_ctx.digest.algo_ctx.sha256.hash;
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
	sha256_final(&algo_ctx, hash);
}
