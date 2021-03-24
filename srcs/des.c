/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:58:03 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/24 01:26:40 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ssl.h"
#include "des.h"
#include "hexa.h"
#include "random_number_generator.h"

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
		.type = ARG_BOOLEAN,
		.name= "print-key-iv",
		.description = "print key and iv",
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

static t_error	des_cmd_set_salt(t_context *ctx, t_des_algo_context *algo_ctx)
{
	const char				*salt = ctx->algo_ctx.des.salt;
	size_t					salt_length;
	t_hexa_to_uint64_result	hexa_number;

	if (salt == NULL)
	{
		get_random_buffer((char *)&algo_ctx->salt, sizeof(algo_ctx->salt));
		return (E_SUCCESS);
	}
	salt_length = ft_strlen(salt);
	if (salt_length > DES_MAX_KEY_HEX_CHARACTERS)
	{
		ft_putf_fd(STDERR_FILENO, "hex string is too long, ignoring excess\n");
		salt_length = DES_MAX_KEY_HEX_CHARACTERS;
	}
	else if (salt_length < DES_MAX_KEY_HEX_CHARACTERS)
		ft_putf_fd(STDERR_FILENO, "hex string is too short, padding with zero bytes to length\n");
	hexa_number = hexa_to_uint64(salt, salt_length);
	if (hexa_number.error != E_SUCCESS)
	{
		ft_putf_fd(STDERR_FILENO, "non-hex digit\n");
		return (hexa_number.error);
	}
	algo_ctx->salt = hexa_number.number;
	return (E_SUCCESS);
}

static t_error	des_cmd_set_key(t_context *ctx, t_des_algo_context *algo_ctx)
{
	const char				*key = ctx->algo_ctx.des.key;
	size_t					key_length;
	t_hexa_to_uint64_result	hexa_number;

	if (key == NULL)
	{
		// Generate key, using or not salt argument
		return (E_SUCCESS);
	}
	key_length = ft_strlen(key);
	if (key_length > DES_MAX_KEY_HEX_CHARACTERS)
	{
		ft_putf_fd(STDERR_FILENO, "hex string is too long, ignoring excess\n");
		key_length = DES_MAX_KEY_HEX_CHARACTERS;
	}
	else if (key_length < DES_MAX_KEY_HEX_CHARACTERS)
		ft_putf_fd(STDERR_FILENO, "hex string is too short, padding with zero bytes to length\n");
	hexa_number = hexa_to_uint64(key, key_length);
	if (hexa_number.error != E_SUCCESS)
	{
		ft_putf_fd(STDERR_FILENO, "non-hex digit\n");
		return (hexa_number.error);
	}
	algo_ctx->key = hexa_number.number;
	return (E_SUCCESS);
}

static void		des_cmd_print_salt_key_iv(t_des_algo_context *algo_ctx)
{
	const int	fd = STDERR_FILENO;

	ft_putf_fd(fd, "salt=");
	print_uint64_to_hexa(fd, algo_ctx->salt);
	ft_putf_fd(fd, "\nkey=");
	print_uint64_to_hexa(fd, algo_ctx->key);
	ft_putchar_fd('\n', fd);
}

static void		des_cmd(t_context *ctx)
{
	t_des_algo_context	algo_ctx;

	if (des_cmd_set_salt(ctx, &algo_ctx) != E_SUCCESS)
	{
		ft_putf_fd(STDERR_FILENO, "invalid hex salt value\n");
		return ;
	}
	if (des_cmd_set_key(ctx, &algo_ctx) != E_SUCCESS)
	{
		ft_putf_fd(STDERR_FILENO, "invalid hex key value\n");
		return ;
	}
	if (ctx->algo_ctx.des.print_key_iv == true)
		des_cmd_print_salt_key_iv(&algo_ctx);
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
	ctx->args[9].value = &ctx->algo_ctx.des.print_key_iv;
	ctx->cmd = des_cmd;
}

void		des_log_command_usage(t_context *ctx)
{
	(void)ctx;
	ft_putf_fd(STDERR_FILENO
		, "usage: ft_ssl des [-ade] [-print-key-iv] [-i in_file] [-o out_file] [-k key] [-p password] [-s salt] [-v iv]\n");
}
