#pragma once

#include <freetype-gl.h>

#include <string>

namespace core {	namespace graphics {

	class Font {
	private:
		ftgl::texture_atlas_t *m_FTAtlas;
		ftgl::texture_font_t *m_FTFont;
		
	public:
		Font(std::string filePath, float size);
	};

}}

