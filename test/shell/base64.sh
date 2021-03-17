#!/usr/bin/env bash

testBase64InvalidArgument() {
	command="./ft_ssl base64 -invalid_argument"
	read -d '' usage << EOF
ft_ssl: base64: illegal option -- invalid_argument$
usage: ft_ssl base64 [-ed] [-b num] [-i in_file] [-o out_file]$
EOF

	assertEquals 'invalid usage' "${usage}" "$(${command} 2>&1 > /dev/null | cat -e)"

	eval "$command 2> /dev/null"
	assertEquals 'invalid exit status' 1 $?
}

testBase64EncodesByDefault() {
	string_to_encode='Man'

	hash_result=$(echo -n "${string_to_encode}" | ./ft_ssl base64 | cat -e)
	official_result='TWFu$'

	assertEquals "${official_result}" "${hash_result}"
}

testBase64EncodesWhenEncodeFlagIsSet() {
	string_to_encode='Man'

	hash_result=$(echo -n "${string_to_encode}" | ./ft_ssl base64 -e | cat -e)
	official_result='TWFu$'

	assertEquals "${official_result}" "${hash_result}"
}

testBase64EncodesFromFile() {
	TMP_DIR=$(mktemp -d)
	INPUT_FILE=./test/shell/md5.sh
	HASHING_RESULT_FILE=$TMP_DIR/hashing_result.txt
	OFFICIAL_RESULT_FILE=$TMP_DIR/official_result.txt

	./ft_ssl base64 -i $INPUT_FILE | cat -e > $HASHING_RESULT_FILE
	base64 -i $INPUT_FILE | cat -e > $OFFICIAL_RESULT_FILE

	cmp --silent $HASHING_RESULT_FILE $OFFICIAL_RESULT_FILE

	assertTrue $?

	rm -rf $TMP_DIR
}

testBase64EncodesIntoFile() {
	TMP_DIR=$(mktemp -d)
	INPUT_FILE=./test/shell/md5.sh
	HASHING_RESULT_FILE=$TMP_DIR/hashing_result.txt
	OFFICIAL_RESULT_FILE=$TMP_DIR/official_result.txt

	./ft_ssl base64 -i $INPUT_FILE -o $HASHING_RESULT_FILE
	base64 -i $INPUT_FILE -o $OFFICIAL_RESULT_FILE

	cmp --silent $HASHING_RESULT_FILE $OFFICIAL_RESULT_FILE

	assertTrue $?

	rm -rf $TMP_DIR
}

testBase64EncodeEmptyString() {
	string_to_encode=''

	hash_result=$(echo -n "${string_to_encode}" | ./ft_ssl base64 -e | cat -e)
	official_result='$'

	assertEquals "${official_result}" "${hash_result}"
}

testBase64EncodeSimpleString() {
	string_to_encode='Man'

	hash_result=$(echo -n "${string_to_encode}" | ./ft_ssl base64 -e | cat -e)
	official_result='TWFu$'

	assertEquals "${official_result}" "${hash_result}"
}

testBase64EncodeMediumString() {
	string_to_encode='Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.'

	hash_result=$(echo -n "${string_to_encode}" | ./ft_ssl base64 -e | cat -e)
	official_result='TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=$'

	assertEquals "${official_result}" "${hash_result}"
}

testBase64EncodeLargeString() {
	read -d '' string_to_encode << EOF
Why should I buy yours vs. theirs?
Sometimes I get asked a direct A vs. B sales question. Like...

"Why should I buy HEY instead of Fastmail?"

My honest answer: "I don't know. You should try both and see which one you like best. And once you've made your choice, I'd love to hear which one you picked and why." I'm not selling, I'm learning.

I can surely point someone to my full video walkthrough, or link up comparison pages focused on a specific angle (like this Gmail vs HEY on privacy page), but when it's why A vs. B on the whole, it's ultimately about a set of feelings and a degree of comfort, it's not a head-to-head comparison chart of features. It's nuance, and nuance has to be experienced to be understood.

The less energy you put into trying to convince someone of something, the more energy they have to figure things out for themselves. And ultimately, when someone comes to their own conclusion, they're more bought-in than if you lead them into it.

Yes, you could argue your/our competitor might put in more effort to woo that customer, convince that customer, and sell that customer on their service. And you'd be right. And that might work for them. But I'm just not interested in trying to convince anyone of anything. I'm sure we lose some customers because of this approach, but that's ok — customers aren't trading cards (or NFTs), and we're not trying to collect the full set.

If you want to genuinely serve a customer who's on the fence, encourage them to try a few things so they can get direct experience. If they're buying something they're going to live with for a while — and email is typically one of those things — they'll be better off having toe dipped in a few ponds before deciding which one to dive into.

And then, maybe, you'll get the answer to the question you're curious about: "Why did you buy theirs instead of ours (or ours instead of theirs)?" That answer is likely more valuable than the sale itself.
EOF

	hash_result=$(echo -n "${string_to_encode}" | ./ft_ssl base64 -e | cat -e)
	official_result='V2h5IHNob3VsZCBJIGJ1eSB5b3VycyB2cy4gdGhlaXJzPwpTb21ldGltZXMgSSBnZXQgYXNrZWQgYSBkaXJlY3QgQSB2cy4gQiBzYWxlcyBxdWVzdGlvbi4gTGlrZS4uLgoKIldoeSBzaG91bGQgSSBidXkgSEVZIGluc3RlYWQgb2YgRmFzdG1haWw/IgoKTXkgaG9uZXN0IGFuc3dlcjogIkkgZG9uJ3Qga25vdy4gWW91IHNob3VsZCB0cnkgYm90aCBhbmQgc2VlIHdoaWNoIG9uZSB5b3UgbGlrZSBiZXN0LiBBbmQgb25jZSB5b3UndmUgbWFkZSB5b3VyIGNob2ljZSwgSSdkIGxvdmUgdG8gaGVhciB3aGljaCBvbmUgeW91IHBpY2tlZCBhbmQgd2h5LiIgSSdtIG5vdCBzZWxsaW5nLCBJJ20gbGVhcm5pbmcuCgpJIGNhbiBzdXJlbHkgcG9pbnQgc29tZW9uZSB0byBteSBmdWxsIHZpZGVvIHdhbGt0aHJvdWdoLCBvciBsaW5rIHVwIGNvbXBhcmlzb24gcGFnZXMgZm9jdXNlZCBvbiBhIHNwZWNpZmljIGFuZ2xlIChsaWtlIHRoaXMgR21haWwgdnMgSEVZIG9uIHByaXZhY3kgcGFnZSksIGJ1dCB3aGVuIGl0J3Mgd2h5IEEgdnMuIEIgb24gdGhlIHdob2xlLCBpdCdzIHVsdGltYXRlbHkgYWJvdXQgYSBzZXQgb2YgZmVlbGluZ3MgYW5kIGEgZGVncmVlIG9mIGNvbWZvcnQsIGl0J3Mgbm90IGEgaGVhZC10by1oZWFkIGNvbXBhcmlzb24gY2hhcnQgb2YgZmVhdHVyZXMuIEl0J3MgbnVhbmNlLCBhbmQgbnVhbmNlIGhhcyB0byBiZSBleHBlcmllbmNlZCB0byBiZSB1bmRlcnN0b29kLgoKVGhlIGxlc3MgZW5lcmd5IHlvdSBwdXQgaW50byB0cnlpbmcgdG8gY29udmluY2Ugc29tZW9uZSBvZiBzb21ldGhpbmcsIHRoZSBtb3JlIGVuZXJneSB0aGV5IGhhdmUgdG8gZmlndXJlIHRoaW5ncyBvdXQgZm9yIHRoZW1zZWx2ZXMuIEFuZCB1bHRpbWF0ZWx5LCB3aGVuIHNvbWVvbmUgY29tZXMgdG8gdGhlaXIgb3duIGNvbmNsdXNpb24sIHRoZXkncmUgbW9yZSBib3VnaHQtaW4gdGhhbiBpZiB5b3UgbGVhZCB0aGVtIGludG8gaXQuCgpZZXMsIHlvdSBjb3VsZCBhcmd1ZSB5b3VyL291ciBjb21wZXRpdG9yIG1pZ2h0IHB1dCBpbiBtb3JlIGVmZm9ydCB0byB3b28gdGhhdCBjdXN0b21lciwgY29udmluY2UgdGhhdCBjdXN0b21lciwgYW5kIHNlbGwgdGhhdCBjdXN0b21lciBvbiB0aGVpciBzZXJ2aWNlLiBBbmQgeW91J2QgYmUgcmlnaHQuIEFuZCB0aGF0IG1pZ2h0IHdvcmsgZm9yIHRoZW0uIEJ1dCBJJ20ganVzdCBub3QgaW50ZXJlc3RlZCBpbiB0cnlpbmcgdG8gY29udmluY2UgYW55b25lIG9mIGFueXRoaW5nLiBJJ20gc3VyZSB3ZSBsb3NlIHNvbWUgY3VzdG9tZXJzIGJlY2F1c2Ugb2YgdGhpcyBhcHByb2FjaCwgYnV0IHRoYXQncyBvayDigJQgY3VzdG9tZXJzIGFyZW4ndCB0cmFkaW5nIGNhcmRzIChvciBORlRzKSwgYW5kIHdlJ3JlIG5vdCB0cnlpbmcgdG8gY29sbGVjdCB0aGUgZnVsbCBzZXQuCgpJZiB5b3Ugd2FudCB0byBnZW51aW5lbHkgc2VydmUgYSBjdXN0b21lciB3aG8ncyBvbiB0aGUgZmVuY2UsIGVuY291cmFnZSB0aGVtIHRvIHRyeSBhIGZldyB0aGluZ3Mgc28gdGhleSBjYW4gZ2V0IGRpcmVjdCBleHBlcmllbmNlLiBJZiB0aGV5J3JlIGJ1eWluZyBzb21ldGhpbmcgdGhleSdyZSBnb2luZyB0byBsaXZlIHdpdGggZm9yIGEgd2hpbGUg4oCUIGFuZCBlbWFpbCBpcyB0eXBpY2FsbHkgb25lIG9mIHRob3NlIHRoaW5ncyDigJQgdGhleSdsbCBiZSBiZXR0ZXIgb2ZmIGhhdmluZyB0b2UgZGlwcGVkIGluIGEgZmV3IHBvbmRzIGJlZm9yZSBkZWNpZGluZyB3aGljaCBvbmUgdG8gZGl2ZSBpbnRvLgoKQW5kIHRoZW4sIG1heWJlLCB5b3UnbGwgZ2V0IHRoZSBhbnN3ZXIgdG8gdGhlIHF1ZXN0aW9uIHlvdSdyZSBjdXJpb3VzIGFib3V0OiAiV2h5IGRpZCB5b3UgYnV5IHRoZWlycyBpbnN0ZWFkIG9mIG91cnMgKG9yIG91cnMgaW5zdGVhZCBvZiB0aGVpcnMpPyIgVGhhdCBhbnN3ZXIgaXMgbGlrZWx5IG1vcmUgdmFsdWFibGUgdGhhbiB0aGUgc2FsZSBpdHNlbGYu$'

	assertEquals "${official_result}" "${hash_result}"
}

testBase64EncodeBigFile() {
	TMP_DIR=$(mktemp -d)
	IN_FILE=$TMP_DIR/pdf.pdf
	HASHING_RESULT_FILE=$TMP_DIR/hashing_result.txt
	OFFICIAL_RESULT_FILE=$TMP_DIR/official_result.txt

	curl https://cdn.intra.42.fr/pdf/pdf/19604/en.subject.pdf 2> /dev/null > $IN_FILE

	cat $IN_FILE | ./ft_ssl base64 -e | cat -e > $HASHING_RESULT_FILE
	cat $IN_FILE | base64 | cat -e > $OFFICIAL_RESULT_FILE

	cmp $HASHING_RESULT_FILE $OFFICIAL_RESULT_FILE

	assertTrue $?

	rm -rf $TMP_DIR
}

testBase64IgnoresZeroLineBreak() {
	string_to_encode='Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.'

	hash_result=$(echo -n "${string_to_encode}" | ./ft_ssl base64 -e -b 0 | cat -e)
	official_result='TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=$'
	read -d '' official_result << EOF
TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=$
EOF

	assertEquals "${official_result}" "${hash_result}"
}

testBase64BreaksExactlyAtOutputLength() {
	string_to_encode='Man'

	hash_result=$(echo -n "${string_to_encode}" | ./ft_ssl base64 -e -b 4 | cat -e)
	read -d '' official_result << EOF
TWFu$
$
EOF

	assertEquals "${official_result}" "${hash_result}"
}

testBase64BreaksExactlyAtLineBreak() {
	string_to_encode='Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.'

	hash_result=$(echo -n "${string_to_encode}" | ./ft_ssl base64 -e -b 10 | cat -e)
	read -d '' official_result << EOF
TWFuIGlzIG$
Rpc3Rpbmd1$
aXNoZWQsIG$
5vdCBvbmx5$
IGJ5IGhpcy$
ByZWFzb24s$
IGJ1dCBieS$
B0aGlzIHNp$
bmd1bGFyIH$
Bhc3Npb24g$
ZnJvbSBvdG$
hlciBhbmlt$
YWxzLCB3aG$
ljaCBpcyBh$
IGx1c3Qgb2$
YgdGhlIG1p$
bmQsIHRoYX$
QgYnkgYSBw$
ZXJzZXZlcm$
FuY2Ugb2Yg$
ZGVsaWdodC$
BpbiB0aGUg$
Y29udGludW$
VkIGFuZCBp$
bmRlZmF0aW$
dhYmxlIGdl$
bmVyYXRpb2$
4gb2Yga25v$
d2xlZGdlLC$
BleGNlZWRz$
IHRoZSBzaG$
9ydCB2ZWhl$
bWVuY2Ugb2$
YgYW55IGNh$
cm5hbCBwbG$
Vhc3VyZS4=$
$
EOF

	assertEquals "${official_result}" "${hash_result}"
}

. ./vendor/shunit2/shunit2
