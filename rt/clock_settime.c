/* Set a clock to a given value.  Stub version.
   Copyright (C) 1999-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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

#include <errno.h>
#include <time.h>

/* Set CLOCK to value TP.  */
int
__clock_settime (clockid_t clock_id, const struct timespec *tp)
{
  __set_errno (ENOSYS);
  return -1;
}
weak_alias (__clock_settime, clock_settime)
stub_warning (clock_settime)
