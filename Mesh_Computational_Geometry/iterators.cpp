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

