#include "lcHead.h"
bool normalMatch(char *s, char *p);
bool starPointMatch(char *s, char *p) {
	int sl = strlen(s);

	for (int i = 0; i < sl + 1; i++) {
		if (normalMatch(&s[i], &p[2]))
			return true;
	}
	return false;
}

bool starCharMatch(char *s, char *p)
{
	int sl = strlen(s);

	for (int i = 0; i < sl + 1; i++) {
		if (normalMatch(&s[i], &p[2]))
			return true;
		if (s[i] != p[0])
			return false;
	}
	return false;
}

bool starMatch(char *s, char *p)
{
	if (p[0] == '.')
		return starPointMatch(s, p);
	else
		return starCharMatch(s,p);
}

bool normalMatch(char *s, char *p)
{
	int sl = strlen(s);
	int pl = strlen(p);

	if (sl == 0 && pl == 0)
		return true;

	if (pl == 0)
		return false;

	if (pl > 1 && p[1]=='*') {
		/* TBD: This right? */
		if (p[0] == '*')
			return false;
		return starMatch(s, p);
	}

	if (sl == 0)
		return false;

	if (p[0] == s[0] || p[0] == '.') {
		return normalMatch(&s[1], &p[1]);
	} else {
		return false;
	}
}


bool isMatchGold(char * s, char * p)
{
	return normalMatch(s, p);
}

bool isMatchGold2(char * s, char * p)
{
	if (!*p) return !*s;
	bool first_match = *s && (*s == *p || *p == '.');
	if (*(p+1) == '*') {
		return isMatchGold2(s, p+2) || (first_match && isMatchGold2(++s, p));
	}
	else {
		return first_match && isMatchGold2(++s, ++p);
	}
}

struct map {
	size_t pl;
	size_t sl;
	size_t size;
	bool map[0]; /* False: not checked. True: checked and failed */
};

static inline void mapSetFalse(struct map *map, size_t entry)
{
	map->map[entry] = 1;
}

#define CHARMATCH(s, p) ((((p[0] == '.')||(s[0] == p[0])) && (s[0] != '\0')))
bool __isMatch(char *s, char *p, struct map *map)
{
#ifdef DEBUG
	printf("sl %ld pl %ld\n", strlen(s), strlen(p));
#endif
	/* if this pattern failed before */
	if (map->map[strlen(s) * map->pl + strlen(p)]) {
		return false;
	}

	while (p[0] != '\0') {
		if (p[1] == '*') {
			/* try to cut [a-z.]* */
			if (__isMatch(s, p + 2, map))
				return true;
			else
				/* try to repeat [a-z.]* */
				if (CHARMATCH(s, p) && __isMatch(s + 1, p, map)) {
					return true;
				} else {
					mapSetFalse(map, strlen(s) * map->pl + strlen(p));
					return false;
				}
		} else if (s[0] == '\0' || (p[0] != '.' && s[0] != p[0])) {
			mapSetFalse(map, strlen(s) * map->pl + strlen(p));
			return false;
		}

		s++;
		p++;
	}

	if (p[0] == '\0' && s[0] == '\0') {
		return true;
	} else {
		mapSetFalse(map, strlen(s) * map->pl + strlen(p));
		return false;
	}

}

bool isMatch(char *s, char *p)
{
	/* perpare a cache for save the result */
	size_t mapSize = sizeof(bool) * ((strlen(s) + 1) * (strlen(p) + 1));
	struct map *map = malloc(mapSize + sizeof(*map));
	memset(map, 0, mapSize + sizeof(*map));
	map->sl = strlen(s) + 1;
	map->pl = strlen(p) + 1;
	map->size = mapSize;

	bool ret = __isMatch(s, p, map);
	free(map);
	return ret;
}

void case_1(void)
{
	char *s = "aa";
	char *p = "a";

	if (isMatch(s, p) != isMatchGold(s, p)) {
		printf("case 1 is failed\n");
	}
}

void case_2(void)
{
	char *s = "aa";
	char *p = "a*";

	if (isMatch(s, p) != isMatchGold(s, p)) {
		printf("case 2 is failed\n");
	}
}

void case_3(void)
{
	char *s = "ab";
	char *p = ".*";

	if (isMatch(s, p) != isMatchGold(s, p)) {
		printf("case 3 is failed\n");
	}
}

void case_4(void)
{
	char *s = "";
	char *p = "b";

	if (isMatch(s, p) != isMatchGold(s, p)) {
		printf("case 4 is failed\n");
	}
}

void case_5(void)
{
	char *s = "ippi";
	char *p = "p*.";

	if (isMatch(s, p) != isMatchGold(s, p)) {
		printf("case 5 is failed\n");
	}
}

void case_6(void)
{
	char *s = "ac";
	char *p = ".*c";

	if (isMatch(s, p) != isMatchGold2(s, p)) {
		printf("case 6 is failed\n");
	}
}

void case_7(void)
{
	char *s = "b";
	char *p = ".*c";

	if (isMatch(s, p) != isMatchGold2(s, p)) {
		printf("case 7 is failed\n");
	}
}

void case_8(void)
{
	char *s = "aabcbcbcaccbcaabc";
	char *p = ".*a*aa*.*b*.c*.*a*";

	if (isMatch(s, p) != isMatchGold2(s, p)) {
		printf("case 8 is failed\n");
	}
}

void case_9(void)
{
	char *s = "aaaaaaaaaaaaab";
	char *p = "a*a*a*a*a*a*a*a*a*a*c";

	if (isMatch(s, p) != isMatchGold2(s, p)) {
		printf("case 9 is failed\n");
	}
}

void case_10(void)
{
	char *s = "aaaaaaaaaaaaab";
	char *p = "a*a*a*a*a*a*a*a*a*a*b";

	if (isMatch(s, p) != isMatchGold2(s, p)) {
		printf("case 10 is failed\n");
	}
}

int main(void)
{
	case_1();
	case_2();
	case_3();
	case_4();
	case_5();
	case_6();
	case_7();
	case_8();
	case_9();
	case_10();
	return 0;
}
