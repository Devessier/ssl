/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 13:07:24 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/24 13:09:55 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "md5_print.h"

void	digest_print(t_context *ctx)
{
	if (ctx->algo == ALGO_MD5)
		md5_hash_print(ctx->algo_ctx.digest.algo_ctx.md5.hash);
}
