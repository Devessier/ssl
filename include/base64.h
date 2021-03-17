/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:38:39 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/17 20:03:17 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64
# define BASE64
# include "ssl.h"
# include "writer.h"
# define BASE64_INPUT_BLOCK_LENGTH 3
# define BASE64_OUTPUT_BLOCK_LENGTH 4
# define BASE64_PADDING_CHAR 64

void				bind_base64_args(t_context *ctx);
void				base64_log_command_usage(t_context *ctx);
void				base64_cmd(t_context *ctx);
t_writer			base64_create_writer(t_context *ctx
	, char *output_file, size_t line_break);
void				base64_encode_cmd(t_context *ctx);
void				base64_decode_cmd(t_context *ctx);

t_error				base64_algo_encode(uint8_t to_encode[BASE64_INPUT_BLOCK_LENGTH]
	, size_t to_encode_length
	, uint8_t dest[BASE64_OUTPUT_BLOCK_LENGTH]);
ssize_t				base64_algo_decode(uint8_t to_decode[BASE64_OUTPUT_BLOCK_LENGTH]
	, uint8_t dest[BASE64_INPUT_BLOCK_LENGTH]);

extern t_arg		g_base64_arguments[];

#endif
