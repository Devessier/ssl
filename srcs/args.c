/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:20:13 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/10 16:02:31 by bdevessi         ###   ########.fr       */
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
			return (E_INVALID_ARG_STRING_VALUE);
		*(char **)arg->value = string_arg_value;
	}
	else
		return (E_INVALID_ARG_TYPE);
	return (E_SUCCESS);
}

static t_error	parse_arg(t_context *ctx, const char *argv[], int *index)
{
	const char			*arg_str = argv[*index] + 1;
	t_arg				*arg;
	t_error				get_arg_value_r;

	arg = ctx->args;
	while (arg->type != ARG_END)
	{
		if (ft_strcmp(arg->name, arg_str) == 0)
		{
			get_arg_value_r = get_arg_value(arg, argv, index);
			if (arg->exec_after != NULL)
				arg->exec_after(ctx);
			return (get_arg_value_r);
		}
		arg++;
	}
	return (E_INVALID_ARG);
}

ssize_t			parse_args(t_context *ctx, int argc, const char **argv)
{
	int			index;
	char		*arg;
	t_error		err;

	index = 0;
	while (index < argc)
	{
		arg = (char *)argv[index];
		if (arg == NULL || *(arg++) != '-')
			break ;
		if (*arg == '-')
		{
			if (*(++arg) == '\0')
				break ;
			log_err(ctx, err, *arg);
			return (-1);
		}
		if ((err = parse_arg(ctx, argv, &index)) != E_SUCCESS)
		{
			log_err(ctx, err, *arg);
			return (-1);
		}
		index++;
	}
	return (index);
}
