/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reader_read.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <baptiste@devessier.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 01:50:59 by bdevessi          #+#    #+#             */
/*   Updated: 2020/12/11 02:58:23 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "catch.hpp"
extern "C" {
	#include "reader.h"
}

TEST_CASE( "Creates a reader reading from a small buffer, reads 3 bytes and ensures the correct part has been copied" ) {
	const char			buff[] = "salut mon gars !";
	const t_reader		reader = create_reader_buffer((char *)buff, strlen(buff));
	char				dest[BUFF_SIZE] = { 0 };

	size_t copied = reader_read((t_reader *)&reader, dest, 3);

	REQUIRE( copied == 3 );
	REQUIRE( strncmp(buff, dest, 3) == 0 );
}

TEST_CASE( "Creates a reader reading from a buffer larger than BUFF_SIZE, reads 3 bytes and ensures the correct part has been copied" ) {
	const char			buff[] = "salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !";
	const t_reader		reader = create_reader_buffer((char *)buff, strlen(buff));
	char				dest[BUFF_SIZE] = { 0 };

	size_t copied = reader_read((t_reader *)&reader, dest, 4090);
	REQUIRE( copied == 4090 );

	copied = reader_read((t_reader *)&reader, dest, BUFF_SIZE);
	REQUIRE( copied == BUFF_SIZE );

	REQUIRE( strncmp("gars !salut mon gars !", dest, 22) == 0 );
}

TEST_CASE( "Creates a reader reading from a buffer larger than BUFF_SIZE, reads it totally and returns 0 when no more data can be read" ) {
	const char			buff[] = "salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !salut mon gars !";
	const t_reader		reader = create_reader_buffer((char *)buff, strlen(buff));
	char				dest[BUFF_SIZE] = { 0 };

	size_t copied = reader_read((t_reader *)&reader, dest, 4090);
	REQUIRE( copied == 4090 );

	copied = reader_read((t_reader *)&reader, dest, BUFF_SIZE);
	REQUIRE( copied == BUFF_SIZE );

	copied = reader_read((t_reader *)&reader, dest, BUFF_SIZE);
	REQUIRE( copied == 6 );

	copied = reader_read((t_reader *)&reader, dest, BUFF_SIZE);
	REQUIRE( copied == 0 );
}