#if defined HAVE_FMA4_SUPPORT || defined HAVE_AVX_SUPPORT
# include <init-arch.h>
# include <math_private.h>

extern double __ieee754_exp_sse2 (double);
extern double __ieee754_exp_avx (double);
# ifdef HAVE_FMA4_SUPPORT
extern double __ieee754_exp_fma4 (double);
# else
#  undef HAS_ARCH_FEATURE
#  define HAS_ARCH_FEATURE(feature) 0
#  define __ieee754_exp_fma4 ((void *) 0)
# endif

libm_ifunc (__ieee754_exp,
	    HAS_ARCH_FEATURE (FMA4_Usable) ? __ieee754_exp_fma4
	    : (HAS_ARCH_FEATURE (AVX_Usable)
	       ? __ieee754_exp_avx : __ieee754_exp_sse2));
strong_alias (__ieee754_exp, __exp_finite)

# define __ieee754_exp __ieee754_exp_sse2
#endif


#include <sysdeps/ieee754/dbl-64/e_exp.c>
