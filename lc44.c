#include "lcHead.h"

/**
 * This question is simple version of lc10.c
 * We can treat lc44:"?" as lc10:"."
 * we can treat lc44:"*" as lc10:".*"
 *
 * Why this question is simple version?
 * in lc10.c we need to handle ".*" as a combo.
 * (not too hard, just need three or four lines of code) in lc10.c
 * But in lc44.c, we definittly not need to do that.
 */

/* every time I meet this kind of question,
 * like there are some possible situation when we hit a *,
 * the first idea come with me is "we need a way to go back and rerouting".
 *
 * and the convenient way is to use the function call stack.
 * another way we need to implement a stack ourself.
 */
bool __isMatch(char *s, char *p);
bool starMatch(char *s, char *p)
{
	/* star can match any sequence of character, include empty. */
	int s_len = strlen(s);

	for (int i = 0; i <= s_len; i++) {
		if (__isMatch(&s[i], &p[1]))
			return true;
	}

	return false;
}

bool anyMatch(char *s, char *p) {
	/* ? match any character */
	if (s[0] == 0)
		return false;
	return __isMatch(&s[1], &p[1]);
}

bool charMatch(char *s, char *p) {
	if (s[0] != p[0])
		return false;
	return __isMatch(&s[1], &p[1]);
}

bool __isMatch(char *s, char *p)
{
	/* in this first version, I don't want to care about the
	 * performance, I mean I will not make a cache in that */
	if (s[0] == 0 && p[0] == 0)
		return true;
	if (p[0] == 0)
		return false;

	switch(p[0]) {
	case '*': 
	{
		/* if there a mulit star, merge then */
		char *temp = p;
		while (temp[1] == '*')
			temp++;
		return starMatch(s, temp);
		break;
	}
	case '?':
		return anyMatch(s, p);
		break;
	default:
		return charMatch(s, p);
		break;
	}
	
}

bool isMatch(char *s, char *p)
{
	return __isMatch(s, p);
}

void case_1(void)
{
	char *s = "aa";
	char *p = "a";
	int key = 0;

	assert(key == isMatch(s, p));
}
REGISTER_TEST_CASE(case_1);

void case_2(void)
{
	char *s = "aa";
	char *p = "*";
	int key = 1;

	assert(key == isMatch(s, p));
}
REGISTER_TEST_CASE(case_2);

void case_3(void)
{
	char *s = "cb";
	char *p = "?a";
	int key = 0;

	assert(key == isMatch(s, p));
}
REGISTER_TEST_CASE(case_3);

void case_4(void)
{
	char *s = "ca";
	char *p = "?a";
	int key = 1;

	assert(key == isMatch(s, p));
}
REGISTER_TEST_CASE(case_4);

void case_5(void)
{
	char *s = "mississippi";
	char *p = "m??*ss*?i*pi";
	int key = 0;

	assert(key == isMatch(s, p));
}
REGISTER_TEST_CASE(case_5);

void case_6(void)
{
	char *s = "bbbbbbbabbaabbabbbbaaabbabbabaaabbababbbabbbabaaabaab";
	char *p = "b*b*ab**ba*b**b***bba";

	int key = 0;

	assert(key == isMatch(s, p));
}
REGISTER_TEST_CASE(case_6);

