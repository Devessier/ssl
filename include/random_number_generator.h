/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_number_generator.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:44:39 by bdevessi          #+#    #+#             */
/*   Updated: 2021/03/23 10:50:23 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_NUMBER_GENERATOR_H
# define RANDOM_NUMBER_GENERATOR_H
# include <unistd.h>

ssize_t		get_random_buffer(char *dest, size_t length);

#endif
