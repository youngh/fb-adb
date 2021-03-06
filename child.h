/*
 *  Copyright (c) 2014, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in
 *  the LICENSE file in the root directory of this source tree. An
 *  additional grant of patent rights can be found in the PATENTS file
 *  in the same directory.
 *
 */
#pragma once
#include "util.h"

#define CHILD_PTY_STDIN  (1<<0)
#define CHILD_PTY_STDOUT (1<<1)
#define CHILD_PTY_STDERR (1<<2)
#define CHILD_INHERIT_STDERR (1<<3)
#define CHILD_MERGE_STDERR (1<<4)
#define CHILD_CTTY (1<<5)
#define CHILD_SETSID (1<<6)
#define CHILD_SOCKETPAIR_STDIO (1<<7)

struct child_start_info {
    int flags;
    const char* exename;
    const char* const* argv;
    void (*pty_setup)(int master, int slave, void* data);
    void* pty_setup_data;
    int deathsig;
    const char* child_chdir;
};

struct child {
    int flags;
    int deathsig;
    pid_t pid;
    int status;
    unsigned dead_p : 1;
    struct fdh* pty_master;
    struct fdh* fd[3];
};

struct child* child_start(const struct child_start_info* csi);
int child_wait(struct child* c);
