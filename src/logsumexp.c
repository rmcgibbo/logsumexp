/*****************************************************************/
/*    From https://github.com/rmcgibbo/mixtape                   */
/*    Copyright (c) 2013, Stanford University and the Authors    */
/*    Author: Robert McGibbon <rmcgibbo@gmail.com>               */
/*    Contributors:                                              */
/*                                                               */
/*****************************************************************/

#include <emmintrin.h>
#include "float.h"
#include <math.h>
#include "sse_mathfun.h"

static inline float MAX(float v1, float v2) {
        return (((v1) > (v2)) ? (v1) : (v2));
    }

float flogsumexp(const float* __restrict__ buf, int N) {
    int nu = (( N >> 2 ) << 2 );
    const float* StX = buf + nu;
    float sum = 0;
    float max = -FLT_MAX;
    const float* X;
    float max4[4] __attribute__((aligned(16))) = {0};
    __m128 _v;
    __m128 _m;

    if (N == 1)
        return buf[0];
    if (N == 2) {
        max = MAX(buf[0], buf[1]);
        return log(exp(buf[0] - max) + exp(buf[1] - max)) + max;
    } if (N == 3) {
        max = MAX(MAX(buf[0], buf[1]), buf[2]);
        return log(exp(buf[0] - max) + exp(buf[1] - max) + exp(buf[2] - max)) + max;
    }
    
    if (N > 0) {
        X = buf;
        if (nu != 0) {
            _v = _mm_loadu_ps(X);
            X += 4;
            while (X != StX) {
                _v = _mm_max_ps(_v, _mm_loadu_ps(X));
                X += 4;
            }

            _mm_store_ps(max4, _v);
            max = MAX(MAX(MAX(max4[0], max4[1]), max4[2]), max4[3]);
        }

        for(; X < buf + N; X++)
            max = MAX(max, *X);

        X = buf;
        if (nu != 0) {
            _m = _mm_load1_ps(&max);
            _v = exp_ps(_mm_sub_ps(_mm_loadu_ps(X), _m));
            X += 4;
            while (X != StX) {
                _v = _mm_add_ps(_v, exp_ps(_mm_sub_ps(_mm_loadu_ps(X), _m)));
                _mm_store_ps(max4, _v);
                X += 4;
            }

            // horizontal add
            _v = _mm_add_ps(_v, _mm_movehl_ps(_v, _v));
            _v = _mm_add_ss(_v, _mm_shuffle_ps(_v, _v, 1));
            _mm_store_ss(&sum, _v);
        }
        for(; X < buf + N; X++)
            sum += expf(*X - max);
    }

    return log(sum) + max;
}
