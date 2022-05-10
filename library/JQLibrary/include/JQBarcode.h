/*
    This file is part of JQLibrary

    Copyright: Jason and others

    Contact email: 188080501@qq.com

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef JQLIBRARY_JQBARCODE_H_
#define JQLIBRARY_JQBARCODE_H_

// Qt lib import
#include <QImage>

class JQBarcode
{
public:
    static qint64 makeNumber(const qint64 &rawNumebr);

    static QImage makeBarcode(const qint64 &number);

private:
    static void paintByteA(QImage &image, const int &number, const int &pos);

    static void paintByteB(QImage &image, const int &number, const int &pos);

    static void paintByteC(QImage &image, const int &number, const int &pos);

    static void paintLines(QImage &image, const QString &key, const int &pos, const int &len = 100);

    static void paintLine(QImage &image, const bool &black, const int &pos, const int &len = 100);
};

#endif//JQLIBRARY_JQBARCODE_H_
