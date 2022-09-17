#include "SFML/Graphics.hpp"
#include "Camera.h"
#include "Sphere.h"
#include "Timer.h"
#include "Triangle.h"
#include <vector>


#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

int main()
{
	using namespace Raytracer;

	sf::RenderWindow raytracer_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Raytracer");


	sf::Sprite renderedSceneSprite;

	sf::Image renderedSceneImage;
	renderedSceneImage.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	sf::Texture renderedSceneTexture;
	renderedSceneTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);


	Raytracer::Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);

	std::vector<Geometry*> geometry;

	geometry.emplace_back(new Sphere(vec3(3.0f, 0.0f, 4.0f), 1.0f, GREEN));
	geometry.emplace_back(new Sphere(vec3(3.0f, 2.0f, 5.0f), 1.0f, RED));
	geometry.emplace_back(new Sphere(vec3(-3.0f, 0.0f, 4.0f), 1.0f, BLUE));
	geometry.emplace_back(new Sphere(vec3(1.0f, 0.0f, 8.0f), 1.0f, YELLOW));
	//geometry.emplace_back(new Sphere(vec3(-2.0f, 10.0f, 4.0f), 1.0f, WHITE, true));
	Geometry* light = new Sphere(vec3(-2.0f, 10.0f, 4.0f), 1.0f, WHITE, true);
	geometry.push_back(light);
	

	camera.Render(renderedSceneImage, geometry);
	renderedSceneTexture.update(renderedSceneImage);
	renderedSceneSprite.setTexture(renderedSceneTexture);

	float move_speed = 1.0f;

	while (raytracer_window.isOpen())
	{
		sf::Event event;
		while (raytracer_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				raytracer_window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Right)
				{
					light->pos += vec3(1.0f, 0, 0) * move_speed;
				}

				if (event.key.code == sf::Keyboard::Left)
				{
					light->pos += vec3(-1.0f, 0, 0) * move_speed;
				}

				if (event.key.code == sf::Keyboard::Up)
				{
					light->pos += vec3(0, 0, 1.0f) * move_speed;
				}

				if (event.key.code == sf::Keyboard::Down)
				{
					light->pos += vec3(0, 0, -1.0f) * move_speed;
				}

				camera.Render(renderedSceneImage, geometry);
				renderedSceneTexture.update(renderedSceneImage);
				renderedSceneSprite.setTexture(renderedSceneTexture);
			}
		}

		// Draw
		raytracer_window.clear();
		raytracer_window.draw(renderedSceneSprite);
		raytracer_window.display();
	}


	for (auto obj : geometry)
	{
		delete obj;
	}

	return 0;
}
