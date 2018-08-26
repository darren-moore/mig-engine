
#include "SpriteRenderer.h"
#include "LAutils.h"

using namespace Eigen;

SpriteRenderer::SpriteRenderer() : Renderer() {
	shader_ = Locator::getResourceEngine()->getShader("defaultSpriteShader");
	initRenderData();
	ioEngine_ = Locator::getIOEngine();
}

SpriteRenderer::SpriteRenderer(Shader* shader) : Renderer(shader) {
	SpriteRenderer();
}

void SpriteRenderer::setTexture(Texture* texture) {
	texture_ = texture;
}

void SpriteRenderer::draw(Eigen::Vector2f position, Eigen::Vector2f size, float rotation) {
	this->shader_->use();
	Matrix4f model = Matrix4f::Identity();

	model = eTranslate(model, Vector3f(position.x(), position.y(),0.0f));

	// Rotate about centre.
	model = eTranslate(model, Vector3f(0.5*texture_->width, 0.5*texture_->height, 0.0f));
	model = eRotate(model, rotation, Vector3f(0.0f, 0.0f, 1.0f));
	model = eTranslate(model, Vector3f(-0.5*texture_->width, -0.5*texture_->height, 0.0f));

	model = eScale(model, Vector3f(size.x(), size.y(), 1.0));

	Matrix4f projection = eOrtho(0.0f, (float)ioEngine_->getWindowWidth(), (float)ioEngine_->getWindowHeight(), 0.0f, -1.0f, 1.0f);
	this->shader_->setMat4("projection", projection);
	this->shader_->setMat4("model", model);
	this->shader_->setVec3("spriteColor", Eigen::Vector3f(1, 1, 1));

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
