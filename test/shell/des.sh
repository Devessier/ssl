#!/usr/bin/env bash

testDesInvalidArgument() {
	command="./ft_ssl des -invalid_argument"
	read -d '' usage << EOF
ft_ssl: des: illegal option -- invalid_argument$
usage: ft_ssl des [-ade] [-print-key-iv] [-i in_file] [-o out_file] [-k key] [-p password] [-s salt] [-v iv] [-iter count]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testDesComputesCorrectKeyFromGivenSalt() {
	salt='F3A662D59028A7FF'
	password='Devessier'

	result=$(./ft_ssl des -e -s "${salt}" -print-key-iv -p "${password}" | cat -e)
	read -d '' expected_key << EOF
salt=F3A662D59028A7FF$
key=F15006A3ECAD2F0E$
EOF

	assertEquals "${expected_key}" "${result}"
}

testDesAddsPaddingToSalt() {
	salt='FF'
	password='Devessier'

	result=$(./ft_ssl des -e -s "${salt}" -print-key-iv -p "${password}" 2>&1 | cat -e)
	read -d '' expected_key << EOF
hex string is too short, padding with zero bytes to length$
salt=FF00000000000000$
key=17C58006A8EB2C70$
EOF

	assertEquals "${expected_key}" "${result}"
}

testDesAddsPaddingToCutKey() {
	key='FF'
	password='Devessier'

	result=$(./ft_ssl des -e -k "${key}" -print-key-iv -p "${password}" 2>&1 | cat -e | grep "^[^salt]")
	read -d '' expected_key << EOF
hex string is too short, padding with zero bytes to length$
key=FF00000000000000$
EOF

	assertEquals "${expected_key}" "${result}"
}

testDesTruncatesTooLongSalt() {
	salt='75a60cc481a13abffffffff'
	password='Devessier'

	result=$(./ft_ssl des -e -s "${salt}" -print-key-iv -p "${password}" 2>&1 | cat -e)
	read -d '' expected_key << EOF
hex string is too long, ignoring excess$
salt=75A60CC481A13ABF$
key=4C8CF489EDE7C860$
EOF

	assertEquals "${expected_key}" "${result}"
}

testDesTruncatesTooLongKey() {
	key='75a60cc481a13abffffffff'
	password='Devessier'

	result=$(./ft_ssl des -e -k "${key}" -print-key-iv -p "${password}" 2>&1 | cat -e | grep "^[^salt]")
	read -d '' expected_key << EOF
hex string is too long, ignoring excess$
key=75A60CC481A13ABF$
EOF

	assertEquals "${expected_key}" "${result}"
}

testDesHandlesExactly16DigitsKey() {
	key='75a60cc481a13abf'
	password='Devessier'

	result=$(./ft_ssl des -e -k "${key}" -print-key-iv -p "${password}" 2>&1 | cat -e | grep "^[^salt]")
	read -d '' expected_key << EOF
key=75A60CC481A13ABF$
EOF

	assertEquals "${expected_key}" "${result}"
}

testDesEncryptsMakefileInBinary() {
	key='75a60cc481a13abf'
	password='Devessier'

	TMP_DIR=$(mktemp -d)
	INPUT_FILE=./Makefile
	ENCRYPTED_FILE_SNAPSHOT=./test/shell/snapshots/des/encrypted-makefile.enc
	ENCRYPTION_RESULT_FILE=$TMP_DIR/encryption-result.enc

	./ft_ssl des -e -k $key -p $password < $INPUT_FILE > $ENCRYPTION_RESULT_FILE

	diff $ENCRYPTED_FILE_SNAPSHOT $ENCRYPTION_RESULT_FILE

	assertTrue $?

	rm -rf $TMP_DIR
}

. ./vendor/shunit2/shunit2
