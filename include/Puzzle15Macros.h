// Copyright (C) 2014 Călin Cruceru <calin@rosedu.org>
//
// This program is free software licenced under MIT Licence. You can
// find a copy of this licence in LICENCE.txt in the top directory of
// source code.
//

#ifndef PUZZLE15MACROS_H__
#define PUZZLE15MACROS_H__

#include <cstdio>
#include <cstdlib>

#define DIE(assertion, call_description) \
    do { \
        if (assertion) { \
            fprintf(stderr, "(%s, %d): ", \
                    __FILE__, __LINE__); \
            perror(call_description); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define UNUSED(Parameter) ((void*)&Parameter)


#endif
