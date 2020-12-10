/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:20:13 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/10 15:41:45 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "args.h"
#include "ssl.h"
#include "libft.h"

static void		log_err(t_context *ctx, t_error err, char invalid_option)
{
	const char	*command_name = ctx->algo_name;

	if (err == E_INVALID_ARG_STRING_VALUE)
		ft_putf("%s: option requires an argument -- %c\n"
			, command_name, invalid_option);
	else if (err == E_INVALID_ARG)
		ft_putf("%s: illegal option -- %c\n", command_name, invalid_option);
}

static t_error	get_arg_value(const t_arg *arg, const char *argv[], int *index)
{
	char	*string_arg_value;

	string_arg_value = NULL;
	if (arg->type == ARG_BOOLEAN)
		*(bool *)arg->value = true;
	else if (arg->type == ARG_STRING)
	{
		if ((string_arg_value = (char *)argv[++*(index)]) == NULL)
			return E_INVALID_ARG_STRING_VALUE;

		*(char **)arg->value = string_arg_value;
	}
	else
		return E_INVALID_ARG_TYPE;

	return E_SUCCESS;
}

static t_error	parse_arg(const t_arg args[], const char *argv[], int *index)
{
	const char			*arg_str = argv[*index] + 1;
	int					arg_index;
	t_arg				*arg;

	arg_index = 0;
	arg = (t_arg *)args;
	while (arg->type != ARG_END) {
		arg = (t_arg *)&args[arg_index];

		if (ft_strcmp(arg->name, arg_str) == 0)
			return get_arg_value(arg, argv, index);

		arg_index++;
	}

	return E_INVALID_ARG;
}

ssize_t		parse_args(t_context *ctx, int argc, const char **argv)
{
	int			index;
	char		*arg;
	t_error		err;

	index = 0;
	while (index < argc)
	{
		arg = (char *)argv[index];

		if (arg == NULL || *(arg++) != '-')
			break;
		if (*arg == '-')
		{
			if (*(++arg) == '\0')
				break;

			log_err(ctx, err, *arg);
			return -1;
		}

		if ((err = parse_arg(ctx->args, argv, &index)) != E_SUCCESS)
		{
			log_err(ctx, err, *arg);
			return -1;
		}

		index++;
	}

	return index;
}
