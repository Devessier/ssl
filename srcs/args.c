/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:20:13 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/08 18:53:40 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "args.h"

t_get_arg_value_r		get_arg_value(const t_arg *arg, const char *argv[], int *index) {
	char	*string_arg_value;

	string_arg_value = NULL;
	if (arg->type == ARG_BOOLEAN)
	{
		*(bool *)arg->value = true;
	}
	else if (arg->type == ARG_STRING)
	{
		if ((string_arg_value = (char *)argv[++*(index)]) == NULL)
		{
			// String value required but not present
			return E_INVALID_STRING_VALUE;
		}
		*(char **)arg->value = string_arg_value;
	}
	else
		return E_INVALID_ARG_TYPE;

	return OK;
}

void	parse_short_arg(const t_arg args[], const char *argv[], int *index) {
	const char	short_arg = argv[*index][1];
	int			arg_index;
	t_arg		*arg;

	arg_index = 0;
	arg = (t_arg *)args;
	while (arg->type != ARG_END) {
		arg = (t_arg *)&args[arg_index];

		if (arg->name == short_arg) {
			get_arg_value(arg, argv, index);

			// Found a matching argument
			return;
		}

		arg_index++;
	}

	// Found no matching argument
}

size_t	parse_args(const t_arg args[], int argc, const char **argv) {
	int		index;
	char	*arg;

	index = 0;
	while (index < argc) {
		arg = (char *)argv[index];

		if (arg == NULL || arg[0] != '-') {
			// Exit now
			return 0;
		}
		if (arg[1] == '-') {
			if (arg[2] == '\0') {
				// Double dash, we stop
				return 0;
			}
			// Illegal argument arg[2]
			return -1;
		}

		parse_short_arg(args, argv, &index);

		index++;
	}

	return 0;
}
