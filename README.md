# Mig Engine
A WIP 2D game engine utilizing an Entity-Component-System(ECS) architecture, built in C++.
##### External libraries/frameworks:
[OpenGL](https://www.opengl.org/) for rendering, [GLFW](http://www.glfw.org/) for window creation, [Eigen](http://eigen.tuxfamily.org/) for vector/matrix math, [Glad](https://glad.dav1d.de/) for OpenGL loading, [irrKlang](https://www.ambiera.com/irrklang/) for audio, and [stb](https://github.com/nothings/stb/blob/master/stb_image.h) for image loading.

#### Usage guide
First create a game, specifying the window width and height.
```
Game myGame(800, 600);
```
You can add resources such as textures with the ```ResourceEngine```. We utilize a service locator to provide access to these sub-engines.
```
Locator::getResourceEngine()->addTexture("mySprite.png", "mySprite");
```
You will fill your game with *Entities*, which can take on a variety of forms. Their form depends on which *components* are applied to them. Components give entities specific properties like a collision-shape or sprite. Note that an entity with applied components does nothing on its own.
```
Entity* e = new Entity();
e->applyComponent<Sprite>(Locator::getResourceEngine()->getTexture("mySprite");
e->applyComponent<gTransform>(Eigen::Vector3f(0,0,0));
```
*Systems* make your game come alive by acting on different entities. Which entities a given system acts on depends on which components it has.
```
myGame.addSystem(new SpriteRenderSystem());
```
Finally, start the game.
```
myGame.start();
```
---
Below we find the ```Sprite``` component used above. Note that the component has no functionality other than storing data. Derive from ```Component``` to create a new component.

```
struct Sprite : public Component {
	Sprite(Texture* texture, Eigen::Vector2f origin = Eigen::Vector2f::Zero()) : texture(texture), origin(origin) {};
	Texture* texture;
	Eigen::Vector2f origin;
};
```
Here is the ```SpriteRenderSystem``` used above. Note that it acts only on entities with ```Sprite``` and ```gTransform``` components applied. The filtering is performed in the base class using ```std::bitset```. Derive from ```System``` to create a new system. You should define ```init``` to add required components and ```execute``` to apply behaviours.
```
class SpriteRenderSystem : public System {
public:
	void init() {
		addRequiredComponent<Sprite>();
		addRequiredComponent<gTransform>();
		renderEngine_ = Locator::getRenderEngine();
		ioEngine_ = Locator::getIOEngine();
	}
private:
	RenderEngine* renderEngine_;
	IOEngine* ioEngine_;

	void execute(Entity* e, const float dt) {
		gTransform* t = e->getComponent<gTransform>();
		renderEngine_->drawTexture(e->getComponent<Sprite>()->texture, t->position, t->scale, t->rotation);
	}
};
```

##### Resources I found helpful:
* [Game Engine Architecture](https://www.gameenginebook.com/)
* [Game Programming Patterns](http://gameprogrammingpatterns.com/)
* [This Stack Exchange answer](https://gamedev.stackexchange.com/a/31491) on ECS.
* [LearnOpenGL](https://learnopengl.com/)
