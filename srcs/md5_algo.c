/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 10:45:32 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/24 14:08:55 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "reader.h"
#include "md5.h"
#include "md5_algo_utils.h"
#include "algo_rotate.h"

static uint32_t				g_md5_constants[] = {
	7, 12, 17, 22, 7, 12, 17, 22,
	7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20,
	5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21, 6, 10, 15, 21,
};

static uint32_t				g_md5_constants_sin[] = {
	0xd76aa478,
	0xe8c7b756,
	0x242070db,
	0xc1bdceee,
	0xf57c0faf,
	0x4787c62a,
	0xa8304613,
	0xfd469501,
	0x698098d8,
	0x8b44f7af,
	0xffff5bb1,
	0x895cd7be,
	0x6b901122,
	0xfd987193,
	0xa679438e,
	0x49b40821,

	0xf61e2562,
	0xc040b340,
	0x265e5a51,
	0xe9b6c7aa,
	0xd62f105d,
	0x02441453,
	0xd8a1e681,
	0xe7d3fbc8,
	0x21e1cde6,
	0xc33707d6,
	0xf4d50d87,
	0x455a14ed,
	0xa9e3e905,
	0xfcefa3f8,
	0x676f02d9,
	0x8d2a4c8a,

	0xfffa3942,
	0x8771f681,
	0x6d9d6122,
	0xfde5380c,
	0xa4beea44,
	0x4bdecfa9,
	0xf6bb4b60,
	0xbebfbc70,
	0x289b7ec6,
	0xeaa127fa,
	0xd4ef3085,
	0x04881d05,
	0xd9d4d039,
	0xe6db99e5,
	0x1fa27cf8,
	0xc4ac5665,

	0xf4292244,
	0x432aff97,
	0xab9423a7,
	0xfc93a039,
	0x655b59c3,
	0x8f0ccc92,
	0xffeff47d,
	0x85845dd1,
	0x6fa87e4f,
	0xfe2ce6e0,
	0xa3014314,
	0x4e0811a1,
	0xf7537e82,
	0xbd3af235,
	0x2ad7d2bb,
	0xeb86d391,
};

static void					md5_transform(t_md5_algo_context *ctx)
{
	t_md5_states	states;
	uint32_t		words[MD5_HASH_SIZE];
	size_t			index;
	uint32_t		tmp;

	states = ctx->states;
	md5_decode_input_le(ctx, words);
	index = 0;
	while (index < 64)
	{
		md5_transform_permute(ctx, &states, index);
		tmp = states.d;
		states.d = states.c;
		states.c = states.b;
		states.b = rotl32((states.a + ctx->permutation
			+ g_md5_constants_sin[index] + words[ctx->word_index])
			, g_md5_constants[index]) + states.b;
		states.a = tmp;
		index++;
	}
	add_md5_states(&ctx->states, states);
}

/*
** Append padding bits and append length.
** Buffer length is at most equal to 64 and MD5 operates on 64 uint8_t.
**
** If the buffer length is lower than 56 we add
** a single "1" bit (which is "Ox80" in little endian) and then append
** 0 bits until we have a buffer length of 56.
**
** If the buffer is greater or equal to 56 we apply the same process
** but until we reach a buffer length of 64, we apply a transformation,
** and finally we clear the md5 context buffer.
**
** We increment the binary length by the buffer length multiplied
** by 8 because each entry in the buffer is an uint8_t.
** We break down the binary length, encode it in little endian
** and save it in the buffer.
** We launch a last transformation.
** We decode the buffer into big endian and save it into the hash array.
*/

static void					md5_final(t_md5_algo_context *ctx, uint8_t hash[4])
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
		md5_transform(ctx);
		ft_bzero(ctx->buffer, 56);
	}
	ctx->binary_length += ctx->buffer_length * 8;
	index = 55;
	while (++index < 64)
		ctx->buffer[index] = (ctx->binary_length >> ((index - 56) * 8))
			& 0x000000ff;
	md5_transform(ctx);
	md5_encode_output_le(ctx, hash);
}

void						md5_algo(t_context *ctx, t_reader *reader)
{
	t_md5_algo_context	algo_ctx;
	ssize_t				buffer_length;
	uint8_t				*hash;

	algo_ctx = md5_init();
	hash = ctx->algo_ctx.digest.algo_ctx.md5.hash;
	while ((buffer_length = reader_read(reader
		, (char *)(algo_ctx.buffer + algo_ctx.buffer_length)
		, MD5_BUFFER_SIZE - algo_ctx.buffer_length)) > 0)
	{
		if (reader->type == READER_TYPE_FD && reader->ctx.fd.auto_print == true)
			write(STDOUT_FILENO, algo_ctx.buffer + algo_ctx.buffer_length,
				buffer_length);
		if ((algo_ctx.buffer_length += buffer_length) == MD5_BUFFER_SIZE)
		{
			md5_transform(&algo_ctx);
			algo_ctx.binary_length += 512;
			algo_ctx.buffer_length = 0;
		}
		if (reader->finished == true)
			break ;
	}
	md5_final(&algo_ctx, hash);
}
