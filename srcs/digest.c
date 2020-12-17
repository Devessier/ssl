/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:05:37 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/17 13:06:28 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

t_arg	g_digest_arguments[] = {
	{
		.type = ARG_BOOLEAN,
		.name = "p",
		.description = "echo STDIN to STDOUT and append the checksum to STDOUT"
	},
	{
		.type = ARG_BOOLEAN,
		.name = "q",
		.description = "quiet mode"
	},
	{
		.type = ARG_BOOLEAN,
		.name = "r",
		.description = "reverse the format of the output"
	},
	{
		.type = ARG_STRING,
		.name = "s",
		.description = "print the sum of the given string"
	},
	{
		.type = ARG_END
	}
};
