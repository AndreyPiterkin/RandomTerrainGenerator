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
    unsigned int loadCubemap();

private:
    std::vector<std::string> m_faces;
};

#endif