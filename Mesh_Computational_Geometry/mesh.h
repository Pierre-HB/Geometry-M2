#ifndef MESH_H
#define MESH_H

#include <QGLWidget> //UpgradeQt6: #include <QOpenGLWidget>
#include <iostream>
#include <fstream>
#include <string>
#include <tgmath.h>
// #include "embededMesh.h"



class Point;
class Vector;
class Vertex;

struct Iterator_on_faces;
typedef Iterator_on_faces Iterator_on_vertices;
struct Circulator_on_faces;
struct Circulator_on_vertices;




class Mesh;
class Embeded_Mesh;


class Point
{
    friend Vector;
public:
    double _x;
    double _y;
    double _z;

    Point():_x(),_y(),_z() {}
    Point(double x_, double y_, double z_):_x(x_),_y(y_),_z(z_) {}
};

class Vector
//a vector going from the point A to B
{
    friend double dot(const Vector& a, const Vector& b);
    friend Vector cross(const Vector& a, const Vector& b);
    double x;
    double y;
    double z;
public:
    Vector(const Point& a, const Point& b):x(b._x-a._x), y(b._y-a._y), z(b._z-a._z){};
    Vector(double x, double y, double z):x(x), y(y), z(z){};
    Vector():x(0), y(0), z(0){};

    double get_x(){return x;};
    double get_y(){return y;};
    double get_z(){return z;};

    double norme(){
        return sqrt(x*x + y*y + z*z);
    }
    Vector* normalize(){
        double n = norme();
        x/=n;
        y/=n;
        z/=n;
        return this;
    }

    friend Vector operator*(const Vector & a, const double & b){return Vector(a.x*b, a.y*b, a.z*b);};
    friend Vector operator/(const Vector & a, const double & b){return Vector(a.x/b, a.y/b, a.z/b);};
    friend Vector operator*(const double & a, const Vector & b){return Vector(a*b.x, a*b.y, a*b.z);};
    friend Vector operator+(const Vector & a, const Vector & b){return Vector(a.x+b.x, a.y+b.y, a.z+b.z);};
    friend Vector operator-(const Vector & a, const Vector & b){return Vector(a.x-b.x, a.y-b.y, a.z-b.z);};
};



class Vertex
{
public:
    Point point;
    uint face_id;
    bool infinit;

    Vertex(): point(), face_id(), infinit(false){};
    Vertex(Point p): point(p), face_id(), infinit(false){};

    void set_face_id(uint f){face_id=f;};
};

void convert_tsv_to_rgb(std::vector<float>& hsv, std::vector<float>& rgb);



class Mesh
{
    friend struct Circulator_on_faces;
    friend struct Circulator_on_vertices;
    friend class Embeded_Mesh;
  // (Q ou STL)Vector of vertices
  // (Q ou STL)Vector of faces
  // Those who do not know about STL Vectors should have a look at cplusplus.com examples
    std::vector<Vertex> vertices;
    std::vector<std::vector<uint>> faces_id;
    std::vector<std::vector<uint>> adjFaces_id;

    std::vector<std::vector<float>> vertices_color;

    void compute_adjFaces();
    void initialize_colors();//give a grey color to every vertices
    void initialize_face_vertex();// link every vertex with an adjacent face
    void read_off(std::string file);//read the off file

public:
    Mesh(); // Constructors automatically called to initialize a Mesh (default strategy)
    Mesh(std::vector<std::vector<uint>> faces_, std::vector<Vertex> vertices_);
    Mesh(std::vector<Vertex> vertices_);
    Mesh(Point p1, Point p2, Point p3);
    Mesh(std::string file);
    ~Mesh(); // Destructor automatically called before a Mesh is destroyed (default strategy)
    void drawMesh();
    void drawMeshWireFrame();

    void print_adj(){for(int i = 0; i < adjFaces_id.size(); i++){
            std::cout << "|";
            for (int j = 0; j < 3; j++){std::cout << adjFaces_id[i][j] << " ";}
        }}

    void print_face(){for(int i = 0; i < faces_id.size(); i++){
            std::cout << "|";
            for (int j = 0; j < 3; j++){std::cout << faces_id[i][j] << " ";}
        }}

    Iterator_on_faces faces_begin();
    Iterator_on_faces faces_end();
    Iterator_on_vertices vertices_begin();
    Iterator_on_vertices vertices_end();

    Circulator_on_faces circulate_on_face_begin(uint vertex_id);
    Circulator_on_faces circulate_on_face_end(uint vertex_id);
    Circulator_on_vertices circulate_on_vertex_begin(uint face_id);
    Circulator_on_vertices circulate_on_vertex_end(uint face_id);

    void set_vertex_color(uint vertex_id, float r, float g, float b);
    void set_face_color(uint face_id, float r, float g, float b);
    void face_neighboring_color(uint face_id);
    bool is_face_infinit(uint face_id);

    void triangle_split(uint face_id, Point p);//add the point p inside the face face_id
    void edge_flip(uint face_id1, uint face_id2);
    void insert_point(Point p);

    void triangulate_naive(std::vector<Point> points);
    void triangulate_lawson();

};

class Embeded_Mesh
{
    std::vector<double> laplacians;
    std::vector<double> curvatures;
    std::vector<Vector> normals;
    std::vector<Vector> gradients;
    std::vector<double> scalar_on_vertex;
    Mesh* mesh;

public:
    Embeded_Mesh();
    Embeded_Mesh(Mesh* mesh);
    ~Embeded_Mesh();

    double compute_area_face(uint face_id, uint vertex_id);//compute the area of the face `face_id` relative to the vertex of id `vertex_id`
    double compute_area_face(uint face_id);//compute the area of the face `face_id` relative to the vertex of id `vertex_id`
    Vector compute_normal_face(uint face_id);//compute the normal of a face

    void compute_laplacian_of_vertex();//compute the laplacian of every vertex
    void set_color_to_laplaian();//set the color of every vertex depending of the laplacian value

    void compute_gradient_of_vertex();//compute the gradient of every vertex
    void set_color_to_gradient();//set the color of every vertex depending of the gradient value

    void compute_curvature_of_vertex();//compute the laplacian of every vertex
    void set_color_to_curvature();//set the color of every vertex depending of the laplacian value

    void compute_normal_of_vertex();//compute the normal of every vertex
    void set_color_to_normal();//set the color of every vertex depending of the laplacian value

    void set_scalar_on_vertex(double f(Point));
    void map(double f(double));
    void set_color_to_scalar();



};

double f_x(Point p);
double f_y(Point p);
double f_y(Point p);
double log1(double x);

double direct_orientation(Point p1, Point p2, Point p3);
double in_triangle(Point p, Point p1, Point p2, Point p3);

struct Iterator_on_faces
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = uint;
    using pointer           = uint*;  // or also value_type*
    using reference         = uint&;  // or also value_type&

    Iterator_on_faces(uint id):face_id(id){};

    void print(){std::cout << "if : " << face_id;}

    reference operator*() { return face_id; }
    pointer operator->() { return &face_id; }

    // Prefix increment
    Iterator_on_faces& operator++() { face_id++; return *this; }
    Iterator_on_faces& operator--() { face_id--; return *this; }

    // Postfix increment
    Iterator_on_faces operator++(int) { Iterator_on_faces tmp = *this; ++(*this); return tmp; }
    Iterator_on_faces operator--(int) { Iterator_on_faces tmp = *this; --(*this); return tmp; }

    friend bool operator== (const Iterator_on_faces& a, const Iterator_on_faces& b) { return a.face_id == b.face_id; };
    friend bool operator!= (const Iterator_on_faces& a, const Iterator_on_faces& b) { return a.face_id != b.face_id; };

private:
    uint face_id;
};

struct Circulator_on_faces
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = uint;
    using pointer           = uint*;  // or also value_type*
    using reference         = uint&;  // or also value_type&
    Circulator_on_faces(uint vertex_id, int rank, Mesh* mesh, uint first_face_id):vertex_id(vertex_id), rank(rank), mesh(mesh), first_face_id(first_face_id), face_id(first_face_id){};

    void print(){std::cout << "f_id : " << face_id << ", v_id : " << vertex_id << ", rank : " << rank << ", first_f_id : " << first_face_id;}

    reference operator*() { return face_id; }
    pointer operator->() { return &face_id; }

    // Prefix increment
    Circulator_on_faces& operator++();
    Circulator_on_faces& operator--();

    // Postfix increment
    Circulator_on_faces operator++(int) { Circulator_on_faces tmp = *this; ++(*this); return tmp; }
    Circulator_on_faces operator--(int) { Circulator_on_faces tmp = *this; --(*this); return tmp; }

    friend bool operator== (const Circulator_on_faces& a, const Circulator_on_faces& b) { return (a.face_id == b.face_id) && (a.rank == b.rank); };
    friend bool operator!= (const Circulator_on_faces& a, const Circulator_on_faces& b) { return (a.face_id != b.face_id) || (a.rank != b.rank); };

private:
    uint vertex_id;
    int rank;
    Mesh* mesh;
    uint face_id;
    uint first_face_id;
};

struct Circulator_on_vertices
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = uint;
    using pointer           = uint*;  // or also value_type*
    using reference         = uint&;  // or also value_type&
    Circulator_on_vertices(uint face_id, int rank, Mesh* mesh):face_id(face_id), inner_vertex_id(0), rank(rank), mesh(mesh){};

    void print(){std::cout << "f_id : " << face_id << ", rank : " << rank;}

    reference operator*();
    pointer operator->();

    // Prefix increment
    Circulator_on_vertices& operator++();
    Circulator_on_vertices& operator--();

    // Postfix increment
    Circulator_on_vertices operator++(int) { Circulator_on_vertices tmp = *this; ++(*this); return tmp; }
    Circulator_on_vertices operator--(int) { Circulator_on_vertices tmp = *this; --(*this); return tmp; }

    friend bool operator== (const Circulator_on_vertices& a, const Circulator_on_vertices& b) { return (a.inner_vertex_id == b.inner_vertex_id) && (a.rank == b.rank); };
    friend bool operator!= (const Circulator_on_vertices& a, const Circulator_on_vertices& b) { return (a.inner_vertex_id != b.inner_vertex_id) || (a.rank != b.rank); };

private:
    uint inner_vertex_id;
    int rank;
    Mesh* mesh;
    uint face_id;
};




class GeometricWorld //Here used to create a singleton instance
{
  QVector<Point> _bBox;  // Bounding box
  Mesh mesh; // object to display
  Embeded_Mesh emb_mesh; // object to display
public :
  GeometricWorld();
  void draw();
  void drawWireFrame();
  void load_queen();
  void set_color_to_normal();
  void set_color_to_curvature();
  void load_triangle();
  void add_point();

  void update();
  // ** TP Can be extended with further elements;
  // Mesh _mesh;
};


#endif // MESH_H
