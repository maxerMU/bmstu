#ifndef COLOR_VIEW_H
#define COLOR_VIEW_H

#include <QWidget>
#include <QColor>

class color_view : public QWidget
{
    Q_OBJECT
public:
    explicit color_view(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void set_color(const QColor &color);
    void get_color(QColor &color);

private:
    QColor widget_color = QColor(255, 255, 255);

signals:

};

#endif // COLOR_VIEW_H
