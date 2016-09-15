#pragma once

#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

namespace bengine
{
	class camera2D
	{
	public:
		camera2D();
		~camera2D();

		void update();
		void init(int screenW, int screenH);
		glm::vec2 ScrnToWorld(glm::vec2 screenCoords);
		bool isInViewBox(glm::vec2 position, glm::vec2 dimensions);
		//setter
		void setPos(const glm::vec2 newPos) { _positions = newPos; _needsMatUpdate = true; }
		void setScale(float newScale) { _scale = newScale; _needsMatUpdate = true; }

		//getter
		glm::vec2 getPos() { return _positions; }
		float getScale() { return _scale; }
		glm::mat4 getCamMatrix() { return _cameraMatrix; }

	private:
		glm::mat4 _orthoMatrix;
		int _screenW, _screenH;
		bool _needsMatUpdate;
		float _scale;
		glm::vec2 _positions;
		glm::mat4 _cameraMatrix;


	};

}