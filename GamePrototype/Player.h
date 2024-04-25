#pragma once
#include <vector>
#include <Vector2f.h>
class Player
{
public:
	Player(Point2f pos, int health, std::vector<Rectf>& rituals);
	~Player();

	void Input(const SDL_KeyboardEvent e);
	void InputStop(const SDL_KeyboardEvent e);

	std::vector<Rectf> GetRituals();
	void GetCultists(std::vector<Circlef> cultists);
	void Ritual();
	void Draw();
	void Update();
	void CheckHit();

private:

	std::vector<Rectf> m_Rituals;
	const std::vector<Rectf> m_StandartRituals;
	std::vector<Circlef> m_Cultist;

	const Point2f m_StartPosition;
	Point2f m_Position;
	int m_Health{};
	const int m_StandartHealth;
	const float PLAYERSIZE{ 5.f };
	const int SPEED{ 3 };
	bool m_IsMovingUp{ false };
	bool m_IsMovingDown{ false };
	bool m_IsMovingLeft{ false };
	bool m_IsMovingRight{ false };
	bool m_IsMoving{ false };
};

