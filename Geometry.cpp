#include "Geometry.h"
#include <cmath>
#include <ctgmath>
const double pi = 2. * atan2(1., 0.);
double to_radians(double theta_d)
{
	return theta_d * pi / 180.0;
}

double to_degrees(double theta_r)
{
	return theta_r * 180.0 / pi;
}
// construct a Cartesian_vector from a Polar_vector
Cartesian_vector::Cartesian_vector(const Polar_vector& pv) {
	delta_x = pv.r * cos(pv.theta);
	delta_y = pv.r * sin(pv.theta);
}
Cartesian_vector::Cartesian_vector()
{
	delta_x = 0.0;
	delta_y = 0.0;
}
void Cartesian_vector::operator=(const Polar_vector& pv)
{
	delta_x = pv.r * cos(pv.theta);
	delta_y = pv.r * sin(pv.theta);
}
// construct a Polar_vector from a Cartesian_vector
Polar_vector::Polar_vector(const Cartesian_vector& cv) {
	r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
	/* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
	theta = atan2(cv.delta_y, cv.delta_x);
	if (theta < 0.)
		theta = 2. * pi + theta; // normalize theta positive
}
Polar_vector::Polar_vector()
{
	r = 0.0;
	theta = 0.0;
}
void Polar_vector::operator=(const Cartesian_vector& cv)
{
	r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
	/* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
	theta = atan2(cv.delta_y, cv.delta_x);
	if (theta < 0.)
		theta = 2. * pi + theta; // normalize theta positive
}

Point::Point(double x, double y) : x(x), y(y)
{
}

Point::Point()
{
	x = 0.0;
	y = 0.0;
}

void Point::print() const
{
	cout << setprecision(2) << fixed << "(" << x << ", " << y << ")";
}

bool Point::operator==(const Point & rhs)
{
	return x == rhs.x && y == rhs.y;
}

void Point::operator=(const Point p1) {
    x = p1.x;
    y = p1.y;
}

double Point::getDistance(Point p1) {
    return sqrt(pow(x - p1.x, 2) + pow(y - p1.y, 2));
}


double time_hm::operator-(time_hm t1) {
    return  (hours - t1.hours) + (double) (minutes - t1.minutes)/60;
}

bool time_hm::operator>(time_hm t1) {
    if(hours > t1.hours)
        return true;
    else if(hours < t1.hours)
        return false;
    else
        return minutes > t1.minutes;
}

bool time_hm::operator<(time_hm t1) {
    if(hours < t1.hours)
        return true;
    else if(hours > t1.hours)
        return false;
    else
        return minutes < t1.minutes;

}

time_hm::time_hm(int h, int m) {
    hours = h;
    minutes = m;
}

time_hm::time_hm() {
    hours = 0;
    minutes = 0;
}

void time_hm::print() {
    cout<< hours<<":"<<minutes;
}

