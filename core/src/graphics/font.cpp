#include "font.h"

#include "../logger/log.h"

namespace core {
	namespace graphics {

		Font::Font(std::string filePath, float size) {
			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 1);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, size, filePath.c_str());
			ASSERT(m_FTFont);
			LOG(Success, "Font", "Load file %s with size %.0f", m_FTFont->filename, m_FTFont->size);
		}

	}
}