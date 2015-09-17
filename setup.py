from distutils.core import setup
from distutils.extension import Extension
import numpy as np

try:
    from Cython.Distutils.build_ext import build_ext
    src = ['sselogsumexp.pyx', 'src/logsumexp.c']
except ImportError:
    from distutils.command.build_ext import build_ext
    src = ['sselogsumexp.c', 'src/logsumexp.c']

ext = Extension("sselogsumexp", src,
    include_dirs=[np.get_include(), 'src'],
    extra_compile_args=['-msse2'])

setup(name='sselogsumexp',
    author='Robert McGibbon',
    author_email='rmcgibbo@gmail.com',
    #url = "http://github.com/rmcgibbo/ftz",
    #description=DOCLINES[0],
    #long_description="\n".join(DOCLINES[2:]),
    version='0.1',
    license='BSD',
    cmdclass={'build_ext': build_ext},
    include_dirs = [np.get_include()],
    ext_modules = [ext]
)
