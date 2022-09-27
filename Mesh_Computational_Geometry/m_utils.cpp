double f_x(Point p){return p._x;}
double f_y(Point p){return p._y;}
double f_z(Point p){return p._z;}
double log1(double x){return log(1+x);}

double direct_orientation(Point p1, Point p2, Point p3){
    // return (p2._x-p1._x)*(p3._y-p1._y) - (p2._y-p1._y)*(p3._z-p1._z);
    Vector e1 = Vector(p1, p2);
    Vector e2 = Vector(p1, p3);
    return cross(e1, e2).get_z();
}

double in_triangle(Point p, Point p1, Point p2, Point p3){
    double signe = 1;
    double t1 = direct_orientation(p, p1, p2);
    double t2 = direct_orientation(p, p2, p3);
    double t3 = direct_orientation(p, p3, p1);
    if(t1<=0) signe = -1; 
    if(t2<=0) signe = -1; 
    if(t3<=0) signe = -1;
    std::cout << "in triangle : " << t1 << ", " << t2 << ", " << t3 << ", output : " << signe*abs(t1*t2*t3) << std::endl;
    return signe*abs(t1*t2*t3);
}


//========================================================= DOT and CROSS
double dot(const Vector& a, const Vector& b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
Vector cross(const Vector& a, const Vector& b){
    return Vector(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
}

void GeometricWorld::load_queen(){
    std::cout << "load queen" << std::endl;
    mesh = Mesh("../queen.off");
    emb_mesh = Embeded_Mesh(&mesh);
}
void GeometricWorld::set_color_to_normal(){
    std::cout << "compute normals" << std::endl;
    emb_mesh.compute_normal_of_vertex();
    emb_mesh.set_color_to_normal();
}
void GeometricWorld::set_color_to_curvature(){
    std::cout << "compute curvatures" << std::endl;
    emb_mesh.compute_curvature_of_vertex();
    emb_mesh.set_color_to_curvature();
}
void GeometricWorld::load_triangle(){
    std::cout << "load triangle" << std::endl;
    Point p1 = Point(-0.5, -0.5, 0);
    Point p2 = Point(0.5, -0.5, 0);
    Point p3 = Point(0, 0.5, 0);
    mesh = Mesh(p1, p2, p3);
}
void GeometricWorld::add_point(){
    std::cout << "TODO add a point" << std::endl;
}
void GeometricWorld::update(){
    if(MainWindow::bForButtonQueen){
        load_queen();
        MainWindow::bForButtonQueen = false;
    }
    if(MainWindow::bForButtonNormal){
        set_color_to_normal();
        MainWindow::bForButtonNormal = false;
    }
    if(MainWindow::bForButtonCurvature){
        set_color_to_curvature();
        MainWindow::bForButtonCurvature = false;
    }
    if(MainWindow::bForButtonTriangle){
        load_triangle();
        MainWindow::bForButtonTriangle = false;
    }
    if(MainWindow::bForButtonAddPoint){
        add_point();
        MainWindow::bForButtonAddPoint = false;
    }
}