/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 17:35:32 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/16 17:47:12 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ssl.h"
#include "digest.h"
#include "md5.h"
#include "sha256.h"
#include "base64.h"

t_arg		*get_algo_arguments(t_algo algo)
{
	if (algo == ALGO_MD5 || algo == ALGO_SHA256
		|| algo == ALGO_SHA224 || algo == ALGO_SHA512
		|| algo == ALGO_SHA384 || algo == ALGO_SHA512_224
		|| algo == ALGO_SHA512_256)
		return (g_digest_arguments);
	if (algo == ALGO_BASE64)
		return (g_base64_arguments);
	return (NULL);
}

t_algo_cmd	get_algo_usage(t_algo algo)
{
	if (algo == ALGO_MD5 || algo == ALGO_SHA256
		|| algo == ALGO_SHA224 || algo == ALGO_SHA512
		|| algo == ALGO_SHA384 || algo == ALGO_SHA512_224
		|| algo == ALGO_SHA512_256)
		return (digest_log_command_usage);
	if (algo == ALGO_BASE64)
		return (base64_log_command_usage);
	return (NULL);
}
