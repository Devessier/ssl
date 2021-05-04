/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_number_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:44:47 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/24 23:14:35 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

ssize_t		get_random_buffer(char *dest, size_t length)
{
	const int	fd = open("/dev/random", O_RDONLY);
	ssize_t		read_bytes_count;

	if (fd == -1)
		return (-1);
	if ((read_bytes_count = read(fd, dest, length)) == -1)
		return (-1);
	close(fd);
	return (read_bytes_count);
}
