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

	float roughness = 1.0f;
	float zpos = -1.0f;
	float rotation = 0.0f;
	float metalness = 0.14f;

	void init() {
		window = new Window("Hello Window", 1280, 720);
		math::mat4 ortho = math::mat4::prespective(70.0f, 16.0f/9.0f, 0.01f, 100.0f);
		shader = new graphics::Shader("res/pbr.vert", "res/pbr.frag");
		shader->enable();
		shader->setUniformMat4("pr_matrix", ortho);
		shader->setUniform3f("diffuse", math::vec3(0.92, 0.64, 0.55));
		shader->setUniform3f("light_pos", math::vec3(0.0f, 0.0f, 0.0f));
		mesh = new graphics::Mesh("C:/Users/Pedro Admin/Desktop/cube.obj");
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_FRAMEBUFFER_SRGB);
	}

	void update() {
		if (window->getKey(GLFW_KEY_UP) == GLFW_PRESS)
			zpos -= 0.01f;
		if (window->getKey(GLFW_KEY_DOWN) == GLFW_PRESS)
			zpos += 0.01f;
		if (window->getKey(GLFW_KEY_LEFT) == GLFW_PRESS)
			rotation -= 1.0f;
		if (window->getKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
			rotation += 1.0f;
		if (window->getKey(GLFW_KEY_R) == GLFW_PRESS) {
			delete shader;
			math::mat4 ortho = math::mat4::prespective(70.0f, 16.0f / 9.0f, 0.01f, 100.0f);
			shader = new graphics::Shader("res/simple.vert", "res/simple.frag");
			shader->enable();
			shader->setUniformMat4("pr_matrix", ortho);
			shader->setUniform3f("light_pos", math::vec3(0.0f, 0.0f, 0.0f));
			shader->setUniform3f("diffuse", math::vec3(0.92, 0.64, 0.55));
		}
		if (window->getKey(GLFW_KEY_W) == GLFW_PRESS)
			metalness += 0.01f;
		if (window->getKey(GLFW_KEY_S) == GLFW_PRESS)
			metalness -= 0.01f;
		if (window->getKey(GLFW_KEY_A) == GLFW_PRESS)
			roughness -= 0.01f;
		if (window->getKey(GLFW_KEY_D) == GLFW_PRESS)
			roughness += 0.01f;
	}

	void tick() {
		std::cout << "FPS: " << getFPS() << " | UPS: " << getUPS() << std::endl;
		std::cout << "Roughness: " << roughness << " | Metalness: " << metalness << std::endl;
	}

	void render() {
		shader->enable();
		math::mat4 ml = math::mat4::translation(math::vec3(0.0f, -0.1f, zpos)) * math::mat4::rotation(rotation, math::vec3(0.0, 1.0, 0.0)) * math::mat4::scale(0.3f);
		shader->setUniformMat4("ml_matrix", ml);
		shader->setUniform1f("roughness", roughness);
		shader->setUniform1f("metalness", metalness);
		glBindVertexArray(mesh->getVaoID());
		glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, (GLvoid*)0);
	}
};

int main() {
	MeshTest game;
	game.start();
	return 0;
}