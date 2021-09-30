//
// Created by stephen on 9/26/21.
//

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <memory>

class Point
{
    public:
        Point(float x, float y, float z)
        {
            _x = x;
            _y = y;
            _z = z;
        }
        std::shared_ptr<Point> translateX(float distance)
        {
            return std::make_shared<Point>(_x+distance,_y,_z);
        }
        std::shared_ptr<Point> translateY(float distance)
        {
            return std::make_shared<Point>(_x,_y+distance,_z);
        }
        std::shared_ptr<Point> translateZ(float distance)
        {
            return std::make_shared<Point>(_x,_y,_z+distance);
        }
    public:
        float _x;
        float _y;
        float _z;
};

class Circle
{
    public:
        Circle(Point& center, float radius) : _center(0.0,0.0,0.0)
        {
            _center = center;
            _radius = radius;
        }
        std::shared_ptr<Circle> scale(float scale)
        {
            return std::make_shared<Circle>(_center, _radius*scale);
        }
    public:
        Point _center;
        float _radius;
};

class Cylinder
{
    public:
        Cylinder(Point& center, float radius, float height) : _center(0.0,0.0,0.0)
        {
            _center = center;
            _radius = radius;
            _height = height;
        }
    public:
        Point _center;
        float _radius;
        float _height;
};

#endif // GEOMETRY_H
