/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:23:52 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/09 01:14:01 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "args.h"

int	main(void)
{
	const int			argc = 1;
	const char			*argv[] = {
		"-a",
		0
	};
	char				*flag1 = NULL;
	char				*flag2 = NULL;
	char				*flag3 = NULL;
	bool				flag4 = false;
	bool				flag5 = false;
	const t_arg			args[] = {
		{
			.type = ARG_BOOLEAN,
			.name = 'w',
			.value = &flag4,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_STRING,
			.name = 'a',
			.value = &flag1,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_STRING,
			.name = 'b',
			.value = &flag2,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_BOOLEAN,
			.name = 'x',
			.value = &flag5,
			.description = (char *)"prints to stdout",
		},
		{
			.type = ARG_STRING,
			.name = 'c',
			.value = &flag3,
			.description = (char *)"prints to stdout",
		},
		{
			ARG_END,
			0,
			0,
			0
		}
	};
	t_context		ctx = {
		.algo = ALGO_MD5,
		.args = (t_arg *)args
	};

	parse_args(&ctx, argc, argv);
}
