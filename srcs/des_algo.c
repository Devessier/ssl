/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:23:23 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/30 20:51:18 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "des_algo.h"
#include "reader.h"
#include "writer.h"

#include <printf.h>

uint64_t	des_permute(uint64_t input_block
	, size_t input_block_bytes_length
	, const uint8_t table[]
	, size_t table_size)
{
	uint64_t	result;
	size_t		index;
	uint8_t		input_bit;

	result = 0;
	index = 0;
	while (index < table_size)
	{
		input_bit = table[index] - 1;
		if ((input_block >> ((input_block_bytes_length * 8 - 1) - input_bit)) & 0b1)
			result |= 0b1LLU << ((table_size - 1) - index);
		index++;
	}
	return (result);
}

uint64_t	des_ip(uint64_t block)
{
	const uint8_t	table[] = {
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7,
	};

	return (des_permute(block, sizeof(block), table, sizeof(table)));
}

uint64_t	des_inv_ip(uint64_t block)
{
	const uint8_t	table[] = {
		40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25,
	};

	return (des_permute(block, sizeof(block), table, sizeof(table)));
}

#include <printf.h>

t_uint48	des_right_block_expand(uint32_t right_block)
{
	const uint8_t	table[] = {
		32, 1, 2, 3, 4, 5,
		4, 5, 6, 7, 8, 9,
		8, 9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32, 1,
	};
	t_uint48	expanded_right_block;

	expanded_right_block.uint = des_permute(right_block, sizeof(right_block), table, sizeof(table));
	return (expanded_right_block);
}

# define DES_SBOX_COUNT 8

static const uint8_t g_des_sbox[DES_SBOX_COUNT][4][16] = {
	{
		{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
		{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
		{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
		{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
	},

	{
		{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
		{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
		{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
		{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
	},

	{
		{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
		{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
		{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
		{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
	},

	{
		{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
		{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
		{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
		{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
	},

	{
		{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
		{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
		{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
		{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
	},

	{
		{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
		{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
		{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
		{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
	},

	{
		{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
		{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
		{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
		{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
	},

	{
		{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
		{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
		{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
		{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11},
	},
};

uint32_t	des_round_s_box_compress(t_uint48 block)
{
	size_t		sbox_index;
	t_uint6 	sbox_input;
	uint32_t	result;

	sbox_index = 0;
	result = 0;
	while (sbox_index < DES_SBOX_COUNT)
	{
		sbox_input.uint = (block.uint >> (42 - (sbox_index * 6))) & 0x3f;
		result |= (g_des_sbox[sbox_index][sbox_input.sbox.first << 1 | sbox_input.sbox.first][sbox_input.sbox.middle]) << (28 - (sbox_index * 4));
		sbox_index++;
	}
	return (result);
}

uint32_t	des_round(uint32_t right_block, t_uint48 key)
{
	t_uint48	expanded_right_block;

	expanded_right_block = des_right_block_expand(right_block);
	expanded_right_block.uint ^= key.uint;
	return (des_round_s_box_compress(expanded_right_block));
}

uint64_t		des_encrypt_algo(t_des_algo_context algo_ctx
	, uint64_t block
	, size_t block_length)
{
	t_uint48	key_schedule[DES_KEY_SCHEDULE_COUNT];
	uint32_t	left_block;
	uint32_t	right_block;
	uint32_t	tmp_block;
	size_t		index;

	des_generate_key_schedule(key_schedule, algo_ctx.key);
	if (block_length < sizeof(block))
	{
		; // pad
	}
	block = des_ip(block);
	left_block = (block >> 32) & 0xffffffff;
	right_block = block & 0xffffffff;
	index = 0;
	while (index < DES_KEY_SCHEDULE_COUNT)
	{
		tmp_block = left_block;
		left_block = des_round(right_block, key_schedule[index]);
		right_block = tmp_block;
		index++;
	}
	block = ((uint64_t)left_block << 32) | (uint64_t)right_block;
	block = des_inv_ip(block);
	return (block);
}
