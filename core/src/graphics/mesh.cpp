#include "mesh.h"

#include <fstream>
#include <vector>

#include <math\vec2.h>
#include <math\vec3.h>

#include "../logger/log.h"

#include <iostream>

namespace core {	namespace graphics {

	Mesh::Mesh(const char *filepath) {
		loadMeshFromObjFile(filepath);
	}

	Mesh::~Mesh() {
		//glDeleteVertexArrays(1, &m_Vao);
	}

	void Mesh::loadMeshFromObjFile(const char *filepath) {
		std::vector<math::vec3> vertices;	//vertices:	each vertex has xyz
		std::vector<math::vec2> uvs_;		//temp_uvs:	each uv	has	xy
		std::vector<math::vec3> normals_;	//temp_normals:	each normal has xyz
		
		std::vector<GLuint> vertex_indices, uv_indices_, normal_indices_;	//indices containers, only vertex is final (others are auxiliaries)
		math::vec3 vertex_;					//temp_vertex buffer used in each scan
		GLuint index_[9];					//temp_index buffer used in the indices scan

		std::ifstream in(filepath, std::ifstream::in | std::ios::binary);
		ASSERT(in);
		
		char str[256];						//buffer for a line
		char header[8];						//buffer for header(usually 2 chars at most but give some headroom)
		while (in.getline(str, 256)) {
			int changed = sscanf_s(str, "%s", header, 8);	//get header
			if (changed <= 0) continue;						//continue in empty or error case
			if (strcmp(header, "v") == 0) {
				sscanf_s(str, "v %f %f %f\n", &vertex_.x, &vertex_.y, &vertex_.z);
				vertices.push_back(vertex_);
			} else if (strcmp(header, "vt") == 0) {
				sscanf_s(str, "vt %f %f\n", &vertex_.x, &vertex_.y);
				uvs_.push_back(*(math::vec2 *)&vertex_);
			} else if (strcmp(header, "vn") == 0) {
				sscanf_s(str, "vn %f %f %f\n", &vertex_.x, &vertex_.y, &vertex_.z);
				normals_.push_back(vertex_);
			} else if (strcmp(header, "f") == 0) {
				sscanf_s(str, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", 
					&index_[0], &index_[1], &index_[2], 
					&index_[3], &index_[4], &index_[5], 
					&index_[6], &index_[7], &index_[8]);
				for (int i = 0; i < 3; ++i) {
					vertex_indices.push_back(index_[i * 3 + 0] - 1);
					uv_indices_.push_back(index_[i * 3 + 1] - 1);
					normal_indices_.push_back(index_[i * 3 +  2] - 1);
				}
			}
		}

		math::vec2 *uvs = new math::vec2[vertices.size()];
		math::vec3 *normals = new math::vec3[vertices.size()];

		for (GLuint i = 0; i < vertex_indices.size(); ++i) {
			GLuint vertexPointer = vertex_indices[i];
			uvs[vertexPointer] = uvs_[uv_indices_[i]];
			normals[vertexPointer] = normals_[normal_indices_[i]];
		}

		glGenVertexArrays(1, &m_Vao);
		glBindVertexArray(m_Vao);
		GLuint vbos[3];
		glGenBuffers(3, vbos);

		glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(math::vec3), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(math::vec3), normals, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_indices.size() * sizeof(GLuint), &vertex_indices[0], GL_STATIC_DRAW);
		m_Count = vertex_indices.size();

		delete uvs;
		delete normals;
	}

}}