/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:17:14 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/17 12:13:01 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "base64.h"
#include "reader.h"
#include "writer.h"
#include "open.h"

t_arg		g_base64_arguments[] = {
	{
		.type = ARG_NOOP,
		.name = "e",
		.description = "encodes input (default)"
	},
	{
		.type = ARG_NOOP,
		.name = "d",
		.description = "decodes input"
	},
	{
		.type = ARG_STRING,
		.name = "i",
		.description = "input file (default: stdin)"
	},
	{
		.type = ARG_STRING,
		.name = "o",
		.description = "output file (default: stdout)"
	},
	{
		.type = ARG_POSITIVE_INTEGER,
		.name = "b",
		.description = "break encoded string into num character lines"
	},
	{
		.type = ARG_END
	}
};

static void	activate_encoding_mode(t_context *ctx)
{
	ctx->algo_ctx.base64.is_encoding = true;
}

static void	activate_decoding_mode(t_context *ctx)
{
	ctx->algo_ctx.base64.is_encoding = false;
}

void		bind_base64_args(t_context *ctx)
{
	ctx->algo_ctx.base64.is_encoding = true;
	ctx->args[0].exec_after = activate_encoding_mode;
	ctx->args[1].exec_after = activate_decoding_mode;
	ctx->args[2].value = &ctx->algo_ctx.base64.input_file;
	ctx->args[3].value = &ctx->algo_ctx.base64.output_file;
	ctx->args[4].value = &ctx->algo_ctx.base64.line_break;
	ctx->cmd = base64_cmd;
}

void		base64_log_command_usage(t_context *ctx)
{
	(void)ctx;

	ft_putf_fd(STDERR_FILENO
		, "usage: ft_ssl base64 [-ed] [-b num] [-i in_file] [-o out_file]\n");
}

static t_reader				base64_create_reader(t_context *ctx)
{
	const char	*input_file = ctx->algo_ctx.base64.input_file;
	int			file_fd;

	if (input_file == NULL)
		return create_reader_fd(STDIN_FILENO, "stdin", false);
	if ((file_fd = open_read_file(ctx, (char *)input_file)) == -1)
		return create_reader_empty();
	return create_reader_fd(file_fd, (char *)input_file, false);
}

static t_writer				base64_create_writer(t_context *ctx)
{
	const char		*output_file = ctx->algo_ctx.base64.output_file;
	const size_t	line_break = ctx->algo_ctx.base64.line_break;
	int				file_fd;
	char			*filename;

	if (output_file == NULL)
	{
		file_fd = STDOUT_FILENO;
		filename = "stdout";
	}
	else
	{
		if ((file_fd = open_write_file(ctx, (char *)output_file)) == -1)
			return (create_writer_empty());
		filename = (char *)output_file;
	}
	if (line_break == 0)
		return (create_writer(file_fd, filename));
	return (create_writer_breaker(file_fd, filename, line_break, "\n"));
}

void						base64_cmd(t_context *ctx)
{
	t_reader	reader;
	t_writer	writer;
	uint8_t		input_block[BASE64_INPUT_BLOCK_LENGTH];
	ssize_t		buffer_length;
	uint8_t		output_chars[BASE64_OUTPUT_BLOCK_LENGTH];

	reader = base64_create_reader(ctx);
	if (reader.type == READER_TYPE_NOOP)
		return ;
	writer = base64_create_writer(ctx);
	if (writer.activated == false)
		return ;
	while ((buffer_length = reader_read(&reader
		, (char *)&input_block, BASE64_INPUT_BLOCK_LENGTH)) > 0)
	{
		base64_algo_encode(input_block, buffer_length, output_chars);
		writer_write(&writer, (char *)output_chars, sizeof(output_chars));
	}
	writer_pad(&writer, '\n', 1);
	writer_flush(&writer);
}

