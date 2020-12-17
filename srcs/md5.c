/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:36:52 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/17 19:34:18 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "reader.h"
#include "md5.h"
#include "md5_exec.h"
#include "open.h"

static void		md5_stdin_cmd(t_context *ctx)
{
	const bool		auto_print = ctx->algo_ctx.digest.print;
	const t_reader	stdin_reader = create_reader_fd(STDIN_FILENO, "stdin", auto_print);

	md5_algo_exec(ctx, (t_reader *)&stdin_reader, DIGEST_EXEC_ORIGIN_STDIN);
}

static void		md5_string_cmd(t_context *ctx)
{
	const char		*string_arg = ctx->algo_ctx.digest.string;
	const size_t	string_len = ft_strlen(string_arg);
	t_reader		reader;

	reader = create_reader_buffer((char *)string_arg, string_len);
	md5_algo_exec(ctx, &reader, DIGEST_EXEC_ORIGIN_STRING);
}

static bool		md5_cmd_should_read_stdin(t_context *ctx)
{
	return (ctx->algo_ctx.digest.string == NULL
		&& ctx->algo_ctx.digest.print == false
		&& (ctx->remaining_args == NULL || *ctx->remaining_args == NULL));
}

static void		md5_cmd(t_context *ctx)
{
	const bool	read_stdin = md5_cmd_should_read_stdin(ctx);
	t_reader	reader;
	int			fd;
	char		*file;

	if (read_stdin)
	{
		md5_stdin_cmd(ctx);
		return ;
	}
	while ((file = *(ctx->remaining_args++)) != NULL)
	{
		if ((fd = open_file(ctx, file)) == -1)
			continue ;
		reader = create_reader_fd(fd, file, false);
		md5_algo_exec(ctx, &reader, DIGEST_EXEC_ORIGIN_FILE);
		close(fd);
	}
}

void			bind_md5_args(t_context *ctx)
{
	ctx->args[0].value = &ctx->algo_ctx.digest.print;
	ctx->args[0].exec_after = md5_stdin_cmd;
	ctx->args[1].value = &ctx->algo_ctx.digest.quiet;
	ctx->args[2].value = &ctx->algo_ctx.digest.reverse;
	ctx->args[3].value = &ctx->algo_ctx.digest.string;
	ctx->args[3].exec_after = md5_string_cmd;
	ctx->cmd = md5_cmd;
}
