#include "..\include\NDEngine.h"
#include <iostream>
#include "logger\log.h"
#include "util\file.h"
#include "util\directory.h"

#include "graphics\shader.h"
#include "graphics\buffers.h"
#include "graphics\sprite_renderer.h"

#include <FreeImage.h>

#include "graphics\mesh.h"

using namespace core;

BYTE *data(std::string filePath, size_t *width, size_t *height, size_t *bpp) {
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib(0);
	BYTE *bits(0);

	const char *cFilePath = filePath.c_str();
	fif = FreeImage_GetFileType(cFilePath, 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(cFilePath);
	ASSERT(fif != FIF_UNKNOWN);
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, cFilePath);
	ASSERT(dib);

	bits = FreeImage_GetBits(dib);
	*width = FreeImage_GetWidth(dib);
	*height = FreeImage_GetHeight(dib);
	*bpp = FreeImage_GetBPP(dib);

	ASSERT(bits != 0 && width != 0 && height != 0);

	size_t size = *width * *height * (*bpp / 8);
	BYTE *result = new BYTE[size];
	memcpy(result, bits, size);
	FreeImage_Unload(dib);
	return result;
}


class Game : public NDEngine {

	int index = 0;
	graphics::Shader *shader;

	void init() {
		window = new Window("Hello Window", 1280, 720);
		size_t width, height, bpp;
		BYTE *bits = data("res/test.png", &width, &height, &bpp);
		BYTE *bits1 = data("res/test1.png", &width, &height, &bpp);

		shader = new graphics::Shader("res/texture.vert", "res/texture.frag");
		shader->enable();

		GLfloat vertices[] = {
			-0.5f, -0.5f,
			-0.5f, 0.5f,
			0.5f, 0.5f,
			0.5f, -0.5f
		};

		GLfloat uv[] = {
			0.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f
		};

		GLuint elements[] = {
			0, 1, 2, 2, 3, 0
		};

		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		GLuint vbo[2];
		glGenBuffers(2, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		GLuint ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(vao);

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
		glTextureStorage3D(texture, 1, GL_RGB8, width, height, 2);
		glTextureSubImage3D(texture, 0, 0, 0, 0, width, height, 1, GL_BGR, GL_UNSIGNED_BYTE, bits);
		glTextureSubImage3D(texture, 0, 0, 0, 1, width, height, 1, GL_BGR, GL_UNSIGNED_BYTE, bits1);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		delete bits;
		delete bits1;
	}

	void update() {

	}

	void tick() {
		std::cout << "FPS: " << getFPS() << " | UPS: " << getUPS() << std::endl;
		if (window->getKey(GLFW_KEY_UP) == GLFW_PRESS) {
			index++;
		}
		if (window->getKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
			index--;
		}
		if (index < 0) index = 0;
		if (index > 1) index = 1;
	}

	
	void render() {
		shader->enable();
		shader->setUniform1i("index", index);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
	}
};

int main() {
	Game game;
	game.start();
	return 0;
}