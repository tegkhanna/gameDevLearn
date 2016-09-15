#pragma once
#include "Agent.h"
const float HUMAN_SPEED = 5.0f;
class Human : public Agent
{
public:
	Human();
	virtual ~Human();
	void init(float speed, glm::vec2 pos, int id);
	void setBaraf();
	void setUnBaraf();
	void setId(int x) { _id = x; }
	int getId() const { return _id; }
	bool getBarafStatus() const { return _baraf; }
	virtual void update(const std::vector<std::string> &levelData,
						std::vector<Human*> &humans,
						float deltaTime) override;
private:
	bool _baraf;
	int _id;
	//float _frames = 0.0f;
};

