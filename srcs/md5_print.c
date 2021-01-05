/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:25:06 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/05 12:51:56 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ssl.h"
#include "hexa.h"

void		md5_hash_print(t_context *ctx)
{
	const uint8_t	*hash = ctx->algo_ctx.digest.algo_ctx.md5.hash;
	size_t			index;

	index = 0;
	while (index < MD5_HASH_SIZE)
		print_hexa_num(STDOUT_FILENO, hash[index++]);
}
