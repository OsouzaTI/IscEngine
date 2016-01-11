#include "VertexArray.hpp"
using namespace IscEngine;

#include <iostream>
using namespace std;

VertexArray::VertexArray() {

	glGenVertexArrays(1, &this->id);

}

VertexArray::~VertexArray() {

	for (Buffer* buffer : this->buffers) delete buffer;
	glDeleteVertexArrays(1, &this->id);

}

void VertexArray::addBuffer(Buffer* buffer, unsigned int index) {

	this->bind();
	buffer->bind();
	
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
	//glDisableVertexAttribArray(index);

	buffer->unbind();
	this->unbind();

	this->buffers.push_back(buffer);

}

void VertexArray::bind() {

	glBindVertexArray(this->id);

}

void VertexArray::unbind() {

	glBindVertexArray(0);

}