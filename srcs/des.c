/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:58:03 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 11:25:44 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"

t_arg		g_des_arguments[] = {
	{
		.type = ARG_BOOLEAN,
		.name= "a",
		.description = "decode/encode the input/output in base64, depending on the encrypt mode",
	},
	{
		.type = ARG_NOOP,
		.name = "d",
		.description = "decrypt input"
	},
	{
		.type = ARG_NOOP,
		.name = "e",
		.description = "encrypt input (default)"
	},
	{
		.type = ARG_STRING,
		.name = "i",
		.description = "input file (default: stdin)"
	},
	{
		.type = ARG_STRING,
		.name= "k",
		.description = "key in hex is the next arguement",
	},
	{
		.type = ARG_STRING,
		.name = "o",
		.description = "output file (default: stdout)"
	},
	{
		.type = ARG_STRING,
		.name= "p",
		.description = "password in ascii is the next argument",
	},
	{
		.type = ARG_STRING,
		.name= "s",
		.description = "the salt in hex is the next argument",
	},
	{
		.type = ARG_STRING,
		.name= "v",
		.description = "initialization vector in hex is the next argument",
	},
	{
		.type = ARG_END
	}
};

static void	activate_encrypt_mode(t_context *ctx)
{
	ctx->algo_ctx.des.is_encrypting = true;
}

static void	activate_decrypt_mode(t_context *ctx)
{
	ctx->algo_ctx.des.is_encrypting = false;
}

static void		des_cmd(t_context *ctx)
{
	ft_putf("des cmd: %s\n", ctx->algo_name);
}

void		bind_des_args(t_context *ctx)
{
	ctx->args[0].value = &ctx->algo_ctx.des.base64_mode;
	ctx->algo_ctx.des.is_encrypting = true;
	ctx->args[1].exec_after = activate_decrypt_mode;
	ctx->args[2].exec_after = activate_encrypt_mode;
	ctx->args[3].value = &ctx->algo_ctx.des.input_file;
	ctx->args[4].value = &ctx->algo_ctx.des.key;
	ctx->args[5].value = &ctx->algo_ctx.des.output_file;
	ctx->args[6].value = &ctx->algo_ctx.des.password;
	ctx->args[7].value = &ctx->algo_ctx.des.salt;
	ctx->args[8].value = &ctx->algo_ctx.des.iv;
	ctx->cmd = des_cmd;
}

void		des_log_command_usage(t_context *ctx)
{
	(void)ctx;
	ft_putf_fd(STDERR_FILENO
		, "usage: ft_ssl des [-ade] [-i in_file] [-o out_file] [-k key] [-p password] [-s salt] [-v iv]\n");
}
