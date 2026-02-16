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
    $$PWD/include/JQGuetzli/

HEADERS *= \
    $$PWD/include/JQGuetzli/JQGuetzli.h

SOURCES *= \
    $$PWD/src/JQGuetzli/JQGuetzli.cpp \
    $$PWD/src/JQGuetzli/guetzli/butteraugli_comparator.cc \
    $$PWD/src/JQGuetzli/guetzli/dct_double.cc \
    $$PWD/src/JQGuetzli/guetzli/debug_print.cc \
    $$PWD/src/JQGuetzli/guetzli/entropy_encode.cc \
    $$PWD/src/JQGuetzli/guetzli/fdct.cc \
    $$PWD/src/JQGuetzli/guetzli/gamma_correct.cc \
    $$PWD/src/JQGuetzli/guetzli/idct.cc \
    $$PWD/src/JQGuetzli/guetzli/jpeg_data.cc \
    $$PWD/src/JQGuetzli/guetzli/jpeg_data_decoder.cc \
    $$PWD/src/JQGuetzli/guetzli/jpeg_data_encoder.cc \
    $$PWD/src/JQGuetzli/guetzli/jpeg_data_reader.cc \
    $$PWD/src/JQGuetzli/guetzli/jpeg_data_writer.cc \
    $$PWD/src/JQGuetzli/guetzli/jpeg_huffman_decode.cc \
    $$PWD/src/JQGuetzli/guetzli/output_image.cc \
    $$PWD/src/JQGuetzli/guetzli/preprocess_downsample.cc \
    $$PWD/src/JQGuetzli/guetzli/processor.cc \
    $$PWD/src/JQGuetzli/guetzli/quality.cc \
    $$PWD/src/JQGuetzli/guetzli/quantize.cc \
    $$PWD/src/JQGuetzli/guetzli/score.cc \
    $$PWD/src/JQGuetzli/butteraugli/butteraugli.cc

