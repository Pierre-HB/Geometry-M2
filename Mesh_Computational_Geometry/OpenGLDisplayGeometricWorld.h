#ifndef OPENGLDISPLAY_H
#define OPENGLDISPLAY_H

#include "mesh.h"

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

#endif // 