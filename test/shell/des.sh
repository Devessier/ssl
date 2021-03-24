#!/usr/bin/env bash

testDesInvalidArgument() {
	command="./ft_ssl des -invalid_argument"
	read -d '' usage << EOF
ft_ssl: des: illegal option -- invalid_argument$
usage: ft_ssl des [-ade] [-print-key-iv] [-i in_file] [-o out_file] [-k key] [-p password] [-s salt] [-v iv]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testDesComputesCorrectKeyFromGivenSalt() {
	salt='F3A662D59028A7FF'

	result=$(./ft_ssl des -e -s "${salt}" -print-key-iv | cat -e)
	read -d '' expected_key << EOF
salt=F3A662D59028A7FF$
key=5DFC6F5FAC101670$
EOF

	assertEquals "${expected_key}" "${result}"
}

testDesAddsPaddingToSalt() {
	salt='FF'

	result=$(./ft_ssl des -e -s "${salt}" -print-key-iv 2>&1 | cat -e)
	read -d '' expected_key << EOF
hex string is too short, padding with zero bytes to length$
salt=FF00000000000000$
key=CC9040549FD7AB76$
EOF

	assertEquals "${expected_key}" "${result}"
}

testDesAddsPaddingToCutKey() {
	key='FF'

	result=$(./ft_ssl des -e -k "${key}" -print-key-iv 2>&1 | cat -e | grep "^[^salt]")
	read -d '' expected_key << EOF
hex string is too short, padding with zero bytes to length$
key=FF00000000000000$
EOF

	assertEquals "${expected_key}" "${result}"
}

. ./vendor/shunit2/shunit2
