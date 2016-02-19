#pragma once

#include <glew.h>

namespace core {	namespace graphics {

	class Mesh {
		private:
		GLuint m_Vao;
		GLsizei m_Count;

		public:
		Mesh(const char *filepath);
		~Mesh();

		private:
		void loadMeshFromObjFile(const char *filePath);

		public:
		inline GLuint getVaoID() const { return m_Vao; }
		inline GLsizei getVertexCount() const { return m_Count; }
	};

}}