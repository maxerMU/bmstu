#ifndef POINT_H
#define POINT_H

class point
{
public:
    point();
    point(double x, double y, double z);

    double get_x() const;
    void set_x(double x);

    double get_y() const;
    void set_y(double y);

    double get_z() const;
    void set_z(double z);

    void move(const point &move);
    void scale(const point &center, const point &scale);
    void rotate(const point &center, const point &rotate);

private:
    double x;
    double y;
    double z;

    void rotate_xy(double angle);
    void rotate_xz(double angle);
    void rotate_yz(double angle);
};

#endif // POINT_H
