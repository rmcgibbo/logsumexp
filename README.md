Fast logsumexp
==============
*Fast Logsumexp function available from Python*

This code is about 2.5x faster than alternative scipy/numpy/cython/numexpr implementations. It's fast because of explicit use of SSE vectorized intrinsics.

[See the example IPython notebook](http://nbviewer.ipython.org/github/rmcgibbo/logsumexp/blob/master/Accelerating%20log-sum-exp.ipynb)

Installation
------------
$ python setup.py install

Usage
-----
```
import sselogsumexp
x = np.random.randn(100)
sselogsumexp.logsumexp(x)
```
