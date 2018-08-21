#include "RenderEngine.h"


void RenderEngine::init() {

}

void RenderEngine::stop() {

}

void RenderEngine::setShader(Shader shader) {
	glUseProgram(shader.ID);
}

void RenderEngine::drawRectangle(float x1, float y1, float x2, float y2) {

}

void RenderEngine::setClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void RenderEngine::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}
