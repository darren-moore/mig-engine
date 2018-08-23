#include "PrimitiveRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

PrimitiveRenderer::PrimitiveRenderer() : Renderer() {
	shader_ = Locator::getResourceEngine()->getShader("defaultPrimitiveShader");
	initRenderData();
	ioEngine_ = Locator::getIOEngine();
}

PrimitiveRenderer::PrimitiveRenderer(Shader* shader) : Renderer(shader) {
	PrimitiveRenderer();
}

void PrimitiveRenderer::drawRectangle(float x1, float y1, float x2, float y2) {
	this->shader_->use();
	mat4 model = mat4(1.0);

	model = translate(model, vec3(x1, y1, 0.0f));
	model = scale(model, vec3(x2 - x1, y2 - y1, 1.0f));

	glm::mat4 projection = glm::ortho(0.0f, (float)ioEngine_->getWindowWidth(), (float)ioEngine_->getWindowHeight(), 0.0f, -1.0f, 1.0f);
	this->shader_->setMat4("projection", projection);
	this->shader_->setMat4("model", model);
	this->shader_->setVec3("inColor", vec3(.1, .3, 1));

	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO_);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


void PrimitiveRenderer::initRenderData() {
	GLuint VBO;
	GLfloat rectVertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->VAO_);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

	glBindVertexArray(this->VAO_);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
