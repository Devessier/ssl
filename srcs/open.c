/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:49:33 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/16 11:38:46 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "ssl.h"

int		open_file(t_context *ctx, char *file)
{
	const int	fd = open(file, O_RDONLY);
	char		*err;

	if (fd != -1 && read(fd, NULL, 0) != -1)
		return (fd);
	err = strerror(errno);
	ft_putf_fd(STDERR_FILENO
		, "ft_ssl: %s: %s: %s\n", ctx->algo_name, file, err);
	return (-1);
}
