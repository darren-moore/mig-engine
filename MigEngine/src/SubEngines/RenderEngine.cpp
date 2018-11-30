#include "RenderEngine.h"
#include "Locator.h"
#include "LAutils.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace Eigen;

void RenderEngine::init() {
	textureShader_ = Locator::getResourceEngine()->getShader("defaultSpriteShader");
	primitiveShader_ = Locator::getResourceEngine()->getShader("defaultPrimitiveShader");
	ioEngine_ = Locator::getIOEngine();
	initTextureData();
	initRectangleData();
	initLineData();
	initCircleData(circleNumSides_);

}

void RenderEngine::stop() {

}

void RenderEngine::setShader(Shader shader) {
	glUseProgram(shader.ID);
}

void RenderEngine::setClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void RenderEngine::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderEngine::drawTexture(Texture* texture, const Eigen::Vector2f& position, const Eigen::Vector2f& size, float rotation) {
	textureShader_->use();
	Matrix4f model = Matrix4f::Identity();

	model = eTranslate(model, Vector3f(position.x(), position.y(), 0.0f));

	// Rotate about centre.
	model = eTranslate(model, Vector3f(0.5f*texture->width, 0.5f*texture->height, 0.0f));
	model = eRotate(model, rotation, Vector3f(0.0f, 0.0f, 1.0f));
	model = eTranslate(model, Vector3f(-0.5f*texture->width, -0.5f*texture->height, 0.0f));

	model = eScale(model, Vector3f(size.x(), size.y(), 1.0));

	Matrix4f projection = eOrtho(0.0f, (float)ioEngine_->getWindowWidth(), (float)ioEngine_->getWindowHeight(), 0.0f, -1.0f, 1.0f);
	textureShader_->setMat4("projection", projection);
	textureShader_->setMat4("model", model);
	textureShader_->setVec3("spriteColor", Eigen::Vector3f(1, 1, 1));

	glActiveTexture(GL_TEXTURE0);
	texture->bind();

	glBindVertexArray(textureVAO_);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


void RenderEngine::drawLine(Eigen::Vector2f a, Eigen::Vector2f b) {
	primitiveShader_->use();
	Matrix4f model = Matrix4f::Identity();
	model = eTranslate(model, Vector3f(a.x(), a.y(), 0.0f));
	model = eScale(model, Vector3f(b.x() - a.x(), b.y() - a.y(), 1.0f));

	Matrix4f projection = eOrtho(0.0f, (float)ioEngine_->getWindowWidth(), (float)ioEngine_->getWindowHeight(), 0.0f, -1.0f, 1.0f);
	primitiveShader_->setMat4("projection", projection);
	primitiveShader_->setMat4("model", model);
	primitiveShader_->setVec3("inColor", Vector3f(.1f, .3f, 1));

	glBindVertexArray(lineVAO_);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

void RenderEngine::drawRectangle(Eigen::Vector2f p1, Eigen::Vector2f p2) {
	primitiveShader_->use();
	Matrix4f model = Matrix4f::Identity();

	model = eTranslate(model, Vector3f(p1.x(), p1.y(), 0.0f));
	model = eScale(model, Vector3f(p2.x() - p1.x(), p2.y() - p1.y(), 1.0f));

	Matrix4f projection = eOrtho(0.0f, (float)ioEngine_->getWindowWidth(), (float)ioEngine_->getWindowHeight(), 0.0f, -1.0f, 1.0f);
	primitiveShader_->setMat4("projection", projection);
	primitiveShader_->setMat4("model", model);
	primitiveShader_->setVec3("inColor", Eigen::Vector3f(.1f, .3f, 1));

	glBindVertexArray(rectangleVAO_);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void RenderEngine::drawCircle(Eigen::Vector2f c, float r) {
	primitiveShader_->use();
	Matrix4f model = Matrix4f::Identity();
	model = eTranslate(model, Vector3f(c.x(), c.y(), 0.0f));
	model = eScale(model, Vector3f(r, r, 1.0f));

	Matrix4f projection = eOrtho(0.0f, (float)ioEngine_->getWindowWidth(), (float)ioEngine_->getWindowHeight(), 0.0f, -1.0f, 1.0f);
	primitiveShader_->setMat4("projection", projection);
	primitiveShader_->setMat4("model", model);
	primitiveShader_->setVec3("inColor", Eigen::Vector3f(.1f, .3f, .1f));

	glBindVertexArray(circleVAO_);
	glDrawElements(GL_TRIANGLES, 3 * (circleNumSides_ + 1), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void RenderEngine::setCircleNumSides(int n) {
	circleNumSides_ = n;
	initCircleData(n);
}

void RenderEngine::initTextureData() {
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &textureVAO_);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(textureVAO_);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)(2 * sizeof(GL_FLOAT)));


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void RenderEngine::initCircleData(int nSides) {
	glGenVertexArrays(1, &circleVAO_);
	glBindVertexArray(circleVAO_);

	// +1 for centre vertex
	GLfloat* circleVertices = (GLfloat*)malloc(sizeof(GLfloat) * 2 * (nSides + 2));
	circleVertices[0] = 0;
	circleVertices[1] = 0;
	for (int i = 0; i <= nSides; i++) {
		int x_i = (i + 1) * 2;
		circleVertices[x_i] = cos(2 * (float)M_PI*i / nSides);
		circleVertices[x_i + 1] = sin(2 * (float)M_PI*i / nSides);
	}

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * (nSides + 2), circleVertices, GL_STATIC_DRAW);

	GLuint* indices = (GLuint*)malloc(sizeof(GLuint) * 3 * (nSides + 1));
	for (int i = 0; i <= nSides; i++) {
		indices[i * 3] = 0;
		indices[i * 3 + 1] = i;
		indices[i * 3 + 2] = i + 1;
	}
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 3 * (nSides + 1), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	delete circleVertices;
	delete indices;
}

void RenderEngine::initRectangleData() {
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

void RenderEngine::initLineData() {
	glGenVertexArrays(1, &lineVAO_);
	glBindVertexArray(lineVAO_);

	GLfloat lineVertices[] = {
		// Pos
		0.0f, 0.0f,
		1.0f, 1.0f,
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

