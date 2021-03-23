/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac_sha256_algo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:38:42 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 18:47:08 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "sha256.h"
#include "sha256_algo.h"

static void		hmac_sha256_algo_hash_key(
	char *key
	, size_t key_length
	, uint8_t hashed_key[SHA256_WORDS_COUNT])
{
	t_sha256_algo_context	context;

	sha256_init(&context);
	sha256_update(&context, (uint8_t *)key, key_length);
	sha256_final(&context, hashed_key);
}

void			hmac_sha256_algo(
	t_reader *reader
	, char *key
	, size_t key_length
	, uint8_t hash[SHA256_HASH_SIZE])
{
	t_sha256_algo_context	context;
	uint8_t					buffer[SHA256_BUFFER_SIZE] = { 0 };
	ssize_t					buffer_length;
	uint8_t					ipad[SHA256_BUFFER_SIZE] = { 0 };
	uint8_t					opad[SHA256_BUFFER_SIZE] = { 0 };
	uint8_t					constrained_key[SHA256_HASH_SIZE] = { 0 };
	size_t					index;

	if (key_length > SHA256_BUFFER_SIZE)
	{
		hmac_sha256_algo_hash_key(key, key_length, constrained_key);
		key = (char *)constrained_key;
		key_length = SHA256_HASH_SIZE;
	}
	ft_memcpy(ipad, key, key_length);
	ft_memcpy(opad, key, key_length);
	index = 0;
	while (index < SHA256_BUFFER_SIZE)
	{
		ipad[index] ^= 0x36;
		opad[index] ^= 0x5c;
		index++;
	}
	sha256_init(&context);
	sha256_update(&context, ipad, sizeof(ipad));
	while ((buffer_length = reader_read(reader, (char *)buffer, sizeof(buffer))) > 0)
	{
		sha256_update(&context, buffer, buffer_length);
		if (reader->finished == true)
			break ;
	}
	sha256_final(&context, hash);
	sha256_init(&context);
	sha256_update(&context, opad, sizeof(opad));
	sha256_update(&context, hash, SHA256_HASH_SIZE);
	sha256_final(&context, hash);
}
