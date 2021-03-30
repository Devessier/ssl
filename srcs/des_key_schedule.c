/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_key_schedule.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 11:38:20 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/30 19:39:17 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_algo.h"
#include "algo_rotate.h"
#include "endianness.h"

static t_uint56	des_pc1(uint64_t key)
{
	const uint8_t	table[] = {
		57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27,
		19, 11, 3, 60, 52, 44, 36,

		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29,
		21, 13, 5, 28, 20, 12, 4,
	};
	t_uint56		result;

	result.uint = des_permute(key, sizeof(key), table, sizeof(table));
	return (result);
}

static void		des_key_permute(t_uint28 *c_block, t_uint28 *d_block, size_t index)
{
	const uint8_t	shifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
	const uint8_t	bit_shift = shifts[index];

	c_block->uint = (c_block->uint << bit_shift) | ((c_block->uint >> (28 - bit_shift)));
	d_block->uint = (d_block->uint << bit_shift) | ((d_block->uint >> (28 - bit_shift)));
}

static t_uint48	des_pc2(t_uint28 c_block, t_uint28 d_block)
{
	t_uint56		combined_blocks;
	const uint8_t	table[] = {
		14, 17, 11, 24, 1, 5,
		3, 28, 15, 6, 21, 10,
		23, 19, 12, 4, 26, 8,
		16, 7, 27, 20, 13, 2,
		41, 52, 31, 37, 47, 55,
		30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53,
		46, 42, 50, 36, 29, 32,
	};
	t_uint48		result;

	combined_blocks.uint = ((uint64_t)c_block.uint << 28) | ((uint64_t)d_block.uint);
	result.uint = des_permute(combined_blocks.uint, 7, table, sizeof(table));
	return (result);
}

void	des_generate_key_schedule(t_uint48 key_schedule[DES_KEY_SCHEDULE_COUNT]
	, uint64_t key)
{
	t_uint28	c_block;
	t_uint28	d_block;
	size_t		index;
	t_uint56	compressed_key;

	key = endianness_swap64(key);
	compressed_key = des_pc1(key);
	c_block.uint = (compressed_key.uint >> 28) & 0xfffffff;
	d_block.uint = compressed_key.uint & 0xfffffff;
	index = 0;
	while (index < DES_KEY_SCHEDULE_COUNT)
	{
		des_key_permute(&c_block, &d_block, index);
		key_schedule[index] = des_pc2(c_block, d_block);
		index++;
	}
}
