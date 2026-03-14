import QtQuick 2.15
import QtQuick.Controls 2.15

TextField {
    id: jqDateTimeTextField
    width: 180
    height: 40
    leftPadding: 6
    rightPadding: 6
    readOnly: false
    selectByMouse: true
    inputMethodHints: Qt.ImhDigitsOnly
    color: (isValid || cursorVisible) ? "black" : "red"

    property bool changingText: false
    property bool isValid: true

    // 限制输入，只允许数字和特定的分隔符
    validator: RegularExpressionValidator {
        regularExpression: /^[0-9\-:\s]*$/
    }

    // 当文本发生变化时触发
    onTextChanged: {
        if (changingText)
            return;
        changingText = true;

        // 获取当前光标位置
        var cursorPosition = jqDateTimeTextField.cursorPosition;

        // 移除所有非数字字符
        var digits = text.replace(/\D/g, '');

        // 重新格式化文本
        var formattedText = formatDigits(digits);

        // 更新文本框内容并保持光标位置
        var delta = formattedText.length - text.length;
        text = formattedText;
        jqDateTimeTextField.cursorPosition = cursorPosition + delta;

        // 数据有效性校验
        isValid = validateDateTime(formattedText);

        changingText = false;
    }

    // 当用户按下回车键时，如果输入未完成，自动填充剩余部分
    onAccepted: {
        if (text.length < 19) {
            changingText = true;

            // 移除所有非数字字符
            var digits = text.replace(/\D/g, '');

            var totalDigits = 14;
            var digitsArray = new Array(totalDigits);

            // 将已输入的数字填充到数组中
            for (var i = 0; i < digits.length; i++) {
                digitsArray[i] = digits.charAt(i);
            }

            // 填充缺失的部分
            i = digits.length;
            while (i < totalDigits) {
                if (i === 4 || i === 6) { // 月份和日期的位置
                    digitsArray[i++] = '0';
                    if (i < totalDigits) {
                        digitsArray[i++] = '1';
                    }
                } else {
                    digitsArray[i++] = '0';
                }
            }

            // 重构数字字符串
            digits = digitsArray.join('');

            // 重新格式化文本
            var formattedText = formatDigits(digits);

            text = formattedText;
            changingText = false;

            // 重新校验数据有效性
            isValid = validateDateTime(formattedText);
        }
    }

    // 格式化数字为日期时间字符串的函数
    function formatDigits(digits) {
        var formattedText = '';
        var positions = [4, 6, 8, 10, 12]; // 分隔符插入位置
        var separators = ['-', '-', ' ', ':', ':']; // 分隔符列表
        var digitIndex = 0;

        for (var i = 0; i < digits.length && i < 14; i++) {
            formattedText += digits.charAt(digitIndex++);

            // 在指定位置插入分隔符
            if (positions.indexOf(i + 1) !== -1 && digitIndex < digits.length) {
                formattedText += separators[positions.indexOf(i + 1)];
            }
        }
        return formattedText;
    }

    // 校验日期时间字符串有效性的函数
    function validateDateTime(formattedText) {
        if (formattedText.length !== 19) {
            return false;
        }

        var dateParts = formattedText.split(/[- :]/);
        var year = parseInt(dateParts[0], 10);
        var month = parseInt(dateParts[1], 10);
        var day = parseInt(dateParts[2], 10);
        var hour = parseInt(dateParts[3], 10);
        var minute = parseInt(dateParts[4], 10);
        var second = parseInt(dateParts[5], 10);

        // 检查年份
        if (isNaN(year) || year < 1000 || year > 9999) {
            return false;
        }

        // 检查月份
        if (isNaN(month) || month < 1 || month > 12) {
            return false;
        }

        // 检查日期
        var maxDays = [31, (year % 4 === 0 && year % 100 !== 0 || year % 400 === 0) ? 29 : 28,
                       31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
        if (isNaN(day) || day < 1 || day > maxDays[month - 1]) {
            return false;
        }

        // 检查小时
        if (isNaN(hour) || hour < 0 || hour > 23) {
            return false;
        }

        // 检查分钟和秒
        if (isNaN(minute) || minute < 0 || minute > 59 ||
            isNaN(second) || second < 0 || second > 59) {
            return false;
        }

        return true;
    }
}
