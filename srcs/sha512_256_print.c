/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_256_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:34:19 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/08 02:50:28 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ssl.h"
#include "hexa.h"

void	sha512_256_hash_print(t_context *ctx)
{
	const uint8_t	*hash = ctx->algo_ctx.digest.algo_ctx.sha512_256.hash;
	size_t			index;

	index = 0;
	while (index < SHA512_256_HASH_SIZE)
		print_hexa_num(STDOUT_FILENO, hash[index++]);
}
