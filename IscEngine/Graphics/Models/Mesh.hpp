#pragma once

#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include <GLM/glm.hpp>
using namespace glm;

#include "../Buffers/Buffers.hpp"
#include "../Shaders/Base/Shader.hpp"

namespace IscEngine {

	class Mesh {

		private:
			
			std::map<Shader*, VertexArray*> vertexArrays; // Each Shader has different Attribute positions :'(

			Buffer* vertexBuffer; // 0
			IndexBuffer* indexBuffer;
			Buffer* normalBuffer; // 1
			Buffer* textureBuffer; // 2
			Buffer* colorBuffer; // 3

		public:

			Mesh(vector<float> vertices);
			Mesh(vector<vec3> vertices);
			Mesh(Buffer* vertexBuffer);
			~Mesh();

			void addIndexes(vector<unsigned short> indexes);
			void addIndexes(vector<unsigned int> indexes);
			void addIndexBuffer(IndexBuffer* indexBuffer);

			void addNormals(vector<float> normals);
			void addNormalBuffer(Buffer* normalBuffer);

			void addTextureCoords(vector<float> textureCoords);
			void addTextureBuffer(Buffer* textureBuffer);

			void addColors(vector<float> colors);
			void addColorBuffer(Buffer* colorBuffer);

			void render(GLenum type);

	};

}