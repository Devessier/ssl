/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac_sha256_algo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:38:42 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/24 11:34:42 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "sha256.h"
#include "sha256_algo.h"
#include "hmac_sha256_algo.h"

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


void				hmac_sha256_init(
	t_hmac_sha256_algo_context *ctx
	, char *key
	, size_t key_length)
{
	uint8_t					constrained_key[SHA256_HASH_SIZE] = { 0 };
	size_t					index;

	*ctx = (t_hmac_sha256_algo_context) {
		.key = key,
		.key_length = key_length,
	};
	ft_bzero(ctx->ipad, sizeof(ctx->ipad));
	ft_bzero(ctx->opad, sizeof(ctx->opad));
	if (key_length > SHA256_BUFFER_SIZE)
	{
		hmac_sha256_algo_hash_key(key, key_length, constrained_key);
		ctx->key = (char *)constrained_key;
		ctx->key_length = SHA256_HASH_SIZE;
	}
	ft_memcpy(ctx->ipad, ctx->key, ctx->key_length);
	ft_memcpy(ctx->opad, ctx->key, ctx->key_length);
	index = 0;
	while (index < SHA256_BUFFER_SIZE)
	{
		ctx->ipad[index] ^= 0x36;
		ctx->opad[index] ^= 0x5c;
		index++;
	}
	sha256_init(&ctx->sha256_context);
	sha256_update(&ctx->sha256_context, ctx->ipad, sizeof(ctx->ipad));
}

void				hmac_sha256_update(
	t_hmac_sha256_algo_context *ctx
	, uint8_t *src
	, size_t len)
{
	sha256_update(&ctx->sha256_context, src, len);
}

void				hmac_sha256_final(
	t_hmac_sha256_algo_context *ctx
	, uint8_t hash[SHA256_HASH_SIZE])
{
	sha256_final(&ctx->sha256_context, hash);
	sha256_init(&ctx->sha256_context);
	sha256_update(&ctx->sha256_context, ctx->opad, sizeof(ctx->opad));
	sha256_update(&ctx->sha256_context, hash, SHA256_HASH_SIZE);
	sha256_final(&ctx->sha256_context, hash);
}

void			hmac_sha256_algo(
	t_reader *reader
	, char *key
	, size_t key_length
	, uint8_t hash[SHA256_HASH_SIZE])
{
	t_hmac_sha256_algo_context	ctx;
	uint8_t						buffer[SHA256_BUFFER_SIZE] = { 0 };
	ssize_t						buffer_length;

	hmac_sha256_init(&ctx, key, key_length);
	while ((buffer_length = reader_read(reader, (char *)buffer, sizeof(buffer))) > 0)
	{
		hmac_sha256_update(&ctx, buffer, buffer_length);
		if (reader->finished == true)
			break ;
	}
	hmac_sha256_final(&ctx, hash);
}
