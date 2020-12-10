/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:23:52 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/10 16:58:32 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "usage.h"
#include "args.h"

int	main(int argc, char **argv)
{
	const char	*command_name = argv[1];
	t_algo		algo;
	t_context	ctx;

	if (argc == 1)
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
	ctx = create_cmd(algo);
	ctx.cmd(&ctx);
	return (0);
}
