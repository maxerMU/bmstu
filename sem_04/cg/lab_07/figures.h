#ifndef FIGURES_H
#define FIGURES_H

#include <QColor>
#include <QPainter>

class Figure
{
public:
    Figure(const QColor &fg = QColor(0, 0, 0), const QColor &bg = QColor(255, 255, 255))
        :fg(fg), bg(bg)
    {
    }

    virtual void paint(QPainter &painter) const = 0;
    virtual ~Figure() {}

    void set_fg(const QColor &color) {fg = color;}
    void set_bg(const QColor &color) {bg = color;}

protected:
    QColor fg;
    QColor bg;
};

class point : public Figure
{
public:
    explicit point(const QColor &fg)
        :Figure(fg)
    {
    }

    point(double x, double y, const QColor &fg = QColor(0, 0, 0))
        :Figure(fg), x(x), y(y)
    {
    }
    virtual void paint(QPainter &painter) const override;

    double get_x() const;
    double get_y() const;
    void set_x(long x);
    void set_y(long y);

    point operator-(const point& p);
    point operator+(const point& p);
    point operator/(double num);
    bool operator<(double eps);

private:
    double x = 0;
    double y = 0;
};

class line : public Figure
{
public:
    explicit line(const QColor &fg)
        :Figure(fg), p1(fg), p2(fg)
    {
    }
    line(const QColor &fg, long x, long y)
        :Figure(fg), p1(point(x, y, fg)), p2(point(x, y, fg))
    {
    }

    virtual void paint(QPainter &painter) const override;

    point get_p1() const;
    point get_p2() const;
    void set_p1(const point &p);
    void set_p2(const point &p);

private:
    point p1;
    point p2;
};

class rectangle : public Figure
{
public:
    explicit rectangle(const QColor &fg)
        :Figure(fg), p1(fg), p2(fg)
    {
    }
    rectangle(const QColor &fg, long x, long y)
        :Figure(fg), p1(point(x, y, fg)), p2(point(x, y, fg))
    {
    }

    virtual void paint(QPainter &painter) const override;

    point get_p1() const;
    point get_p2() const;
    void set_p1(const point &p);
    void set_p2(const point &p);

    long get_top() const;
    long get_bottom() const;
    long get_right() const;
    long get_left() const;

private:
    point p1;
    point p2;
};

#endif // FIGURES_H
