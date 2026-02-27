var items = [
    { bookmarkName: "首页", titleName: "首页", qrcLocation: "qrc:/Welcome/Welcome.qml", children: [ ] },
    {
        bookmarkName: "文本类",
        titleName: "文本类",
        qrcLocation: "",
        children: [
            { bookmarkName: "UTF-16转换", titleName: "UTF-16转换", qrcLocation: "qrc:/Utf16Transform/Utf16Transform.qml" },
            { bookmarkName: "RGB转16进制", titleName: "RGB转16进制", qrcLocation: "qrc:/RgbStringTransform/RgbStringTransform.qml" },
            { bookmarkName: "大小写转换", titleName: "大小写转换", qrcLocation: "qrc:/CaseTransform/CaseTransform.qml" },
            { bookmarkName: "密码随机器", titleName: "密码随机器", qrcLocation: "qrc:/RandomPassword/RandomPassword.qml" },
            { bookmarkName: "UUID生成器", titleName: "UUID生成器", qrcLocation: "qrc:/RandomUuid/RandomUuid.qml" },
            { bookmarkName: "URL转码", titleName: "URL转码", qrcLocation: "qrc:/UrlEncode/UrlEncode.qml" },
            { bookmarkName: "JSON格式化", titleName: "JSON格式化", qrcLocation: "qrc:/JsonFormat/JsonFormat.qml" },
            { bookmarkName: "字符串排序", titleName: "字符串排序", qrcLocation: "qrc:/StringSort/StringSort.qml" }
        ]
    },
    {
        bookmarkName: "计算类",
        titleName: "计算类",
        qrcLocation: "",
        children: [
            { bookmarkName: "HASH计算器", titleName: "HASH计算器", qrcLocation: "qrc:/HashCalculate/HashCalculate.qml" },
            { bookmarkName: "Unix时间戳转换", titleName: "Unix时间戳转换", qrcLocation: "qrc:/TimestampTransform/TimestampTransform.qml" },
            { bookmarkName: "二分法助手", titleName: "二分法助手", qrcLocation: "qrc:/BinarySearchAssistant/BinarySearchAssistant.qml" },
            { bookmarkName: "RSA密钥生成", titleName: "RSA密钥生成", qrcLocation: "qrc:/RsaKeyGenerate/RsaKeyGenerate.qml" },
            { bookmarkName: "RSA加解密", titleName: "RSA加解密", qrcLocation: "qrc:/RsaCrypt/RsaCrypt.qml" },
            { bookmarkName: "AES加解密", titleName: "AES加解密 & HMAC", qrcLocation: "qrc:/AesCrypt/AesCrypt.qml" },
            { bookmarkName: "文件哈希值", titleName: "文件哈希值", qrcLocation: "qrc:/FileHashCalculate/FileHashCalculate.qml" }
        ]
    },
    {
        bookmarkName: "图片类",
        titleName: "图片类",
        qrcLocation: "",
        children: [
            { bookmarkName: "图标生成器", titleName: "图标生成器", qrcLocation: "qrc:/IconMaker/IconMaker.qml" },
            { bookmarkName: "图标字体转PNG", titleName: "图标字体转PNG", qrcLocation: "qrc:/FontToPng/FontToPng.qml" },
            { bookmarkName: "PNG警告消除", titleName: "PNG警告消除", qrcLocation: "qrc:/PngWarningRemover/PngWarningRemover.qml" },
            { bookmarkName: "WebP图片制作器", titleName: "WebP图片制作器", qrcLocation: "qrc:/WebPMaker/WebPMaker.qml" },
            { bookmarkName: "PNG图片压缩", titleName: "PNG图片压缩", qrcLocation: "qrc:/PngOptimize/PngOptimize.qml" },
            { bookmarkName: "JPG图片压缩", titleName: "JPG图片压缩", qrcLocation: "qrc:/JpgOptimize/JpgOptimize.qml" }
        ]
    },
    {
        bookmarkName: "工具类",
        titleName: "工具类",
        qrcLocation: "",
        children: [
            { bookmarkName: "代码行数统计", titleName: "代码行数统计", qrcLocation: "qrc:/LinesStatistics/LinesStatistics.qml" },
            { bookmarkName: "批量替换", titleName: "批量替换", qrcLocation: "qrc:/BatchReplacement/BatchReplacement.qml" },
            { bookmarkName: "屏幕拾色器", titleName: "屏幕拾色器", qrcLocation: "qrc:/ScreenColorPicker/ScreenColorPicker.qml" }
        ]
    },
    {
        bookmarkName: "二维码类",
        titleName: "二维码类",
        qrcLocation: "",
        children: [
            { bookmarkName: "二维码生成器", titleName: "二维码生成器", qrcLocation: "qrc:/QRCodeMaker/QRCodeMaker.qml" },
            { bookmarkName: "条形码生成器", titleName: "条形码生成器", qrcLocation: "qrc:/BarcodeMaker/BarcodeMaker.qml" },
            { bookmarkName: "二维码识别器", titleName: "二维码识别器", qrcLocation: "qrc:/QRCodeReader/QRCodeReader.qml" }
        ]
    },
    {
        bookmarkName: "Qt相关",
        titleName: "Qt相关",
        qrcLocation: "",
        children: [
            { bookmarkName: "PROPERTY生成", titleName: "PROPERTY生成", qrcLocation: "qrc:/PropertyMaker/PropertyMaker.qml" },
            { bookmarkName: "CPP文件生成", titleName: "CPP文件生成", qrcLocation: "qrc:/CppFileMaker/CppFileMaker.qml" }
        ]
    }
];
