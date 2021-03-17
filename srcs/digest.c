/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:05:37 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/17 01:46:11 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "digest_exec.h"
#include "reader.h"
#include "open.h"

t_arg			g_digest_arguments[] = {
	{
		.type = ARG_BOOLEAN,
		.name = "p",
		.description = "echo STDIN to STDOUT and append the checksum to STDOUT"
	},
	{
		.type = ARG_BOOLEAN,
		.name = "q",
		.description = "quiet mode"
	},
	{
		.type = ARG_BOOLEAN,
		.name = "r",
		.description = "reverse the format of the output"
	},
	{
		.type = ARG_STRING,
		.name = "s",
		.description = "print the sum of the given string"
	},
	{
		.type = ARG_END
	}
};

void			digest_log_command_usage(t_context *ctx)
{
	ft_putf_fd(STDERR_FILENO
		, "usage: ft_ssl %s [-p] [-q] [-r] [-s string] [files ...]\n"
		, ctx->algo_name);
}

void			digest_stdin_cmd(t_context *ctx)
{
	const bool		auto_print = ctx->algo_ctx.digest.print;
	const t_reader	rd = create_reader_fd(STDIN_FILENO, "stdin", auto_print);

	digest_algo_exec(ctx, (t_reader *)&rd, DIGEST_EXEC_ORIGIN_STDIN);
}

void			digest_string_cmd(t_context *ctx)
{
	const char		*string_arg = ctx->algo_ctx.digest.string;
	const size_t	length = ft_strlen(string_arg);
	const t_reader	rd = create_reader_buffer((char *)string_arg, length);

	digest_algo_exec(ctx, (t_reader *)&rd, DIGEST_EXEC_ORIGIN_STRING);
}

static bool		digest_cmd_should_read_stdin(t_context *ctx)
{
	return (ctx->algo_ctx.digest.string == NULL
		&& ctx->algo_ctx.digest.print == false
		&& (ctx->remaining_args == NULL || *ctx->remaining_args == NULL));
}

void			digest_cmd(t_context *ctx)
{
	const bool	read_stdin = digest_cmd_should_read_stdin(ctx);
	t_reader	reader;
	int			fd;
	char		*file;

	if (read_stdin)
	{
		digest_stdin_cmd(ctx);
		return ;
	}
	while ((file = *(ctx->remaining_args++)) != NULL)
	{
		if ((fd = open_read_file(ctx, file)) == -1)
			continue ;
		reader = create_reader_fd(fd, file, false);
		digest_algo_exec(ctx, &reader, DIGEST_EXEC_ORIGIN_FILE);
		close(fd);
	}
}
