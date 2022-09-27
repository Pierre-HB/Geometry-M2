// #include "embededMesh.h"
// #include "mesh.h"
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <math.h>
// #include "OpenGLDisplayGeometricWorld.h"

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

    // std::vector<double> laplacians_coord[3];
    // std::vector<double (Point)> callbacks = {f_x, f_y, f_z};

    // for(int i = 0; i < 3; i++){
    //     set_scalar_on_vertex(callbacks[i]);
    //     compute_laplacian_of_vertex();
    //     laplacians_coord[i] = laplacians
    //     laplacians.clear();

    // }
    // for(int i = 0; i < laplacians.size(); i++){
    //     curvatures[i] = Vector(laplacians_coord[0][i], laplacians_coord[1][i], laplacians_coord[2][i]).norme()/2.0;
    // }

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

