/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:00:25 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/05 17:00:44 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ssl.h"
#include "hexa.h"

void	sha224_hash_print(t_context *ctx)
{
	const uint8_t	*hash = ctx->algo_ctx.digest.algo_ctx.sha224.hash;
	size_t			index;

	index = 0;
	while (index < SHA224_HASH_SIZE)
		print_hexa_num(STDOUT_FILENO, hash[index++]);
}
