/*
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version
 * 1.0 of the CDDL.
 *
 * A full copy of the text of the CDDL should have accompanied this
 * source.  A copy of the CDDL is also available via the Internet at
 * http://www.illumos.org/license/CDDL.
 */

/*
 * Copyright 2015 Joyent, Inc.
 */

#ifndef	_LX_SYSCALL_H
#define	_LX_SYSCALL_H

#include <sys/lx_brand.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The br_scall_args field of lx_lwp_data is going to be populated with
 * pointers to structs. The types of these structs should be defined in this
 * header file.  These are Linux specific arguments to system calls that don't
 * exist in illumos. Each section should be labelled with which system call it
 * belongs to.
 */

/* arguments for waitpid(2) */
/* see comments in usr/src/lib/brand/lx/lx_brand/common/wait.c */
#define	LX_WNOTHREAD	0x20000000 /* Do not wait on siblings' children */
#define	LX_WALL		0x40000000 /* Wait on all children */
#define	LX_WCLONE	0x80000000 /* Wait only on clone children */

/* For arch_prctl(2) */
#define	LX_ARCH_SET_GS	0x1001
#define	LX_ARCH_SET_FS	0x1002
#define	LX_ARCH_GET_FS	0x1003
#define	LX_ARCH_GET_GS	0x1004

/*
 * For ptrace(2):
 */
#define	LX_PTRACE_TRACEME	0
#define	LX_PTRACE_PEEKTEXT	1
#define	LX_PTRACE_PEEKDATA	2
#define	LX_PTRACE_PEEKUSER	3
#define	LX_PTRACE_POKETEXT	4
#define	LX_PTRACE_POKEDATA	5
#define	LX_PTRACE_POKEUSER	6
#define	LX_PTRACE_CONT		7
#define	LX_PTRACE_KILL		8
#define	LX_PTRACE_SINGLESTEP	9
#define	LX_PTRACE_GETREGS	12
#define	LX_PTRACE_SETREGS	13
#define	LX_PTRACE_GETFPREGS	14
#define	LX_PTRACE_SETFPREGS	15
#define	LX_PTRACE_ATTACH	16
#define	LX_PTRACE_DETACH	17
#define	LX_PTRACE_GETFPXREGS	18
#define	LX_PTRACE_SETFPXREGS	19
#define	LX_PTRACE_SYSCALL	24
#define	LX_PTRACE_SETOPTIONS	0x4200
#define	LX_PTRACE_GETEVENTMSG	0x4201
#define	LX_PTRACE_GETSIGINFO	0x4202

/*
 * For clone(2):
 */
#define	LX_CSIGNAL		0x000000ff
#define	LX_CLONE_VM		0x00000100
#define	LX_CLONE_FS		0x00000200
#define	LX_CLONE_FILES		0x00000400
#define	LX_CLONE_SIGHAND	0x00000800
#define	LX_CLONE_PID		0x00001000
#define	LX_CLONE_PTRACE		0x00002000
#define	LX_CLONE_VFORK		0x00004000
#define	LX_CLONE_PARENT		0x00008000
#define	LX_CLONE_THREAD		0x00010000
#define	LX_CLONE_NEWNS		0x00020000
#define	LX_CLONE_SYSVSEM	0x00040000
#define	LX_CLONE_SETTLS		0x00080000
#define	LX_CLONE_PARENT_SETTID	0x00100000
#define	LX_CLONE_CHILD_CLEARTID	0x00200000
#define	LX_CLONE_DETACH		0x00400000
#define	LX_CLONE_UNTRACED	0x00800000
#define	LX_CLONE_CHILD_SETTID	0x01000000
#define	LX_CLONE_NEWCGROUP	0x02000000
#define	LX_CLONE_NEWUTS		0x04000000
#define	LX_CLONE_NEWIPC		0x08000000
#define	LX_CLONE_NEWUSER	0x10000000
#define	LX_CLONE_NEWPID		0x20000000
#define	LX_CLONE_NEWNET		0x40000000
#define	LX_CLONE_IO		0x80000000

#define	SHARED_AS \
	(LX_CLONE_VM | LX_CLONE_FS | LX_CLONE_FILES | LX_CLONE_SIGHAND | \
	LX_CLONE_THREAD)

/*
 * Valid clone flags when not a full process or full thread (SHARED_AS), This
 * can be expanded as additional clone-group support is added.
 */
#define	LX_CLONE_GRP_SUBSET	(LX_CLONE_FS)

#define	LX_IS_CLONE_GRP(X)	((X & SHARED_AS) != 0 && \
				(X & SHARED_AS) != SHARED_AS && \
				((X & SHARED_AS) & ~LX_CLONE_GRP_SUBSET) == 0)

#define	LX_CLONE_NS_UNSUP	(LX_CLONE_NEWNS | LX_CLONE_NEWCGROUP | \
				LX_CLONE_NEWUTS | LX_CLONE_NEWIPC | \
				LX_CLONE_NEWUSER | LX_CLONE_NEWPID | \
				LX_CLONE_NEWNET | LX_CLONE_IO)

#ifdef	__cplusplus
}
#endif

#endif	/* _LX_SYSCALL_H */
