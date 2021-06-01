#include <QPainter>
#include <QBrush>
#include "color_view.h"

color_view::color_view(QWidget *parent) : QWidget(parent)
{

}

void color_view::set_color(const QColor &color)
{
    widget_color = color;

    update();
}

QColor color_view::get_color()
{
    return widget_color;
}

void color_view::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.setPen(QPen(QColor(0, 0, 0)));
    painter.setBrush(QBrush(this->widget_color));

    painter.drawRect(0, 0, this->width(), this->height());
}
