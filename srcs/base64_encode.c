/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:39:37 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/17 12:41:37 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "base64.h"
#include "reader.h"
#include "writer.h"
#include "open.h"

static t_reader				base64_encode_create_reader(t_context *ctx)
{
	const char	*input_file = ctx->algo_ctx.base64.input_file;
	int			file_fd;

	if (input_file == NULL)
		return create_reader_fd(STDIN_FILENO, "stdin", false);
	if ((file_fd = open_read_file(ctx, (char *)input_file)) == -1)
		return create_reader_empty();
	return create_reader_fd(file_fd, (char *)input_file, false);
}

static t_writer				base64_encode_create_writer(t_context *ctx)
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

void						base64_encode_cmd(t_context *ctx)
{
	t_reader	reader;
	t_writer	writer;
	uint8_t		input_block[BASE64_INPUT_BLOCK_LENGTH];
	ssize_t		buffer_length;
	uint8_t		output_chars[BASE64_OUTPUT_BLOCK_LENGTH];

	reader = base64_encode_create_reader(ctx);
	if (reader.type == READER_TYPE_NOOP)
		return ;
	writer = base64_encode_create_writer(ctx);
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

