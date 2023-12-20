#ifndef XSTRTOK__H
#define XSTRTOK__H

#include <stddef.h>

/// Return value of @c xstrtok.
struct xstrtok {
    /// Pointer to beginning of token.
    const char *buf;
    /// Size of token.
    size_t len;
    /// The matching delimiter (or NUL if end-of-string reached).
    char delimiter;
};

/// Variant of strtok(3) which does not modify the input string @c str.
/// The separator string, @c sep, must be supplied each time, and may change between calls.
/// The tokens returned by @c xstrtok are always nonempty strings.
/// @return Tuple of @c buf and @c len (where @c buf is NULL when all tokens have been consumed).
struct xstrtok xstrtok(const char *str, const char *sep);

/// Variant of strtok(3) which does not modify the input string @c str.
/// @return Copy of token (caller frees) or NULL when all tokens have been consumed.
char *xstrtok_dup(const char *str, const char *sep);

#endif
