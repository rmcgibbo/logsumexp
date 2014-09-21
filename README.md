Fast logsumexp
==============
*Fast [log-sum-exp](http://machineintelligence.tumblr.com/post/4998477107/the-log-sum-exp-trick) function in Python*

This code is about 2.5x faster than alternative scipy/numpy/cython/numexpr implementations. It's fast because of explicit use of SSE vectorized intrinsics.

[See the example IPython notebook](http://nbviewer.ipython.org/github/rmcgibbo/logsumexp/blob/master/Accelerating%20log-sum-exp.ipynb)

Installation
------------
```
$ python setup.py install
```

Usage
-----
```
import sselogsumexp
x = np.random.randn(100)
sselogsumexp.logsumexp(x)
```
