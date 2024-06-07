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
	case SDL_SCANCODE_X:
		break;
	case SDL_SCANCODE_SPACE:
		break;

	}
}

void Player::Update(float elapsedSec)
{
	for(int i{}; i < m_Bible.size(); ++i)
	{
		m_Bible[i]->Update(elapsedSec);
	}
	if(m_TransformBlocked)
	{
		m_ElapsedBlocked += elapsedSec;
		if(m_ElapsedBlocked >= 0.2)
		{
			m_ElapsedBlocked = 0;
			m_TransformBlocked = false;
		}
	}
	std::cout << m_Hidden;
	FinishRitual();
	if (Ritual() && !m_Hidden)
		m_ElapsedSec += elapsedSec;
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
		if (m_Position.x <= WINDOWRIGHT - SPEED)
		{
			m_Position.x += SPEED;
		}
	}
	if (m_IsMovingUp == true)
	{
		if(m_Position.y <= WINDOWTOP -SPEED)
		m_Position.y += SPEED;
	}
	if (m_IsMovingDown == true)
	{
		if(m_Position.y >= SPEED)
		m_Position.y -= SPEED;
	}
	if(m_Health <= 0)
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
	else if (e.keysym.scancode == SDL_SCANCODE_SPACE)
	{
		if(m_Bibles >= 0)
		{
			m_Bible.push_back(new Bible(m_Position));
			--m_Bibles;
		}
	}
	else if (e.keysym.scancode == SDL_SCANCODE_R)
	{
		if(!m_Cooldown)
			m_Hidden = !m_Hidden;
		else
		{
			m_TransformBlocked = true;
		}
	}



}


void Player::Draw()
{
	for(int i{}; i<= m_Bibles; ++i)
	{
		utils::SetColor(Color4f(0.f, 1.f, 1.f, 1.f));
		utils::DrawRect(10 + i*4, 10 + i*8, 40, 40, 2);
		utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
	}
	if(m_Hidden)
	{
		utils::SetColor(Color4f(0.f, 0.f, 1.f, 1.f));
		utils::FillArc(m_Position, 10, 10, 0, 7);
		utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
	}
	else 
	{
		if(m_TransformBlocked)
		{
			utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
			utils::DrawPoint(m_Position, PLAYERSIZE + 5.f);
			utils::DrawArc(m_Position, LOADINGBARRADIUS, LOADINGBARRADIUS, 0, 6.2832 * (m_ElapsedSec / MAXELAPSED), LOADINGBARWIDTH);
			utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
		}
		else
		{
			utils::SetColor(Color4f(1.f, 1.f, 0.f, 1.f));
			utils::DrawPoint(m_Position, PLAYERSIZE);
			utils::DrawArc(m_Position, LOADINGBARRADIUS, LOADINGBARRADIUS, 0, 6.2832 * (m_ElapsedSec / MAXELAPSED), LOADINGBARWIDTH);
			utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
		}
	}
	for (int i{}; i < m_Bible.size(); ++i)
	{
		m_Bible[i]->Draw();
	}

}

std::vector<Rectf> Player::GetRituals()
{

	return m_Rituals;
}

bool Player::Ritual()
 {
	for (int i{}; i < m_Rituals.size(); ++i)
	{
		if (utils::IsPointInRect(m_Position, m_Rituals[i]))
		{
			return true;
			//Rectf t{ m_Rituals[i] };
			//m_Rituals.erase(m_Rituals.begin() + i);
		}
	}
	return false;
}

void Player::GetCultists( std::vector<Circlef> cultists)
{
	m_Cultist = cultists;
}

void Player::CheckHit()
{
	if(!m_Hidden)
	{
		for (int i{}; i < m_Cultist.size(); ++i)
		{
			if (utils::IsPointInCircle(m_Position, m_Cultist[i]))
			{
				--m_Health;
				m_ElapsedSec = 0;
				m_Cooldown = false;
				m_Hidden = true;
				m_Bibles = STARTBIBLES;
			}
		}
	}
}

void Player::FinishRitual()
{
	if(!m_Hidden)
	{
		for (int i{}; i < m_Rituals.size(); ++i)
		{
			if (utils::IsPointInRect(m_Position, m_Rituals[i]))
			{
				if (m_ElapsedSec >= MAXELAPSED)
				{
					Rectf t{ m_Rituals[i] };
					m_Rituals.erase(m_Rituals.begin() + i);
					m_ElapsedSec = 0;
					m_FinishedSabotaging = true;
					m_Cooldown = true;
					++m_Bibles;
				}
			}
		}
	}

}

void Player::RecentlySabotaged( float e)
{
	if(m_FinishedSabotaging)
	{
		m_SabatageAgo += e;
		if (m_SabatageAgo >= m_HiddenCooldown)
		{
			m_Cooldown = false;
			m_SabatageAgo = 0;
		}
	}

}

std::vector<Bible*> Player::GetBible()
{
	return m_Bible;
}

int Player::GetBibleSize()
{
	return m_Bible.size();
}

Bible::Bible(Point2f pos)
	:m_Pos{ pos }
{

}

Bible::~Bible()
{
	m_Pos = Point2f(10000000, 10000000);
}

void Bible::Draw()
{
	utils::SetColor(Color4f(0.f, 1.f, 1.f, 1.f));
	utils::FillRect(m_Pos, 30, 30);
	utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
}

void Bible::Update(float e)
{
	m_elapsedSec += e;
	if (m_elapsedSec >= timespan)
	{
		Bible::~Bible();
	}
}