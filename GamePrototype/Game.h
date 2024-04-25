#pragma once
#include "BaseGame.h"
#include <vector>
#include "Player.h"
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
	void GetRitualsLeft(std::vector<Rectf> rituals);

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	Player* m_Player;

	std::vector<Circlef> m_Cultists;
	std::vector<Rectf> m_Rituals;
	const int RECTSIZE{ 30 };
	const int CULTISTSAMOUNT{ 70 };
	const int CULTISTSIZE{ 10 };
	int m_cultistspeed{ 10 };
	float m_elapsedsec{};
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};