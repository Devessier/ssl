/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:35:08 by bdevessi          #+#    #+#             */
/*   Updated: 2021/01/12 23:30:11 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USAGE_H
# define USAGE_H
# include "ssl.h"

typedef struct	s_algo_type_desc
{
	t_algo_type	type;
	char		*name;
}				t_algo_type_desc;

void			print_usage(void);
void			print_available_commands(void);
void			print_unavailable_command_usage(const char *invalid_command);

#endif
