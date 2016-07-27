#include "NDEngine.h"
#include <iostream>
#include "logger\log.h"
#include "util\file.h"

#include "graphics\shader.h"
#include "graphics\buffers.h"
#include "graphics\sprite_renderer.h"
#include "graphics\mesh.h"

using namespace core;

class MeshTest : public NDEngine {

	graphics::Shader *shader;
	graphics::Shader *normal_debug;
	graphics::Mesh *mesh;

	float roughness = 1.0f;
	float zpos = -1.0f;
	float rotation = 0.0f;
	float metalness = 0.14f;
	math::vec3 light_pos = math::vec3(0.0f, 0.0f, 0.0f);

	void init() {
		//logger::setLogLevel(logger::LogLevel::Fatal);
		window = new Window("Hello Window", 1280, 720);
		math::mat4 ortho = math::mat4::prespective(70.0f, 16.0f/9.0f, 0.01f, 100.0f);
		normal_debug = new graphics::Shader({ 
			{graphics::ShaderType::VERTEX, "res/normal.vert"}, 
			{graphics::ShaderType::GEOMETRY, "res/normal.geom"},
			{graphics::ShaderType::FRAGMENT, "res/normal.frag"}
		});
		shader = new graphics::Shader({
			{ graphics::ShaderType::VERTEX, "res/pbr.vert" },
			{ graphics::ShaderType::FRAGMENT, "res/pbr.frag" }
		});
		
		shader->enable();
		shader->setUniformMat4("pr_matrix", ortho);
		shader->setUniform3f("diffuse", math::vec3(0.92f, 0.20f, 0.90f));

		normal_debug->enable();
		normal_debug->setUniformMat4("pr_matrix", ortho);
		
		mesh = new graphics::Mesh("C:/Users/Pedro Admin/Desktop/sphere.obj");
		
		glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
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
			shader = new graphics::Shader({
				{ graphics::ShaderType::VERTEX, "res/pbr.vert" },
				{ graphics::ShaderType::GEOMETRY, "res/pbr.geom" },
				{ graphics::ShaderType::FRAGMENT, "res/pbr.frag" }
			});
			shader->enable();
			shader->setUniformMat4("pr_matrix", ortho);
			shader->setUniform3f("diffuse", math::vec3(0.92f, 0.20f, 0.90f));
		}
		if (window->getKey(GLFW_KEY_W) == GLFW_PRESS)
			metalness += 0.01f;
		if (window->getKey(GLFW_KEY_S) == GLFW_PRESS)
			metalness -= 0.01f;
		if (window->getKey(GLFW_KEY_A) == GLFW_PRESS)
			roughness -= 0.01f;
		if (window->getKey(GLFW_KEY_D) == GLFW_PRESS)
			roughness += 0.01f;
		if (window->getKey(GLFW_KEY_J) == GLFW_PRESS)
			light_pos.x -= 0.1f;
		if (window->getKey(GLFW_KEY_L) == GLFW_PRESS)
			light_pos.x += 0.1f;
		if (window->getKey(GLFW_KEY_I) == GLFW_PRESS)
			light_pos.y += 0.1f;
		if (window->getKey(GLFW_KEY_K) == GLFW_PRESS)
			light_pos.y -= 0.1f;
		if (window->getKey(GLFW_KEY_U) == GLFW_PRESS)
			light_pos.z += 0.1f;
		if (window->getKey(GLFW_KEY_O) == GLFW_PRESS)
			light_pos.z -= 0.1f;
		if (roughness > 1.0f) roughness = 1.0f;
		if (roughness < 0.0f) roughness = 0.0f;
		if (metalness > 1.0f) metalness = 1.0f;
		if (metalness < 0.0f) metalness = 0.0f;
	}

	void tick() {
		//std::cout << "FPS: " << getFPS() << " | UPS: " << getUPS() << std::endl;
		std::cout << "Roughness: " << roughness << " | Metalness: " << metalness << " | Light Pos: " << light_pos << std::endl;
	}

	void render() {
		shader->enable();
		math::mat4 ml = math::mat4::translation(math::vec3(0.0f, 0.0f, zpos)) * math::mat4::rotation(rotation, math::vec3(0.0, 1.0, 0.0)) * math::mat4::scale(0.03f);
		shader->setUniformMat4("ml_matrix", ml);
		shader->setUniform3f("light_pos", light_pos);
		shader->setUniform1f("roughness", roughness);
		shader->setUniform1f("metalness", metalness);

		glBindVertexArray(mesh->getVaoID());
		glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, (GLvoid*)0);

		normal_debug->enable();
		normal_debug->setUniformMat4("ml_matrix", ml);
		normal_debug->setUniform3f("light_pos", light_pos);
		//normal_debug->setUniform1f("roughness", roughness);
		//normal_debug->setUniform1f("metalness", metalness);

		glBindVertexArray(mesh->getVaoID());
		glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, (GLvoid*)0);
	}
};

//int main() {
//	MeshTest game;
//	game.start();
//	return 0;
//}