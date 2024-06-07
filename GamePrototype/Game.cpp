#include "pch.h"
#include "Game.h"
#include <utils.h>
#include <iostream>

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
	startScreen = new Texture{ "StartScreen.png" };
	endScreen = new Texture{ "EndScreen.png" };
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	SpawnRituals();
	SpawnCultists();
	m_Player = new Player{ Point2f(134.f, 62.f), 1 , m_Rituals};
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	m_Bible2 = m_Player->GetBible();
	if(running)
	{
		m_Player->RecentlySabotaged(elapsedSec);
		m_Player->GetCultists(m_Cultists);
		m_Player->Update(elapsedSec);
		m_Rituals = m_Player->GetRituals();
		m_elapsedsec += elapsedSec;
		if (m_elapsedsec >= 0.05f)
		{
			m_elapsedsec -= 0.05f;
			CultistMovement();
		}
	}


	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground();
	if (m_Rituals.empty())
	{
		endScreen->Draw(Point2f(0, 0), Rectf(0, 0, startScreen->GetWidth(), startScreen->GetHeight()));
	}else
	{
		if (running)
		{
			for (int i{}; i < m_Rituals.size(); ++i)
			{
				utils::SetColor(Color4f(0, 1, 0, 1));
				utils::FillRect(Rectf{ m_Rituals[i] });
				utils::SetColor(Color4f(1, 1, 1, 1));
			}
			for (int i{}; i < m_Cultists.size(); ++i)
			{
				utils::FillArc(m_Cultists[i].center, m_Cultists[i].radius, m_Cultists[i].radius, 0.f, 360.f);
			}
			m_Player->Draw();
		}
		else
		{
			startScreen->Draw(Point2f(0, 0), Rectf(0, 0, startScreen->GetWidth(), startScreen->GetHeight()));
		}
	}



}	

void Game::SpawnRituals()
{
	m_Rituals.push_back(Rectf{ 250.f,150.f   , float(RECTSIZE), float(RECTSIZE)});
	m_Rituals.push_back(Rectf{ 1150.f, 200.f , float(RECTSIZE), float(RECTSIZE)});
	m_Rituals.push_back(Rectf{ 150.f, 680.f  , float(RECTSIZE), float(RECTSIZE)});
	m_Rituals.push_back(Rectf{ 1150.f, 500.f , float(RECTSIZE), float(RECTSIZE)});

}
void Game::SpawnCultists()
{
	for(int i{}; i <= CULTISTSAMOUNT; ++i)
	{
		m_Cultists.push_back(Circlef(Point2f{float( rand() % int((GetViewPort().width - 20))- 10),float(rand()% int((GetViewPort().height-20))-10) }, float(CULTISTSIZE)));
	}
}

void Game::CultistMovement()
{
	for (int i{}; i < m_Cultists.size(); ++i)
	{
		for(int j{}; j < m_Player->GetBibleSize(); ++j)
		{
			if((abs(m_Player->m_Bible[j]->m_Pos.x - m_Cultists[i].center.x) + abs(m_Player->m_Bible[j]->m_Pos.y - m_Cultists[i].center.y)) <= 200)
			{
				if (m_Player->m_Bible[j]->m_Pos.x > m_Cultists[i].center.x) { m_Cultists[i].center.x += 10; }
				else
				{
					m_Cultists[i].center.x -= 10;
					break;

				}
				if (m_Player->m_Bible[j]->m_Pos.y > m_Cultists[i].center.y) { m_Cultists[i].center.y += 10; }
				else
				{
					m_Cultists[i].center.y -= 10;
					break;

				}
			}
		}
		int rand1{ rand() % 3 };
		int rand2{ rand() % 3 };
		if (rand1 == 0)
		{
		}
		else if (rand1 == 1)
		{
			m_Cultists[i].center.x -= m_cultistspeed;
		}
		else if (rand1 == 2)
		{
			m_Cultists[i].center.x += m_cultistspeed;
		}

		if (rand2 == 0) {}
		else if (rand2 == 1)
		{
			m_Cultists[i].center.y -= m_cultistspeed;
		}
		else if (rand2 == 2)m_Cultists[i].center.y += m_cultistspeed;
		if (m_Cultists[i].center.x <= 0)
		{
			m_Cultists[i].center.x += m_cultistspeed;
		}
		if (m_Cultists[i].center.x >= GetViewPort().width)
		{
			m_Cultists[i].center.x -= m_cultistspeed;
		}
		if (m_Cultists[i].center.x <= 0)
		{
			m_Cultists[i].center.y += m_cultistspeed;
		}
		if (m_Cultists[i].center.y >= GetViewPort().height)
		{
			m_Cultists[i].center.y -= m_cultistspeed;
		}
		if (!m_Player->m_Hidden)
		{
			if((abs(m_Player->m_Position.x - m_Cultists[i].center.x) + abs(m_Player->m_Position.y - m_Cultists[i].center.y)) <= 200)
			{
				if (m_Player->m_Position.x > m_Cultists[i].center.x) { m_Cultists[i].center.x += 3; }
				else
				{
					m_Cultists[i].center.x -= 3;

				}
				if (m_Player->m_Position.y > m_Cultists[i].center.y) { m_Cultists[i].center.y += 3; }
				else
				{
					m_Cultists[i].center.y -= 3;

				}
			}
		}
		
	}
}

void Game::GetRitualsLeft(std::vector<Rectf> rituals)
{
	m_Rituals = rituals;
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_Player->Input(e);
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_Player->InputStop(e);
	if (e.keysym.scancode == SDL_SCANCODE_T) running = true;
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
