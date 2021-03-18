/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:39:36 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/18 01:41:21 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "base64.h"
#include "reader.h"
#include "writer.h"
#include "open.h"

static bool					base64_decode_reader_skipper(char character)
{
	return (ft_isspace(character));
}

static t_reader				base64_decode_create_reader(t_context *ctx)
{
	const char	*input_file = ctx->algo_ctx.base64.input_file;
	int			file_fd;

	if (input_file == NULL)
		return (create_reader_fd(STDIN_FILENO, "stdin", false));
	if ((file_fd = open_read_file(ctx, (char *)input_file)) == -1)
		return (create_reader_empty());
	return (create_reader_fd(file_fd, (char *)input_file, false));
}

void						base64_decode_cmd(t_context *ctx)
{
	t_reader	reader;
	t_writer	writer;
	uint8_t		input_block[BASE64_OUTPUT_BLOCK_LENGTH];
	ssize_t		buffer_length;
	ssize_t		decoded_characters_count;
	uint8_t		output_chars[BASE64_INPUT_BLOCK_LENGTH];

	reader = base64_decode_create_reader(ctx);
	if (reader.type == READER_TYPE_NOOP)
		return ;
	writer = base64_create_writer(ctx, ctx->algo_ctx.base64.output_file, 0);
	if (writer.activated == false)
		return ;
	while ((buffer_length = reader_read_skip(&reader
		, (char *)&input_block, BASE64_OUTPUT_BLOCK_LENGTH
		, base64_decode_reader_skipper)) > 0)
	{
		if (buffer_length != BASE64_OUTPUT_BLOCK_LENGTH
			|| (decoded_characters_count = base64_algo_decode(input_block, output_chars)) == -1)
		{
			ft_putf_fd(STDERR_FILENO, "Invalid character in input stream.\n");
			return ;
		}
		writer_write(&writer, (char *)output_chars, decoded_characters_count);
	}
	writer_flush(&writer);
}
