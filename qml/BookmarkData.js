function pushChild(children, bookmarkName, titleName, qrcLocation) {
    children.push({
                      bookmarkName: bookmarkName,
                      titleName: titleName,
                      qrcLocation: qrcLocation
                  });
}

function pushGroup(groups, bookmarkName, titleName, qrcLocation, children) {
    groups.push({
                    bookmarkName: bookmarkName,
                    titleName: titleName,
                    qrcLocation: qrcLocation,
                    children: children
                });
}

function itemsByPlatform(platformOs) {
    var isWasm = (platformOs === "wasm");
    var result = [];
    var children = [];

    result.push({
                    bookmarkName: "首页",
                    titleName: "首页",
                    qrcLocation: "qrc:/Welcome/Welcome.qml",
                    children: []
                });

    children = [];
    pushChild(children, "UTF-16转换", "UTF-16转换", "qrc:/Utf16Transform/Utf16Transform.qml");
    pushChild(children, "RGB转16进制", "RGB转16进制", "qrc:/RgbStringTransform/RgbStringTransform.qml");
    pushChild(children, "大小写转换", "大小写转换", "qrc:/CaseTransform/CaseTransform.qml");
    pushChild(children, "密码随机器", "密码随机器", "qrc:/RandomPassword/RandomPassword.qml");
    pushChild(children, "UUID生成器", "UUID生成器", "qrc:/RandomUuid/RandomUuid.qml");
    pushChild(children, "URL转码", "URL转码", "qrc:/UrlEncode/UrlEncode.qml");
    pushChild(children, "JSON格式化", "JSON格式化", "qrc:/JsonFormat/JsonFormat.qml");
    pushChild(children, "字符串排序", "字符串排序", "qrc:/StringSort/StringSort.qml");
    pushChild(children, "文本去重排序", "文本去重排序", "qrc:/TextDedupSort/TextDedupSort.qml");
    pushGroup(result, "文本类", "文本类", "", children);

    children = [];
    pushChild(children, "HASH计算器", "HASH计算器", "qrc:/HashCalculate/HashCalculate.qml");
    pushChild(children, "Unix时间戳转换", "Unix时间戳转换", "qrc:/TimestampTransform/TimestampTransform.qml");
    pushChild(children, "二分法助手", "二分法助手", "qrc:/BinarySearchAssistant/BinarySearchAssistant.qml");
    pushChild(children, "RSA密钥生成", "RSA密钥生成", "qrc:/RsaKeyGenerate/RsaKeyGenerate.qml");
    pushChild(children, "RSA加解密", "RSA加解密", "qrc:/RsaCrypt/RsaCrypt.qml");
    pushChild(children, "AES加解密", "AES加解密 & HMAC", "qrc:/AesCrypt/AesCrypt.qml");
    pushChild(children, "文件哈希值", "文件哈希值", "qrc:/FileHashCalculate/FileHashCalculate.qml");
    pushGroup(result, "计算类", "计算类", "", children);

    if (!isWasm) {
        children = [];
        pushChild(children, "图标生成器", "图标生成器", "qrc:/IconMaker/IconMaker.qml");
        pushChild(children, "图标字体转PNG", "图标字体转PNG", "qrc:/FontToPng/FontToPng.qml");
        pushChild(children, "PNG警告消除", "PNG警告消除", "qrc:/PngWarningRemover/PngWarningRemover.qml");
        pushChild(children, "WebP图片制作器", "WebP图片制作器", "qrc:/WebPMaker/WebPMaker.qml");
        pushChild(children, "PNG图片压缩", "PNG图片压缩", "qrc:/PngOptimize/PngOptimize.qml");
        pushChild(children, "JPG图片压缩", "JPG图片压缩", "qrc:/JpgOptimize/JpgOptimize.qml");
        pushGroup(result, "图片类", "图片类", "", children);
    }

    children = [];
    if (!isWasm) {
        pushChild(children, "代码行数统计", "代码行数统计", "qrc:/LinesStatistics/LinesStatistics.qml");
    }
    pushChild(children, "批量替换", "批量替换", "qrc:/BatchReplacement/BatchReplacement.qml");
    if (!isWasm) {
        pushChild(children, "屏幕拾色器", "屏幕拾色器", "qrc:/ScreenColorPicker/ScreenColorPicker.qml");
    }
    pushGroup(result, "工具类", "工具类", "", children);

    if (!isWasm) {
        children = [];
        pushChild(children, "二维码生成器", "二维码生成器", "qrc:/QRCodeMaker/QRCodeMaker.qml");
        pushChild(children, "条形码生成器", "条形码生成器", "qrc:/BarcodeMaker/BarcodeMaker.qml");
        pushChild(children, "二维码识别器", "二维码识别器", "qrc:/QRCodeReader/QRCodeReader.qml");
        pushGroup(result, "二维码类", "二维码类", "", children);
    }

    children = [];
    pushChild(children, "PROPERTY生成", "PROPERTY生成", "qrc:/PropertyMaker/PropertyMaker.qml");
    pushChild(children, "CPP文件生成", "CPP文件生成", "qrc:/CppFileMaker/CppFileMaker.qml");
    pushGroup(result, "Qt相关", "Qt相关", "", children);

    return result;
}

var items = itemsByPlatform((typeof Qt !== "undefined" && Qt.platform) ? Qt.platform.os : "");
