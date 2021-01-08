/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:48:04 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 01:18:26 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "sha2.h"
#include "sha512.h"
#include "sha512_algo.h"
#include "algo_rotate.h"

const uint64_t		g_sha384_sha512_k[80] = {
	0x428a2f98d728ae22,
	0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc,
	0x3956c25bf348b538,

	0x59f111f1b605d019,
	0x923f82a4af194f9b,
	0xab1c5ed5da6d8118,
	0xd807aa98a3030242,
	0x12835b0145706fbe,

	0x243185be4ee4b28c,
	0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f,
	0x80deb1fe3b1696b1,
	0x9bdc06a725c71235,

	0xc19bf174cf692694,
	0xe49b69c19ef14ad2,
	0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5,
	0x240ca1cc77ac9c65,

	0x2de92c6f592b0275,
	0x4a7484aa6ea6e483,
	0x5cb0a9dcbd41fbd4,
	0x76f988da831153b5,
	0x983e5152ee66dfab,

	0xa831c66d2db43210,
	0xb00327c898fb213f,
	0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2,
	0xd5a79147930aa725,

	0x06ca6351e003826f,
	0x142929670a0e6e70,
	0x27b70a8546d22ffc,
	0x2e1b21385c26c926,
	0x4d2c6dfc5ac42aed,

	0x53380d139d95b3df,
	0x650a73548baf63de,
	0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6,
	0x92722c851482353b,

	0xa2bfe8a14cf10364,
	0xa81a664bbc423001,
	0xc24b8b70d0f89791,
	0xc76c51a30654be30,
	0xd192e819d6ef5218,

	0xd69906245565a910,
	0xf40e35855771202a,
	0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8,
	0x1e376c085141ab53,

	0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63,
	0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373,

	0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc,
	0x78a5636f43172f60,
	0x84c87814a1f0ab72,
	0x8cc702081a6439ec,

	0x90befffa23631e28,
	0xa4506cebde82bde9,
	0xbef9a3f7b2c67915,
	0xc67178f2e372532b,
	0xca273eceea26619c,

	0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e,
	0xf57d4f7fee6ed178,
	0x06f067aa72176fba,
	0x0a637dc5a2c898a6,

	0x113f9804bef90dae,
	0x1b710b35131c471b,
	0x28db77f523047d84,
	0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc,

	0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6,
	0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec,
	0x6c44198c4a475817
};

static void		sha512_compression(size_t index
	, uint64_t words[80], t_sha512_states *states)
{
	uint64_t		tmp[2];

	tmp[0] = states->h + bsig1_64(states->e)
		+ ch_64(states->e, states->f, states->g)
		+ g_sha384_sha512_k[index] + words[index];
	tmp[1] = bsig0_64(states->a) + maj_64(states->a, states->b, states->c);
	states->h = states->g;
	states->g = states->f;
	states->f = states->e;
	states->e = states->d + tmp[0];
	states->d = states->c;
	states->c = states->b;
	states->b = states->a;
	states->a = tmp[0] + tmp[1];
}

void			sha512_transform(t_sha512_algo_context *ctx)
{
	t_sha512_states	states;
	uint64_t		words[80];
	ssize_t			index;

	index = -1;
	while (++index < 16)
		words[index] = (uint64_t)ctx->buffer[index * 8] << 56
			| (uint64_t)ctx->buffer[index * 8 + 1] << 48
			| (uint64_t)ctx->buffer[index * 8 + 2] << 40
			| (uint64_t)ctx->buffer[index * 8 + 3] << 32
			| (uint64_t)ctx->buffer[index * 8 + 4] << 24
			| (uint64_t)ctx->buffer[index * 8 + 5] << 16
			| (uint64_t)ctx->buffer[index * 8 + 6] << 8
			| (uint64_t)ctx->buffer[index * 8 + 7];
	index = 15;
	while (++index < 80)
		words[index] = ssig1_64(words[index - 2]) + words[index - 7]
			+ ssig0_64(words[index - 15]) + words[index - 16];
	fill_sha512_states(&states, ctx->intermediate_hash);
	index = -1;
	while (++index < 80)
		sha512_compression(index, words, &states);
	add_sha512_states(ctx->intermediate_hash, states);
}

static void		fill_hash(t_sha512_algo_context *ctx
	, uint8_t hash[SHA512_HASH_SIZE])
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
		hash[index + 48] = (ctx->intermediate_hash[6] >> (56 - index * 8))
			& 0x00000000000000ff;
		hash[index + 56] = (ctx->intermediate_hash[7] >> (56 - index * 8))
			& 0x00000000000000ff;
		index++;
	}
}

static void		sha512_final(t_sha512_algo_context *ctx
	, uint8_t hash[SHA512_HASH_SIZE])
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

void			sha512_algo(t_context *ctx, t_reader *reader)
{
	t_sha512_algo_context	algo_ctx;
	ssize_t					buffer_length;
	uint8_t					*hash;

	sha512_init(&algo_ctx);
	hash = ctx->algo_ctx.digest.algo_ctx.sha512.hash;
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
	sha512_final(&algo_ctx, hash);
}
