#include "PrimitiveRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>
#define PI 3.14159265
using namespace glm;

PrimitiveRenderer::PrimitiveRenderer() : Renderer() {
	shader_ = Locator::getResourceEngine()->getShader("defaultPrimitiveShader");
	initRectangleData();
	initCircleData(circleNumSides_);
	ioEngine_ = Locator::getIOEngine();
}

PrimitiveRenderer::PrimitiveRenderer(Shader* shader) : Renderer(shader) {
	PrimitiveRenderer();
}

void PrimitiveRenderer::drawRectangle(float x1, float y1, float x2, float y2) {
	shader_->use();
	mat4 model = mat4(1.0);

	model = translate(model, vec3(x1, y1, 0.0f));
	model = scale(model, vec3(x2 - x1, y2 - y1, 1.0f));

	glm::mat4 projection = glm::ortho(0.0f, (float)ioEngine_->getWindowWidth(), (float)ioEngine_->getWindowHeight(), 0.0f, -1.0f, 1.0f);
	shader_->setMat4("projection", projection);
	shader_->setMat4("model", model);
	shader_->setVec3("inColor", vec3(.1, .3, 1));

	glBindVertexArray(rectangleVAO_);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void PrimitiveRenderer::drawCircle(float x, float y, float r) {
	shader_->use();
	mat4 model = mat4(1.0);

	model = translate(model, vec3(x, y, 0.0f));
	model = scale(model, vec3(r, r, 1.0f));

	glm::mat4 projection = glm::ortho(0.0f, (float)ioEngine_->getWindowWidth(), (float)ioEngine_->getWindowHeight(), 0.0f, -1.0f, 1.0f);
	shader_->setMat4("projection", projection);
	shader_->setMat4("model", model);
	shader_->setVec3("inColor", vec3(.1, 3, .1));

	glBindVertexArray(circleVAO_);
	glDrawElements(GL_TRIANGLES, 3*(circleNumSides_+1), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void PrimitiveRenderer::setCircleNumSides(int n) {
	circleNumSides_ = n;
	initCircleData(n);
}

void PrimitiveRenderer::initCircleData(int nSides) {
	glGenVertexArrays(1, &circleVAO_);
	glBindVertexArray(circleVAO_);

	// +1 for centre vertex
	GLfloat* circleVertices = (GLfloat*) malloc(sizeof(GLfloat)*2*(nSides+2));
	circleVertices[0] = 0;
	circleVertices[1] = 0;
	for (int i = 0; i <= nSides; i++) {
		int x_i = (i + 1) * 2;
		circleVertices[x_i] = cos(2*PI*i/nSides);
		circleVertices[x_i + 1] = sin(2*PI*i/ nSides);
	}

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * (nSides + 2), circleVertices, GL_STATIC_DRAW);

	GLuint* indices = (GLuint*) malloc(sizeof(GLuint)*3*(nSides+1));
	for (int i = 0; i <= nSides; i++) {
		indices[i * 3] = 0;
		indices[i * 3 + 1] = i;
		indices[i * 3 + 2] = i+1;
	}
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3*(nSides+1), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	delete circleVertices;
	delete indices;
}

void PrimitiveRenderer::initRectangleData() {
	glGenVertexArrays(1, &rectangleVAO_);
	glBindVertexArray(rectangleVAO_);

	GLfloat rectVertices[] = {
		// Pos
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
