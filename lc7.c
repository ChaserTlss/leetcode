#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
bool normalMatch(char *s, char *p);
bool starPointMatch(char *s, char *p) {
    int sl = strlen(s);

    for (int i = 0; i < sl + 1; i++) {
        if (normalMatch(&s[i], &p[2]))
            return true;
    }
    return false;
}

bool starCharMatch(char *s, char *p) {
    int sl = strlen(s);

    for (int i = 0; i < sl + 1; i++) {
        if (normalMatch(&s[i], &p[2]))
            return true;
        if (s[i] != p[0])
            return false;
    }
    return false;
}

bool starMatch(char *s, char *p) {
    if (p[0] == '.')
        return starPointMatch(s, p);
    else
        return starCharMatch(s,p);
}

bool normalMatch(char *s, char *p) {
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


bool isMatch(char * s, char * p){
    return normalMatch(s, p);
}

#define CASE_1
#ifdef CASE_1
int case_1(void)
{
	char *s = "ab";
	char *p = "a*";
	bool r = false;

	if (isMatch(s, p) == r) {
		return 0;
	} else {
		printf("s=%s p=%s r=%d g=%d\n",
				s, p, r, isMatch(s, p));
		return 1;
	}

}
#endif

#define CASE_2
#ifdef CASE_2
int case_2(void)
{
	char *s = "aa";
	char *p = "a*";
	bool r = true;

	if (isMatch(s, p) == r) {
		return 0;
	} else {
		printf("s=%s p=%s r=%d g=%d\n",
				s, p, r, isMatch(s, p));
		return 1;
	}

}
#endif

#define CASE_3
#ifdef CASE_3
int case_3(void)
{
	char *s = "aab";
	char *p = "c*a*b";
	bool r = true;

	if (isMatch(s, p) == r) {
		return 0;
	} else {
		printf("s=%s p=%s r=%d g=%d\n",
				s, p, r, isMatch(s, p));
		return 1;
	}

}
#endif

#define CASE_4
#ifdef CASE_4
int case_4(void)
{
	char *s = "a";
	char *p = "ab*";
	bool r = true;

	if (isMatch(s, p) == r) {
		return 0;
	} else {
		printf("s=%s p=%s r=%d g=%d\n",
				s, p, r, isMatch(s, p));
		return 1;
	}

}
#endif

int main(void)
{
#ifdef CASE_1
	if (case_1()) {
		printf("case 1 false\n");
	}
#endif
#ifdef CASE_2
	if (case_2()) {
		printf("case 2 false\n");
	}
#endif
#ifdef CASE_3
	if (case_3()) {
		printf("case 3 false\n");
	}
#endif
#ifdef CASE_4
	if (case_4()) {
		printf("case 4 false\n");
	}
#endif
}
