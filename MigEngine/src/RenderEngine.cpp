#include "RenderEngine.h"


void RenderEngine::init() {

}

void RenderEngine::stop() {

}

void RenderEngine::run() {

}

void RenderEngine::setClearColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void RenderEngine::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}
