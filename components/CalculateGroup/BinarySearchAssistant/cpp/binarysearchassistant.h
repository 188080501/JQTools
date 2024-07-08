/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: shijie.chen

    Contact email: xingwozhonghua@126.com

    GitHub: https://github.com/xingwozhonghua126

    TODO:
        1. 调整控件间距，以改善用户界面的布局和可读性
        2. 编写过程记录显示功能 - 需要实现一个方法来记录每次猜测的数值，并将这些数值显示给用户。
        3. 对每个猜测后面可以追加备注框，记录在日志里面 - 提供用户输入备注的界面元素，并将备注与猜测数值一同记录。
        4. "更高"和"更低"不好理解，改成"目标在数和数之间" - 调整用户界面上的提示信息，使其更加直观易懂。

*/

#ifndef GROUP_CALCULATEGROUP_BINARYSEARCHASSISTANT_CPP_BINARYSEARCHASSISTANT_H_
#define GROUP_CALCULATEGROUP_BINARYSEARCHASSISTANT_CPP_BINARYSEARCHASSISTANT_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

#define BINARYSEARCHASSISTANT_INITIALIZA                                                                            \
{                                                                                                                   \
    qmlRegisterType<BinarySearchAssistant::Manage>("BinarySearchAssistant", 1, 0, "BinarySearchAssistantManage");   \
}

namespace BinarySearchAssistant
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    inline int guess() const { return m_guess; }

public slots:
    void startNewGame(int min, int max);

    void guessHigher();

    void guessLower();

signals:
    void guessChanged();

private:
    int m_min;
    int m_max;
    int m_guess;

    void updateGuess();
};

}

#endif//GROUP_CALCULATEGROUP_BINARYSEARCHASSISTANT_CPP_BINARYSEARCHASSISTANT_H_
