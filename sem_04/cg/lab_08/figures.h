#ifndef FIGURES_H
#define FIGURES_H

#include <QColor>
#include <QPainter>
#include <vector>

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
    explicit point(const QColor &fg = QColor(0, 0, 0))
        :Figure(fg)
    {
    }

    point(double x, double y, const QColor &fg = QColor(0, 0, 0))
        :Figure(fg), x(x), y(y)
    {
    }
    virtual void paint(QPainter &painter) const override;

    long get_x() const;
    long get_y() const;
    void set_x(long x);
    void set_y(long y);

    point operator-(const point& p);
    point operator+(const point& p);
    point operator *(double num);
    point operator/(double num);
    bool operator<(double eps);

private:
    long x = 0;
    long y = 0;
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
    point get_vec() const;
    void set_p1(const point &p);
    void set_p2(const point &p);
    point find_distance(const point &a) const;

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

class polygon : public Figure
{
public:
    explicit polygon(const QColor &fg)
        :Figure(fg)
    {
    }

    virtual void paint(QPainter &painter) const override;

    void close();
    void add_p1(long x, long y);
    void add_p2(long x, long y);
    void render_p2(long x, long y);
    long is_convex() const;
    std::vector<line> get_lines() const;

private:
    std::vector<line> lines;
};

#endif // FIGURES_H
