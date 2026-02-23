# JQTools

JQTools（Jason Qt Tools）是一个基于 Qt & QML & C++ 开发的开源工具集合，聚焦于开发过程中的高频小功能。

- GitHub: https://github.com/188080501/JQTools
- 最新版下载: https://github.com/188080501/JQTools/releases/latest
- 问题反馈 & 功能建议: https://github.com/188080501/JQTools/issues

## 项目状态（2026）

项目正在进行重构与升级。

- 项目始于 2016 年，当前正在进行十年版本重构。
- 重构前最后一个稳定版本: [V26.2.14](https://github.com/188080501/JQTools/releases/tag/V26.2.14)
- 新功能与重构代码优先在 `develop` 分支推进，稳定后再合并至 `master`。

## 界面预览

![](./doc/JQToolsPreview.png)

## 功能说明

### 文本类

- UTF16 转换  
  将字符串和 UTF-16 之间进行互转，例如将 `"中文"` 和 `"\u4E2D\u6587"` 互转。

- RGB 转 16 进制  
  将颜色数值和 HEX 颜色字符串（例如 `"#112233"`）互转。

- 大小写转换  
  文本转大写、文本转小写。

- 密码随机器  
  可以生成随机密码字符串，例如：`"Hau-eqS-5EC-"`。

- UUID 随机器  
  可以生成随机 UUID 字符串，例如：`"bff98ea4-b861-422a-8627-6eb6cbca8716"`。

- URL 转码  
  将字符串和编码后的 URL 之间进行互转，例如将 `"中文"` 和 `"%E4%B8%AD%E6%96%87"` 互转。

- JSON 格式化  
  可以将 JSON 内容进行格式化，可选压缩或者不压缩模式。

- 字符串排序  
  按行对字符串内容进行排序，支持升序和降序。

### 计算类

- HASH 计算器  
  计算常用的摘要值，如 SHA1、MD5。

- Unix 时间戳转换  
  Unix 时间戳与日期转换。

- 二分法助手  
  可以用二分法查找一个有序数组中的某个值。

- RSA 密钥生成  
  生成 RSA 公钥和私钥（PEM 格式），支持常见密钥位数选择。

- RSA 加解密  
  支持使用 RSA 公钥加密（输出 Base64 密文）和私钥解密（输入 Base64 密文）。

### 图片类

- 图标生成器  
  根据已有的 PNG/JPG/JPEG/BMP 图片，生成可以用于发布 App 的特定分辨率图片，例如 OSX 的 `icon_128x128@2x.png`。

- 图标字体转 PNG  
  将内置的 ttf 字体转换为 PNG，目前一共有 5555 个图标可供选择。

- PNG 警告消除  
  消除在 Qt 里，部分 PNG 图片在加载时控制台会报警告的问题。使用本工具可以将 PNG 图片进行转换，使用转换后的图片不会再报错。  

- WebP 图片制作器  
  可以将图片制作并导出为 WebP 格式。  

- PNG 图片压缩  
  基于 Zopfli 开发，用于压缩 PNG 图片，压缩是无损的。

- JPG 图片压缩  
  基于 Guetzli 开发，用于压缩 JPG 图片，压缩是有损的。

### 工具类

- 代码行数统计  
  可以统计文件中代码行数（`'\n'` 数量）。

- 批量替换  
  可以批量替换文件名或者文件内容中的特定关键字。

- 屏幕拾色器  
  可以拾取屏幕中某个点的颜色。

### 二维码类

- 二维码生成器  
  可以将文本生成二维码图片，并且保存为 PNG。

- 条形码生成器  
  可以将 EAN-13（需 13 位数字且 6 开头）生成条形码图片，并且保存为 PNG。

- 二维码识别器  
  可以将二维码识别成字符串。

### Qt 相关

- Q_PROPERTY 代码生成  
  可以根据 Q_PROPERTY 的内容生成代码。

- CPP 文件生成  
  生成 CPP 文件基本结构。

## 快速开始

### 方式一：直接使用发布版（推荐）

1. 打开 `Releases` 页面下载最新可执行文件。  
2. 解压后直接运行。

### 方式二：从源码构建

当前已验证环境：

- Windows 10/11
- Qt 5.15.2
- MSVC2019 64bit Kit

兼容性说明：

- 建议最低使用 Qt 5.15。
- Qt 6.7.2（含 WASM）正在逐步适配中，尚未全部完成。

本项目是标准 `qmake` 工程，无额外生成脚本或预处理步骤。

构建入口：

- 工程文件: `JQTools.pro`

#### 方式 A：使用 Qt Creator（推荐）

1. 打开 Qt Creator，选择 `File -> Open File or Project...`。
2. 选择仓库根目录下的 `JQTools.pro`。
3. 在 Kit 中选择 `Desktop Qt 5.15.2 MSVC2019 64bit`（或本机可用的等效 Kit）。
4. 点击“配置项目”后直接构建并运行。

#### 方式 B：使用命令行（qmake）

以下示例基于 `Qt 5.15.2 + MSVC2019 64bit`：

```powershell
mkdir build
cd build
qmake ..\JQTools.pro -spec win32-msvc "CONFIG+=release"
nmake
```

构建完成后，可执行文件通常位于 `build\release\`（具体以实际构建目录为准）。

## 依赖说明（Qt 与第三方库）

JQTools 的程序主体（界面、交互、功能编排）基于 Qt/QML/C++ 实现。  
当前仅在特定功能中引入少量第三方源码库，引用入口统一在 `JQTools.pro` -> `library/JQLibraryImport.pri`。

| 模块 | 第三方来源 | 主要用途 | 引用入口 |
| --- | --- | --- | --- |
| JQQRCodeReader | ZXing | 二维码/条码识别 | `library/JQLibrary/JQQRCodeReader.pri` |
| JQQRCodeWriter | qrencode | 二维码生成 | `library/JQLibrary/JQQRCodeWriter.pri` |
| JQZopfli | Zopfli + LodePNG | PNG 无损压缩及相关图片处理 | `library/JQLibrary/JQZopfli.pri` |
| JQGuetzli | Guetzli + Butteraugli | JPG 有损压缩 | `library/JQLibrary/JQGuetzli.pri` |
| JQMbedTLS | Mbed TLS | RSA 密钥生成与加解密 | `library/JQLibrary/JQMbedTLS.pri` |

补充说明：

- 上述第三方库均以内置源码方式随仓库管理，不需要额外安装对应第三方库。
- 通用能力（如 HASH 计算）优先使用 Qt 自带能力（如 `QCryptographicHash`）。

## 目录结构

```text
JQTools
├─ cpp/           # 应用入口与核心逻辑
├─ qml/           # 主界面与QML资源
├─ components/    # 各功能模块（文本、图片、二维码等）
├─ library/       # 三方库与基础库封装
├─ doc/           # 文档与预览图
└─ icon/          # 图标资源
```

## 参与贡献

欢迎通过以下方式参与项目：

1. 提交 Issue 反馈问题或需求。
2. 在 `develop` 分支提交 PR 参与改进。
3. 给项目点一个 Star 支持维护。

## License

See the [LICENSE](LICENSE.txt) file for license rights and limitations (MIT).
