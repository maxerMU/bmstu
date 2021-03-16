#ifndef METHODS_H
#define METHODS_H

#include <QPainter>
#include <QPoint>

typedef void (*draw_func_t)(QPainter &, const QPoint &, const QPoint &);

void lib(QPainter &painter, const QPoint &p1, const QPoint &p2);
void cda(QPainter &painter, const QPoint &p1, const QPoint &p2);
void brezenhem_real(QPainter &painter, const QPoint &p1, const QPoint &p2);

#endif // METHODS_H
