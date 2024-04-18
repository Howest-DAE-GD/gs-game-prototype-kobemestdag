#include "pch.h"
#include "Game.h"
#include <utils.h>
#include <iostream>

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	SpawnRituals();
	SpawnCultists();
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	m_elapsedsec += elapsedSec;
	if(m_elapsedsec >= 0.05f)
	{
		m_elapsedsec -= 0.05f;
		CultistMovement();
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
	for (int i{}; i < m_Rituals.size(); ++i)
	{
		utils::FillRect(Rectf{ m_Rituals[i].x,m_Rituals[i].y,float(RECTSIZE), float(RECTSIZE) });
	}
	for (int i{}; i < m_Cultists.size(); ++i)
	{
		utils::FillArc(m_Cultists[i].x,m_Cultists[i].y,float(CULTISTSIZE), float(CULTISTSIZE),0.f,360.f );
	}

}

void Game::SpawnRituals()
{
	m_Rituals.push_back(Point2f{ 250.f,150.f });
	m_Rituals.push_back(Point2f{ 1150.f, 200.f });
	m_Rituals.push_back(Point2f{ 150.f, 680.f });
	m_Rituals.push_back(Point2f{ 1150.f, 500.f });

}
void Game::SpawnCultists()
{
	for(int i{}; i <= CULTISTSAMOUNT; ++i)
	{
		m_Cultists.push_back(Point2f{float( rand() % int((GetViewPort().width - 20))- 10),float(rand()% int((GetViewPort().height-20))-10) });
	}
}

void Game::CultistMovement()
{
	for (int i{}; i < m_Cultists.size(); ++i)
	{
		int rand1{ rand() % 3 };
		int rand2{ rand() % 3 };
		if(rand1 == 0)
		{
		}else if(rand1 == 1)
		{
			m_Cultists[i].x -= 10;
		}
		else if (rand1 == 2)
		{
			m_Cultists[i].x += 10;
		}

		if (rand2 == 0) {}
		else if (rand2 == 1)
		{
			m_Cultists[i].y -= 10;
		}
		else if (rand2 == 2)m_Cultists[i].y += 10;
		if (m_Cultists[i].x <= 0)
		{
			m_Cultists[i].x += 10;
		}
		if (m_Cultists[i].x >= GetViewPort().width)
		{
			m_Cultists[i].x -= 10;
		}
		if (m_Cultists[i].y <= 0)
		{
			m_Cultists[i].y += 10;
		}
		if (m_Cultists[i].y >= GetViewPort().height)
		{
			m_Cultists[i].y -= 10;
		}
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
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
