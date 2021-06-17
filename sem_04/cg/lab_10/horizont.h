#ifndef HORIZONT_H
#define HORIZONT_H

#define EPS 1e-6
#define OFFSET 0.05
#define DRAW_COLOR QColor(0, 0, 0)

#include <math.h>
#include <vector>

static inline double f0(double x, double z)
{
    return cos(x) * sin(z);
}

static inline double f1(double x, double z)
{
    return exp(sin(sqrt(x * x + z * z)));
}

static inline double f2(double x, double z)
{
    return sqrt(fabs(x * x - 2 * z));
}

static inline double f3(double x, double z)
{
    return sin(x) * sin(z);
}

static inline double f4(double x, double z)
{
    return cos(x) * cos(z);
}

typedef double (*surf_func_t)(double, double);

#include <QObject>
#include <QString>

#include "figures.h"
#include "canvas.h"

class horizont : public QObject
{
    Q_OBJECT

public:
    explicit horizont(QObject *parent = nullptr);
    ~horizont() = default;

    void find_horizonts(canvas &field) const;

public slots:
    void set_func_index(int ind);
    void set_xmin(QString x);
    void set_xmax(QString x);
    void set_xstep(double step);
    void set_zmin(QString z);
    void set_zmax(QString z);
    void set_zstep(double step);
    void set_xangle(int angle);
    void set_yangle(int angle);
    void set_zangle(int angle);

private:
    void find_limits(double &xmin_conv, double &xmax_conv, double &ymin, double &ymax) const;
    void find_scale_coefs(long &xc, long &yc, long &k, const canvas &field) const;
    void convert_coords(double &x, double &y, long xc, long yc, long k) const;
    void rotate_x(double &y, double &z) const;
    void rotate_y(double &x, double &z) const;
    void rotate_z(double &x, double &y) const;
    void rotate(double &x, double & y, double & z) const;
    void edge_handling(long &xprev, long &yprev, std::vector<long> &top, std::vector<long> &bottom,
                       long x, long y) const;
    void is_visible(long &flag, long x, long y,
                    const std::vector<long> &top, const std::vector<long> &bottom) const;
    void hor(std::vector<long> &top, std::vector<long> &bottom, long x1, long y1, long x2, long y2) const;
    void find_inter(long &xi, long &yi, long x1, long y1, long x2, long y2,
                    const std::vector<long> &hor) const;

private:
    int func_index = 0;

    double xmin = -5;
    double xmax = 5;
    double xstep = 0.10;

    double zmin = -5;
    double zmax = 5;
    double zstep = 0.10;

    double xangle = 0;
    double yangle = 0;
    double zangle = 0;

    std::vector<surf_func_t> funcs;
};

#endif // HORIZONT_H
