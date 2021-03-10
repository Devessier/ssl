#!/usr/bin/env bash

testSHA512256InvalidArgument() {
	command="./ft_ssl sha512256 -invalid_argument"
	read -d '' usage << EOF
ft_ssl: sha512256: illegal option -- invalid_argument$
usage: ft_ssl sha512256 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testSHA512256InvalidDoubleDash() {
	command="./ft_ssl sha512256 --a"
	read -d '' usage << EOF
ft_ssl: sha512256: illegal option -- -a$
usage: ft_ssl sha512256 [-p] [-q] [-r] [-s string] [files ...]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testSHA512256BasicStringHashing() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha512256 -s "${string_to_hash}")
	official_result='SHA512256 ("1") = 18d27566bd1ac66b2332d8c54ad43f7bb22079c906d05f491f3f07a28d5c6990'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512256BasicStringHashingInQuietMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha512256 -q -s "${string_to_hash}")
	official_result='18d27566bd1ac66b2332d8c54ad43f7bb22079c906d05f491f3f07a28d5c6990'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512256BasicStringHashingInReverseMode() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha512256 -r -s "${string_to_hash}")
	official_result='18d27566bd1ac66b2332d8c54ad43f7bb22079c906d05f491f3f07a28d5c6990 "1"'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512256BasicStringHashingInReverseAndQuietModes() {
	string_to_hash='1'

	hash_result=$(./ft_ssl sha512256 -r -q -s "${string_to_hash}")
	official_result='18d27566bd1ac66b2332d8c54ad43f7bb22079c906d05f491f3f07a28d5c6990'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512256MediumStringHashing() {
	string_to_hash='Salut à vous tous ! Ceci est un super projet ssl !'

	hash_result=$(./ft_ssl sha512256 -s "${string_to_hash}")
	official_result='SHA512256 ("Salut à vous tous ! Ceci est un super projet ssl !") = 5ca974f4714390347d628b95b9ad9e529601ff65f7171bb2374eefa5955d5058'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512256ReadsBigFileFromStdin() {
	TMP_DIR=$(mktemp -d)
	IN_FILE=$TMP_DIR/pdf.pdf
	HASHING_RESULT_FILE=$TMP_DIR/hashing_result.txt
	OFFICIAL_RESULT_FILE=$TMP_DIR/official_result.txt

	curl https://cdn.intra.42.fr/pdf/pdf/19603/en.subject.pdf 2> /dev/null > $IN_FILE

	cat $TMP_DIR/pdf.pdf | ./ft_ssl sha512256 -p | cat -e > $HASHING_RESULT_FILE
	cat << EOF > $OFFICIAL_RESULT_FILE
$(cat -e $TMP_DIR/pdf.pdf)
1bb7c28dc895969178eac2c548433c9ef2d22e48efb90d0ba9dd5170fba21b79$
EOF

	cmp --silent $HASHING_RESULT_FILE $OFFICIAL_RESULT_FILE

	assertTrue $?

	rm -rf $TMP_DIR
}

# 42 subject tests

testSHA512256ReadsFromStdinWhenNoArgumentsAreProvided() {
	string_to_hash='pickle rick'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha512256)
	official_result='1edf0b58cbed6a838b2634fe6c255e67e7a155b8dd0a442008c28d9c4609f40a'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512256ReadsFromStdinAndPrintInputText() {
	string_to_hash='Do not pity the dead, Harry.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha512256 -p | cat -e)
	read -d '' official_result << EOF
Do not pity the dead, Harry.$
319202d37a2bf4784cab2bb1919be3bde373fc8ee8f4769d31c90a964fbee86f$
EOF

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512256ReadsFromStdinAndDoesNotTakeIntoAccountQuietAndReverseModes() {
	string_to_hash='Pity the living.'

	hash_result=$(echo "${string_to_hash}" | ./ft_ssl sha512256 -q -r)
	official_result='75c725b83581ecfb05cfa49b1acb4ec260e46f2a44e65c8d3072c83ffa108f8d'

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512256ReadsFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl sha512256 $TMP_FILE)
	official_result="SHA512256 ($TMP_FILE) = f446efe045416d2dd48208c80627088cb3ee33140f9baf75fbd8a399323fe587"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512256ReadsFromFileInReverseMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(./ft_ssl sha512256 -r $TMP_FILE)
	official_result="f446efe045416d2dd48208c80627088cb3ee33140f9baf75fbd8a399323fe587 $TMP_FILE"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512256MediumStringHashing2() {
	string_to_hash="pity those that aren't following baerista on spotify."

	hash_result=$(./ft_ssl sha512256 -s "$string_to_hash")
	official_result="SHA512256 (\"pity those that aren't following baerista on spotify.\") = 2c732ef74d4176317bc57e316ce68e8023bfafaf2b37520bfb8e0b67cdb32920"

	assertEquals "${official_result}" "${hash_result}"
}

testSHA512256ReadsFromStdinThenFromFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "be sure to handle edge cases carefully" | ./ft_ssl sha512256 -p $TMP_FILE | cat -e)
	read -d '' official_result << EOF
be sure to handle edge cases carefully$
c6e85e21a0ee6e52c1c73a32d5abce7ff9e2dd02e31686abeccdd22c921c4ad9$
SHA512256 ($TMP_FILE) = f446efe045416d2dd48208c80627088cb3ee33140f9baf75fbd8a399323fe587$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512256DoesNotReadStdinIfCanReadFile() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "some of this will not make sense at first" | ./ft_ssl sha512256 $TMP_FILE | cat -e)
	official_result="SHA512256 ($TMP_FILE) = f446efe045416d2dd48208c80627088cb3ee33140f9baf75fbd8a399323fe587$"

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512256ReadsFromStdinEvenIfFileProvidedIfInPrintMode() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "but eventually you will understand" | ./ft_ssl sha512256 -p -r $TMP_FILE | cat -e)
	read -d '' official_result << EOF
but eventually you will understand$
85dbd643894d470e9cf28bb5c148851d0827fdf5ee2efc56e14dad7554665963$
f446efe045416d2dd48208c80627088cb3ee33140f9baf75fbd8a399323fe587 $TMP_FILE$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512256ReadsFromStdinEvenIfFileProvidedIfInPrintModeAndHashesString() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "GL HF let's go" | ./ft_ssl sha512256 -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
GL HF let's go$
e2e03dd2f6f520180ed8d8017edebe1e249e67ea963522de522242b747c8b63e$
SHA512256 ("foo") = d58042e6aa5a335e03ad576c6a9e43b41591bfd2077f72dec9df7930e492055d$
SHA512256 ($TMP_FILE) = f446efe045416d2dd48208c80627088cb3ee33140f9baf75fbd8a399323fe587$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512256ConsidersArgumentsAfterFirstFileAsFiles() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "one more thing" | ./ft_ssl sha512256 -r -p -s "foo" $TMP_FILE -s "bar" 2>&1 | cat -e)
	read -d '' official_result << EOF
one more thing$
6adebc53fa10e5c250abdd528e8e77a2ce9394e13bef71b6c7682e9554306e97$
d58042e6aa5a335e03ad576c6a9e43b41591bfd2077f72dec9df7930e492055d "foo"$
f446efe045416d2dd48208c80627088cb3ee33140f9baf75fbd8a399323fe587 $TMP_FILE$
ft_ssl: sha512256: -s: No such file or directory$
ft_ssl: sha512256: bar: No such file or directory$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

testSHA512256AllParametersWorkProperlyWhenUsedTogether() {
	TMP_FILE=$(mktemp)
	echo "And above all," > $TMP_FILE

	hash_result=$(echo "just to be extra clear" | ./ft_ssl sha512256 -r -q -p -s "foo" $TMP_FILE | cat -e)
	read -d '' official_result << EOF
just to be extra clear$
8a4e99023ad3faff3a59e09bb49f7eaaee98b3196e67f6765fa41b0ee1fb65b9$
d58042e6aa5a335e03ad576c6a9e43b41591bfd2077f72dec9df7930e492055d$
f446efe045416d2dd48208c80627088cb3ee33140f9baf75fbd8a399323fe587$
EOF

	assertEquals "${official_result}" "${hash_result}"

	rm $TMP_FILE
}

. ./vendor/shunit2/shunit2
