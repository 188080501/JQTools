#
#   This file is part of JQLibrary
#
#   Library introduce: https://github.com/188080501/JQLibrary
#
#   Copyright: Jason
#
#   Contact email: Jason@JasonServer.com
#
#   GitHub: https://github.com/188080501/
#

INCLUDEPATH *= \
    $$PWD/include/JQQRCodeReader/

# 定义JQQRCodeReader的版本
JQQRCODEREADER_VERSIONSTRING = 1.6

# 判断Qt版本，小于等于5.6就报错
lessThan( QT_MAJOR_VERSION, 5 ) | lessThan( QT_MINOR_VERSION, 7 ) {
    error( JQQRCodeReader request minimum Qt version is 5.7.0 )
}

# 准备bin库目录
JQQRCODEREADER_BIN_NO1_DIR = JQQRCodeReader$$JQQRCODEREADER_VERSIONSTRING/Qt$$[QT_VERSION]
JQQRCODEREADER_BIN_NO2_DIR = $$QT_ARCH
JQQRCODEREADER_BIN_NO3_DIR = $$[QMAKE_XSPEC]
JQQRCODEREADER_BIN_NO3_DIR ~= s/g\+\+/gcc

# 根据编译参数，追加static名称
contains( CONFIG, static ) {
    JQQRCODEREADER_BIN_NO3_DIR = $$JQQRCODEREADER_BIN_NO3_DIR-static
}

JQQRCODEREADER_BIN_DIR = $$PWD/bin/$$JQQRCODEREADER_BIN_NO1_DIR/$$JQQRCODEREADER_BIN_NO2_DIR/$$JQQRCODEREADER_BIN_NO3_DIR
#message($$JQQRCODEREADER_BIN_DIR)

# 若bin目录不存在则创建
!exists( $$JQQRCODEREADER_BIN_DIR ) {
    mkpath( $$JQQRCODEREADER_BIN_DIR )
}

# 根据不同系统，选择合适的名字
unix | linux | mingw {
    CONFIG( debug, debug | release ) {
        JQQRCODEREADER_LIB_FILENAME = libJQQRCodeReaderd.a
    }
    CONFIG( release, debug | release ) {
        JQQRCODEREADER_LIB_FILENAME = libJQQRCodeReader.a
    }
}
else: msvc {
    CONFIG( debug, debug | release ) {
        JQQRCODEREADER_LIB_FILENAME = JQQRCodeReaderd.lib
    }
    CONFIG( release, debug | release ) {
        JQQRCODEREADER_LIB_FILENAME = JQQRCodeReader.lib
    }
}
else {
    error( unknow platfrom )
}

# 生成bin路径
JQQRCODEREADER_LIB_FILEPATH = $$JQQRCODEREADER_BIN_DIR/$$JQQRCODEREADER_LIB_FILENAME

# 如果未指定编译模式，并且本地存在bin文件，那么使用bin文件
!equals(JQQRCODEREADER_COMPILE_MODE, SRC) {
    exists($$JQQRCODEREADER_LIB_FILEPATH) {
        JQQRCODEREADER_COMPILE_MODE = LIB
    }
    else {
        JQQRCODEREADER_COMPILE_MODE = SRC
    }
}

equals(JQQRCODEREADER_COMPILE_MODE,SRC) {

    DEFINES *= \
        ZXING_ICONV_CONST \
        DISABLE_LIBRARY_FEATURES \
        NO_ICONV

    INCLUDEPATH *= \
        $$PWD/src/JQQRCodeReader/zxing

    HEADERS *= \
        $$PWD/include/JQQRCodeReader/JQQRCodeReader.h

    SOURCES *= \
        $$PWD/src/JQQRCodeReader/JQQRCodeReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/bigint/BigInteger.cc \
        $$PWD/src/JQQRCodeReader/zxing/bigint/BigIntegerAlgorithms.cc \
        $$PWD/src/JQQRCodeReader/zxing/bigint/BigIntegerUtils.cc \
        $$PWD/src/JQQRCodeReader/zxing/bigint/BigUnsigned.cc \
        $$PWD/src/JQQRCodeReader/zxing/bigint/BigUnsignedInABase.cc \
        $$PWD/src/JQQRCodeReader/zxing/zxing/aztec/decoder/Decoder1.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/aztec/detector/Detector1.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/aztec/AztecDetectorResult.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/aztec/AztecReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/detector/MonochromeRectangleDetector.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/detector/WhiteRectangleDetector.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/reedsolomon/GenericGF.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/reedsolomon/GenericGFPoly.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/reedsolomon/ReedSolomonDecoder.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/reedsolomon/ReedSolomonException.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/BitArray.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/BitArrayIO.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/BitMatrix.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/BitSource.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/CharacterSetECI.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/DecoderResult.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/DetectorResult.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/GlobalHistogramBinarizer.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/GreyscaleLuminanceSource.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/GreyscaleRotatedLuminanceSource.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/GridSampler.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/HybridBinarizer.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/IllegalArgumentException.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/PerspectiveTransform.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/Str.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/common/StringUtils.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/BitMatrixParser1.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/DataBlock1.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/DecodedBitStreamParser1.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/Decoder2.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/detector/CornerPoint.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/detector/Detector2.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/detector/DetectorException.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/DataMatrixReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/Version1.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/multi/qrcode/detector/MultiDetector.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/multi/qrcode/detector/MultiFinderPatternFinder1.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/multi/qrcode/QRCodeMultiReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/multi/ByQuadrantReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/multi/GenericMultipleBarcodeReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/multi/MultipleBarcodeReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/CodaBarReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/Code128Reader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/Code39Reader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/Code93Reader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/EAN13Reader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/EAN8Reader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/ITFReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/MultiFormatOneDReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/MultiFormatUPCEANReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/OneDReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/OneDResultPoint.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/UPCAReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/UPCEANReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/oned/UPCEReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/ec/ErrorCorrection.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/ec/ModulusGF.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/ec/ModulusPoly.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/BitMatrixParser2.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/DecodedBitStreamParser2.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/decoder/Decoder3.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/detector/Detector3.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/detector/LinesSampler.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/pdf417/PDF417Reader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/BitMatrixParser3.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/DataBlock2.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/DataMask.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/DecodedBitStreamParser3.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/Decoder4.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/decoder/Mode.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/AlignmentPattern.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/AlignmentPatternFinder.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/Detector4.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/FinderPattern.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/FinderPatternFinder2.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/detector/FinderPatternInfo.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/ErrorCorrectionLevel.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/FormatInformation.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/QRCodeReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/qrcode/Version2.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/BarcodeFormat.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/Binarizer.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/BinaryBitmap.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/ChecksumException.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/DecodeHints.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/Exception.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/FormatException.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/InvertedLuminanceSource.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/LuminanceSource.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/MultiFormatReader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/Reader.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/Result.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/ResultIO.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/ResultPoint.cpp \
        $$PWD/src/JQQRCodeReader/zxing/zxing/ResultPointCallback.cpp

    win32-msvc* {

        INCLUDEPATH *= \
            $$PWD/src/JQQRCodeReader/zxing/win32/zxing \
            $$PWD/src/JQQRCodeReader/zxing/win32/zxing/msvc

        SOURCES *= \
            $$PWD/src/JQQRCodeReader/zxing/win32/zxing/win_iconv.c
    }
}
else : equals(JQQRCODEREADER_COMPILE_MODE,LIB) {

    LIBS *= $$JQQRCODEREADER_LIB_FILEPATH
}
else {
    error(unknow JQQRCODEREADER_COMPILE_MODE: $$JQQRCODEREADER_COMPILE_MODE)
}

# 判断是否要引入JQQRCodeReader的qml扩展部分
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

DEFINES *= JQQRCODEREADER_COMPILE_MODE_STRING=\\\"$$JQQRCODEREADER_COMPILE_MODE\\\"
DEFINES *= JQQRCODEREADER_VERSIONSTRING=\\\"$$JQQRCODEREADER_VERSIONSTRING\\\"
