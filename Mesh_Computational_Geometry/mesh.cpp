#include "mesh.h"
// #include "embededMesh.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "OpenGLDisplayGeometricWorld.h"
#include "mainwindow.h"


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
    // std::string file = "../queen.off";
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

    emb_mesh = Embeded_Mesh(&mesh);

    // points = {Point(-1, -0.8, 0)};

    // mesh.triangulate_naive(points);


    // mesh.face_neighboring_color(7);
    // mesh.face_neighboring_color(0);
    // mesh.edge_flip(0, 7);

    // mesh.face_neighboring_color(7);


    // emb_mesh.set_color_to_normal();
    // emb_mesh.set_scalar_on_vertex(f_x);
    // emb_mesh.set_color_to_scalar();
    // emb_mesh.compute_laplacian_of_vertex();
    // emb_mesh.set_color_to_laplaian();
    // emb_mesh.compute_curvature_of_vertex();
    
    // emb_mesh.set_color_to_curvature();

    // emb_mesh.set_scalar_on_vertex(f_x);
    // emb_mesh.compute_gradient_of_vertex();
    // emb_mesh.set_color_to_gradient();



    std::cout << "DONE============================" << std::endl;
}


#include "m_utils.cpp"
#include "iterators.cpp"
#include "embededMesh.cpp"

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
    faces_id[0] = std::vector<uint>({1, 2, 3});
    faces_id[1] = std::vector<uint>({3, 2, 0});
    faces_id[2] = std::vector<uint>({1, 3, 0});
    faces_id[3] = std::vector<uint>({2, 1, 0});

    adjFaces_id = std::vector<std::vector<uint>>();
    compute_adjFaces();
    initialize_colors();



}

Mesh::~Mesh(){

};


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

#include "mesh_triangulation.cpp"

