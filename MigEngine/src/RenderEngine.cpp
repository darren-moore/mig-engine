#include "RenderEngine.h"
#include "Locator.h"
#include "LAutils.h"

using namespace Eigen;

void RenderEngine::init() {
	textureShader_ = Locator::getResourceEngine()->getShader("defaultSpriteShader");
	ioEngine_ = Locator::getIOEngine();
	initTextureData();
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
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
