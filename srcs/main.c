/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:23:52 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/12 16:41:51 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "ssl.h"
#include "repl.h"

int	main(int argc, char **argv)
{
	argc--;
	argv++;
	if (argc == 0)
		return (repl());
	return (ssl_exec(argc, argv));
}
