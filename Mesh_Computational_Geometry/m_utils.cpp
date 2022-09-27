double f_x(Point p){return p._x;}
double f_y(Point p){return p._y;}
double f_z(Point p){return p._z;}
double log1(double x){return log(1+x);}

double direct_orientation(Point p1, Point p2, Point p3){
    return (p2._x-p1._x)*(p3._y-p1._y) - (p2._y-p1._y)*(p3._z-p1._z);
    // Vector e1 = Vector(p1, p2);
    // Vector e2 = Vector(p1, p3);
    // return cross(e1, e2).get_z();
}

double in_triangle(Point p, Point p1, Point p2, Point p3){
    double signe = 1;
    double t1 = direct_orientation(p, p1, p2);
    double t2 = direct_orientation(p, p2, p3);
    double t3 = direct_orientation(p, p3, p1);
    if(t1<=0) signe = -1; 
    if(t2<=0) signe = -1; 
    if(t3<=0) signe = -1; 
    return signe*abs(t1*t2*t3);
}


//========================================================= DOT and CROSS
double dot(const Vector& a, const Vector& b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
Vector cross(const Vector& a, const Vector& b){
    return Vector(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
}