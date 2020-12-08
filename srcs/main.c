/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:23:52 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/08 18:13:54 by bdevessi         ###   ########.fr       */
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
		"-p",
		0
	};
	bool				p_flag = false;
	const t_arg			args[] = {
		{
			.type = ARG_BOOLEAN,
			.name = 'p',
			.value = &p_flag,
			.description = (char *)"prints to stdout",
		}
	};

	parse_args(args, argc, argv);

	printf("ok: %i\n", *(bool *)(args[0].value) == true);
}
