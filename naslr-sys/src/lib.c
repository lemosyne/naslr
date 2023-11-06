/*
 * Functionality to disable ASLR
 *
 * Code is stripped down from [no-aslr](https://github.com/kccqzy/no-aslr),
 * which derives portions of code from util-linux, which are copyrighted by
 * Red Hat, Inc.
 *
 * Copyright (C) 2003-2007 Red Hat, Inc.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#if defined(__APPLE__)

#include <spawn.h>

#   ifndef _POSIX_SPAWN_DISABLE_ASLR
#       define _POSIX_SPAWN_DISABLE_ASLR 0x100
#   endif

int disable_aslr_real(void) {
    posix_spawnattr_t atts;
    posix_spawnattr_init(&attrs);

    short flags = 0;
    flags |= POSIX_SPAWN_SETEXEC;
    flags |= _POSIX_SPAWN_DISABLE_ASLR;

    return posix_spawnattr_setflags(&attrs, flags);
}


#elif defined(__linux__)
#   define _GNU_SOURCE
#   include <sys/personality.h>
#   include <unistd.h>

#   ifndef HAVE_PERSONALITY
#       include <syscall.h>
#       define personality(persona) ((long)syscall(SYS_personality, persona))
#   endif

#   ifndef ADDR_NO_RANDOMIZE
#       define ADDR_NO_RANDOMIZE 0x0040000
#   endif

int disable_aslr_real(void) {
    unsigned long persona = PER_LINUX | ADDR_NO_RANDOMIZE;

     /* Depending on architecture and kernel version, personality */
     /* syscall is either capable or incapable of returning an error. */
     /* If the return value is not an error, then it's the previous */
     /* personality value, which can be an arbitrary value */
     /* undistinguishable from an error value. */
     /* To make things clear, a second call is needed. */
    if (personality(persona) < 0 && personality(persona) < 0) {
        return 1;
    }

    return 0;
}

#else
#   error "Unsupported operating system"
#endif
