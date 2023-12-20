#include "xstrtok.h"

#include <errno.h>
#include <string.h>

struct xstrtok xstrtok(const char *str, const char *sep)
{
    static const char *context_;

    struct xstrtok ret = { NULL, 0, 0 };

    if (str) {
        /* Reset. */
        context_ = str;
    }

    if (!sep) {
        /* Default. */
        sep = "";
    }

    /* Find start of token. */
    while (*context_ && strchr(sep, *context_)) {
        context_++;
    }

    if (*context_) {
        ret.buf = context_;

        /* Find end of token. */
        while (*context_ && !strchr(sep, *context_)) {
            context_++;
        }

        ret.len = (size_t)(context_ - ret.buf);

        if (*context_) {
            ret.delimiter = *context_;

            /* Skip delimiter.
             * Must be done here, since delimiter string could change on next call. */
            context_++;
        }
    }

    return ret;
}

char *xstrtok_dup(const char *str, const char *sep)
{
    struct xstrtok r = xstrtok(str, sep);

    if (r.buf) {
        /* errno is set if strndup(3) fails. */
        errno = 0;
        return strndup(r.buf, r.len);
    }

    return NULL;
}
