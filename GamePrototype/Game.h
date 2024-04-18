#pragma once
#include "BaseGame.h"
#include <vector>
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;
	void SpawnCultists();
	void SpawnRituals();
	void CultistMovement();

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	std::vector<Point2f> m_Cultists;
	Point2f m_Player{ 10.f,10.f };
	std::vector<Point2f> m_Rituals;
	const int RECTSIZE{ 30 };
	const int CULTISTSAMOUNT{ 25 };
	const int CULTISTSIZE{ 5 };
	float m_elapsedsec{};
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};