#pragma once
#include <vector>
#include <Vector2f.h>
class Bible
{
public:
	Bible(Point2f pos);
	~Bible();
	void Draw();
	void Update(float e);
	Point2f m_Pos{};
	float m_elapsedSec{};
	float timespan{ 3.f };
private:
};

class Player
{
public:
	Player(Point2f pos, int health, std::vector<Rectf>& rituals);
	~Player();

	void Input(const SDL_KeyboardEvent e);
	void InputStop(const SDL_KeyboardEvent e);

	std::vector<Rectf> GetRituals();
	void GetCultists(std::vector<Circlef> cultists);
	bool Ritual();
	void FinishRitual();
	void Draw();
	void Update(float elapsedSec);
	void CheckHit();
	void RecentlySabotaged(float e);
	std::vector<Bible*> GetBible();
	int GetBibleSize();

	Point2f m_Position;
	bool m_Hidden{ true };
	std::vector<Bible*> m_Bible;

private:

	std::vector<Rectf> m_Rituals;
	const std::vector<Rectf> m_StandartRituals;
	std::vector<Circlef> m_Cultist;

	const Point2f m_StartPosition;
	int m_Health{};
	const int m_StandartHealth;
	const float PLAYERSIZE{ 10.f };
	const int SPEED{ 3 };
	const int LOADINGBARRADIUS{ 20 };
	const int LOADINGBARWIDTH{ 5 };
	const int WINDOWTOP{ 800 };
	const int WINDOWRIGHT{ 1400 };
	const float MAXELAPSED{ 2.f };
	int m_Bibles{ 5 };
	const int STARTBIBLES{ 5 };
	float m_ElapsedSec{};
	bool m_IsMovingUp{ false };
	bool m_IsMovingDown{ false };
	bool m_IsMovingLeft{ false };
	bool m_IsMovingRight{ false };
	bool m_IsMoving{ false };
	bool m_TransformBlocked{ false };
	float m_ElapsedBlocked{};
	int m_HiddenCooldown{ 10 };
	bool m_Cooldown{ false };
	bool m_FinishedSabotaging{ false };
	float m_SabatageAgo{0.f};


};