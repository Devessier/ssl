/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_pbkdf2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:55:07 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/29 12:29:51 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hmac_sha256_algo.h"
#include "sha256.h"
#include "endianness.h"

uint64_t	des_pbkdf2(char *password, size_t password_length, uint64_t salt, size_t iter)
{
	const uint8_t				be_block_index[] = {0x0, 0x0, 0x0, 0x1};
	t_hmac_sha256_algo_context	ctx;
	uint8_t						block[SHA256_HASH_SIZE] = { 0 };
	uint8_t						tmp[SHA256_HASH_SIZE] = { 0 };
	size_t						index;
	size_t						byte_index;
	uint64_t					key;

	hmac_sha256_init(&ctx, password, password_length);
	hmac_sha256_update(&ctx, (uint8_t *)&salt, sizeof(salt));
	hmac_sha256_update(&ctx, (uint8_t *)be_block_index, sizeof(be_block_index));
	hmac_sha256_final(&ctx, tmp);
	ft_memcpy(block, tmp, sizeof(key));
	index = 1;
	while (index < iter)
	{
		hmac_sha256_init(&ctx, password, password_length);
		hmac_sha256_update(&ctx, (uint8_t *)tmp, sizeof(tmp));
		hmac_sha256_final(&ctx, tmp);
		byte_index = 0;
		while (byte_index < sizeof(key))
		{
			block[byte_index] ^= tmp[byte_index];
			byte_index++;
		}
		index++;
	}
	index = 0;
	key = 0;
	while (index < sizeof(key))
	{
		key |= ((uint64_t)block[index]) << (8 * index);
		index++;
	}
	return (key);
}
