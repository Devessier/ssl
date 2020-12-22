/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:23:52 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/17 20:15:03 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "usage.h"
#include "args.h"
#include "ssl.h"

int	main(int argc, char **argv)
{
	const char	*command_name = *(++argv);
	t_algo		algo;
	t_context	ctx;
	ssize_t		parsed_args;

	if (--argc == 0)
	{
		print_usage();
		return (1);
	}
	algo = algo_name_to_algo(command_name);
	if (algo == ALGO_INVALID)
	{
		print_unavailable_command_usage(command_name);
		return (1);
	}
	init_cmd(&ctx, algo);
	if ((parsed_args = parse_args(&ctx, ++argc, ++argv)) == -1)
		return (1);
	ctx.cmd(&ctx);
	return (0);
}
