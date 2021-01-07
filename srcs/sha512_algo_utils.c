/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_algo_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:02:29 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 00:10:07 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include "sha512.h"

void	sha512_init(t_sha512_algo_context *ctx)
{
	*ctx = (t_sha512_algo_context) {
		.buffer_length = 0,
		.intermediate_hash[0] = 0x6a09e667f3bcc908,
		.intermediate_hash[1] = 0xbb67ae8584caa73b,
		.intermediate_hash[2] = 0x3c6ef372fe94f82b,
		.intermediate_hash[3] = 0xa54ff53a5f1d36f1,
		.intermediate_hash[4] = 0x510e527fade682d1,
		.intermediate_hash[5] = 0x9b05688c2b3e6c1f,
		.intermediate_hash[6] = 0x1f83d9abfb41bd6b,
		.intermediate_hash[7] = 0x5be0cd19137e2179,
		.binary_length = 0,
	};
	ft_bzero(ctx->buffer, sizeof(ctx->buffer));
}

void	fill_sha512_states(t_sha512_states *to_fill
	, uint64_t intermediate_hash[8])
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

void	add_sha512_states(uint64_t intermediate_hash[8]
	, t_sha512_states to_add)
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
