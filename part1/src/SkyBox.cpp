#include "SkyBox.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Constructor
SkyBox::SkyBox(std::vector<std::string> faces){
    m_faces = faces;
}

// Destructor
SkyBox::~SkyBox(){

}

// Load the cubemap from the given faces
unsigned int SkyBox::loadCubemap()
{
    // Generate and bind texture
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    // Set the texture target parameter for each face of the cubemap 
    int width, height, nrChannels;
    for (unsigned int i = 0; i < m_faces.size(); i++)
    {
        unsigned char *data = stbi_load(m_faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << m_faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    // Specify wrapping and filtering methods
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}  