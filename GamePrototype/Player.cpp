#include "pch.h"
#include "Player.h"
#include <utils.h>
#include <iostream>

Player::Player(Point2f pos, int health, std::vector<Rectf>& rituals)
	:m_StartPosition{ pos }, m_StandartRituals{rituals}, m_StandartHealth{health}
{
	m_Rituals = rituals;
	m_Position = m_StartPosition;
	m_Health = health;

}

Player::~Player()
{
}

void Player::Input(const SDL_KeyboardEvent e)
{

	switch (e.keysym.scancode)
	{
	case SDL_SCANCODE_A:
		m_IsMovingLeft = true;
		break;
	case SDL_SCANCODE_D:
		m_IsMovingRight = true;
		break;
	case SDL_SCANCODE_S:
		m_IsMovingDown = true;
		break;
	case SDL_SCANCODE_W:
		m_IsMovingUp = true;
		break;
	case SDL_SCANCODE_R:
		Ritual();
		break;
	case SDL_SCANCODE_X:
		break;
	case SDL_SCANCODE_SPACE:
		break;

	}
}

void Player::Update()
{
	std::cout << m_Health;
	CheckHit();
	if (m_IsMovingLeft == true || m_IsMovingRight == true || m_IsMovingUp == true || m_IsMovingDown == true)
		m_IsMoving = true;
	if (m_IsMovingLeft == true)
	{
		if (m_Position.x >= 0 + SPEED)
		{
			m_Position.x -= SPEED;
		}
	}
	if (m_IsMovingRight == true)
	{
		if (m_Position.x <= 2684 + SPEED)
		{
			m_Position.x += SPEED;
		}
	}
	if (m_IsMovingUp == true)
	{
		m_Position.y += SPEED;
	}
	if (m_IsMovingDown == true)
	{
		m_Position.y -= SPEED;
	}
	if(m_Health == 0)
	{
		m_Position = m_StartPosition;
		m_Rituals = m_StandartRituals;
		m_Health = m_StandartHealth;
	}
}

void Player::InputStop(const SDL_KeyboardEvent e)
{

	if (e.keysym.scancode == SDL_SCANCODE_D)
	{
		m_IsMovingRight = false;
	}
	else if (e.keysym.scancode == SDL_SCANCODE_A)
	{
		m_IsMovingLeft = false;
	}
	else if (e.keysym.scancode == SDL_SCANCODE_W)
	{
		m_IsMovingUp = false;
	}
	else if (e.keysym.scancode == SDL_SCANCODE_S)
	{
		m_IsMovingDown = false;
	}



}


void Player::Draw()
{
	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	utils::DrawPoint(m_Position, PLAYERSIZE);
	utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
}

std::vector<Rectf> Player::GetRituals()
{

	return m_Rituals;
}

void Player::Ritual()
{
	for (int i{}; i < m_Rituals.size(); ++i)
	{
		if (utils::IsPointInRect(m_Position, m_Rituals[i]))
		{
			Rectf t{ m_Rituals[i] };
			m_Rituals.erase(m_Rituals.begin() + i);
		}
	}
}

void Player::GetCultists( std::vector<Circlef> cultists)
{
	m_Cultist = cultists;
}

void Player::CheckHit()
{
	for (int i{}; i < m_Cultist.size(); ++i)
	{
		if (utils::IsPointInCircle(m_Position, m_Cultist[i]))
		{
			--m_Health;
		}
	}
	
}
