#include <math.h>
#include <time.h>
#include <stack>
#include <QSize>
#include <QWidget>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include "polygon.h"

polygon::polygon(const QColor &fg, const QColor &bg, const QColor &paint_col)
    :fg(fg), bg(bg), paint_col(paint_col)
{
}

void polygon::draw(QPainter &painter) const
{
    painter.setPen(QColor(0, 0, 0));
    for (polygon_fig::point *point : points)
    {
        QString text("(");
        text.append(QString::number(point->x));
        text.append(", ");
        text.append(QString::number(point->y));
        text.append(")");
        painter.drawText(point->x - 5, point->y - 10, text);
    }

    painter.setPen(QPen(fg));
    for (polygon_fig::edge edge: edges)
    {
        painter.drawLine(edge.p1->x, edge.p1->y, edge.p2->x, edge.p2->y);
    }

}

void polygon::find_extrems(polygon_fig::point &min, polygon_fig::point &max) const
{
    min.x = points[0]->x;
    min.y = points[0]->y;
    max.x = points[0]->x;
    max.y = points[0]->y;

    for (polygon_fig::point *p : points)
    {
        if (p->x < min.x)
            min.x = p->x;
        else if (p->x > max.x)
            max.x = p->x;
        if (p->y < min.y)
            min.y = p->y;
        else if (p->y > max.y)
            max.y = p->y;
    }
}

void polygon::paint_sleep(size_t delay)
{
    QTime end = QTime::currentTime().addMSecs(delay);
    while (QTime::currentTime() < end)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
    }
}

void polygon::set_seed_ptr(const polygon_fig::point &ptr)
{
    seed_ptr = ptr;
}

void polygon::sort_edges_points()
{
    for (polygon_fig::edge &edge : edges)
    {
        if (edge.p1->y > edge.p2->y)
        {
            polygon_fig::point *temp = edge.p1;
            edge.p1 = edge.p2;
            edge.p2 = temp;
        }
    }
}

void polygon::paint(QPainter &painter, QImage *image, size_t delay, QWidget *widget)
{
    polygon_fig::point min, max;
    find_extrems(min, max);

    long xp = min.x + (max.x - min.x) / 2;

    sort_edges_points();

    for (polygon_fig::edge edge: edges)
    {
        if (edge.p2->y == edge.p1->y)
            continue;

        double dx = (double) (edge.p2->x - edge.p1->x) / fabs(edge.p2->y - edge.p1->y);

        double x = edge.p1->x;

        for (long y = edge.p1->y; y != edge.p2->y; y += 1, x += dx)
        {
            if (y == min.y || y == max.y)
                continue;

            long xstart, xfinish;
            if (x < xp)
            {
                xstart = round(x);
                xfinish = xp;
            }
            else
            {
                xstart = xp;
                xfinish = round(x);
            }

            for (long xi = xstart; xi < xfinish; xi++)
            {
                if (image->pixelColor(xi, y) == paint_col)
                    painter.setPen(bg);
                else
                    painter.setPen(paint_col);

                painter.drawPoint(xi, y);
            }

            if (delay)
            {
                paint_sleep(delay);
                widget->update();
            }
        }

    }
}

void polygon::seed_paint(QPainter &painter, QImage *image, size_t delay, QWidget *widget)
{
    painter.setPen(paint_col);
    std::stack<polygon_fig::point> stk;
    stk.push(seed_ptr);

    while (!stk.empty())
    {
        polygon_fig::point p = stk.top();
        stk.pop();
        painter.drawPoint(p.x, p.y);

        polygon_fig::point tmp = p;

        tmp.x++;
        while (image->pixelColor(tmp.x, tmp.y) != fg)
        {
            painter.drawPoint(tmp.x, tmp.y);
            tmp.x++;
        }
        long right = tmp.x - 1;

        tmp.x = p.x - 1;
        while (image->pixelColor(tmp.x, tmp.y) != fg)
        {
            painter.drawPoint(tmp.x, tmp.y);
            tmp.x--;
        }
        long left = tmp.x + 1;

        tmp.y = p.y - 1;
        for (size_t i = 0; i < 2; i++)
        {
            tmp.x = left;
            while (tmp.x <= right)
            {
                bool found = false;
                while (image->pixelColor(tmp.x, tmp.y) != paint_col &&
                       image->pixelColor(tmp.x, tmp.y) != fg &&
                       tmp.x <= right)
                {
                    found = true;
                    tmp.x++;
                }

                if (found)
                {
                    if (image->pixelColor(tmp.x, tmp.y) != paint_col &&
                       image->pixelColor(tmp.x, tmp.y) != fg)
                        stk.push(tmp);
                    else
                        stk.push(polygon_fig::point(tmp.x - 1, tmp.y));
                }


                while ((image->pixelColor(tmp.x, tmp.y) == paint_col ||
                       image->pixelColor(tmp.x, tmp.y) == fg) &&
                       tmp.x <= right)
                {
                    tmp.x++;
                }
            }
            tmp.y = p.y + 1;
        }
        if (delay)
        {
            paint_sleep(delay);
            widget->update();
        }

    }
}

double polygon::paint_time()
{
    polygon_fig::point min, max;
    find_extrems(min, max);

    QImage *img = new QImage(QSize(max.x + 10, max.y + 10), QImage::Format_RGBA64);
    QPainter painter(img);

    clock_t clk = clock();
    paint(painter, img, 0, nullptr);
    clk = clock() - clk;

    return (double) clk / CLOCKS_PER_SEC;
}

double polygon::seed_paint_time()
{
    polygon_fig::point min, max;
    find_extrems(min, max);

    QImage *img = new QImage(QSize(max.x + 10, max.y + 10), QImage::Format_RGBA64);
    QPainter painter(img);
    draw(painter);

    clock_t clk = clock();
    seed_paint(painter, img, 0, nullptr);
    clk = clock() - clk;

    return (double) clk / CLOCKS_PER_SEC;
}

void polygon::add_point(polygon_fig::point *point)
{
    points.push_back(point);

    if (new_edge_state)
    {
        edges.push_back(polygon_fig::edge(points[points.size() - 1], points[points.size() - 2]));
    }

    new_edge_state = true;
}

void polygon::add_hole()
{
    close();

    new_edge_state = false;

    start_pos = points.size();
}

void polygon::close()
{
    if (points.size() != edges.size())
        edges.push_back(polygon_fig::edge(points[points.size() - 1], points[start_pos]));
}
