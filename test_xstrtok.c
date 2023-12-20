#include "xstrtok.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    struct xstrtok r;

    {
        char *s = strdup(",,,aaa;;bbb,");
        const char *d = ";,";

        assert(!strcmp(strtok(s,    d), "aaa"));
        assert(!strcmp(strtok(NULL, d), "bbb"));
        assert(NULL == strtok(NULL, d)        );
        assert(NULL == strtok(NULL, d)        );

        free(s);
    }

    {
        const char *s = ",,,aaa;;bbb,";
        const char *d = ";,";

        r = xstrtok(s, d);
        assert(!strncmp("aaa", r.buf, r.len));
        assert(r.delimiter == ';');

        r = xstrtok(NULL, d);
        assert(!strncmp("bbb", r.buf, r.len));
        assert(r.delimiter == ',');

        r = xstrtok(NULL, d);
        assert(r.buf == NULL);
        assert(r.len == 0);
        assert(r.delimiter == 0);

        r = xstrtok(NULL, d);
        assert(r.buf == NULL);
        assert(r.len == 0);
        assert(r.delimiter == 0);
    }

    {
        const char *s = ",,,aaa;;bbb,";
        const char *d = ";,";
        char *t;

        t = xstrtok_dup(s, d);
        assert(!strcmp(t, "aaa"));
        free(t);
        t = xstrtok_dup(NULL, d);
        assert(!strcmp(t, "bbb"));
        free(t);
        assert(NULL == xstrtok_dup(NULL, d));
        assert(NULL == xstrtok_dup(NULL, d));
    }

    r = xstrtok("", NULL);
    assert(r.buf == NULL);
    assert(r.len == 0);

    r = xstrtok(NULL, NULL);
    assert(r.buf == NULL);
    assert(r.len == 0);

    r = xstrtok("", "+");
    assert(r.buf == NULL);
    assert(r.len == 0);

    {
        const char *s = "abc";

        r = xstrtok(s, "+");
        assert(!strcmp(r.buf, s));

        r = xstrtok(NULL, "+");
        assert(r.buf == NULL);
        assert(r.len == 0);

        r = xstrtok(s, "");
        assert(!strcmp(r.buf, s));

        r = xstrtok(NULL, "");
        assert(r.buf == NULL);
        assert(r.len == 0);

        r = xstrtok(s, NULL);
        assert(!strcmp(r.buf, s));

        r = xstrtok(NULL, NULL);
        assert(r.buf == NULL);
        assert(r.len == 0);
    }

    {
        const char *s = ":abc::d:ef";
        const char *d = ":";

        r = xstrtok(s, d);
        assert(!strncmp("abc", r.buf, r.len));
        assert(r.delimiter == ':');

        r = xstrtok(NULL, d);
        assert(!strncmp("d", r.buf, r.len));
        assert(r.delimiter == ':');

        r = xstrtok(NULL, d);
        assert(!strncmp("ef", r.buf, r.len));
        assert(r.delimiter == 0);

        r = xstrtok(NULL, d);
        assert(r.buf == NULL);
        assert(r.len == 0);
        assert(r.delimiter == 0);

        r = xstrtok(NULL, d);
        assert(r.buf == NULL);
        assert(r.len == 0);
        assert(r.delimiter == 0);
    }

    {
        const char *s = "a:b+c/d*e";

        r = xstrtok(s, "+/*");
        assert(!strncmp("a:b", r.buf, r.len));
        assert(r.delimiter == '+');

        r = xstrtok(NULL, "+/*");
        assert(!strncmp("c", r.buf, r.len));
        assert(r.delimiter == '/');

        r = xstrtok(NULL, "+/");
        assert(!strncmp("d*e", r.buf, r.len));
        assert(r.delimiter == 0);

        r = xstrtok(NULL, ":");
        assert(r.buf == NULL);
        assert(r.len == 0);
    }
}
