/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 17:35:32 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/07 16:58:37 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ssl.h"
#include "digest.h"
#include "md5.h"
#include "sha256.h"

t_arg		*get_algo_arguments(t_algo algo)
{
	if (algo == ALGO_MD5 || algo == ALGO_SHA256 || algo == ALGO_SHA224 || algo == ALGO_SHA512)
		return (g_digest_arguments);
	return (NULL);
}

t_algo_cmd	get_algo_usage(t_algo algo)
{
	if (algo == ALGO_MD5 || algo == ALGO_SHA256 || algo == ALGO_SHA224 || algo == ALGO_SHA512)
		return (digest_log_command_usage);
	return (NULL);
}
