
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
    uint adjf0 = adjFaces_id[f0][0];
    uint adjf1 = adjFaces_id[f0][1];

    adjFaces_id[f0][0] = f1;
    adjFaces_id[f0][1] = f2;

    adjFaces_id[f1][0] = f2;
    adjFaces_id[f1][1] = f0;
    adjFaces_id[f1][2] = adjf0;

    adjFaces_id[f2][0] = f0;
    adjFaces_id[f2][1] = f1;
    adjFaces_id[f2][2] = adjf1;

    uint inner_f0_0 = index_of(f0, adjFaces_id[adjf0]);
    uint inner_f0_1 = index_of(f0, adjFaces_id[adjf1]);

    adjFaces_id[adjf0][inner_f0_0] = f1;
    adjFaces_id[adjf1][inner_f0_1] = f2;
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
    std::cout << "instert a new point" << std::endl;
    for(auto fit = faces_begin(); fit != faces_end(); ++fit){
        std::cout << "infinit face : " << is_face_infinit(*fit) << std::endl;
        if(in_triangle(p, vertices[faces_id[*fit][0]].point, vertices[faces_id[*fit][1]].point, vertices[faces_id[*fit][2]].point) > 0){
            std::cout << "triangle split : " << *fit << std::endl;
            // std::cout << "signe : " << tmp;
            triangle_split(*fit, p);
            return;
        }
    }
}

// void Mesh::insert_point(Point p){
//     for(auto fit = faces_begin(); fit != faces_end(); ++fit){
//         // double tmp = in_triangle(p, vertices[faces_id[*fit][0]].point, vertices[faces_id[*fit][1]].point, vertices[faces_id[*fit][2]].point);
//         // if(is_face_infinit(*fit)){
//         //     // uint offset = -1;//inner index of infinit point
//         //     // for(uint i = 0; i < 3; i++){
//         //     //     if(vertices[faces_id[*fit][i]].infinit)offset = i;
//         //     // }
//         //     // // std::cout << "test on : " << std::endl;
//         //     // // std::cout << "(" << p._x << ", " << p._y << ", " << p._z << ")" << std::endl;
//         //     // // std::cout << "(" << vertices[faces_id[*fit][(offset+1)%3]].point._x << ", " << vertices[faces_id[*fit][(offset+1)%3]].point._y << ", " << vertices[faces_id[*fit][(offset+1)%3]].point._z << ")" << std::endl;
//         //     // // std::cout << "(" << vertices[faces_id[*fit][(offset+2)%3]].point._x << ", " << vertices[faces_id[*fit][(offset+2)%3]].point._y << ", " << vertices[faces_id[*fit][(offset+2)%3]].point._z << ")" << std::endl;
//         //     // // std::cout << "infinit index : " << offset << ", point_id : " << faces_id[*fit][offset] << ", infinit : " << vertices[faces_id[*fit][offset]].infinit << std::endl;
//         //     // // std::cout << "(" << vertices[faces_id[*fit][offset]].point._x << ", " << vertices[faces_id[*fit][offset]].point._y << ", " << vertices[faces_id[*fit][offset]].point._z << ")" << std::endl;

//         //     // double tmp = direct_orientation(p, vertices[faces_id[*fit][(offset+1)%3]].point, vertices[faces_id[*fit][(offset+2)%3]].point);
//         //     // // std::cout << "in triangle test " << tmp << std::endl;
//         //     // if(direct_orientation(p, vertices[faces_id[*fit][(offset+1)%3]].point, vertices[faces_id[*fit][(offset+2)%3]].point) > 0){
//         //     //     //then we know that the point is outside the convex enveloppe
//         //     //     bool found = false;//if we have found an infinit triangle containing our point
//         //     //     for(auto fit_inf = circulate_on_face_infinit_begin(faces_id[*fit][offset]); fit_inf != circulate_on_face_infinit_end(faces_id[*fit][offset]); fit_inf++){
//         //     //         //circulate on the convexe enveloppe
//         //     //         if(!found){
//         //     //             uint offset_ = -1;//inner index of infinit point
//         //     //             for(uint i = 0; j < 3; i++){
//         //     //                 if(vertices[faces_id[*fit][i]].infinit)offset_ = j;
//         //     //             }
//         //     //             if(direct_orientation(p, vertices[faces_id[*fit_inf][(offset_+1)%3]].point, vertices[faces_id[*fit_inf][(offset_+2)%3]].point) > 0){
//         //     //                 found = true;
//         //     //                 triangle_split(*fit_inf, p);
//         //     //             }
//         //     //         }else{
//         //     //             uint offset_ = -1;//inner index of infinit point
//         //     //             for(uint i = 0; j < 3; i++){
//         //     //                 if(vertices[faces_id[*fit][i]].infinit)offset_ = j;
//         //     //             }
//         //     //             if(direct_orientation(p, vertices[faces_id[*fit_inf][(offset_+1)%3]].point, vertices[faces_id[*fit_inf][(offset_+2)%3]].point) > 0){
//         //     //                 //flip with previous triangle


//         //     //             }else{
//         //     //                 return;
//         //     //             }
//         //     //         }

//         //     //     }

//         //     //     // triangle_split(*fit, p);
//         //     //     // std::cout << "find infinit face" << std::endl;
//         //     //     return;
//         //     // }
//         // }else{
//         //     if(in_triangle(p, vertices[faces_id[*fit][0]].point, vertices[faces_id[*fit][1]].point, vertices[faces_id[*fit][2]].point) > 0){
//         //         std::cout << "triangle split : " << *fit << std::endl;
//         //         // std::cout << "signe : " << tmp;
//         //         triangle_split(*fit, p);
//         //         return;
//         //     }
//         // }
//         if(in_triangle(p, vertices[faces_id[*fit][0]].point, vertices[faces_id[*fit][1]].point, vertices[faces_id[*fit][2]].point) > 0){
//             std::cout << "triangle split : " << *fit << std::endl;
//             // std::cout << "signe : " << tmp;
//             triangle_split(*fit, p);
//             return;
//         }
//     }
// }
void Mesh::triangulate_naive(std::vector<Point> points){
    for(Point p : points){
        std::cout << "inster : (" << p._x << ", " << p._y << ", " << p._z << ")" << std::endl;
        insert_point(p);
    }
}