#pragma once
#include "RenderEngine.h"
#include "IOEngine.h"

// An implementation of the Service Locator pattern.
// Simply provide the sub-engines and  get them.
class Locator {
public:

	static IOEngine getIOEngine() { return ioEngine_; }
	static void provide(IOEngine& ioEngine) {
		ioEngine_ = ioEngine;
	}

	static RenderEngine getRenderEngine() { return renderEngine_; }
	static void provide(RenderEngine& RenderEngine) {
		renderEngine_ = renderEngine_;
	}

private:
	static IOEngine ioEngine_;
	static RenderEngine renderEngine_;
};