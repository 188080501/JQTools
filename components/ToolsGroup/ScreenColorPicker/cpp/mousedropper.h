#ifndef MOUSEDROPPER_H
#define MOUSEDROPPER_H

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

#endif // MOUSEDROPPER_H
