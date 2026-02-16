#include "colorpicker.h"

#include <QApplication>
#include <QGuiApplication>
#include <QPainter>
#include <QScreen>

ColorPicker::ColorPicker(QWidget *parent)
    : QWidget( parent )
    , mousedropper( new MouseDropper( this ) )
{
    resize( QGuiApplication::primaryScreen()->size() );
    setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint ); // 设置为无边框窗口
    setAttribute( Qt::WA_TranslucentBackground );
    setCursor( QCursor( QPixmap( "qrc:/ColorPickerPen.png" ), 0, 19 ) );
}

void ColorPicker::paintEvent(QPaintEvent *e)
{
    Q_UNUSED( e );

    QPainter painter( this );
    painter.fillRect( rect(), QColor( 255, 255, 255, 1 ) );
}

void ColorPicker::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED( e );

    emit colorSelect( mousedropper->getColor() );
    close();
}
