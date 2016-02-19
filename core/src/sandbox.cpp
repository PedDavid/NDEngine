#include "..\include\NDEngine.h"
#include <iostream>
#include "logger\log.h"
#include "util\file.h"
#include "util\directory.h"

#include "graphics\shader.h"
#include "graphics\buffers.h"
#include "graphics\sprite_renderer.h"

using namespace core;

class Game : public NDEngine {

	util::DirectoryWatcher *watcher;
	input::InputManager *inputx;
	graphics::Shader *shader;

	void hi() {
		shader->disable();
		delete shader;
		shader = new graphics::Shader("res/basic.vert", "res/basic.frag");
		shader->enable();
		shader->setUniformMat4("pr_matrix", math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	}
	
	graphics::SpriteRenderer *renderer;
	std::vector<graphics::Sprite*> sprites;

	void init() {
		watcher = new util::DirectoryWatcher("C:/Users/Pedro Admin/Documents/visual studio 2015/Projects/NDEngine/core/res/");
		window = new Window("Hello Window", 1280, 720);
		inputx = new input::InputManager(state::StateManager());
		class CommandA : public Command {
			Window *win;
			public:
			CommandA(Window *win) : win(win) {}
			void execute() { win->close(); }
		};
		inputx->setCommand(GLFW_KEY_ESCAPE, new CommandA(window));
		window->setInputManager(inputx);

		math::mat4 ortho = math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
		shader = new graphics::Shader("res/basic.vert", "res/basic.frag");
		shader->enable();
		shader->setUniformMat4("pr_matrix", ortho);

		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

		GLuint buffsize = 100;
		GLsizei length;
		GLsizei size;
		GLenum type;
		GLchar name[100];

		GLint count;
		glGetProgramiv(1, GL_ACTIVE_UNIFORMS, &count);
		std::cout << count << std::endl;
		for (int i = 0; i < count; ++i) {
			glGetActiveUniform(1, i, buffsize, &length, &size, &type, name);
			std::cout << "Type: " << type << " | Name: " << name << " | Size: " << size << " | Length: " << length << std::endl;
		}
		glGetProgramiv(1, GL_ACTIVE_ATTRIBUTES, &count);
		for (int i = 0; i < count; ++i) {
			glGetActiveAttrib(1, i, buffsize, &length, &size, &type, name);
			std::cout << "Type: " << type << " | Name: " << name << " | Size: " << size << " | Length: " << length << std::endl;
		}

		//GLuint vao;
		//glGenVertexArrays(1, &vao);
		//glBindVertexArray(vao);
		//GLuint vbo[2];
		//glGenBuffers(2, vbo);
		//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		//glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(1);
		//GLuint ibo;
		//glGenBuffers(1, &ibo);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
		//glBindVertexArray(0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//glBindVertexArray(vao);
		renderer = new graphics::SpriteRenderer();
		//for (int i = 0; i < 160; ++i) {
		//	for (int c = 0; c < 90; ++c) {
		//		if ((i + c) % 2 == 1)
		//			sprites.push_back(new graphics::Sprite(math::vec3(i * 0.1f, c * 0.1f, 0.0f), math::vec2(1.0f, 1.0f), 0xFF00FFFF, shader));
		//		else
		//			sprites.push_back(new graphics::Sprite(math::vec3(i * 0.1f, c * 0.1f, 0.0f), math::vec2(1.0f, 1.0f), 0x8822FFFF, shader));
		//	}
		//}
		sprites.push_back(new graphics::Sprite(math::vec3(0.0f, 0.0f, 0.0f), math::vec2(1.0f, 1.0f), 0x8822FFFF, shader));
		sprites.push_back(new graphics::Sprite(math::vec3(1.0f, 1.0f, 0.0f), math::vec2(2.0f, 3.0f), 0x8822FFFF, shader));
	}

	void update() {

	}

	void tick() {
		std::cout << "FPS: " << getFPS() << " | UPS: " << getUPS() << std::endl;
		if (watcher->updated()) {
			hi();
		}
	}

	void render() {
		double x, y;
		window->getCursorPosition(&x, &y);
		shader->enable();
		shader->setUniform2f("light_pos", math::vec2((float)(x * 16.0f / 1280.0f), (float)(9.0f - y * 9.0f / 720.0f)));
		for (auto sprite : sprites) {
			renderer->submit(sprite);
		}
		renderer->flush();
	}
};

//int main() {
//	Game game;
//	game.start();
//	return 0;
//}