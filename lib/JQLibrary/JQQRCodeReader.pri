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

INCLUDEPATH *= \
    $$PWD/include/JQQRCodeReader/

DEFINES *= \
    QZXING_LIBRARY \
    ZXING_ICONV_CONST \
    DISABLE_LIBRARY_FEATURES \
    NO_ICONV

INCLUDEPATH *= \
    $$PWD/src/JQQRCodeReader/QZXing \
    $$PWD/src/JQQRCodeReader/zxing

HEADERS *= \
    $$PWD/include/JQQRCodeReader/JQQRCodeReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/ZXing.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/IllegalStateException.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/InvertedLuminanceSource.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/ChecksumException.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/ResultPointCallback.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/ResultPoint.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/Result.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/ReaderException.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/Reader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/NotFoundException.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/MultiFormatReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/LuminanceSource.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/FormatException.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/Exception.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/DecodeHints.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/BinaryBitmap.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/Binarizer.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/BarcodeFormat.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/aztec/AztecReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/aztec/AztecDetectorResult.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/aztec/decoder/Decoder.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/aztec/detector/Detector.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/StringUtils.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/Str.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/Point.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/PerspectiveTransform.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/IllegalArgumentException.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/HybridBinarizer.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/GridSampler.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/GreyscaleRotatedLuminanceSource.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/GreyscaleLuminanceSource.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/GlobalHistogramBinarizer.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/DetectorResult.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/DecoderResult.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/Counted.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/CharacterSetECI.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/BitSource.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/BitMatrix.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/BitArray.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/Array.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/detector/MathUtils.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/detector/JavaMath.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/detector/WhiteRectangleDetector.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/detector/MonochromeRectangleDetector.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/reedsolomon/ReedSolomonException.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/reedsolomon/ReedSolomonDecoder.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/reedsolomon/GenericGFPoly.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/reedsolomon/GenericGF.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/Version.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/DataMatrixReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/Decoder.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/DecodedBitStreamParser.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/DataBlock.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/BitMatrixParser.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/detector/DetectorException.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/detector/Detector.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/detector/CornerPoint.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/UPCEReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/UPCEANReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/UPCAReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/OneDResultPoint.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/OneDReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/MultiFormatUPCEANReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/MultiFormatOneDReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/ITFReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/EAN13Reader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/EAN8Reader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/Code128Reader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/Code39Reader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/CodaBarReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/Code93Reader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/Version.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/QRCodeReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/FormatInformation.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/ErrorCorrectionLevel.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/Mode.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/Decoder.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/DecodedBitStreamParser.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/DataMask.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/DataBlock.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/BitMatrixParser.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/FinderPatternInfo.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/FinderPatternFinder.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/FinderPattern.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/Detector.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/AlignmentPatternFinder.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/AlignmentPattern.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/multi/MultipleBarcodeReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/multi/GenericMultipleBarcodeReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/multi/ByQuadrantReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/multi/qrcode/QRCodeMultiReader.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/multi/qrcode/detector/MultiDetector.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/ec/ErrorCorrection.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/ec/ModulusGF.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/ec/ModulusPoly.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/BitMatrixParser.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/DecodedBitStreamParser.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/Decoder.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/detector/Detector.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/detector/LinesSampler.h \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/PDF417Reader.h \
    $$PWD/src/JQQRCodeReader/zxing/bigint/NumberlikeArray.hh \
    $$PWD/src/JQQRCodeReader/zxing/bigint/BigUnsignedInABase.hh \
    $$PWD/src/JQQRCodeReader/zxing/bigint/BigUnsigned.hh \
    $$PWD/src/JQQRCodeReader/zxing/bigint/BigIntegerUtils.hh \
    $$PWD/src/JQQRCodeReader/zxing/bigint/BigIntegerLibrary.hh \
    $$PWD/src/JQQRCodeReader/zxing/bigint/BigIntegerAlgorithms.hh \
    $$PWD/src/JQQRCodeReader/zxing/bigint/BigInteger.hh

SOURCES *= \
    $$PWD/src/JQQRCodeReader/JQQRCodeReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/ResultIO.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/InvertedLuminanceSource.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/ChecksumException.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/ResultPointCallback.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/ResultPoint.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/Result.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/Reader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/MultiFormatReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/LuminanceSource.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/FormatException.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/Exception.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/DecodeHints.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/BinaryBitmap.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/Binarizer.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/BarcodeFormat.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/aztec/AztecReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/aztec/AztecDetectorResult.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/StringUtils.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/Str.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/PerspectiveTransform.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/IllegalArgumentException.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/HybridBinarizer.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/GridSampler.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/GreyscaleRotatedLuminanceSource.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/GreyscaleLuminanceSource.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/GlobalHistogramBinarizer.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/DetectorResult.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/DecoderResult.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/CharacterSetECI.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/BitSource.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/BitMatrix.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/BitArray.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/BitArrayIO.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/detector/WhiteRectangleDetector.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/detector/MonochromeRectangleDetector.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/reedsolomon/ReedSolomonException.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/reedsolomon/ReedSolomonDecoder.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/reedsolomon/GenericGFPoly.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/common/reedsolomon/GenericGF.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/DataMatrixReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/UPCEReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/UPCEANReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/UPCAReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/OneDResultPoint.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/OneDReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/MultiFormatUPCEANReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/MultiFormatOneDReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/ITFReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/EAN13Reader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/EAN8Reader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/Code128Reader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/Code39Reader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/CodaBarReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/oned/Code93Reader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/QRCodeReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/multi/MultipleBarcodeReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/multi/GenericMultipleBarcodeReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/multi/ByQuadrantReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/multi/qrcode/QRCodeMultiReader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/multi/qrcode/detector/MultiDetector.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/aztec/decoder/AztecDecoder.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/aztec/detector/AztecDetector.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/DataMatrixVersion.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/DataMatrixDecoder.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/DataMatrixBitMatrixParser.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/DataMatrixDataBlock.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/DataMatrixDecodedBitStreamParser.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/detector/DataMatrixCornerPoint.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/detector/DataMatrixDetector.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/detector/DataMatrixDetectorException.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/QRBitMatrixParser.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/QRDataBlock.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/QRDataMask.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/QRDecodedBitStreamParser.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/QRDecoder.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/QRMode.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/QRAlignmentPattern.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/QRAlignmentPatternFinder.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/QRDetector.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/QRFinderPattern.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/QRFinderPatternFinder.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/QRFinderPatternInfo.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/QRVersion.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/QRFormatInformation.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/QRErrorCorrectionLevel.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/ec/ErrorCorrection.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/ec/ModulusGF.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/ec/ModulusPoly.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/PDF417BitMatrixParser.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/PDF417DecodedBitStreamParser.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/PDF417Decoder.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/detector/PDF417Detector.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/detector/LinesSampler.cpp \
    $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/PDF417Reader.cpp \
    $$PWD/src/JQQRCodeReader/zxing/bigint/BigUnsignedInABase.cc \
    $$PWD/src/JQQRCodeReader/zxing/bigint/BigUnsigned.cc \
    $$PWD/src/JQQRCodeReader/zxing/bigint/BigIntegerUtils.cc \
    $$PWD/src/JQQRCodeReader/zxing/bigint/BigIntegerAlgorithms.cc \
    $$PWD/src/JQQRCodeReader/zxing/bigint/BigInteger.cc

win32-msvc* {

    INCLUDEPATH *= \
        $$PWD/src/JQQRCodeReader/zxing/win32/zxing \
        $$PWD/src/JQQRCodeReader/zxing/win32/zxing/msvc

    HEADERS *= \
        $$PWD/src/JQQRCodeReader/zxing/win32/zxing/msvc/stdint.h \
        $$PWD/src/JQQRCodeReader/zxing/win32/zxing/iconv.h

    SOURCES *= \
        $$PWD/src/JQQRCodeReader/zxing/win32/zxing/win_iconv.c
}

win32-g++ {

    INCLUDEPATH *= \
        $$PWD/src/JQQRCodeReader/zxing/win32/zxing

    HEADERS *= \
        $$PWD/src/JQQRCodeReader/zxing/win32/zxing/iconv.h

    SOURCES *= \
        $$PWD/src/JQQRCodeReader/zxing/win32/zxing/win_iconv.c
}

contains( QT, qml ) {

    contains(QT, concurrent) {

        contains(QT, multimedia) {

            HEADERS *= \
                $$PWD/include/JQQRCodeReader/JQQRCodeReaderForQml.h

            SOURCES *= \
                $$PWD/src/JQQRCodeReader/JQQRCodeReaderForQml.cpp

            RESOURCES *= \
                $$PWD/qml/JQQRCodeReaderQml.qrc

            QML_IMPORT_PATH *= \
                $$PWD/qml/

            PLUGINS *= \
                declarative_multimedia
        }
    }
}
