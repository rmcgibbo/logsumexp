import sys
import numpy as np
cimport numpy as np

cdef extern from "logsumexp.h":
    float flogsumexp(const float* buf, int N) nogil

def logsumexp(np.ndarray[dtype=np.float32_t] a):
    """
    Compute the log of the sum of exponentials of input elements.

    Parameters
    ----------
    a : np.ndarray
        Input data. Must be contiguous.
    """
    if not (a.flags['C_CONTIGUOUS'] or a.flags['F_CONTIGUOUS']):
        raise TypeError('a must be contiguous')
    
    return flogsumexp(&a[0], a.size)


