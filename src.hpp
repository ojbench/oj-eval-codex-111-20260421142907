// Header-only implementation of C strtok
// No standard library and no globals; uses function-static state.

#ifndef __restrict
#define __restrict
#endif

extern "C" {
char *strtok(char * __restrict str, const char * __restrict delim);
}

static int __oj_is_delim(char c, const char *delim) {
    // Returns 1 if c is in delim, else 0
    // Works even if delim is empty string
    while (*delim) {
        if (*delim == c) return 1;
        ++delim;
    }
    return 0;
}

extern "C" char *strtok(char * __restrict str, const char * __restrict delim) {
    static char *last = (char*)0;

    char *s = str ? str : last;
    if (s == (char*)0) return (char*)0;

    // Skip leading delimiters
    while (*s && __oj_is_delim(*s, delim)) ++s;

    if (*s == '\0') {
        last = (char*)0;
        return (char*)0;
    }

    char *token = s;
    while (*s && !__oj_is_delim(*s, delim)) ++s;

    if (*s == '\0') {
        last = (char*)0;
    } else {
        *s = '\0';
        last = s + 1;
    }

    return token;
}

