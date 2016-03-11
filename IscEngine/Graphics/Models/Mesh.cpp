#include "Mesh.hpp"
#include "../../Utils/Log.hpp"
using namespace IscEngine;

//////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
Mesh::Mesh(const vector<vec3>& vertices) {

	vector<float> vertexVector;
	for (const vec3& vertice : vertices) {
		vertexVector.push_back(vertice.x);
		vertexVector.push_back(vertice.y);
		vertexVector.push_back(vertice.z);
	}

	this->vertexBuffer = new Buffer(vertexVector, 3);
	this->indexBuffer = nullptr;
	this->normalBuffer = nullptr;
	this->UVBuffer = nullptr;
	this->tangentBuffer = nullptr;
	this->bitangentBuffer = nullptr;
	this->colorBuffer = nullptr;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
Mesh::Mesh(const vector<float>& vertices) {

	this->vertexBuffer = new Buffer(vertices, 3);
	this->indexBuffer = nullptr;
	this->normalBuffer = nullptr;
	this->UVBuffer = nullptr;
	this->tangentBuffer = nullptr;
	this->bitangentBuffer = nullptr;
	this->colorBuffer = nullptr;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
Mesh::Mesh(Buffer* const vertexBuffer) {

	this->vertexBuffer = vertexBuffer;
	this->indexBuffer = nullptr;
	this->normalBuffer = nullptr;
	this->UVBuffer = nullptr;
	this->tangentBuffer = nullptr;
	this->bitangentBuffer = nullptr;
	this->colorBuffer = nullptr;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
Mesh::~Mesh() {
	
	this->vertexArrays.clear();

	delete this->vertexBuffer; this->vertexBuffer = nullptr;
	delete this->indexBuffer; this->indexBuffer = nullptr;
	delete this->normalBuffer; this->normalBuffer = nullptr;
	delete this->UVBuffer; this->UVBuffer = nullptr;
	delete this->tangentBuffer; this->tangentBuffer = nullptr;
	delete this->bitangentBuffer; this->bitangentBuffer = nullptr;
	delete this->colorBuffer; this->colorBuffer = nullptr;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the vertex indices
void Mesh::addIndices(const vector<unsigned short>& indices) {

	this->indexBuffer = new IndexBuffer(indices);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the vertex indices
void Mesh::addIndices(const vector<unsigned int>& indices) {

	this->indexBuffer = new IndexBuffer(indices);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the IndexBuffer
void Mesh::addIndexBuffer(IndexBuffer* const indexBuffer) {

	this->indexBuffer = indexBuffer;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the normals
void Mesh::addNormals(const vector<float>& normals) {

	this->normalBuffer = new Buffer(normals, 3);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the normals
void Mesh::addNormals(const vector<vec3>& normals) {

	vector<float> normalVector;
	for (const vec3& vertice : normals) {
		normalVector.push_back(vertice.x);
		normalVector.push_back(vertice.y);
		normalVector.push_back(vertice.z);
	}

	this->addNormals(normalVector);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the normal Buffer
void Mesh::addNormalBuffer(Buffer* const normalBuffer) {

	this->normalBuffer = normalBuffer;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the UVs
void Mesh::addUVs(const vector<float>& textureCoords) {

	this->UVBuffer = new Buffer(textureCoords, 2);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the UVs
void Mesh::addUVs(const vector<vec2>& textureCoords) {

	vector<float> UVs;
	for (const vec2& vertice : textureCoords) {
		UVs.push_back(vertice.x);
		UVs.push_back(vertice.y);
	}

	this->addUVs(UVs);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the UV Buffer
void Mesh::addUVBuffer(Buffer* const textureBuffer) {

	this->UVBuffer = textureBuffer;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the tangents
void Mesh::addTangents(const vector<float>& tangents) {

	this->tangentBuffer = new Buffer(tangents, 3);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the tangents
void Mesh::addTangents(const vector<vec3>& tangents) {

	vector<float> tangentVector;
	for (const vec3& vertice : tangents) {
		tangentVector.push_back(vertice.x);
		tangentVector.push_back(vertice.y);
		tangentVector.push_back(vertice.z);
	}

	this->addTangents(tangentVector);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the tangent Buffer
void Mesh::addTangentBuffer(Buffer* const tangentBuffer) {

	this->tangentBuffer = tangentBuffer;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the bitangents
void Mesh::addBitangents(const vector<float>& bitangents) {

	this->bitangentBuffer = new Buffer(bitangents, 3);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the bitangents
void Mesh::addBitangents(const vector<vec3>& bitangents) {

	vector<float> bitangentVector;
	for (const vec3& vertice : bitangents) {
		bitangentVector.push_back(vertice.x);
		bitangentVector.push_back(vertice.y);
		bitangentVector.push_back(vertice.z);
	}

	this->addBitangents(bitangentVector);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the bitangent Buffer
void Mesh::addBitangentBuffer(Buffer* const bitangentBuffer) {

	this->bitangentBuffer = bitangentBuffer;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the colors
void Mesh::addColors(const vector<float>& colors) {

	this->colorBuffer = new Buffer(colors, 3);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the colors
void Mesh::addColors(const vector<vec3>& colors) {

	vector<float> colorVector;
	for (const vec3& vertice : colors) {
		colorVector.push_back(vertice.x);
		colorVector.push_back(vertice.y);
		colorVector.push_back(vertice.z);
	}

	this->colorBuffer = new Buffer(colorVector, 3);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Adds the color Buffer
void Mesh::addColorBuffer(Buffer* const colorBuffer) {

	this->colorBuffer = colorBuffer;

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Returns the VAO for the Shader if exists. If not, creates and returns it
VertexArray* Mesh::cacheVertexArray(Shader* const currentShader) {
	
	if (this->vertexArrays.find(currentShader) == this->vertexArrays.end()) {

		Log::cout << "  + Creating VAO for shader" << std::endl;

		int position;
		VertexArray* currentVertexArray = new VertexArray();
		position = currentShader->getAttributeLocation("vertexPosition_modelspace");
		if (position > -1 && this->vertexBuffer != nullptr) currentVertexArray->addBuffer(this->vertexBuffer, position);
		position = currentShader->getAttributeLocation("vertexUV");
		if (position > -1 && this->UVBuffer != nullptr) currentVertexArray->addBuffer(this->UVBuffer, position);
		position = currentShader->getAttributeLocation("vertexNormal_modelspace");
		if (position > -1 && this->normalBuffer != nullptr) currentVertexArray->addBuffer(this->normalBuffer, position);
		position = currentShader->getAttributeLocation("vertexTangent_modelspace");
		if (position > -1 && this->tangentBuffer != nullptr) currentVertexArray->addBuffer(this->tangentBuffer, position);
		position = currentShader->getAttributeLocation("vertexBitangent_modelspace");
		if (position > -1 && this->bitangentBuffer != nullptr) currentVertexArray->addBuffer(this->bitangentBuffer, position);

		vertexArrays[currentShader] = currentVertexArray;
		return currentVertexArray;

	} else {

		return vertexArrays[currentShader];

	}

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Renders the Mesh
void Mesh::render(const unsigned int type) { // WIREFRAME: GL_LINE_LOOP

	Shader* currentShader = Shader::currentShader;

	if (GLEW_ARB_vertex_array_object) {
		
		VertexArray* currentVertexArray = cacheVertexArray(currentShader);
		
		VertexArray::bind(currentVertexArray);

		if (this->indexBuffer != nullptr) {
			IndexBuffer::bind(this->indexBuffer);
			glDrawElements(type, this->indexBuffer->getSize(), this->indexBuffer->getType(), 0);
			IndexBuffer::unbind();
		} else {
			glDrawArrays(type, 0, this->vertexBuffer->getSize());
		}

		VertexArray::unbind();

	} else {

		int attributeLocation[5];

		attributeLocation[0] = currentShader->getAttributeLocation("vertexPosition_modelspace");
		if (attributeLocation[0] > -1 && this->vertexBuffer != nullptr) {
			glEnableVertexAttribArray(attributeLocation[0]);
			Buffer::bind(this->vertexBuffer);
			glVertexAttribPointer(
				attributeLocation[0],
				this->vertexBuffer->getComponentCount(),
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);
			Buffer::unbind();
		}

		attributeLocation[1] = currentShader->getAttributeLocation("vertexUV");
		if (attributeLocation[1] > -1 && this->UVBuffer != nullptr) {
			glEnableVertexAttribArray(attributeLocation[1]);
			Buffer::bind(this->UVBuffer);
			glVertexAttribPointer(
				attributeLocation[1],
				this->UVBuffer->getComponentCount(),
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);
			Buffer::unbind();
		}

		attributeLocation[2] = currentShader->getAttributeLocation("vertexNormal_modelspace");
		if (attributeLocation[2] > -1 && this->normalBuffer != nullptr) {
			glEnableVertexAttribArray(attributeLocation[2]);
			Buffer::bind(this->normalBuffer);
			glVertexAttribPointer(
				attributeLocation[2],
				this->normalBuffer->getComponentCount(),
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);
			Buffer::unbind();
		}

		attributeLocation[3] = currentShader->getAttributeLocation("vertexTangent_modelspace");
		if (attributeLocation[3] > -1 && this->tangentBuffer != nullptr) {
			glEnableVertexAttribArray(attributeLocation[3]);
			Buffer::bind(this->tangentBuffer);
			glVertexAttribPointer(
				attributeLocation[3],
				this->tangentBuffer->getComponentCount(),
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
				);
			Buffer::unbind();
		}

		attributeLocation[4] = currentShader->getAttributeLocation("vertexBitangent_modelspace");
		if (attributeLocation[4] > -1 && this->bitangentBuffer != nullptr) {
			glEnableVertexAttribArray(attributeLocation[4]);
			Buffer::bind(this->bitangentBuffer);
			glVertexAttribPointer(
				attributeLocation[4],
				this->bitangentBuffer->getComponentCount(),
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
				);
			Buffer::unbind();
		}

		if (this->indexBuffer != nullptr) {
			IndexBuffer::bind(this->indexBuffer);
			glDrawElements(type, this->indexBuffer->getSize(), this->indexBuffer->getType(), 0);
			IndexBuffer::unbind();
		} else {
			glDrawArrays(type, 0, this->vertexBuffer->getSize());
		}

		if (attributeLocation[0] > -1 && this->vertexBuffer != nullptr) glDisableVertexAttribArray(attributeLocation[0]);
		if (attributeLocation[1] > -1 && this->UVBuffer != nullptr) glDisableVertexAttribArray(attributeLocation[1]);
		if (attributeLocation[2] > -1 && this->normalBuffer != nullptr) glDisableVertexAttribArray(attributeLocation[2]);
		if (attributeLocation[3] > -1 && this->tangentBuffer != nullptr) glDisableVertexAttribArray(attributeLocation[3]);
		if (attributeLocation[4] > -1 && this->bitangentBuffer != nullptr) glDisableVertexAttribArray(attributeLocation[4]);

	}

}