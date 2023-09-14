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
/* use a bitmap as a cache */
struct cache {
	size_t p_size;
	size_t s_size;
	struct bitmap *map;
};

bool __isMatch(char *s, char *p, struct cache *c);
bool starMatch(char *s, char *p, struct cache *c)
{
	/* star can match any sequence of character, include empty. */
	int s_len = strlen(s);

	for (int i = 0; i <= s_len; i++) {
		if (__isMatch(&s[i], &p[1], c))
			return true;
	}

	return false;
}

bool __isMatch(char *s, char *p, struct cache *c)
{
	/* if map[index] be set, it means this pattern is checked, and false */
	if (getBitmap(c->map, strlen(s) * c->p_size + strlen(p))) {
		return false;
	}
	/* in this first version, I don't want to care about the
	 * performance, I mean I will not make a cache in that */
	char *p_t = p;
	char *s_t = s;

	while (p_t[0] != 0) {
		switch(p_t[0]) {
		case '*': 
		{
			/* if there a mulit star, merge then */
			char *temp = p_t;
			while (temp[1] == '*')
				temp++;
			if (starMatch(s_t, temp, c))
				return true;
			else
				goto FALSE;
			break;
		}
		case '?':
			if (s_t[0] == 0)
				goto FALSE;
			p_t ++;
			s_t ++;
			break;
		default:
			if (s_t[0] != p_t[0])
				goto FALSE;
			p_t ++;
			s_t ++;
			break;
		}
	}

	if (s_t[0] == 0 && p_t[0] == 0)
		return true;
FALSE:
	setBitmap(c->map, strlen(s) * c->p_size + strlen(p));
	return false;
	
}

bool isMatch(char *s, char *p)
{
	struct cache c;

	c.p_size = strlen(p) + 1; /* 1 for '\0' */
	c.s_size = strlen(s) + 1;

	c.map = newBitmap(c.p_size * c.s_size);
	setAllBitmap(c.map, 0);

	bool ret =  __isMatch(s, p, &c);
	free(c.map);

	return ret;
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

void case_7(void)
{
	char *s = "abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb";
	char *p = "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb";

	int key = 0;
	assert(key == isMatch(s, p));
}
REGISTER_TEST_CASE(case_7);

