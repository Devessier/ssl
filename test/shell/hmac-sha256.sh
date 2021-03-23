#!/usr/bin/env bash

testHMACSHA256InvalidArgument() {
	command="./ft_ssl hmac-sha256 -invalid_argument"
	read -d '' usage << EOF
ft_ssl: hmac-sha256: illegal option -- invalid_argument$
usage: ft_ssl hmac-sha256 [-s string] [-k key]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testHMACSHA256NecessitatesKey() {
	command="./ft_ssl hmac-sha256 -s 1"
	read -d '' usage << EOF
ft_ssl: hmac-sha256: invalid empty key$
EOF

	assertEquals 'invalid empty key message' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	# eval "$command 2> /dev/null"
	# assertEquals 'invalid exit status' 1 $?
}

testHMACSHA256RefusesEmptyKey() {
	read -d '' usage << EOF
ft_ssl: hmac-sha256: invalid empty key$
EOF

	assertEquals 'invalid empty key message' "${usage}" "$(./ft_ssl hmac-sha256 -s 1 -k '' 2>&1 > /dev/null | cat -e)"
}

testHMACSHA256BasicStringHashing() {
	string_to_hash='1'
	password='Devessier'

	hash_result=$(./ft_ssl hmac-sha256 -s "${string_to_hash}" -k "${password}")
	official_result='HMAC-SHA256 ("1") = 69bfa19cfa2b0c5282e31b021efd09eea04ecd4afec3557b6b617926b94ef80e'

	assertEquals "${official_result}" "${hash_result}"
}

testHMACSHA256MediumStringHashing() {
	string_to_hash='Salut à vous tous ! Ceci est un super projet ssl !'
	password='Devessier'

	hash_result=$(./ft_ssl hmac-sha256 -s "${string_to_hash}" -k "${password}")
	official_result='HMAC-SHA256 ("Salut à vous tous ! Ceci est un super projet ssl !") = fa93468d13721bcf24cc626cf852d50ce0924c669dc093723f2c7be0029292aa'

	assertEquals "${official_result}" "${hash_result}"
}

testHMACSHA256Handles64bitsKey() {
	string_to_hash='Salut à vous tous ! Ceci est un super projet ssl !'
	password='AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'

	hash_result=$(./ft_ssl hmac-sha256 -s "${string_to_hash}" -k "${password}")
	official_result='HMAC-SHA256 ("Salut à vous tous ! Ceci est un super projet ssl !") = 21db4f2f3817e706ce154b6e5e15a855fac4fdcd2b00d99a413055b9adb0dad2'

	assertEquals "${official_result}" "${hash_result}"
}

testHMACSHA256HashesTooLongKey() {
	string_to_hash='Salut à vous tous ! Ceci est un super projet ssl !'
	password='AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'

	hash_result=$(./ft_ssl hmac-sha256 -s "${string_to_hash}" -k "${password}")
	official_result='HMAC-SHA256 ("Salut à vous tous ! Ceci est un super projet ssl !") = b96eaab38580457fdc6c8c4ad34e8a5c9ea7e2e4594caee014f808767796b9db'

	assertEquals "${official_result}" "${hash_result}"
}

testHMACSHA256HashesBigFile() {
	password='Devessier'

	TMP_DIR=$(mktemp -d)
	IN_FILE=$TMP_DIR/pdf.pdf
	HASHING_RESULT_FILE=$TMP_DIR/hashing_result.txt
	OFFICIAL_RESULT_FILE=$TMP_DIR/official_result.txt
	cat << EOF > $OFFICIAL_RESULT_FILE
2ebdf0a41926cf42ecbcb2f60d792f264ed0b907982e01f8df395b3b65dc12fe$
EOF

	curl https://cdn.intra.42.fr/pdf/pdf/19604/en.subject.pdf 2> /dev/null > $IN_FILE

	cat $IN_FILE | ./ft_ssl hmac-sha256 -k $password | cat -e > $HASHING_RESULT_FILE

	cmp $HASHING_RESULT_FILE $OFFICIAL_RESULT_FILE

	assertTrue $?

	rm -rf $TMP_DIR
}

. ./vendor/shunit2/shunit2
