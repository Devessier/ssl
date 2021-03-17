/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:37:57 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/17 10:39:51 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "ssl.h"
#include "base64.h"
#include "reader.h"
#include "writer.h"
#include "open.h"

static const char	g_base64_dictionary[65] = {
	[0] = 'A',
	[1] = 'B',
	[2] = 'C',
	[3] = 'D',
	[4] = 'E',
	[5] = 'F',
	[6] = 'G',
	[7] = 'H',
	[8] = 'I',
	[9] = 'J',
	[10] = 'K',
	[11] = 'L',
	[12] = 'M',
	[13] = 'N',
	[14] = 'O',
	[15] = 'P',
	[16] = 'Q',
	[17] = 'R',
	[18] = 'S',
	[19] = 'T',
	[20] = 'U',
	[21] = 'V',
	[22] = 'W',
	[23] = 'X',
	[24] = 'Y',
	[25] = 'Z',
	[26] = 'a',
	[27] = 'b',
	[28] = 'c',
	[29] = 'd',
	[30] = 'e',
	[31] = 'f',
	[32] = 'g',
	[33] = 'h',
	[34] = 'i',
	[35] = 'j',
	[36] = 'k',
	[37] = 'l',
	[38] = 'm',
	[39] = 'n',
	[40] = 'o',
	[41] = 'p',
	[42] = 'q',
	[43] = 'r',
	[44] = 's',
	[45] = 't',
	[46] = 'u',
	[47] = 'v',
	[48] = 'w',
	[49] = 'x',
	[50] = 'y',
	[51] = 'z',
	[52] = '0',
	[53] = '1',
	[54] = '2',
	[55] = '3',
	[56] = '4',
	[57] = '5',
	[58] = '6',
	[59] = '7',
	[60] = '8',
	[61] = '9',
	[62] = '+',
	[63] = '/',

	[BASE64_PADDING_CHAR] = '=',
};

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

void						base64_algo(t_context *ctx)
{
	t_reader	reader;
	t_writer	writer;
	char		input_block[BASE64_INPUT_BLOCK_LENGTH];
	uint8_t		sextets[BASE64_OUTPUT_BLOCK_LENGTH];
	ssize_t		buffer_length;
	size_t		index;
	char		output_chars[BASE64_OUTPUT_BLOCK_LENGTH];

	reader = base64_create_reader(ctx);
	if (reader.type == READER_TYPE_NOOP)
		return ;
	writer = base64_create_writer(ctx);
	if (writer.activated == false)
		return ;
	while ((buffer_length = reader_read((t_reader *)&reader, (char *)&input_block, BASE64_INPUT_BLOCK_LENGTH)) > 0)
	{
		sextets[0] = input_block[0] >> 2 & 0b111111;
		if (buffer_length == 1)
			sextets[1] = ((input_block[0] & 0b11) << 4);
		else
			sextets[1] = ((input_block[0] & 0b11) << 4) | ((input_block[1] >> 4) & 0b1111);

		if (buffer_length == 2)
			sextets[2] = ((input_block[1] & 0b1111) << 2);
		else if (buffer_length == 1)
			sextets[2] = BASE64_PADDING_CHAR;
		else
			sextets[2] = ((input_block[1] & 0b1111) << 2) | ((input_block[2] >> 6) & 0b11);

		if (buffer_length == 3)
			sextets[3] = input_block[2] & 0b111111;
		else
			sextets[3] = BASE64_PADDING_CHAR;

		index = 0;
		while (index < BASE64_OUTPUT_BLOCK_LENGTH)
		{
			output_chars[index] = g_base64_dictionary[sextets[index]];
			index++;
		}
		writer_write(&writer, output_chars, sizeof(output_chars));
	}
	writer_pad(&writer, '\n', 1);
	writer_flush(&writer);
}
