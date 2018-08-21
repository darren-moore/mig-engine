
#include "SpriteRenderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

SpriteRenderer::SpriteRenderer() : Renderer() {
	initRenderData();
	ioEngine_ = Locator::getIOEngine();
}

SpriteRenderer::SpriteRenderer(Shader* shader) : Renderer(shader) {
	SpriteRenderer();
}

void SpriteRenderer::setTexture(Texture* texture) {
	texture_ = texture;
}

void SpriteRenderer::draw(glm::vec2 position, glm::vec2 size, GLfloat rotation) {
	this->shader_->use();
	mat4 model = mat4(1.0);

	model = translate(model, vec3(position, 0.0f));

	// Rotate about centre.
	model = translate(model, vec3(vec2(0.5*texture_->width, 0.5*texture_->height), 0.0f));
	model = rotate(model, rotation, vec3(0.0f, 0.0f, 1.0f));
	model = translate(model, vec3(vec2(-0.5*texture_->width, -0.5*texture_->height), 0.0f));

	model = scale(model, vec3(size, 1.0f));

	glm::mat4 projection = glm::ortho(0.0f, (float)ioEngine_->getWindowWidth(), (float)ioEngine_->getWindowHeight(), 0.0f, -1.0f, 1.0f);
	this->shader_->setMat4("projection", projection);
	this->shader_->setMat4("model", model);
	this->shader_->setVec3("spriteColor", vec3(1, 1, 1));

	glActiveTexture(GL_TEXTURE0);
	texture_->bind();

	glBindVertexArray(VAO_);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


void SpriteRenderer::initRenderData() {
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

	glGenVertexArrays(1, &this->VAO_);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->VAO_);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
