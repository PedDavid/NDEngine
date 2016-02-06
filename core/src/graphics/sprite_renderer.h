#pragma once

#include <stack>
#include "sprite.h"

namespace core {	namespace graphics {
	class SpriteRenderer {
		private:
		std::stack<Sprite*> m_RenderQueue;
		public:
		void submit(Sprite *sprite);
		void flush();
	};
}}