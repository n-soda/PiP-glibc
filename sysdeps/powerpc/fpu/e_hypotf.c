/* Pythagorean addition using floats
   Copyright (C) 2011, 2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Adhemerval Zanella <azanella@br.ibm.com>, 2011

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If
   not, see <http://www.gnu.org/licenses/>.  */

#include <math.h>
#include <math_private.h>


static const float two30  = 1.0737418e09;

/* __ieee754_hypotf(x,y)

   This a FP only version without any FP->INT conversion.
   It is similar to default C version, making appropriates
   overflow and underflows checks as using double precision
   instead of scaling.  */

#ifdef _ARCH_PWR7
/* POWER7 isinf and isnan optimizations are fast. */
# define TEST_INF_NAN(x, y)                                      \
   if (isinff(x) || isinff(y))                                   \
     return INFINITY;                                            \
   if (isnanf(x) || isnanf(y))                                   \
     return NAN;
# else
/* For POWER6 and below isinf/isnan triggers LHS and PLT calls are
 * costly (especially for POWER6). */
# define GET_TWO_FLOAT_WORD(f1,f2,i1,i2)                         \
 do {                                                            \
   ieee_float_shape_type gf_u1;                                  \
   ieee_float_shape_type gf_u2;                                  \
   gf_u1.value = (f1);                                           \
   gf_u2.value = (f2);                                           \
   (i1) = gf_u1.word & 0x7fffffff;                               \
   (i2) = gf_u2.word & 0x7fffffff;                               \
 } while (0)

# define TEST_INF_NAN(x, y)                                      \
 do {                                                            \
   uint32_t hx, hy;                                              \
   GET_TWO_FLOAT_WORD(x, y, hx, hy);                             \
   if (hy > hx) {                                                \
     uint32_t ht = hx; hx = hy; hy = ht;                         \
   }                                                             \
   if (hx >= 0x7f800000) {                                       \
     if (hx == 0x7f800000 || hy == 0x7f800000)                   \
       return INFINITY;                                          \
     return NAN;                                                 \
   }                                                             \
 } while (0)
#endif


float
__ieee754_hypotf (float x, float y)
{
  x = fabsf (x);
  y = fabsf (y);

  TEST_INF_NAN (x, y);

  if (y > x)
    {
      float t = y;
      y = x;
      x = t;
    }
  if (y == 0.0 || (x / y) > two30)
    {
      return x + y;
    }

  return __ieee754_sqrt ((double) x * x + (double) y * y);
}
strong_alias (__ieee754_hypotf, __hypotf_finite)
