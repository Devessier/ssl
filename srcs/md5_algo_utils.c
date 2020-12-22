/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_algo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 23:57:24 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/23 00:01:13 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "md5.h"

t_md5_algo_context	md5_init(void)
{
	return ((t_md5_algo_context) {
		.buffer_length = 0,
		.states.a = 0x67452301,
		.states.b = 0xefcdab89,
		.states.c = 0x98badcfe,
		.states.d = 0x10325476,
		.binary_length = 0,
		.permutation = 0,
		.word_index = 0,
	});
}

/*
** Transforms big endian words in little endian.
*/

void				md5_decode_input_le(t_md5_algo_context *ctx
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

void				md5_encode_output_le(t_md5_algo_context *ctx
	, uint8_t hash[MD5_HASH_SIZE])
{
	size_t		index;

	index = 0;
	while (index < 4)
	{
		hash[index] = (ctx->states.a >> (index * 8)) & 0x000000ff;
		hash[index + 4] = (ctx->states.b >> (index * 8)) & 0x000000ff;
		hash[index + 8] = (ctx->states.c >> (index * 8)) & 0x000000ff;
		hash[index + 12] = (ctx->states.d >> (index * 8)) & 0x000000ff;
		index++;
	}
}

void				add_md5_states(t_md5_states *ref
	, t_md5_states to_add)
{
	ref->a += to_add.a;
	ref->b += to_add.b;
	ref->c += to_add.c;
	ref->d += to_add.d;
}

void				md5_transform_permute(t_md5_algo_context *ctx
	, t_md5_states *states, size_t index)
{
	if (index <= 15)
	{
		ctx->permutation = (states->b & states->c) | (~states->b & states->d);
		ctx->word_index = index;
	}
	else if (16 <= index && index <= 31)
	{
		ctx->permutation = (states->b & states->d) | (states->c & ~states->d);
		ctx->word_index = (5 * index + 1) % 16;
	}
	else if (32 <= index && index <= 47)
	{
		ctx->permutation = states->b ^ states->c ^ states->d;
		ctx->word_index = (3 * index + 5) % 16;
	}
	else
	{
		ctx->permutation = states->c ^ (states->b | ~states->d);
		ctx->word_index = (7 * index) % 16;
	}
}
