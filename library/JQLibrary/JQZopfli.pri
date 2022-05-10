#
#   This file is part of JQLibrary
#
#   Copyright: Jason and others
#
#   Contact email: 188080501@qq.com
#
#   Permission is hereby granted, free of charge, to any person obtaining
#   a copy of this software and associated documentation files (the
#   "Software"), to deal in the Software without restriction, including
#   without limitation the rights to use, copy, modify, merge, publish,
#   distribute, sublicense, and/or sell copies of the Software, and to
#   permit persons to whom the Software is furnished to do so, subject to
#   the following conditions:
#
#   The above copyright notice and this permission notice shall be
#   included in all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
#   LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
#   OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
#   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#


CONFIG *= c++11
CONFIG *= c++14

INCLUDEPATH *= \
    $$PWD/include/JQZopfli/ \
    $$PWD/include/JQZopfli/zopfli/ \
    $$PWD/include/JQZopfli/zopflipng/ \
    $$PWD/include/JQZopfli/zopflipng/lodepng/

HEADERS *= \
    $$PWD/include/JQZopfli/JQZopfli.h

SOURCES *= \
    $$PWD/src/JQZopfli/JQZopfli.cpp \
    $$PWD/src/JQZopfli/zopflipng/lodepng/lodepng.cpp \
    $$PWD/src/JQZopfli/zopflipng/lodepng/lodepng_util.cpp \
    $$PWD/src/JQZopfli/zopfli/blocksplitter.c \
    $$PWD/src/JQZopfli/zopfli/cache.c \
    $$PWD/src/JQZopfli/zopfli/deflate.c \
    $$PWD/src/JQZopfli/zopfli/gzip_container.c \
    $$PWD/src/JQZopfli/zopfli/hash.c \
    $$PWD/src/JQZopfli/zopfli/katajainen.c \
    $$PWD/src/JQZopfli/zopfli/lz77.c \
    $$PWD/src/JQZopfli/zopfli/squeeze.c \
    $$PWD/src/JQZopfli/zopfli/symbols.c \
    $$PWD/src/JQZopfli/zopfli/tree.c \
    $$PWD/src/JQZopfli/zopfli/util.c \
    $$PWD/src/JQZopfli/zopfli/zlib_container.c
