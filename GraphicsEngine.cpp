// GraphicsEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "olcConsoleGameEngine.h"


using namespace std;


struct vec3D {
    float x, y, z;
};

struct triangle3D {
    vec3D vert[3];
};

struct mesh3D {
    vector<triangle3D> triangleMesh;
};

struct mat4x4 {
    float m[4][4] = { 0 };
};


class GameEngine3D : public olcConsoleGameEngine {
    // Constructor
public :
    GameEngine3D() {
        m_sAppName = L"3D Game Engine Demo";
    }

private:
    mesh3D meshObject;
    mat4x4 projectionMatrix;

    void MatrixMultiplicationVector(vec3D& i, vec3D& o, mat4x4& m) {
        o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
        o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
        o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
        float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

        if (w != 0.0f) {
            o.x /= w;
            o.y /= w;
            o.z /= w;
        }
    }


    // overridden functions
public :
    bool OnUserCreate() override {
        meshObject.triangleMesh = {
            // SOUTH
            { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

            // EAST                                                      
            { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
            { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

            // NORTH                                                     
            { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
            { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

            // WEST                                                      
            { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

            // TOP                                                       
            { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
            { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

            // BOTTOM                                                    
            { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
        };

        float fFar = 1000.0f;
        float fNear = 1.0f;
        float fAspectRatio = (float)ScreenWidth() / (float)ScreenHeight();
        float fFOV = 90.0f;
        float fFOVRad = 1.0f / tanf(fFOV * 0.5f / 180.0f * 3.14159f);
        float fQuotient = fFar / (fFar - fNear);

        projectionMatrix.m[0][0] = fFOVRad * fAspectRatio;    
        projectionMatrix.m[1][1] = fFOVRad;
        projectionMatrix.m[2][2] = fQuotient;
        projectionMatrix.m[3][2] = -fNear * fQuotient;
        projectionMatrix.m[2][3] = 1.0f;
        projectionMatrix.m[3][3] = 0.0f;

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {

        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

        // draw triangles
        for (auto triangle : meshObject.triangleMesh) {
            triangle3D triangleProjected;
            MatrixMultiplicationVector(triangle.vert[0], triangleProjected.vert[0], projectionMatrix);
            MatrixMultiplicationVector(triangle.vert[1], triangleProjected.vert[1], projectionMatrix);
            MatrixMultiplicationVector(triangle.vert[2], triangleProjected.vert[2], projectionMatrix);
        }

        return true;
    }
};

int main()
{
    GameEngine3D demo;
    if (demo.ConstructConsole(256, 240, 4, 4))
        demo.Start();


    //return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
