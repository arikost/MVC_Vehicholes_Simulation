#ifndef MVC_VEHICHOLES_SIMULATION_GEOMETRY_H
#define MVC_VEHICHOLES_SIMULATION_GEOMETRY_H

#include <iostream>
#include <iomanip>
using namespace std;
// angle units conversion functions
double to_radians(double theta_d);
double to_degrees(double theta_r);
// class declarations
typedef struct time_hm{
    int hours;
    int minutes;
    time_hm(int, int);

    time_hm();
    void print();
    double operator-(time_hm t1);
    bool operator>(time_hm t1);
    bool operator<(time_hm t1);
}time_hm;

typedef struct Point {
	double x;
	double y;
	Point(double x, double y);
	Point();
	double getDistance(Point p1);
	void print() const;
	void operator=(const Point p1);
	bool operator==(const Point& rhs);
} Point;
struct Polar_vector;
typedef struct Cartesian_vector {
	Cartesian_vector(const struct Polar_vector & pv);
	Cartesian_vector();
	void operator=(const struct Polar_vector & pv);
	double delta_x;
	double delta_y;
} Cartesian_vector;
typedef struct Polar_vector {
	Polar_vector(const Cartesian_vector & cv);
	Polar_vector();
	void operator=(const Cartesian_vector & cv);
	double r;
	double theta;
} Polar_vector;
#endif //MVC_VEHICHOLES_SIMULATION_GEOMETRY_H
