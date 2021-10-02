#pragma once

#include "common.h"

// argv dtor -- uses a ton of nullptr checks.
void dtor_argv(char **argv, size_t len);

// program dtor
void dtor_pgrm(pgrm *p);

// client ctor
CLIENT *ctor_cl(char *host);

// client dtor
void dtor_cl(CLIENT * cl);
