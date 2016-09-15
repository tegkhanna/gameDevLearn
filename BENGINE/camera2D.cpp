#include "camera2D.h"



//camera manager
namespace bengine

{
	camera2D::camera2D() :
		_screenH(500),
		_screenW(500),
		_orthoMatrix(1.0f),
		_needsMatUpdate(1),//check weather cameraneeds to be updated
		_scale(1),
		_positions(0.0f, 0.0f),
		_cameraMatrix(1.0f)
	{
	}


	camera2D::~camera2D()
	{
	}



	void camera2D::init(int screenW, int screenH)
	{
		_screenH = screenH;
		_screenW = screenW;
		_orthoMatrix = glm::ortho(0.0f, (float)screenW, 0.0f, (float)screenH);

	}


	void camera2D::update()
	{
		if (_needsMatUpdate)
		{
			//cam translate
			glm::vec3 translate(-_positions.x + _screenW/2, -_positions.y + _screenH / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

			_needsMatUpdate = false;
		}

	}

	glm::vec2 camera2D::ScrnToWorld(glm::vec2 screenCoords)
	{	//invert y axis;
		screenCoords.y = _screenH - screenCoords.y;
		
		//makes center 0,0
		screenCoords -= glm::vec2(_screenW / 2, _screenH / 2);
		//world cords according to scale
		screenCoords /= _scale;
		screenCoords += _positions;
		return screenCoords;
	}
	bool camera2D::isInViewBox(glm::vec2 position, glm::vec2 dimensions)
	{
		//collisoipn  check
		glm::vec2 scaledScreenDim = glm::vec2(_screenW, _screenH) / (_scale );
		const float MIN_DIST_X = dimensions.x / 2.0f + scaledScreenDim.x/ 2.0f;
		const float MIN_DIST_Y = dimensions.y / 2.0f + scaledScreenDim.y / 2.0f;
		
		glm::vec2 centerPos = _positions;//bad s
		glm::vec2 distVec = centerPos - (position + dimensions/2.0f); //gets the distance vector between centers	   
													   //x dir;
		float xDepth = MIN_DIST_X - abs(distVec.x);
		float yDepth = MIN_DIST_Y - abs(distVec.y);//absolute value

		if (xDepth > 0 && yDepth > 0)
		{
			return true;//if colliding, return true
		}
		return false;

	}
}