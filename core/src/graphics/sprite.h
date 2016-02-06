#pragma once

#include <math\vec3.h>
#include <math\vec2.h>

#include "buffers.h"
#include "shader.h"

namespace core {	namespace graphics {
	class Sprite {
		public:
		math::vec3 m_Position;
		math::vec2 m_Size;
		unsigned int m_Color;

		vao *m_vao;
		GLuint m_vaoid;
		size_t elem_count;

		Shader *shader;

		public:
		Sprite(math::vec3 position, math::vec2 size, unsigned int color, Shader *shader);
		~Sprite();
		
	};
}}