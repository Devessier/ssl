/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 10:45:32 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/22 19:27:59 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "reader.h"
#include "md5.h"
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

t_md5_algo_context			md5_init(void)
{
	return ((t_md5_algo_context) {
		.buffer_length = 0,
		.states[0] = 0x67452301,
		.states[1] = 0xefcdab89,
		.states[2] = 0x98badcfe,
		.states[3] = 0x10325476,
		.binary_length = 0,
	});
}

/*
** Transforms big endian words in little endian.
*/

static void					md5_decode_input_le(t_md5_algo_context *ctx
	, uint32_t words[MD5_HASH_SIZE])
{
	size_t		index;

	index = 0;
	while (index < 16)
	{
		words[index] = ctx->buffer[index * 4]
			| (ctx->buffer[index * 4 + 1] << 8)
			| (ctx->buffer[index * 4 + 2] << 16)
			| (ctx->buffer[index * 4 + 3] << 24);
		index++;
	}
}

static void					md5_encode_output_le(t_md5_algo_context *ctx
	, uint8_t hash[MD5_HASH_SIZE])
{
	size_t		index;

	index = 0;
	while (index < 4)
	{
		hash[index] = (ctx->states[0] >> (index * 8)) & 0x000000ff;
		hash[index + 4] = (ctx->states[1] >> (index * 8)) & 0x000000ff;
		hash[index + 8] = (ctx->states[2] >> (index * 8)) & 0x000000ff;
		hash[index + 12] = (ctx->states[3] >> (index * 8)) & 0x000000ff;
		index++;
	}
}

static void					md5_transform(t_md5_algo_context *ctx)
{
	uint32_t	tmp_states[4];
	uint32_t	words[MD5_HASH_SIZE];
	size_t		index;
	uint32_t	f;
	uint32_t	word_index;
	uint32_t	tmp;

	tmp_states[0] = ctx->states[0];
	tmp_states[1] = ctx->states[1];
	tmp_states[2] = ctx->states[2];
	tmp_states[3] = ctx->states[3];
	md5_decode_input_le(ctx, words);
	index = 0;
	while (index < 64)
	{
		if (index <= 15)
		{
			f = (tmp_states[1] & tmp_states[2]) | (~tmp_states[1] & tmp_states[3]);
			word_index = index;
		}
		else if (16 <= index && index <= 31)
		{
			f = (tmp_states[1] & tmp_states[3]) | (tmp_states[2] & ~tmp_states[3]);
			word_index = (5 * index + 1) % 16;
		}
		else if (32 <= index && index <= 47)
		{
			f = tmp_states[1] ^ tmp_states[2] ^ tmp_states[3];
			word_index = (3 * index + 5) % 16;
		}
		else
		{
			f = tmp_states[2] ^ (tmp_states[1] | ~tmp_states[3]);
			word_index = (7 * index) % 16;
		}
		tmp = tmp_states[3];
		tmp_states[3] = tmp_states[2];
		tmp_states[2] = tmp_states[1];
		tmp_states[1] = rotl32((tmp_states[0] + f + g_md5_constants_sin[index]
			+ words[word_index]), g_md5_constants[index]) + tmp_states[1];
		tmp_states[0] = tmp;
		index++;
	}
	ctx->states[0] += tmp_states[0];
	ctx->states[1] += tmp_states[1];
	ctx->states[2] += tmp_states[2];
	ctx->states[3] += tmp_states[3];
}

/*
** Append padding bits and append length.
** Buffer length is at most equal to 64 and MD5 operates on 64 uint8_t.
**
** If the buffer length is lower than 56 we add a single "1" bit (which is "Ox80" in little endian)
** and then append 0 bits until we have a buffer length of 56.
**
** If the buffer is greater or equal to 56 we apply the same process but until we reach a buffer length of 64,
** we apply a transformation, and finally we clear the md5 context buffer.
**
** We increment the binary length by the buffer length multiplied by 8 because each entry
** in the buffer is an uint8_t.
** We break down the binary length, encode it in little endian and save it in the buffer.
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
		ctx->buffer[index] = (ctx->binary_length >> ((index - 56) * 8)) & 0x000000ff;
	md5_transform(ctx);
	md5_encode_output_le(ctx, hash);
}

void						md5_algo(t_reader *reader
	, uint8_t hash[MD5_HASH_SIZE])
{
	t_md5_algo_context	algo_ctx;
	ssize_t				buffer_length;

	algo_ctx = md5_init();
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
