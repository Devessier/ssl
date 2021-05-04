/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac_sha256.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:56:15 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 18:46:16 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hexa.h"

#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "hmac_sha256_algo.h"

static void		hmac_sha256_print(uint8_t *hash)
{
	size_t			index;

	index = 0;
	while (index < SHA256_HASH_SIZE)
		print_hexa_num(STDOUT_FILENO, hash[index++]);
}

static void		hmac_sha256_print_error(t_context *ctx, const char *error)
{
	ft_putf_fd(STDERR_FILENO, "ft_ssl: %s: %s\n", ctx->algo_name, error);
}

static t_reader	hmac_sha256_get_reader(t_context *ctx)
{
	const char	*string = ctx->algo_ctx.hmac.string;

	if (string == NULL)
		return (create_reader_fd(STDIN_FILENO, "stdin", false));
	return (create_reader_buffer((char *)string, ft_strlen(string)));
}

static void		hmac_sha256_cmd(t_context *ctx)
{
	const t_reader	reader = hmac_sha256_get_reader(ctx);
	const char		*key = ctx->algo_ctx.hmac.key;
	uint8_t			hash[SHA256_HASH_SIZE];

	if (key == NULL || key[0] == '\0')
		return (hmac_sha256_print_error(ctx, "invalid empty key"));
	hmac_sha256_algo((t_reader *)&reader, (char *)key, ft_strlen(key), hash);
	if (reader.type != READER_TYPE_FD)
		ft_putf("%s (\"%s\") = ", ctx->algo_name_capital, ctx->algo_ctx.hmac.string);
	hmac_sha256_print(hash);
	ft_putchar('\n');
}

void	bind_hmac_sha256_args(t_context *ctx)
{
	ctx->args[0].value = &ctx->algo_ctx.hmac.string;
	ctx->args[1].value = &ctx->algo_ctx.hmac.key;
	ctx->cmd = hmac_sha256_cmd;
}
