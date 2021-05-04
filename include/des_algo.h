/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_algo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:23:37 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/31 01:34:22 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_ALGO_H
# define DES_ALGO_H
# include "ssl.h"
# include "des.h"
# define DES_KEY_SCHEDULE_COUNT 16
# define DES_SBOX_COUNT 8

typedef union	u_uint6
{
	uint8_t		uint:6;
	struct {
		uint8_t first:1;
		uint8_t middle:4;
		uint8_t last:1;
	}			sbox;
}				t_uint6;

typedef union	u_uint48
{
	uint64_t	uint:48;
	uint64_t	uint64;
}				t_uint48;

typedef union	u_uint56
{
	uint64_t	uint:56;
	uint64_t	uint64;
}				t_uint56;

typedef union	u_uint28
{
	uint32_t	uint:28;
	uint32_t	uint32;
}				t_uint28;

typedef union	u_uint24
{
	uint32_t	uint:24;
	uint32_t	uint32;
}				t_uint24;

uint64_t		des_encrypt_algo(t_des_algo_context algo_ctx
	, uint64_t block
	, size_t block_length);

uint64_t	des_permute(uint64_t input_block
	, size_t input_block_bytes_length
	, const uint8_t table[]
	, size_t table_size);
uint64_t	des_ip(uint64_t block);
void	des_generate_key_schedule(t_uint48 key_schedule[DES_KEY_SCHEDULE_COUNT]
	, uint64_t key);

#endif
