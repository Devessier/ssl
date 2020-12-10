/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 00:24:10 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/10 12:41:26 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "libft.h"
#include "ssl.h"
#include "md5.h"
#include "sha256.h"

static t_algo_desc	g_algo_descs[] = {
	{ ALGO_MD5, "md5", md5_cmd },
	{ ALGO_SHA256, "sha256", sha256_cmd },
	{ 0, NULL, NULL }
};

t_algo				algo_name_to_algo(char *algo_name)
{
	t_algo_desc		*algo_desc;

	algo_desc = g_algo_descs;
	while (algo_desc->name != NULL)
	{
		if (ft_strcmp(algo_desc->name, algo_name) == 0)
			return (algo_desc->algo);
		algo_desc++;
	}
	return (ALGO_INVALID);
}

static t_algo_desc	*get_algo_desc(t_algo algo)
{
	t_algo_desc		*algo_desc;

	algo_desc = g_algo_descs;
	while (algo_desc->name != NULL)
	{
		if (algo_desc->algo == algo)
			return (algo_desc);
		algo_desc++;
	}
	return (NULL);
}

t_context			create_cmd(t_algo algo)
{
	const t_algo_desc	*algo_desc = get_algo_desc(algo);

	return ((t_context) {
		.algo = algo,
		.algo_name = algo_desc->name,
		.cmd = algo_desc->cmd,
		.args = NULL,
	});
}