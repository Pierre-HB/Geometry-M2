#include "mesh.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

GeometricWorld::GeometricWorld()
{
    double width=0.5, depth=0.6, height=0.8;
    _bBox.push_back(Point(-0.5*width,-0.5*depth,-0.5*height)); //0
    _bBox.push_back(Point(-0.5*width,0.5*depth,-0.5*height)); // 1
    _bBox.push_back(Point(0.5*width,-0.5*depth,-0.5*height)); // 2
    _bBox.push_back(Point(-0.5*width,-0.5*depth,0.5*height)); // 3

    Point p0 = Point(0, 0, 0);
    Point p1 = Point(1, 0, 0);
    Point p2 = Point(0, 1, 0);
    Point p3 = Point(0, 0, 1);
    //test

    std::vector<Vertex> vertices = {Vertex(p0), Vertex(p1), Vertex(p2), Vertex(p3)};
    std::vector<std::vector<uint>> faces = { {1, 2, 3}, {0, 2, 3}, {0, 3, 1}, {0, 1, 2} };

    // mesh = Mesh(faces, vertices);
    std::string file = "../queen.off";
    // std::string file = "../tetra.off";
    // mesh = Mesh(file);
    // Embeded_Mesh emb_mesh = Embeded_Mesh(&mesh);


    Point p1_ = Point(-0.5, -0.5, 0);
    Point p2_ = Point(0.5, -0.5, 0);
    Point p3_ = Point(0, 0.5, 0);

    Point p4_ = Point(-0.2, -0.2, 0);
    Point p5_ = Point(0.2, -0.2, 0);
    Point p6_ = Point(0, 0.2, 0);

    std::vector<Point> points = {p4_, p5_, p6_};

    mesh = Mesh(p1_, p2_, p3_);
    mesh.triangulate_naive(points);

    points = {Point(-1, -0.8, 0)};

    mesh.triangulate_naive(points);

    // mesh.face_neighboring_color(7);
    // mesh.face_neighboring_color(0);
    // mesh.edge_flip(0, 7);

    // mesh.face_neighboring_color(7);

    // for(Point p : points){
    //     std::cout << "inster : (" << p._x << ", " << p._y << ", " << p._z << ")" << std::endl;
    //     insert_point(p);
    // }

    // mesh.insert_point(Point(-0.2, -0.2, 0));
    // mesh.insert_point(Point(0.2, -0.2, 0));
    // mesh.insert_point(Point(0, 0.2, 0));

    // mesh.triangle_split(0, Point(0, 0, 0));


    // std::cout << "start computing normal" << std::endl;
    // emb_mesh.compute_normal_of_vertex();
    // std::cout << "end computing normal" << std::endl;

    //mesh.print_face();
    //std::cout << std::endl;
    //mesh.print_adj();
    //std::cout << std::endl;

    // std::cout << "looping throw vertices" << std::endl;
    // for (Iterator_on_vertices it = mesh.vertices_begin(); it != mesh.vertices_end(); it++){
    //     mesh.set_vertex_color(*it, 0.0f, 0.5f, 0.0f);
    // }
    // std::cout << "finish looping throw vertices" << std::endl;
    // std::cout << "try a cirvulator on face" << std::endl;
    // uint vertex_cenral = 1;
    // Circulator_on_faces it = mesh.circulate_on_face_begin(vertex_cenral);


    // for(Circulator_on_faces it = mesh.circulate_on_face_begin(vertex_cenral); it != mesh.circulate_on_face_end(vertex_cenral); it++){
    //     std::cout << *it << std::endl;
    //     mesh.set_face_color(*it, 1.0f, 0.0f, 0.0f);
    // }

    // uint face_central = 0;
    // for(Circulator_on_vertices it = mesh.circulate_on_vertex_begin(face_central); it != mesh.circulate_on_vertex_end(face_central); it++){
    //     std::cout << *it << std::endl;
    //     mesh.set_vertex_color(*it, 0.0f, 0.0f, 1.0f);
    // }

    // emb_mesh.set_color_to_normal();
    // emb_mesh.set_scalar_on_vertex(f_x);
    // emb_mesh.set_color_to_scalar();
    // emb_mesh.compute_laplacian_of_vertex();
    // emb_mesh.set_color_to_laplaian();
    // emb_mesh.compute_curvature_of_vertex();
    
    // emb_mesh.set_color_to_curvature();

    // mesh.face_neighboring_color(7);

    // emb_mesh.set_scalar_on_vertex(f_x);
    // emb_mesh.compute_gradient_of_vertex();
    // emb_mesh.set_color_to_gradient();



    std::cout << "DONE============================" << std::endl;

  
}
double f_x(Point p){
    return p._x;
}
double f_y(Point p){
    return p._y;
}
double f_z(Point p){
    return p._z;
}
double log1(double x){
    return log(1+x);
}

double direct_orientation(Point p1, Point p2, Point p3){
    Vector e1 = Vector(p1, p2);
    Vector e2 = Vector(p1, p3);
    // std::cout << "Vectors : " << std::endl;
    // std::cout << "[" << e1.get_x() << ", " << e1.get_y() << ", " << e1.get_z() << "]" << std::endl;
    // std::cout << "[" << e2.get_x() << ", " << e2.get_y() << ", " << e2.get_z() << "]" << std::endl;
    // std::cout << "cross : [" << cross(e1, e2).get_x() << ", " << cross(e1, e2).get_y() << ", " << cross(e1, e2).get_z() << "]" << std::endl;
    std::cout << "result of test : " << cross(e1, e2).get_z() << std::endl;
    return cross(e1, e2).get_z();
}
double in_triangle(Point p, Point p1, Point p2, Point p3){
    // std::cout << "Points : " << std::endl;
    // std::cout << "(" << p._x << ", " << p._y << ", " << p._z << ")" << std::endl;
    // std::cout << "(" << p1._x << ", " << p1._y << ", " << p1._z << ")" << std::endl;
    // std::cout << "(" << p2._x << ", " << p2._y << ", " << p2._z << ")" << std::endl;
    // std::cout << "(" << p3._x << ", " << p3._y << ", " << p3._z << ")" << std::endl;
    double signe = 1;
    double t1 = direct_orientation(p, p1, p2);
    double t2 = direct_orientation(p, p2, p3);
    double t3 = direct_orientation(p, p3, p1);
    // std::cout << "in triangle : " << t1 << ", " << t2 << ", " << t3 << std::endl;
    if(t1<=0) signe = -1; 
    if(t2<=0) signe = -1; 
    if(t3<=0) signe = -1; 
    // std::cout << "signe : " << (signe*abs(t1*t2*t3)) << std::endl;
    return signe*abs(t1*t2*t3);
}




//===================================================== Utils
// The following functions could be displaced into a module OpenGLDisplayGeometricWorld that would include mesh.h

// Draw a Point
void glPointDraw(const Point & p) {
    glVertex3f(p._x, p._y, p._z);
}

uint index_of_other(uint a, uint b, std::vector<uint> v){
    //given 3 uint, return the third uint (not a or b)
    if(v[0] != a && v[0] != b) return 0;
    if(v[1] != a && v[1] != b) return 1;
    return 2;
}
uint index_of(uint a, std::vector<uint> v){
    //given 3 uint, return the third uint (not a or b)
    if(v[0] == a) return 0;
    if(v[1] == a) return 1;
    return 2;
}

void convert_tsv_to_rgb(std::vector<float>& tsv, std::vector<float>& rgb){
    // t: teinte (0°-360°)
    // s: saturation (0-1)
    // v: valeur, brillance (0-1)
    float t = tsv[0];
    float s = tsv[1];
    float v = tsv[2];
    int ti = int(floor(tsv[0]/60))%6;
    float f = tsv[0]/60 - ti;
    float l = tsv[2] * (1 - tsv[1]);
    float m = tsv[2] * (1 - f * tsv[1]);
    float n = tsv[2] * (1 - (1 - f)*tsv[1]);

    if(ti == 0){
        rgb[0] = v;
        rgb[1] = n;
        rgb[2] = l;
    };
    if(ti == 1){
        rgb[0] = m;
        rgb[1] = v;
        rgb[2] = l;
    };
    if(ti == 2){
        rgb[0] = l;
        rgb[1] = v;
        rgb[2] = n;
    };
    if(ti == 3){
        rgb[0] = l;
        rgb[1] = m;
        rgb[2] = v;
    };
    if(ti == 4){
        rgb[0] = n;
        rgb[1] = l;
        rgb[2] = v;
    };
    if(ti == 5){
        rgb[0] = v;
        rgb[1] = l;
        rgb[2] = m;
    };
}


//========================================================= DOT and CROSS
double dot(const Vector& a, const Vector& b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
Vector cross(const Vector& a, const Vector& b){
    return Vector(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
}
//========================================================== Iterator

Circulator_on_faces_infinit& Circulator_on_faces_infinit::operator++() {
    uint id_on_face = index_of(vertex_id, mesh->faces_id[face_id]);
    face_id = mesh->adjFaces_id[face_id][(id_on_face+1)%3];
    if(face_id == first_face_id)rank++;
    return *this;
}

Circulator_on_vertices_infinit::reference Circulator_on_vertices_infinit::operator*(){
    return mesh->faces_id[face_id][inner_vertex_id];
}

Circulator_on_vertices_infinit::pointer Circulator_on_vertices_infinit::operator->(){
    return &(mesh->faces_id[face_id][inner_vertex_id]);
}

Circulator_on_vertices_infinit& Circulator_on_vertices_infinit::operator++(){
    inner_vertex_id++;
    if(inner_vertex_id == 3){
        inner_vertex_id = 0;
        rank++;
    }
    return *this;
};



//================================================== MESH
Iterator_on_faces Mesh::faces_begin(){return Iterator_on_faces(0);}
Iterator_on_faces Mesh::faces_end(){return Iterator_on_faces(faces_id.size());}
Iterator_on_vertices Mesh::vertices_begin(){return Iterator_on_vertices(0);}
Iterator_on_vertices Mesh::vertices_end(){return Iterator_on_vertices(vertices.size());}
Circulator_on_faces Mesh::circulate_on_face_begin(uint vertex_id){return Circulator_on_faces(vertex_id, 0, this, vertices[vertex_id].face_id);}
Circulator_on_faces Mesh::circulate_on_face_end(uint vertex_id){return Circulator_on_faces(vertex_id, 1, this, vertices[vertex_id].face_id);}
Circulator_on_vertices Mesh::circulate_on_vertex_begin(uint face_id){return Circulator_on_vertices(face_id, 0, this);}
Circulator_on_vertices Mesh::circulate_on_vertex_end(uint face_id){return Circulator_on_vertices(face_id, 1, this);}
Iterator_on_faces_infinit Mesh::faces_infinit_begin(){return Iterator_on_faces_infinit(0);}
Iterator_on_faces_infinit Mesh::faces_infinit_end(){return Iterator_on_faces_infinit(faces_id.size());}
Iterator_on_vertices_infinit Mesh::vertices_infinit_begin(){return Iterator_on_vertices_infinit(0);}
Iterator_on_vertices_infinit Mesh::vertices_infinit_end(){return Iterator_on_vertices_infinit(vertices.size());}
Circulator_on_faces_infinit Mesh::circulate_on_face_infinit_begin(uint vertex_id){return Circulator_on_faces_infinit(vertex_id, 0, this, vertices[vertex_id].face_id);}
Circulator_on_faces_infinit Mesh::circulate_on_face_infinit_end(uint vertex_id){return Circulator_on_faces_infinit(vertex_id, 1, this, vertices[vertex_id].face_id);}
Circulator_on_vertices_infinit Mesh::circulate_on_vertex_infinit_begin(uint face_id){return Circulator_on_vertices_infinit(face_id, 0, this);}
Circulator_on_vertices_infinit Mesh::circulate_on_vertex_infinit_end(uint face_id){return Circulator_on_vertices_infinit(face_id, 1, this);}

void Mesh::drawMesh(){
    for (ulong i = 0; i < faces_id.size(); i++){
        if(!vertices[faces_id[i][0]].infinit && !vertices[faces_id[i][1]].infinit && !vertices[faces_id[i][2]].infinit){
            glBegin(GL_TRIANGLES);
            for (int j = 0; j < 3; j++){
                glColor3d(vertices_color[faces_id[i][j]][0],vertices_color[faces_id[i][j]][1],vertices_color[faces_id[i][j]][2]);
                glPointDraw(vertices[faces_id[i][j]].point);
            }
            glEnd();
        }
    }
};
void Mesh::drawMeshWireFrame(){
    for (ulong i = 0; i < faces_id.size(); i++){
        for(uint j = 0; j < 3; j++){
            if(!vertices[faces_id[i][j]].infinit && !vertices[faces_id[i][(j+1)%3]].infinit){
                glBegin(GL_LINE_STRIP);
                
                glPointDraw(vertices[faces_id[i][j]].point);
                glPointDraw(vertices[faces_id[i][(j+1)%3]].point);
                glEnd();
            }else{
                glLineStipple(15, 0xAAAA);
                glEnable(GL_LINE_STIPPLE);
                glBegin(GL_LINE_STRIP);                
                glPointDraw(vertices[faces_id[i][j]].point);
                glPointDraw(vertices[faces_id[i][(j+1)%3]].point);
                glEnd();
                glDisable(GL_LINE_STIPPLE);
            }
        }
    }

};

void Mesh::compute_adjFaces(){
    std::map<std::tuple<uint, uint>, uint> face_map = std::map<std::tuple<uint, uint>, uint>();

    for(ulong i = 0; i < faces_id.size(); i++){
        adjFaces_id.push_back(std::vector({uint(0), uint(0), uint(0)}));
        for(uint j = 0; j < 3; j++){//loop a travers les edges
            uint a = faces_id[i][j];
            uint b = faces_id[i][(j+1)%3];

            if(face_map.count(std::tuple(a, b)) == 1){
                uint adjFace = face_map[std::tuple(a, b)];
                adjFaces_id[adjFace][index_of_other(a, b, faces_id[adjFace])] = i;
                adjFaces_id[i][(j+2)%3] = adjFace;
            }
            else{
                face_map[std::tuple(b, a)] = i;
            }
        }
    }
};
void Mesh::initialize_colors(){
    vertices_color = std::vector<std::vector<float>>();
    for(int i = 0; i < vertices.size(); i++){vertices_color.push_back(std::vector({0.0f, 0.0f, 0.0f}));};
};
void Mesh::initialize_face_vertex(){
    for(int i = 0; i < faces_id.size(); i++){
        for(int j = 0; j < 3; j++){
            vertices[faces_id[i][j]].set_face_id(i);
        };
    }
};
void Mesh::read_off(std::string file){
    std::ifstream myfile (file);
    if ( myfile.is_open() ) {
        int nb_vertices;
        int nb_faces;
        int unknow;
        myfile >> nb_vertices;
        myfile >> nb_faces;
        myfile >> unknow;

        for(int i = 0; i < nb_vertices; i++){
            double x;
            double y;
            double z;
            myfile >> x;
            myfile >> y;
            myfile >> z;
            vertices.push_back(Vertex(Point(x, y, z)));
        }
        initialize_colors();

        for(int i = 0; i < nb_faces; i++){
            myfile >> unknow;// clear the 3 at the start of the line

            uint a;
            uint b;
            uint c;
            myfile >> a;
            myfile >> b;
            myfile >> c;
            faces_id.push_back(std::vector({a, b, c}));
        }
    }
    else{
        std::cout << "NOT READ" << std::endl;
    }
}


Mesh::Mesh(){
    faces_id = std::vector<std::vector<uint>>();
    vertices = std::vector<Vertex>();
    adjFaces_id = std::vector<std::vector<uint>>();
    vertices_color = std::vector<std::vector<float>>();
};

Mesh::Mesh(std::vector<std::vector<uint>> faces_, std::vector<Vertex> vertices_){
    faces_id = faces_;
    vertices = vertices_;
    adjFaces_id = std::vector<std::vector<uint>>();

    initialize_colors();
    initialize_face_vertex();
    compute_adjFaces();
};
Mesh::Mesh(std::vector<Vertex> vertices_){
    vertices = vertices_;

    initialize_colors();
    // initialize_face_vertex();
    // compute_adjFaces();
};

Mesh::Mesh(std::string file){
    faces_id = std::vector<std::vector<uint>>();
    vertices = std::vector<Vertex>();
    adjFaces_id = std::vector<std::vector<uint>>();

    
    read_off(file);
    initialize_face_vertex();
    compute_adjFaces();

    //==================DEBUG
    int nb_zero = 0;
    for(int i = 0; i < adjFaces_id.size(); i++){
        for(int j = 0; j < 3; j++){
            if(adjFaces_id[i][j] == 0)nb_zero++;
        }
    }
    std::cout << "Nb face adj to zero : " << nb_zero << std::endl;

    nb_zero = 0;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].face_id == 0)nb_zero++;
    }
    std::cout << "Nb Vertex on zero : " << nb_zero << std::endl;
    std::cout << "Nb Vertex : " << vertices.size() << std::endl;


}

Mesh::Mesh(Point p1, Point p2, Point p3){
    //make sur that the triangle is well oriented
    if(!direct_orientation(p1, p2, p3)){
        Point tmp = p1;
        p1 = p2;
        p2 = tmp;
    }
    vertices = std::vector<Vertex>(4);
    vertices[1] = Vertex(p1);
    vertices[2] = Vertex(p2);
    vertices[3] = Vertex(p3);
    vertices[0] = Vertex(Point(0, 0, -1));
    vertices[0].infinit = true;

    faces_id = std::vector<std::vector<uint>>(4);
    
    //first triangle (only one that is not infinit)
    // faces_id[0] = std::vector<uint>(3);
    // faces_id[0][0] = 1;
    // faces_id[0][1] = 2;
    // faces_id[0][2] = 3;

    faces_id[0] = std::vector<uint>({1, 2, 3});
    faces_id[1] = std::vector<uint>({3, 2, 0});
    faces_id[2] = std::vector<uint>({1, 3, 0});
    faces_id[3] = std::vector<uint>({2, 1, 0});

    // faces_id[1] = std::vector<uint>(3);
    // faces_id[1][0] = 3;
    // faces_id[1][1] = 2;
    // faces_id[1][2] = 0;

    // faces_id[2] = std::vector<uint>(3);
    // faces_id[2][0] = 1;
    // faces_id[2][1] = 3;
    // faces_id[2][2] = 0;

    // faces_id[3] = std::vector<uint>(3);
    // faces_id[3][0] = 2;
    // faces_id[3][1] = 1;
    // faces_id[3][2] = 0;

    adjFaces_id = std::vector<std::vector<uint>>();
    // adjFaces_id = std::vector<std::vector<uint>>(4);

    compute_adjFaces();

    // adjFaces_id[0] = std::vector<uint>(3);
    // adjFaces_id[0][0] = 1;
    // adjFaces_id[0][1] = 2;
    // adjFaces_id[0][2] = 3;

    // adjFaces_id[1] = std::vector<uint>(3);
    // adjFaces_id[1][0] = 3;
    // adjFaces_id[1][1] = 2;
    // adjFaces_id[1][2] = 0;

    // adjFaces_id[2] = std::vector<uint>(3);
    // adjFaces_id[2][0] = 1;
    // adjFaces_id[2][1] = 3;
    // adjFaces_id[2][2] = 0;

    // adjFaces_id[3] = std::vector<uint>(3);
    // adjFaces_id[3][0] = 2;
    // adjFaces_id[3][1] = 1;
    // adjFaces_id[3][2] = 0;

    // vertices[0].face_id = 1;
    // vertices[1].face_id = 2;
    // vertices[2].face_id = 3;
    // vertices[3].face_id = 0;

    initialize_colors();

    // std::cout << "mesh created" << std::endl;


}

Mesh::~Mesh(){

};

bool Mesh::is_face_infinit(uint face_id){
    return vertices[faces_id[face_id][0]].infinit || vertices[faces_id[face_id][1]].infinit || vertices[faces_id[face_id][2]].infinit;
}

void Mesh::triangle_split(uint face_id, Point p){
    uint v0 = faces_id[face_id][0];
    uint v1 = faces_id[face_id][1];
    uint v2 = faces_id[face_id][2];
    Vertex v = Vertex(p);
    uint vertex_id = vertices.size();
    vertices.push_back(v);
    // std::cout << "creating color" << std::endl;
    std::vector<float> tmp = std::vector<float>({0.0, 0.0, 0.0});
    // tmp[0] = 0.0;
    // tmp[1] = 0.0;
    // tmp[2] = 0.0;
    vertices_color.push_back(tmp);

    //adding the two new faces
    uint f0 = face_id;
    uint f1 = faces_id.size();
    std::vector<uint> newf1 = {v1, v2, vertex_id};
    std::vector<uint> newadjf1 = std::vector<uint>(3);
    std::vector<uint> newadjf2 = std::vector<uint>(3);
    faces_id.push_back(newf1);
    adjFaces_id.push_back(newadjf1);
    adjFaces_id.push_back(newadjf2);

    uint f2 = faces_id.size();
    std::vector<uint> newf2 = {v2, v0, vertex_id};
    faces_id.push_back(newf2);

    //modifiing the current face
    faces_id[face_id][2] = vertex_id;

    //linking vertex to faces
    vertices[v0].face_id = f0;
    vertices[v1].face_id = f1;
    vertices[v2].face_id = f2;
    vertices[vertex_id].face_id = f0;

    //managing adjacent faces
    // std::cout << "manage adj" << std::endl;

    uint adjf0 = adjFaces_id[f0][0];
    uint adjf1 = adjFaces_id[f0][1];

    // std::cout << "temp" << std::endl;
    adjFaces_id[f0][0] = f1;
    adjFaces_id[f0][1] = f2;

    adjFaces_id[f1][0] = f2;
    adjFaces_id[f1][1] = f0;
    adjFaces_id[f1][2] = adjf0;

    adjFaces_id[f2][0] = f0;
    adjFaces_id[f2][1] = f1;
    adjFaces_id[f2][2] = adjf1;

    // std::cout << "search of index" << std::endl;

    uint inner_f0_0 = index_of(f0, adjFaces_id[adjf0]);
    uint inner_f0_1 = index_of(f0, adjFaces_id[adjf1]);

    // std::cout << "find index" << std::endl;
    adjFaces_id[adjf0][inner_f0_0] = f1;
    adjFaces_id[adjf1][inner_f0_1] = f2;

    // std::cout << "end split" << std::endl;
}

void Mesh::edge_flip(uint face_id1, uint face_id2){
    // std::cout << "edge_flip : " << face_id1 << ", " << face_id2 << std::endl;
    // std::cout << "f1 : [" << faces_id[face_id1][0] << ", " << faces_id[face_id1][1] << ", " << faces_id[face_id1][2] << "]" << std::endl;
    // std::cout << "f2 : [" << faces_id[face_id2][0] << ", " << faces_id[face_id2][1] << ", " << faces_id[face_id2][2] << "]" << std::endl;
    uint offset1 = -1;
    uint offset2 = -1;//offset to have faces_id[face_id1][offset1] == faces_id[face_id2][offset2]
    //and faces_id[face_id1][offset1+1] == faces_id[face_id2][offset2-1]
    for(uint i = 0; i < 3; i++){
        for(uint j = 0; j < 3; j++){
            if((faces_id[face_id1][i] == faces_id[face_id2][j]) && (faces_id[face_id1][(i+1)%3] == faces_id[face_id2][(j+2)%3])){
                offset1 = i;
                offset2 = j;
            }
        }
    }
    if(offset1 == -1){
        std::cout << "no common edge" << std::endl;
        return; //no common edge
    } 
    

    uint vertex_id1 = faces_id[face_id1][(offset1+2)%3];//vertex of face_1 wich is not in face_2
    uint vertex_id2 = faces_id[face_id2][(offset2+1)%3];//vertex of face_2 wich is not in face_1

    // swap edges:
    faces_id[face_id1][(offset1+0)%3] = vertex_id2;
    faces_id[face_id2][(offset2+2)%3] = vertex_id1;

    //managing adjacent faces
    uint adjFace_id1 = adjFaces_id[face_id1][(offset1+1)%3];
    uint adjFace_id2 = adjFaces_id[face_id2][(offset2+0)%3];

    uint inner_id_f1 = index_of(face_id1, adjFaces_id[adjFace_id1]);
    uint inner_id_f2 = index_of(face_id2, adjFaces_id[adjFace_id2]);

    adjFaces_id[face_id1][(offset1+1)%3] = face_id2;
    adjFaces_id[face_id2][(offset2+0)%3] = face_id1;

    adjFaces_id[face_id1][(offset1+2)%3] = adjFace_id2;
    adjFaces_id[face_id2][(offset2+1)%3] = adjFace_id1;

    adjFaces_id[adjFace_id1][inner_id_f1] = face_id2;
    adjFaces_id[adjFace_id2][inner_id_f2] = face_id1;

    //manage adjacent vertex (brut)
    vertices[faces_id[face_id1][0]].face_id = face_id1;
    vertices[faces_id[face_id1][1]].face_id = face_id1;
    vertices[faces_id[face_id1][2]].face_id = face_id1;
    vertices[faces_id[face_id2][0]].face_id = face_id2;
    vertices[faces_id[face_id2][1]].face_id = face_id2;
    vertices[faces_id[face_id2][2]].face_id = face_id2;

}

void Mesh::insert_point(Point p){
    for(auto fit = faces_infinit_begin(); fit != faces_infinit_end(); ++fit){
        // double tmp = in_triangle(p, vertices[faces_id[*fit][0]].point, vertices[faces_id[*fit][1]].point, vertices[faces_id[*fit][2]].point);
        if(is_face_infinit(*fit)){
            // std::cout << "infinit" << std::endl;
            uint offset = -1;//inner index of infinit point
            for(uint i = 0; i < 3; i++){
                if(vertices[faces_id[*fit][i]].infinit)offset = i;
            }
            // std::cout << "test on : " << std::endl;
            // std::cout << "(" << p._x << ", " << p._y << ", " << p._z << ")" << std::endl;
            // std::cout << "(" << vertices[faces_id[*fit][(offset+1)%3]].point._x << ", " << vertices[faces_id[*fit][(offset+1)%3]].point._y << ", " << vertices[faces_id[*fit][(offset+1)%3]].point._z << ")" << std::endl;
            // std::cout << "(" << vertices[faces_id[*fit][(offset+2)%3]].point._x << ", " << vertices[faces_id[*fit][(offset+2)%3]].point._y << ", " << vertices[faces_id[*fit][(offset+2)%3]].point._z << ")" << std::endl;
            // std::cout << "infinit index : " << offset << ", point_id : " << faces_id[*fit][offset] << ", infinit : " << vertices[faces_id[*fit][offset]].infinit << std::endl;
            // std::cout << "(" << vertices[faces_id[*fit][offset]].point._x << ", " << vertices[faces_id[*fit][offset]].point._y << ", " << vertices[faces_id[*fit][offset]].point._z << ")" << std::endl;

            double tmp = direct_orientation(p, vertices[faces_id[*fit][(offset+1)%3]].point, vertices[faces_id[*fit][(offset+2)%3]].point);
            // std::cout << "in triangle test " << tmp << std::endl;
            if(direct_orientation(p, vertices[faces_id[*fit][(offset+1)%3]].point, vertices[faces_id[*fit][(offset+2)%3]].point) > 0){
                //then we know that the point is outside the convex enveloppe
                bool found = false;//if we have found an infinit triangle containing our point
                for(auto fit_inf = circulate_on_face_infinit_begin(faces_id[*fit][offset]); fit_inf != circulate_on_face_infinit_end(faces_id[*fit][offset]); fit_inf++){
                    //circulate on the convexe enveloppe
                    if(!found){
                        uint offset_ = -1;//inner index of infinit point
                        for(uint i = 0; j < 3; i++){
                            if(vertices[faces_id[*fit][i]].infinit)offset_ = j;
                        }
                        if(direct_orientation(p, vertices[faces_id[*fit_inf][(offset_+1)%3]].point, vertices[faces_id[*fit_inf][(offset_+2)%3]].point) > 0){
                            found = true;
                            triangle_split(*fit_inf, p);
                        }
                    }else{
                        uint offset_ = -1;//inner index of infinit point
                        for(uint i = 0; j < 3; i++){
                            if(vertices[faces_id[*fit][i]].infinit)offset_ = j;
                        }
                        if(direct_orientation(p, vertices[faces_id[*fit_inf][(offset_+1)%3]].point, vertices[faces_id[*fit_inf][(offset_+2)%3]].point) > 0){
                            //flip with previous triangle
                            

                        }else{
                            return;
                        }
                    }

                }

                // triangle_split(*fit, p);
                // std::cout << "find infinit face" << std::endl;
                return;
            }
        }else{
            if(in_triangle(p, vertices[faces_id[*fit][0]].point, vertices[faces_id[*fit][1]].point, vertices[faces_id[*fit][2]].point) > 0){
                // std::cout << "triangle split : " << *fit << std::endl;
                // std::cout << "signe : " << tmp;
                triangle_split(*fit, p);
                return;
            }
        }
    }
}
void Mesh::triangulate_naive(std::vector<Point> points){
    for(Point p : points){
        std::cout << "inster : (" << p._x << ", " << p._y << ", " << p._z << ")" << std::endl;
        insert_point(p);
    }
}

void Mesh::set_vertex_color(uint vertex_id, float r, float g, float b){
    vertices_color[vertex_id][0] = r;
    vertices_color[vertex_id][1] = g;
    vertices_color[vertex_id][2] = b;
}
void Mesh::set_face_color(uint face_id, float r, float g, float b){
    for(int j = 0; j < 3; j++){
        vertices_color[faces_id[face_id][j]][0] = r;
        vertices_color[faces_id[face_id][j]][1] = g;
        vertices_color[faces_id[face_id][j]][2] = b;
    }
}

void Mesh::face_neighboring_color(uint face_id){
    for(uint i = 0; i < 3; i++){
        for(uint j = 0; j < 3; j++){
            for(uint k = 0; k < 3; k++){
                vertices_color[faces_id[adjFaces_id[face_id][i]][j]][k] = 0;
            }
        }
    }
    for(uint i = 0; i < 3; i++){
        for(uint j = 0; j < 3; j++){
            vertices_color[faces_id[adjFaces_id[face_id][i]][j]][i] = 255;
        }
    }
    for(uint i = 0; i < 3; i++){
        for(uint j = 0; j < 3; j++){
            vertices_color[faces_id[face_id][i]][j] = 255;
        }
    }



}

//=============================================== EmbededMesh

Embeded_Mesh::Embeded_Mesh(Mesh* mesh):mesh(mesh){
    laplacians = std::vector<double>(mesh->vertices.size());
    curvatures = std::vector<double>(mesh->vertices.size());
    normals = std::vector<Vector>(mesh->vertices.size());
    scalar_on_vertex = std::vector<double>(mesh->vertices.size());
    gradients = std::vector<Vector>(mesh->vertices.size());
}
Embeded_Mesh::~Embeded_Mesh(){};
Embeded_Mesh::Embeded_Mesh(){};


double Embeded_Mesh::compute_area_face(uint face_id, uint vertex_id){
    uint i = index_of(vertex_id, mesh->faces_id[face_id]);
    Point p1 = mesh->vertices[mesh->faces_id[face_id][i]].point;
    Vector v1 = Vector(p1._x, p1._y, p1._z);
    Point p2 = mesh->vertices[mesh->faces_id[face_id][(i+1)%3]].point;
    Vector v2 = Vector(p2._x, p2._y, p2._z);
    Point p3 = mesh->vertices[mesh->faces_id[face_id][(i+2)%3]].point;
    Vector v3 = Vector(p3._x, p3._y, p3._z);

    Vector barycentre = (v1 + v2 + v3)/3.0;
    Vector m1 = (v1 + v2)/2.0;
    Vector m2 = (v1 + v3)/2.0;

    double a1 = cross(m1-v1, barycentre-v1).norme()/2.0;
    double a2 = cross(barycentre-v1, m2-v1).norme()/2.0;
    return a1+a2;



    // Vector e1 = Vector(mesh->vertices[mesh->faces_id[face_id][0]].point, mesh->vertices[mesh->faces_id[face_id][1]].point);
    // Vector e2 = Vector(mesh->vertices[mesh->faces_id[face_id][0]].point, mesh->vertices[mesh->faces_id[face_id][2]].point);
    // return cross(e1, e2).norme()/6.0;// a third of the triangle area
}
double Embeded_Mesh::compute_area_face(uint face_id){

    Vector e1 = Vector(mesh->vertices[mesh->faces_id[face_id][0]].point, mesh->vertices[mesh->faces_id[face_id][1]].point);
    Vector e2 = Vector(mesh->vertices[mesh->faces_id[face_id][0]].point, mesh->vertices[mesh->faces_id[face_id][2]].point);
    return cross(e1, e2).norme()/2.0;
}

Vector Embeded_Mesh::compute_normal_face(uint face_id){
    Vector e1 = Vector(mesh->vertices[mesh->faces_id[face_id][0]].point, mesh->vertices[mesh->faces_id[face_id][1]].point);
    Vector e2 = Vector(mesh->vertices[mesh->faces_id[face_id][0]].point, mesh->vertices[mesh->faces_id[face_id][2]].point);
    Vector n = cross(e1, e2);
    n.normalize();
    return n;
}

void Embeded_Mesh::compute_normal_of_vertex(){
    for(auto it = mesh->vertices_begin(); it != mesh->vertices_end(); it++){
        normals[*it] = Vector();
        for(auto fit = mesh->circulate_on_face_begin(*it); fit != mesh->circulate_on_face_end(*it); fit++){
            normals[*it] = normals[*it] + compute_normal_face(*fit)*compute_area_face(*fit, *it);
        }
        normals[*it].normalize();
    }
}

void Embeded_Mesh::set_color_to_normal(){
    for(auto it = mesh->vertices_begin(); it != mesh->vertices_end(); it++){
        mesh->set_vertex_color(*it, (normals[*it].get_x()+1)/2, (normals[*it].get_y()+1)/2, (normals[*it].get_z()+1)/2);
    }
}

void Embeded_Mesh::set_scalar_on_vertex(double f(Point)){
    for(auto it = mesh->vertices_begin(); it != mesh->vertices_end(); it++){
        scalar_on_vertex[*it] = f(mesh->vertices[*it].point);
    }
}

void Embeded_Mesh::map(double f(double)){
    for(auto it = mesh->vertices_begin(); it != mesh->vertices_end(); it++){
        scalar_on_vertex[*it] = f(scalar_on_vertex[*it]);
    }
}

void Embeded_Mesh::set_color_to_scalar(){
    double min_value = scalar_on_vertex[0];
    double max_value = scalar_on_vertex[0];
    for(auto it = mesh->vertices_begin(); it != mesh->vertices_end(); it++){
        if(scalar_on_vertex[*it] < min_value)min_value = scalar_on_vertex[*it];
        if(scalar_on_vertex[*it] > max_value)max_value = scalar_on_vertex[*it];
    };
    std::cout << "min value : " << min_value << ", max max_value : " << max_value << std::endl;
    std::vector<float> tsv = std::vector<float>(3);
    tsv[1] = 1.0f;
    tsv[2] = 1.0f;
    const float crop = 80.0f;//avoid having the min and max value to be assosciated with the same color
    for(auto it = mesh->vertices_begin(); it != mesh->vertices_end(); it++){
        tsv[0] = crop + (360.0f-2*crop)*(1-(scalar_on_vertex[*it]-min_value)/(max_value-min_value));
        convert_tsv_to_rgb(tsv, mesh->vertices_color[*it]);
    }
}

void Embeded_Mesh::set_color_to_gradient(){
    for(auto it = mesh->vertices_begin(); it != mesh->vertices_end(); it++){
        mesh->set_vertex_color(*it, (gradients[*it].get_x()+1)/2, (gradients[*it].get_y()+1)/2, (gradients[*it].get_z()+1)/2);
    }
}

void Embeded_Mesh::set_color_to_laplaian(){
    std::vector<double> temp = scalar_on_vertex;
    scalar_on_vertex = laplacians;
    set_color_to_scalar();
    scalar_on_vertex = temp;
}

void Embeded_Mesh::set_color_to_curvature(){
    std::vector<double> temp = scalar_on_vertex;
    scalar_on_vertex = curvatures;
    map(log1);
    set_color_to_scalar();
    scalar_on_vertex = temp;

}

void Embeded_Mesh::compute_gradient_of_vertex(){
    for(auto it = mesh->vertices_begin(); it != mesh->vertices_end(); it++){
        gradients[*it] = Vector();
    }
    for(auto fit = mesh->faces_begin(); fit != mesh->faces_end(); fit++){
        Vector temp = Vector();
        Vector n = compute_normal_face(*fit);
        for(int i = 0; i < 3; i++){
            temp = temp + cross(n, Vector(mesh->vertices[mesh->faces_id[*fit][i]].point, mesh->vertices[mesh->faces_id[*fit][(i+1)%3]].point))*scalar_on_vertex[mesh->faces_id[*fit][(i+2)%3]];
        }
        for(int i = 0; i < 3; i++){
            gradients[mesh->faces_id[*fit][i]] = gradients[mesh->faces_id[*fit][i]] + temp/(2*compute_area_face(*fit));
        }
    }
}

void Embeded_Mesh::compute_laplacian_of_vertex(){
    for(auto it = mesh->vertices_begin(); it != mesh->vertices_end(); it++){
        laplacians[*it] = 0;
    }

    for(auto fit = mesh->faces_begin(); fit != mesh->faces_end(); fit++){
        for(int i = 0; i < 3; i++){
            Vector e1 = Vector(mesh->vertices[mesh->faces_id[*fit][i]].point, mesh->vertices[mesh->faces_id[*fit][(i+1)%3]].point);
            Vector e2 = Vector(mesh->vertices[mesh->faces_id[*fit][i]].point, mesh->vertices[mesh->faces_id[*fit][(i+2)%3]].point);
            double kcos_a = dot(e1, e2);
            double ksin_a = cross(e1, e2).norme();
            double cot_a = kcos_a/ksin_a;

            laplacians[mesh->faces_id[*fit][(i+1)%3]] += cot_a*(scalar_on_vertex[mesh->faces_id[*fit][(i+2)%3]] - scalar_on_vertex[mesh->faces_id[*fit][(i+1)%3]]);
            laplacians[mesh->faces_id[*fit][(i+2)%3]] += cot_a*(scalar_on_vertex[mesh->faces_id[*fit][(i+1)%3]] - scalar_on_vertex[mesh->faces_id[*fit][(i+2)%3]]);
        }
    }

    //normalisation
    for(auto it = mesh->vertices_begin(); it != mesh->vertices_end(); it++){
        double relative_area = 0;
        for(auto fit = mesh->circulate_on_face_begin(*it); fit != mesh->circulate_on_face_end(*it); fit++){
            relative_area += compute_area_face(*fit, *it);
        }
        //min value : -391.815, max max_value : 319.511
        laplacians[*it]/=2*relative_area;
    }    
}

void Embeded_Mesh::compute_curvature_of_vertex(){

    set_scalar_on_vertex(f_x);
    compute_laplacian_of_vertex();
    std::vector<double> laplacians_x = laplacians;
    laplacians = std::vector<double>(laplacians.size());

    set_scalar_on_vertex(f_y);
    compute_laplacian_of_vertex();
    std::vector<double> laplacians_y = laplacians;
    laplacians = std::vector<double>(laplacians.size());

    set_scalar_on_vertex(f_z);
    compute_laplacian_of_vertex();
    std::vector<double> laplacians_z = laplacians;
    laplacians = std::vector<double>(laplacians.size());

    for(int i = 0; i < laplacians.size(); i++){
        curvatures[i] = Vector(laplacians_x[i], laplacians_y[i], laplacians_z[i]).norme()/2.0;
    }

}



//============================================== GEOMETRIC WORLD
//Example with a bBox
void GeometricWorld::draw() {
    glColor3d(0.5,0.5,0.5);
    mesh.drawMesh();
}

//Example with a wireframe bBox
void GeometricWorld::drawWireFrame() {
    glColor3d(0,1,0);
    glBegin(GL_LINE_STRIP);
    glPointDraw(_bBox[0]);
    glPointDraw(_bBox[1]);
    glEnd();
    glColor3d(0,0,1);
    glBegin(GL_LINE_STRIP);
    glPointDraw(_bBox[0]);
    glPointDraw(_bBox[2]);
    glEnd();
    glColor3d(1,0,0);
    glBegin(GL_LINE_STRIP);
    glPointDraw(_bBox[0]);
    glPointDraw(_bBox[3]);
    glEnd();

    glColor3d(1,1,1);
    mesh.drawMeshWireFrame();
}