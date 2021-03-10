#!/usr/bin/env bash

testMD5InvalidArgument() {
	command="./ft_ssl md5 -invalid_argument"
	read -d '' usage << EOF
ft_ssl: md5: illegal option -- invalid_argument$
usage: ft_ssl md5 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testMD5InvalidDoubleDash() {
	command="./ft_ssl md5 --a"
	read -d '' usage << EOF
ft_ssl: md5: illegal option -- -a$
usage: ft_ssl md5 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testMD5BasicStringHashing() {
	string_to_hash='1'

	hash_result=$(./ft_ssl md5 -s "${string_to_hash}")
	official_result='MD5 ("1") = c4ca4238a0b923820dcc509a6f75849b'

	assertEquals "${official_result}" "${hash_result}"
}

testMD5BasicStringHashingInQuietMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl md5 -q -s "${string_to_hash}")
	official_result='c4ca4238a0b923820dcc509a6f75849b'

	assertEquals "${official_result}" "${hash_result}"
}

testMD5BasicStringHashingInReverseMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl md5 -r -s "${string_to_hash}")
	official_result='c4ca4238a0b923820dcc509a6f75849b "1"'

	assertEquals "${official_result}" "${hash_result}"
}

testMD5BasicStringHashingInReverseAndQuietModes() {
	string_to_hash='1'

	hash_result=$(./ft_ssl md5 -r -q -s "${string_to_hash}")
	official_result='c4ca4238a0b923820dcc509a6f75849b'

	assertEquals "${official_result}" "${hash_result}"
}

testMD5MediumStringHashing() {
	string_to_hash='Salut à vous tous ! Ceci est un super projet ssl !'

	hash_result=$(./ft_ssl md5 -s "${string_to_hash}")
	official_result='MD5 ("Salut à vous tous ! Ceci est un super projet ssl !") = f80d1cc01fec46058aef395f9cbd8cae'

	assertEquals "${official_result}" "${hash_result}"
}

testMD5ReadsBigFileFromStdin() {
	TMP_DIR=$(mktemp -d)
	IN_FILE=$TMP_DIR/pdf.pdf
	HASHING_RESULT_FILE=$TMP_DIR/hashing_result.txt
	OFFICIAL_RESULT_FILE=$TMP_DIR/official_result.txt

	curl https://cdn.intra.42.fr/pdf/pdf/19603/en.subject.pdf 2> /dev/null > $IN_FILE

	cat $TMP_DIR/pdf.pdf | ./ft_ssl md5 -p | cat -e > $HASHING_RESULT_FILE
	cat << EOF > $OFFICIAL_RESULT_FILE
$(cat -e $TMP_DIR/pdf.pdf)
91f1130b7a7665026955893b73f6b02f$
EOF

	cmp --silent $HASHING_RESULT_FILE $OFFICIAL_RESULT_FILE

	assertTrue $?

	rm -rf $TMP_DIR
}

# 42 subject tests

testMD5ReadsFromStdinWhenNoArgumentsAreProvided() {
	string_to_hash='pickle rick'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl md5)
	official_result='c5e433c1dbd7ba01e3763a9483e74b04'

	assertEquals "${official_result}" "${hash_result}"
}

testMD5ReadsFromStdinAndPrintInputText() {
	string_to_hash='Do not pity the dead, Harry.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl md5 -p | cat -e)
	read -d '' official_result << EOF
Do not pity the dead, Harry.$
2d95365bc44bf0a298e09a3ab7b34d2f$
EOF

	assertEquals "${official_result}" "${hash_result}"
}

testMD5ReadsFromStdinAndDoesNotTakeIntoAccountQuietAndReverseModes() {
	string_to_hash='Pity the living.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl md5 -q -r)
	official_result='e20c3b973f63482a778f3fd1869b7f25'

	assertEquals "${official_result}" "${hash_result}"
}

testMD5ReadsFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl md5 $TMP_FILE)
	official_result="MD5 ($TMP_FILE) = 53d53ea94217b259c11a5a2d104ec58a"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testMD5ReadsFromFileInReverseMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl md5 -r $TMP_FILE)
	official_result="53d53ea94217b259c11a5a2d104ec58a $TMP_FILE"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testMD5MediumStringHashing2() {
	string_to_hash="pity those that aren't following baerista on spotify."

	hash_result=$(./ft_ssl md5 -s "$string_to_hash")
	official_result="MD5 (\"pity those that aren't following baerista on spotify.\") = a3c990a1964705d9bf0e602f44572f5f"

	assertEquals "${official_result}" "${hash_result}"
}

testMD5ReadsFromStdinThenFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p $TMP_FILE | cat -e)
	read -d '' official_result << EOF
be sure to handle edge cases carefully$
3553dc7dc5963b583c056d1b9fa3349c$
MD5 ($TMP_FILE) = 53d53ea94217b259c11a5a2d104ec58a$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testMD5DoesNotReadStdinIfCanReadFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "some of this will not make sense at first" | ./ft_ssl md5 $TMP_FILE | cat -e)
	official_result="MD5 ($TMP_FILE) = 53d53ea94217b259c11a5a2d104ec58a$"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testMD5ReadsFromStdinEvenIfFileProvidedIfInPrintMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "but eventually you will understand" | ./ft_ssl md5 -p -r $TMP_FILE | cat -e)
	read -d '' official_result << EOF
but eventually you will understand$
dcdd84e0f635694d2a943fa8d3905281$
53d53ea94217b259c11a5a2d104ec58a $TMP_FILE$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testMD5ReadsFromStdinEvenIfFileProvidedIfInPrintModeAndHashesString() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
GL HF let's go$
d1e3cc342b6da09480b27ec57ff243e2$
MD5 ("foo") = acbd18db4cc2f85cedef654fccc4a4d8$
MD5 ($TMP_FILE) = 53d53ea94217b259c11a5a2d104ec58a$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testMD5ConsidersArgumentsAfterFirstFileAsFiles() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" $TMP_FILE -s "bar" 2>&1 | cat -e)
	read -d '' official_result << EOF
one more thing$
a0bd1876c6f011dd50fae52827f445f5$
acbd18db4cc2f85cedef654fccc4a4d8 "foo"$
53d53ea94217b259c11a5a2d104ec58a $TMP_FILE$
ft_ssl: md5: -s: No such file or directory$
ft_ssl: md5: bar: No such file or directory$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testMD5AllParametersWorkProperlyWhenUsedTogether() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
just to be extra clear$
3ba35f1ea0d170cb3b9a752e3360286c$
acbd18db4cc2f85cedef654fccc4a4d8$
53d53ea94217b259c11a5a2d104ec58a$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

. ./vendor/shunit2/shunit2
