#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int howLongPalindrome(const char *s, int p, int *start, int *end)
{
	int laba = 0;
	int laa = 0;
	int sl = strlen(s);

	/* a(1,2) aba(2,4) abcba(3, 6)*/
	while(p - laba >= 0 && laba + p < sl && s[p - laba] == s[p + laba])
		laba++;

	/* aa(1, 3) aaaa(2, 5) aaaaaa(3, 7)*/
	while(p - laa >= 0 && laa + p + 1< sl && s[p - laa] == s[p + laa + 1])
		laa++;

	if ((laba * 2) > (laa * 2 + 1)) {
		*start = p - laba + 1;
		*end = p + laba - 1;
		return laba * 2;
	} else {
		*start = p - laa + 1;
		*end = p + laa;
		return laa * 2 + 1;
	}


}

char * longestPalindrome(char * s){
	int sl = strlen(s);
	int maxlen = 0;
	int start = 0;
	int end = 0;

	for (int i = 0; i < sl; i++) {
		int tstart = 0;
		int tend = 0;
		int tlen = howLongPalindrome(s, i, &tstart, &tend);
		if (maxlen < tlen) {
			maxlen = tlen;
			start = tstart;
			end = tend;
		}
	}
	char *ret = malloc(maxlen);
	strncpy(ret, &s[start], maxlen);

	ret[maxlen - 1] = 0;
	return ret;
}

#define CASE_1
#ifdef CASE_1
void case_1(void)
{
	char s[] = "babad";
	printf("bab/aba %s\n", longestPalindrome(s));
}
#endif

#define CASE_2
#ifdef CASE_2
void case_2(void)
{
	char s[] = "chhb";
	printf("hh %s\n", longestPalindrome(s));
}
#endif

void main(void)
{
#ifdef CASE_1
	case_1();
#endif
#ifdef CASE_2
	case_2();
#endif
}
