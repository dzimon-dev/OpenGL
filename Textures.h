#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <../stb_image.h>

#include <string>
#include <iostream>
#include <fstream>


class Texture 
{
public:

	unsigned int ID;

	Texture(const char* texturePath, const bool flipped) {

        std::ifstream f(texturePath);
        if (!f.good()) {
            std::cout << texturePath << " Doesnt exist" << std::endl;
        }

		int width, height, nrChannels;
		unsigned char* data;


        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        //wrapovani textury
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        //filtrovani textury
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(flipped);
        
        data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

        if (data && nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else if (data && nrChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Nepovedla se nacist texture!!!" << std::endl;
        }

        stbi_image_free(data);

	}

};


#endif