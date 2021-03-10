#!/usr/bin/env bash

testSHA512224InvalidArgument() {
	command="./ft_ssl sha512224 -invalid_argument"
	read -d '' usage << EOF
ft_ssl: sha512224: illegal option -- invalid_argument$
usage: ft_ssl sha512224 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testSHA512224InvalidDoubleDash() {
	command="./ft_ssl sha512224 --a"
	read -d '' usage << EOF
ft_ssl: sha512224: illegal option -- -a$
usage: ft_ssl sha512224 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testSHA512224BasicStringHashing() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha512224 -s "${string_to_hash}")
	official_result='SHA512224 ("1") = a5d8adf6032b5f333d9cd6696dd0c520b4dca7f0c3238aa8de33e87c'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512224BasicStringHashingInQuietMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha512224 -q -s "${string_to_hash}")
	official_result='a5d8adf6032b5f333d9cd6696dd0c520b4dca7f0c3238aa8de33e87c'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512224BasicStringHashingInReverseMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha512224 -r -s "${string_to_hash}")
	official_result='a5d8adf6032b5f333d9cd6696dd0c520b4dca7f0c3238aa8de33e87c "1"'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512224BasicStringHashingInReverseAndQuietModes() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha512224 -r -q -s "${string_to_hash}")
	official_result='a5d8adf6032b5f333d9cd6696dd0c520b4dca7f0c3238aa8de33e87c'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512224MediumStringHashing() {
	string_to_hash='Salut à vous tous ! Ceci est un super projet ssl !'

	hash_result=$(./ft_ssl sha512224 -s "${string_to_hash}")
	official_result='SHA512224 ("Salut à vous tous ! Ceci est un super projet ssl !") = 2647896d7faf37b03f9892c7e5223697c887262c973ca77f21ea6f7e'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512224ReadsBigFileFromStdin() {
	TMP_DIR=$(mktemp -d)
	IN_FILE=$TMP_DIR/pdf.pdf
	HASHING_RESULT_FILE=$TMP_DIR/hashing_result.txt
	OFFICIAL_RESULT_FILE=$TMP_DIR/official_result.txt

	curl https://cdn.intra.42.fr/pdf/pdf/19603/en.subject.pdf 2> /dev/null > $IN_FILE

	cat $TMP_DIR/pdf.pdf | ./ft_ssl sha512224 -p | cat -e > $HASHING_RESULT_FILE
	cat << EOF > $OFFICIAL_RESULT_FILE
$(cat -e $TMP_DIR/pdf.pdf)
fbcb1d0c9dac63c866563bfa8c4cb8b1af3fdd202fb14bfcdba8feb3$
EOF

	cmp --silent $HASHING_RESULT_FILE $OFFICIAL_RESULT_FILE

	assertTrue $?

	rm -rf $TMP_DIR
}

# 42 subject tests

testSHA512224ReadsFromStdinWhenNoArgumentsAreProvided() {
	string_to_hash='pickle rick'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha512224)
	official_result='1ce9cb1ec8916f97c0e2113ca8d10d5792848220bd42d6390433dd9b'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512224ReadsFromStdinAndPrintInputText() {
	string_to_hash='Do not pity the dead, Harry.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha512224 -p | cat -e)
	read -d '' official_result << EOF
Do not pity the dead, Harry.$
46d86c4d0057a136d739acacad33076a34e9749cd80f0dbe099a2634$
EOF

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512224ReadsFromStdinAndDoesNotTakeIntoAccountQuietAndReverseModes() {
	string_to_hash='Pity the living.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha512224 -q -r)
	official_result='d3bbb0f8ad91c29e6eec8d1c4332bb1c67c08476e196847110bda661'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512224ReadsFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl sha512224 $TMP_FILE)
	official_result="SHA512224 ($TMP_FILE) = 85c5a74f0d4a09d54dce5ef4a8be9f1a7c0455309dca7ff1bcb20e57"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512224ReadsFromFileInReverseMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl sha512224 -r $TMP_FILE)
	official_result="85c5a74f0d4a09d54dce5ef4a8be9f1a7c0455309dca7ff1bcb20e57 $TMP_FILE"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512224MediumStringHashing2() {
	string_to_hash="pity those that aren't following baerista on spotify."

	hash_result=$(./ft_ssl sha512224 -s "$string_to_hash")
	official_result="SHA512224 (\"pity those that aren't following baerista on spotify.\") = 1f8280f9e938e23add3661b8406d8564d71b0db85015b4b11ae2c993"

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512224ReadsFromStdinThenFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "be sure to handle edge cases carefully" | ./ft_ssl sha512224 -p $TMP_FILE | cat -e)
	read -d '' official_result << EOF
be sure to handle edge cases carefully$
d3acf459eda6366e837bfb73026085a8c14342f8210f697e3405b920$
SHA512224 ($TMP_FILE) = 85c5a74f0d4a09d54dce5ef4a8be9f1a7c0455309dca7ff1bcb20e57$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512224DoesNotReadStdinIfCanReadFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "some of this will not make sense at first" | ./ft_ssl sha512224 $TMP_FILE | cat -e)
	official_result="SHA512224 ($TMP_FILE) = 85c5a74f0d4a09d54dce5ef4a8be9f1a7c0455309dca7ff1bcb20e57$"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512224ReadsFromStdinEvenIfFileProvidedIfInPrintMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "but eventually you will understand" | ./ft_ssl sha512224 -p -r $TMP_FILE | cat -e)
	read -d '' official_result << EOF
but eventually you will understand$
9e4a6a9dd6cddb4d05ea125e6fe2d3ca002a0e92835406e141420e9f$
85c5a74f0d4a09d54dce5ef4a8be9f1a7c0455309dca7ff1bcb20e57 $TMP_FILE$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512224ReadsFromStdinEvenIfFileProvidedIfInPrintModeAndHashesString() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "GL HF let's go" | ./ft_ssl sha512224 -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
GL HF let's go$
bbbd59b6228c1cd8a567b7e26b316e4eeba63a3973246da0d25959d8$
SHA512224 ("foo") = d68f258d37d670cfc1ec1001a0394784233f88f056994f9a7e5e99be$
SHA512224 ($TMP_FILE) = 85c5a74f0d4a09d54dce5ef4a8be9f1a7c0455309dca7ff1bcb20e57$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512224ConsidersArgumentsAfterFirstFileAsFiles() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "one more thing" | ./ft_ssl sha512224 -r -p -s "foo" $TMP_FILE -s "bar" 2>&1 | cat -e)
	read -d '' official_result << EOF
one more thing$
77bcd4e9adb9d2b110268bc8a580d5cd4e35fdfbe7c0161990dc296e$
d68f258d37d670cfc1ec1001a0394784233f88f056994f9a7e5e99be "foo"$
85c5a74f0d4a09d54dce5ef4a8be9f1a7c0455309dca7ff1bcb20e57 $TMP_FILE$
ft_ssl: sha512224: -s: No such file or directory$
ft_ssl: sha512224: bar: No such file or directory$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512224AllParametersWorkProperlyWhenUsedTogether() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "just to be extra clear" | ./ft_ssl sha512224 -r -q -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
just to be extra clear$
d0e7900d033c7e18c568ecbaad8098d9d1dbc7f72ac4898c0d0e71d8$
d68f258d37d670cfc1ec1001a0394784233f88f056994f9a7e5e99be$
85c5a74f0d4a09d54dce5ef4a8be9f1a7c0455309dca7ff1bcb20e57$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

. ./vendor/shunit2/shunit2
