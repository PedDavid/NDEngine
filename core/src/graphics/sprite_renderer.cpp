#include "sprite_renderer.h"

namespace core {	namespace graphics {

	void SpriteRenderer::submit(Sprite *sprite) {
		m_RenderQueue.push(sprite);
	}
	void SpriteRenderer::flush() {
		math::vec3 tempScale;
		tempScale.z = 0.0f;
		while (!m_RenderQueue.empty()) {
			Sprite *sprite = m_RenderQueue.top();
			m_RenderQueue.pop();
			sprite->m_vao->bind();
			sprite->shader->enable();
			tempScale.x = sprite->m_Size.x;
			tempScale.y = sprite->m_Size.y;
			sprite->shader->setUniformMat4("ml_matrix", math::mat4::translation(sprite->m_Position) * math::mat4::scale(tempScale));
			glDrawElements(GL_TRIANGLES, sprite->elem_count, GL_UNSIGNED_INT, 0);
			sprite->shader->disable();
			sprite->m_vao->unbind();
		}
	}

}}