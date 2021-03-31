/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_encrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 12:41:22 by bdevessi          #+#    #+#             */
/*   Updated: 2021/04/01 00:50:41 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"
#include "open.h"
#include "reader.h"
#include "writer.h"
#include "des.h"
#include "des_algo.h"
#include "endianness.h"

static const char	g_des_magic[] = "Salted__";

static t_reader	des_encrypt_create_reader(t_context *ctx)
{
	const char	*input_file = ctx->algo_ctx.des.input_file;
	int			file_fd;

	if (input_file == NULL)
		return (create_reader_fd(STDIN_FILENO, "stdin", false));
	if ((file_fd = open_read_file(ctx, (char *)input_file)) == -1)
		return (create_reader_empty());
	return (create_reader_fd(file_fd, (char *)input_file, false));
}

static t_writer	des_encrypt_create_writer(t_context *ctx)
{
	const char	*output_file = ctx->algo_ctx.des.output_file;
	int			file_fd;
	char		*filename;

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
	return (create_writer(file_fd, filename));
}

#include <printf.h>

t_error		des_encrypt_cmd(t_context *ctx, t_des_algo_context algo_ctx)
{
	t_reader	reader;
	t_writer	writer;
	uint64_t	block;
	ssize_t		buffer_length;
	uint64_t	encrypted_block;

	block = 0;
	reader = des_encrypt_create_reader(ctx);
	if (reader.finished == true)
		return (E_FAILURE);
	writer = des_encrypt_create_writer(ctx);
	if (writer.activated == false)
		return (E_FAILURE);
	writer_write(&writer, (char *)g_des_magic, sizeof(g_des_magic) - 1);
	writer_write(&writer, (char *)&algo_ctx.salt, sizeof(algo_ctx.salt));
	while ((buffer_length = reader_read(&reader, (char *)&block, sizeof(block))) == DES_KEY_BYTES_SIZE)
	{
		encrypted_block = des_encrypt_algo(algo_ctx, block, buffer_length);
		writer_write(&writer, (char *)&encrypted_block, sizeof(encrypted_block));
	}
	encrypted_block = des_encrypt_algo(algo_ctx, block, buffer_length);
	writer_write(&writer, (char *)&encrypted_block, sizeof(encrypted_block));
	writer_flush(&writer);
	return (E_SUCCESS);
}
