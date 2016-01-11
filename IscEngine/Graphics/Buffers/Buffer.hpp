#pragma once

#include <GL/glew.h>
#include <vector>
using namespace std;

namespace IscEngine {

	class Buffer {

		private:

			GLuint id;
			GLuint count;
			GLuint componentCount;

		public:

			Buffer(vector<float> data, unsigned int componentCount);
			~Buffer();

			void bind();
			void unbind();

			GLuint getCount() { return this->count; }
			GLuint getComponentCount() { return this->componentCount; }

	};

}