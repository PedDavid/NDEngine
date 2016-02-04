#include "buffers.h"

namespace core {	namespace graphics {
	vao::vao() {
		glGenVertexArrays(1, &id);
	}
}}