/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_algo_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:52:26 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/05 13:01:51 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sha256.h"

void		sha256_init(t_sha256_algo_context *ctx)
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

void		fill_sha256_states(t_sha256_states *to_fill
	, uint32_t intermediate_hash[8])
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

void		add_sha256_states(uint32_t intermediate_hash[8]
	, t_sha256_states to_add)
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
