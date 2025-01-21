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


class GameEngine3D : public olcConsoleGameEngine {
    // Constructor
public :
    GameEngine3D() {
        m_sAppName = L"3D Game Engine Demo";
    }

    // overridden functions
public :
    bool OnUserCreate() override {
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
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
