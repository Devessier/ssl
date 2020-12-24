/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:41:05 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/24 15:42:41 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ssl.h"
#include "hexa.h"

void	sha256_hash_print(t_context *ctx)
{
	const uint8_t	*hash = ctx->algo_ctx.digest.algo_ctx.sha256.hash;
	size_t	index;

	index = 0;
	while (index < SHA256_HASH_SIZE)
		print_hexa_num(STDOUT_FILENO, hash[index++]);
}
