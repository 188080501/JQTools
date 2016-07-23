#
#   This file is part of JQLibrary
#
#   Copyright: Jason
#
#   Contact email: 188080501@qq.com
#
#   GNU Lesser General Public License Usage
#   Alternatively, this file may be used under the terms of the GNU Lesser
#   General Public License version 2.1 or version 3 as published by the Free
#   Software Foundation and appearing in the file LICENSE.LGPLv21 and
#   LICENSE.LGPLv3 included in the packaging of this file. Please review the
#   following information to ensure the GNU Lesser General Public License
#   requirements will be met: https://www.gnu.org/licenses/lgpl.html and
#   http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
#

CONFIG *= c++11
CONFIG *= c++14

INCLUDEPATH *= \
    $$PWD/include/JQZopfli/

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
