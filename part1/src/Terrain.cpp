#include "Terrain.hpp"
#include "Image.hpp"
#include <Perlin2D.hpp>

#include <iostream>

// Constructor for our object
// Calls the initialization method
Terrain::Terrain(unsigned int xSegs, unsigned int zSegs) : 
                m_xSegments(xSegs), m_zSegments(zSegs) {
    std::cout << "(Terrain.cpp) Constructor called \n";

    // Create height data
    m_heightData = new float[m_xSegments*m_zSegments];

    // Generate Perlin noise
    Perlin2D hm(m_xSegments, m_zSegments, 15);
    hm.saveAsPPM("./assets/textures/noise.ppm");
    m_heightData = hm.getTexture();

    // Initialize the terrain
    Init();
}

// Destructor
Terrain::~Terrain(){
    // Delete our allocatted higheithmap data
    if(m_heightData!=nullptr){
        delete m_heightData;
    }
}


// Creates a grid of segments
// This article has a pretty handy illustration here:
// http://www.learnopengles.com/wordpress/wp-content/uploads/2012/05/vbo.png
// of what we are trying to do.
void Terrain::Init(){
    // Create the initial grid of vertices.

    // TODO: (Inclass) Build grid of vertices! 
    for(unsigned int z=0; z < m_zSegments; ++z){
        for(unsigned int x =0; x < m_xSegments; ++x){
            float u = ((float)x/(float)m_xSegments);
            float v = ((float)z/(float)m_zSegments);
            m_geometry.AddVertex(x,300.f / (1 + exp(-2 * pow(m_heightData[x+z*m_xSegments]+0.3,3) + 2))-100,z,u,v);
        }
    }
    
    // Figure out which indices make up each triangle
    // By writing out a few of the indicies you can figure out
    // the pattern here. Note there is an offset.
    
    // TODO: (Inclass) Build triangle strip
    for(unsigned int z=0; z < m_zSegments-1; ++z){
        for(unsigned int x =0; x < m_xSegments-1; ++x){
            m_geometry.AddIndex(x+(z*m_zSegments));
            m_geometry.AddIndex(x+(z*m_zSegments)+m_xSegments);
            m_geometry.AddIndex(x+(z*m_zSegments+1));

            m_geometry.AddIndex(x+(z*m_zSegments)+1);
            m_geometry.AddIndex(x+(z*m_zSegments)+m_xSegments);
            m_geometry.AddIndex(x+(z*m_zSegments)+m_xSegments+1);
        }
    }


   // Finally generate a simple 'array of bytes' that contains
   // everything for our buffer to work with.
   m_geometry.Gen();  
   // Create a buffer and set the stride of information
   m_vertexBufferLayout.CreateNormalBufferLayout(m_geometry.GetBufferDataSize(),
                                        m_geometry.GetIndicesSize(),
                                        m_geometry.GetBufferDataPtr(),
                                        m_geometry.GetIndicesDataPtr());
}

void Terrain::LoadTextures(std::string colormap, std::string detailmap, std::string auxilMap){ 
        // Load our actual textures
        m_textureDiffuse.LoadTexture(colormap, 0); // Found in object
        m_detailMap.LoadTexture(detailmap, 0);     // Found in object
        m_auxilDetail.LoadTexture(auxilMap, 0);
}
