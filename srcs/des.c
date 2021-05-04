/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:58:03 by bdevessi          #+#    #+#             */
/*   Updated: 2021/05/04 15:50:21 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readpassphrase.h>
#include "libft.h"
#include "ssl.h"
#include "des.h"
#include "hexa.h"
#include "random_number_generator.h"
#include "des_pbkdf2.h"
#include "endianness.h"

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
		.type = ARG_POSITIVE_INTEGER,
		.name= "iter",
		.description = "pbkdf2 iteration count",
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

static t_error	des_cmd_set_password(t_context *ctx, t_des_algo_context *algo_ctx)
{
	const char	*password = ctx->algo_ctx.des.password;
	char		*password_input;
	static char	entered_password[128];

	if (password == NULL)
	{
		ft_bzero(entered_password, sizeof(entered_password));
		password_input = readpassphrase("enter des encryption password:", entered_password
			, sizeof(entered_password), RPP_ECHO_OFF);
		if (password_input == NULL || password_input[0] == '\0')
			return (E_EMPTY_INPUT);
		algo_ctx->password = password_input;
	}
	else
		algo_ctx->password = (char *)password;
	return (E_SUCCESS);
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
		return (E_DES_SALT_INVALID_HEX);
	}
	algo_ctx->salt = hexa_number.number;
	if (salt_length < DES_MAX_KEY_HEX_CHARACTERS)
		algo_ctx->salt <<= ((DES_MAX_KEY_HEX_CHARACTERS - salt_length) * 4);
	algo_ctx->salt = endianness_swap64(algo_ctx->salt);
	return (E_SUCCESS);
}

static t_error	des_cmd_set_key(t_context *ctx, t_des_algo_context *algo_ctx)
{
	const char				*key = ctx->algo_ctx.des.key;
	const size_t			iter = ctx->algo_ctx.des.iter;
	size_t					key_length;
	t_hexa_to_uint64_result	hexa_number;

	if (key == NULL)
	{
		algo_ctx->key = des_pbkdf2(algo_ctx->password
			, ft_strlen(algo_ctx->password), algo_ctx->salt, iter);
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
		return (E_DES_KEY_INVALID_HEX);
	}
	algo_ctx->key = hexa_number.number;
	if (key_length < DES_MAX_KEY_HEX_CHARACTERS)
		algo_ctx->key <<= ((DES_MAX_KEY_HEX_CHARACTERS - key_length) * 4);
	algo_ctx->key = endianness_swap64(algo_ctx->key);
	return (E_SUCCESS);
}

static void		des_cmd_print_salt_key_iv(t_des_algo_context *algo_ctx)
{
	const int	fd = STDOUT_FILENO;

	ft_putf_fd(fd, "salt=");
	print_uint64_to_hexa(fd, endianness_swap64(algo_ctx->salt));
	ft_putf_fd(fd, "\nkey=");
	print_uint64_to_hexa(fd, endianness_swap64(algo_ctx->key));
	ft_putchar_fd('\n', fd);
}

static t_error	des_generate_key_iv(t_context *ctx, t_des_algo_context *algo_ctx)
{
	const bool	has_not_key_arg = ctx->algo_ctx.des.key == NULL;
	t_error		err;

	if (has_not_key_arg)
	{
		if ((err = des_cmd_set_password(ctx, algo_ctx)) != E_SUCCESS)
			return (err);
		if ((err = des_cmd_set_salt(ctx, algo_ctx)) != E_SUCCESS)
			return (err);
	}
	if ((err = des_cmd_set_key(ctx, algo_ctx)) != E_SUCCESS)
		return (err);
	return (E_SUCCESS);
}

static void		des_cmd(t_context *ctx)
{
	t_des_algo_context	algo_ctx;
	t_error				key_iv_err;

	key_iv_err = des_generate_key_iv(ctx, &algo_ctx);
	if (key_iv_err == E_EMPTY_INPUT)
		ft_putf_fd(STDERR_FILENO, "bad password read\n");
	else if (key_iv_err == E_DES_SALT_INVALID_HEX)
		ft_putf_fd(STDERR_FILENO, "invalid hex salt value\n");
	else if (key_iv_err == E_DES_KEY_INVALID_HEX)
		ft_putf_fd(STDERR_FILENO, "invalid hex key value\n");

	if (ctx->algo_ctx.des.print_key_iv == true)
		des_cmd_print_salt_key_iv(&algo_ctx);
	if (ctx->algo_ctx.des.is_encrypting)
		des_encrypt_cmd(ctx, algo_ctx);
	else
		;
}

void		bind_des_args(t_context *ctx)
{
	const size_t	default_iter = 10000;

	ctx->algo_ctx.des.is_encrypting = true;
	ctx->algo_ctx.des.iter = default_iter;
	ctx->args[0].value = &ctx->algo_ctx.des.base64_mode;
	ctx->args[1].exec_after = activate_decrypt_mode;
	ctx->args[2].exec_after = activate_encrypt_mode;
	ctx->args[3].value = &ctx->algo_ctx.des.input_file;
	ctx->args[4].value = &ctx->algo_ctx.des.key;
	ctx->args[5].value = &ctx->algo_ctx.des.output_file;
	ctx->args[6].value = &ctx->algo_ctx.des.password;
	ctx->args[7].value = &ctx->algo_ctx.des.salt;
	ctx->args[8].value = &ctx->algo_ctx.des.iv;
	ctx->args[9].value = &ctx->algo_ctx.des.print_key_iv;
	ctx->args[10].value = &ctx->algo_ctx.des.iter;
	ctx->cmd = des_cmd;
}

void		des_log_command_usage(t_context *ctx)
{
	(void)ctx;
	ft_putf_fd(STDERR_FILENO
		, "usage: ft_ssl des [-ade] [-print-key-iv] [-i in_file] [-o out_file] [-k key] [-p password] [-s salt] [-v iv] [-iter count]\n");
}
