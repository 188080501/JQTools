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
JQQRCODEREADER_VERSIONSTRING = 1.1

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
        $$PWD/src/JQQRCodeReader/zxing/zxing/datamatrix/decoder/DataMatrixDecodedBitSP.cpp \
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
