/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:23:52 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/10 12:10:05 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "args.h"

int	main(int argc, char **argv)
{
	t_algo		algo;
	t_context	ctx;

	if (argc == 1)
	{
		// show ft_ssl usage
		return 1;
	}

	algo = algo_name_to_algo(argv[1]);
	if (algo == ALGO_INVALID)
	{
		// Invalid algorithm
		return 1;
	}

	ctx = create_cmd(algo);

	ctx.cmd(&ctx);
}
