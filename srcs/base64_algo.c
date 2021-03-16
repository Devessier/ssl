/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:37:57 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/16 18:34:31 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "ssl.h"
#include "reader.h"

void						base64_algo(t_context *ctx)
{
	ft_putf("is encoding = %d, break line = %d\n", ctx->algo_ctx.base64.is_encoding, ctx->algo_ctx.base64.line_break);
}
