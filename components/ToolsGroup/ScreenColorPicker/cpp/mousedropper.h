#ifndef GROUP_TOOLSGROUP_SCREENCOLORPICKER_CPP_MOUSEDROPPER_H_
#define GROUP_TOOLSGROUP_SCREENCOLORPICKER_CPP_MOUSEDROPPER_H_

#include <QMouseEvent>
#include <QWidget>
#include <QDebug>
#include <QTimer>
class MouseDropper : public QWidget
{
    Q_OBJECT
public:
    explicit MouseDropper(QWidget *parent = nullptr);
    QColor getColor() const;

private:
    QColor color;
protected:
    void paintEvent(QPaintEvent *e);

};

#endif//GROUP_TOOLSGROUP_SCREENCOLORPICKER_CPP_MOUSEDROPPER_H_
