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
    $$PWD/include/JQGuetzli/

HEADERS *= \
    $$PWD/include/JQGuetzli/*.h

SOURCES *= \
    $$PWD/src/JQGuetzli/*.cpp \
    $$PWD/src/JQGuetzli/guetzli/*.cc \
    $$PWD/src/JQGuetzli/butteraugli/*.cc

LIBS *= \
    $$PWD/bin/JQGuetzli/x86_64/macx-clang/gflags/libgflags.2.2.0.dylib \
    $$PWD/bin/JQGuetzli/x86_64/macx-clang/png/libpng16.16.dylib
