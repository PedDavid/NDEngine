#include "..\include\NDEngine.h"
#include <iostream>
#include "logger\log.h"
#include "util\file.h"
#include "util\directory.h"

#include "graphics\shader.h"
#include "graphics\buffers.h"
#include "graphics\sprite_renderer.h"
#include "graphics\mesh.h"

using namespace core;

class MeshTest : public NDEngine {


	graphics::Shader *shader;
	graphics::Mesh *mesh;
	math::mat4 ml;

	float rotation = 0.0f;

	void init() {
		window = new Window("Hello Window", 1280, 720);

		math::mat4 ortho = math::mat4::prespective(70.0f, 16.0f/9.0f, 0.01f, 100.0f);
		//math::mat4 ortho = math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
		shader = new graphics::Shader("res/simple.vert", "res/simple.frag");
		shader->enable();
		shader->setUniformMat4("pr_matrix", ortho);
		ml = math::mat4::translation(math::vec3(0.0f, 0.0f, -1.0f)) * math::mat4::rotation(150.0f, math::vec3(rotation, 1.0f, 0.0f)) * math::mat4::scale(0.025f);
		
		shader->setUniformMat4("ml_matrix", ml);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		mesh = new graphics::Mesh("C:/Users/Pedro Admin/Desktop/dragon.obj");
	}

	void update() {

	}

	void tick() {
		std::cout << "FPS: " << getFPS() << " | UPS: " << getUPS() << std::endl;
	}

	void render() {
		shader->enable();
		if (window->getKey(GLFW_KEY_LEFT) == GLFW_PRESS)
			rotation -= 0.01f;
		else if (window->getKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
			rotation += 0.01f;
		ml = math::mat4::translation(math::vec3(0.0f, 0.0f, -1.0f)) * math::mat4::rotation(150.0f, math::vec3(rotation, 1.0f, 0.0f)) * math::mat4::scale(0.025f);
		shader->setUniformMat4("ml_matrix", ml);
		glBindVertexArray(mesh->getVaoID());
		glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, (GLvoid*)0);
	}
};

int main() {
	MeshTest game;
	game.start();
	return 0;
}