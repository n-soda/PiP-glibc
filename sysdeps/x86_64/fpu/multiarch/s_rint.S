/* Copyright (C) 2011 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@gmail.come>, 2011.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <machine/asm.h>
#include <init-arch.h>


ENTRY(__rint)
	.type	__rint, @gnu_indirect_function
	LOAD_RTLD_GLOBAL_RO_RDX
	leaq	__rint_sse41(%rip), %rax
	HAS_CPU_FEATURE (SSE4_1)
	jnz	2f
	leaq	__rint_c(%rip), %rax
2:	ret
END(__rint)
weak_alias (__rint, rint)


ENTRY(__rint_sse41)
	roundsd	$4, %xmm0, %xmm0
	ret
END(__rint_sse41)
