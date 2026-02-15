#ifndef COLORPICKER_H_
#define COLORPICKER_H_

#include "mousedropper.h"
#include <QWidget>

class ColorPicker : public QWidget
{
    Q_OBJECT
public:
    explicit ColorPicker(QWidget *parent = nullptr);
private:
    MouseDropper *mousedropper;
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
signals:
    void colorSelect(const QColor & c);
public slots:
};
#endif//COLORPICKER_H_
