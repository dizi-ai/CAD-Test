#pragma once
#include <cmath>
#include <iostream>

struct Coordinates{
    double x = 0;
    double y = 0;
    double z = 0;
};

class Figure
{
protected:
    Figure()= default;
public:
    virtual Coordinates GetPoints(double)=0;
    virtual Coordinates derivative(double)=0;
    virtual void print(std::ostream& o) const =0;
    virtual double GetRadius() const {
    return -1;
    }
};

class Ellipse : public Figure {
private:
    double _radiusx;
    double _radiusy;
public:
    Ellipse(double radiusx, double radiusy): _radiusx(radiusx), _radiusy(radiusy), Figure(){}
    void print(std::ostream& o) const{
        o << "Ellipse with x_radius = " << _radiusx << " and y_radius = " << _radiusy << std::endl;
    }
    Coordinates GetPoints(double t) {
        // returning in x,y,z form
        return Coordinates{_radiusx * std::cos(t),
            _radiusy * std::sin(t), 0};
    }

    Coordinates derivative(double t) {
        // returning in x,y,z form
        return Coordinates{-1 * _radiusx * std::sin(t),
            _radiusy * std::cos(t), 0};
    }

};
std::ostream& operator<<(std::ostream& o, const Ellipse& e) {
    e.print(o);
    return o;
}

class Circle : public Figure {
private:
    double _radius;
public:
    Circle(double radius): _radius(radius), Figure(){}
    void print(std::ostream& o) const {
        o << "Circle with radius = " << GetRadius() << std::endl;
    }
    double GetRadius() const{
        return _radius;
    }
    Coordinates GetPoints(double t) {
        // returning in x,y,z form
        return Coordinates{_radius * std::cos(t),
            _radius * std::sin(t), 0};
    }
    Coordinates derivative(double t) {
        // returning in x,y,z form
        return Coordinates{-1 * _radius * std::sin(t),
            _radius * std::cos(t), 0};
    }
};
std::ostream& operator<<(std::ostream& o, const Circle& c) {
    c.print(o);
    return o;
}

class Helix : public Figure {
private:
    double _radius;
    double _step;
public:
    Helix(double radius, double step): _radius(radius), _step(step), Figure(){}
    void print(std::ostream& o) const{
        o << "Helix with radius = " << _radius <<" and step = " << _step << std::endl;
    }
    Coordinates GetPoints(double t) {
        // returning in x,y,z form
        return Coordinates{_radius * t * acos(t),
            _radius * t * asin(t), _step * t};  
    }
    Coordinates derivative(double t) {
        // returning in x,y,z form
        return Coordinates{_radius * (std::cos(t) - t * std::sin(t)),
            _radius * (asin(t) + t * acos(t)), _step};
    }
};
std::ostream& operator<<(std::ostream& o, const Helix& h) {
    h.print(o);
    return o;
}