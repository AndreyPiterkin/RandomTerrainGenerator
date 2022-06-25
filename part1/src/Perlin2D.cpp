#include <Perlin2D.hpp>

Perlin2D::Perlin2D(int width, int height, int s) {
    m_width = width;
    m_height = height;
    seed = s;
    m_tex2d = new float[width*height];
    // number of octaves
    float octaves = 8;
    // frequency (size of noise)
    for(int y = 0; y < m_height; y++){
        for(int x = 0; x < m_width; x++){
            float frequency = 0.003f;
            float amplitude = 12.0;
            float total = 0;
            float denom = 0.0;

            // performs octave passes, adding to total and computing denominator
            for(int i=0; i<octaves; i++) {
                denom += 256 * amplitude;
                total += perlin(x * frequency, y * frequency) * amplitude;
                amplitude *= 0.5;
                frequency *= 2;
            }

            // final noise value for this coordinate
            m_tex2d[y*m_width+x] = total/denom;
        }
    }
}

Perlin2D::~Perlin2D() {
    
}

// get the pointer of the internal noise texture
float* Perlin2D::getTexture() {
    return m_tex2d;
}

// linear interpolation
float Perlin2D::lerp(float a1, float a2, float t) {
    return a1 + t * (a2 - a1);
}

// produce the pseudorandom permutation
float Perlin2D::gradient(int x, int y) {
    int tmp = permutation[(y + seed) % 256];
    return permutation[(tmp + x) % 256];
}

// save texture as PPM P3
void Perlin2D::saveAsPPM(std::string filename) const {
    std::ofstream out;
    out.open(filename);

    out << "P3" << std::endl;
    out << m_width << " " << m_height << std::endl;
    out << 255 << std::endl;

    for (int i = 0; i < m_width * m_height; i++) {
        out << (int)(m_tex2d[i] * 255.f) << " " << (int)(m_tex2d[i] * 255.f) << " " << (int)(m_tex2d[i] * 255.f) << std::endl;
    }
}

// compute the noise at the given pixel, getting conrern gradients and interpolating the gradient and distance vectors
float Perlin2D::perlin(float x, float y) {
    int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = gradient(x_int, y_int);
    int t = gradient(x_int+1, y_int);
    int u = gradient(x_int, y_int+1);
    int v = gradient(x_int+1, y_int+1);
    float low = lerp(s, t, x_frac);
    float high = lerp(u, v, x_frac);
    return lerp(low, high, y_frac);
}



