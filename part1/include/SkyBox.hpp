#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <iostream>
#include <vector>
#include <glad/glad.h>

class SkyBox{
public:
    // Constructor
    SkyBox(std::vector<std::string> faces);
    // Destructor
    ~SkyBox();
    // Load the cubemap from the given faces
    unsigned int loadCubemap();

private:
    // Stores the files for the faces of the cube
    std::vector<std::string> m_faces;
};

#endif