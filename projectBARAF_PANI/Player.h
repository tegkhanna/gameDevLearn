#pragma once
#include"Human.h"
#include<BENGINE\InputManager.h>
#include<BENGINE\camera2D.h>
//#include"Bullet.h"

//class Gun;

class Player : public Human
{
public:
	Player();
	~Player();

	void init(float speed, glm::vec2 position, bengine::InputManager *inputManager, bengine::camera2D *camera);
	void update(const std::vector<std::string> &levelData,
				std::vector<Human*> &humans,
				float deltaTime) override;
	/*void addGun(Gun *gun);*/
	void ZombieKilled() { _zombieKilled++; }
private:
	bengine::InputManager *_inputManager;
	/*std::vector<Gun*> _guns;*/
	int _currGunIndex;
	int _zombieKilled;
	bengine::camera2D *_camera;
	//std::vector<Bullet> *_bullets;
};

