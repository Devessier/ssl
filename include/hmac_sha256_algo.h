/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac_sha256_algo.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:58:54 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/24 10:56:36 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HMAC_SHA256_ALGO_H
# define HMAC_SHA256_ALGO_H
# include "ssl.h"
# include "reader.h"
# include "sha256.h"

typedef struct		s_hmac_sha256_algo_context
{
	char					*key;
	size_t					key_length;
	t_sha256_algo_context	sha256_context;
	uint8_t					ipad[SHA256_BUFFER_SIZE];
	uint8_t					opad[SHA256_BUFFER_SIZE];
}					t_hmac_sha256_algo_context;

void				hmac_sha256_init(
	t_hmac_sha256_algo_context *ctx
	, char *key
	, size_t key_length);
void				hmac_sha256_update(
	t_hmac_sha256_algo_context *ctx
	, uint8_t *src
	, size_t len);
void				hmac_sha256_final(
	t_hmac_sha256_algo_context *ctx
	, uint8_t *hash);

void		hmac_sha256_algo(
	t_reader *reader
	, char *key
	, size_t key_length
	, uint8_t *hash);

#endif
