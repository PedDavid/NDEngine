#pragma once

#include "../shader.h"
#include "../renderable/renderable_2d.h"

#include <math\vec3.h>
#include <math\vec4.h>

namespace core { namespace graphics {

	class Renderer2D {

	public:

		Renderer2D();

		void submit(Renderable2D *renderable);
		void flush(Shader *shader);
	
	};
}}