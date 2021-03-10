#!/usr/bin/env bash

testSHA256InvalidArgument() {
	command="./ft_ssl sha256 -invalid_argument"
	read -d '' usage << EOF
ft_ssl: sha256: illegal option -- invalid_argument$
usage: ft_ssl sha256 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testSHA256InvalidDoubleDash() {
	command="./ft_ssl sha256 --a"
	read -d '' usage << EOF
ft_ssl: sha256: illegal option -- -a$
usage: ft_ssl sha256 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testSHA256BasicStringHashing() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha256 -s "${string_to_hash}")
	official_result='SHA256 ("1") = 6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA256BasicStringHashingInQuietMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha256 -q -s "${string_to_hash}")
	official_result='6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA256BasicStringHashingInReverseMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha256 -r -s "${string_to_hash}")
	official_result='6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b "1"'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA256BasicStringHashingInReverseAndQuietModes() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha256 -r -q -s "${string_to_hash}")
	official_result='6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA256MediumStringHashing() {
	string_to_hash='Salut à vous tous ! Ceci est un super projet ssl !'

	hash_result=$(./ft_ssl sha256 -s "${string_to_hash}")
	official_result='SHA256 ("Salut à vous tous ! Ceci est un super projet ssl !") = 7cccc4601f75df9339c44f225d437b5284d7bcb92a987bbba509154432a0ec37'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA256ReadsBigFileFromStdin() {
	TMP_DIR=$(mktemp -d)
	IN_FILE=$TMP_DIR/pdf.pdf
	HASHING_RESULT_FILE=$TMP_DIR/hashing_result.txt
	OFFICIAL_RESULT_FILE=$TMP_DIR/official_result.txt

	curl https://cdn.intra.42.fr/pdf/pdf/19603/en.subject.pdf 2> /dev/null > $IN_FILE

	cat $TMP_DIR/pdf.pdf | ./ft_ssl sha256 -p | cat -e > $HASHING_RESULT_FILE
	cat << EOF > $OFFICIAL_RESULT_FILE
$(cat -e $TMP_DIR/pdf.pdf)
5c446dbe5dd170b2bdf93ff0c68539bcf253eca2b7471b00ebe2466c3801d263$
EOF

	cmp --silent $HASHING_RESULT_FILE $OFFICIAL_RESULT_FILE

	assertTrue $?

	rm -rf $TMP_DIR
}

# 42 subject tests

testSHA256ReadsFromStdinWhenNoArgumentsAreProvided() {
	string_to_hash='pickle rick'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha256)
	official_result='a9c55180c67a4bc62753d836843f46fa47af28874600cdc637de921d711937ed'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA256ReadsFromStdinAndPrintInputText() {
	string_to_hash='Do not pity the dead, Harry.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha256 -p | cat -e)
	read -d '' official_result << EOF
Do not pity the dead, Harry.$
7197000d32ca5a13cf923ba196286a72daa06e9f168c4dd5753f917568ea373f$
EOF

	assertEquals "${official_result}" "${hash_result}"
}

testSHA256ReadsFromStdinAndDoesNotTakeIntoAccountQuietAndReverseModes() {
	string_to_hash='Pity the living.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha256 -q -r)
	official_result='40133cfe543247c1cae0ffb0003c1179ce9fb0046bee19f9fca167380643ba45'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA256ReadsFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl sha256 $TMP_FILE)
	official_result="SHA256 ($TMP_FILE) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA256ReadsFromFileInReverseMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl sha256 -r $TMP_FILE)
	official_result="f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 $TMP_FILE"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA256MediumStringHashing2() {
	string_to_hash="pity those that aren't following baerista on spotify."

	hash_result=$(./ft_ssl sha256 -s "$string_to_hash")
	official_result="SHA256 (\"pity those that aren't following baerista on spotify.\") = 7838c25c9debff86c584245d67b429186d3850c89da31c0b49b8d0380a3e14bf"

	assertEquals "${official_result}" "${hash_result}"
}

testSHA256ReadsFromStdinThenFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "be sure to handle edge cases carefully" | ./ft_ssl sha256 -p $TMP_FILE | cat -e)
	read -d '' official_result << EOF
be sure to handle edge cases carefully$
ef9241f878a1da676104a81239792a2817bc0390a427ca20bad1a59030fd20c2$
SHA256 ($TMP_FILE) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA256DoesNotReadStdinIfCanReadFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "some of this will not make sense at first" | ./ft_ssl sha256 $TMP_FILE | cat -e)
	official_result="SHA256 ($TMP_FILE) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705$"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA256ReadsFromStdinEvenIfFileProvidedIfInPrintMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "but eventually you will understand" | ./ft_ssl sha256 -p -r $TMP_FILE | cat -e)
	read -d '' official_result << EOF
but eventually you will understand$
43da940057fd3b7453ee91b3a056a41343e6f0bce315570ed27e06c993a539da$
f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 $TMP_FILE$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA256ReadsFromStdinEvenIfFileProvidedIfInPrintModeAndHashesString() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "GL HF let's go" | ./ft_ssl sha256 -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
GL HF let's go$
f33201f3d70c9dccccec022e2ff0df2006e016f153f600407917d14955fbec22$
SHA256 ("foo") = 2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae$
SHA256 ($TMP_FILE) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA256ConsidersArgumentsAfterFirstFileAsFiles() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "one more thing" | ./ft_ssl sha256 -r -p -s "foo" $TMP_FILE -s "bar" 2>&1 | cat -e)
	read -d '' official_result << EOF
one more thing$
720bbf63077e0bea3b70c87954123daa6fcf32f973f4d646622bd016b140ec75$
2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae "foo"$
f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 $TMP_FILE$
ft_ssl: sha256: -s: No such file or directory$
ft_ssl: sha256: bar: No such file or directory$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA256AllParametersWorkProperlyWhenUsedTogether() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "just to be extra clear" | ./ft_ssl sha256 -r -q -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
just to be extra clear$
41c3da28172faf72bb777d6a428b6d801427d02513c56cd9e3672f44383f8eee$
2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae$
f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

. ./vendor/shunit2/shunit2
