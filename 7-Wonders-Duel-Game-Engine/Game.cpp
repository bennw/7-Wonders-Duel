#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.h"
#include "GameState.h"

// Adds a state on top of state stack
void Game::pushState(GameState * state)
{
	states.push(state);
}

// Removes a state from the top of state stack
void Game::popState()
{
	delete states.top();
	states.pop();
}

// Removes a state from the top of state stack (if there is one) and adds another state
void Game::changeState(GameState * state)
{
	if (!states.empty())
		popState();
	pushState(state);
}

// Returns pointer to top state, if there is one
GameState * Game::peekState()
{
	if (states.empty()) return nullptr;
	return states.top();
}

void Game::gameLoop()
{
	sf::Clock clock;
	
	// while loop for the game window
	while (window.isOpen())
	{
		// time-update controls
		sf::Time timeElapsed = clock.restart();
		float dt = timeElapsed.asSeconds();

		/* looks at state on top of stack and runs functions of that state 
		   if the state stack is empty, it runs the loop again...basically if
		   no state is loaded at the beginning of the game, a black screen is shown */
		if (peekState() == nullptr) continue;
		peekState()->handleInput();
		peekState()->update(dt);
		window.clear(sf::Color::Black);
		peekState()->draw(dt);
		window.display();
	}
}

Game::Game()
{
	// Loading textures, but should probably be done depending on state
	loadTextures();
	
	// Loading fonts
	loadFonts();

	// Loading sounds
	loadSounds();
	
	// Creating the window, with no resizing option
	window.create(sf::VideoMode(Seven_Wonders::GAME_WINDOW_WIDTH, Seven_Wonders::GAME_WINDOW_HEIGHT), "7 Wonders Duel", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

}

Game::~Game()
{
	// Will remove states one at a time from stack until empty
	while (!states.empty()) popState();
}

void Game::loadTextures()
{
	/* With a small game like this, it's probably ok to load all textures at game creation
	   However, for efficiency, only textures needed for a specific game state should be loaded unless 
	   states are stil stacked.  We can keep doing it this way for now, until we run into problems, if any. 
	   Textures should be defined in the game logic, in some type of container (likely a map). */
	textureManager.loadTexture("The Appian Way", "Resources/WonderCards/TheAppianWay.jpg");
	textureManager.loadTexture("Circus Maximus", "Resources/WonderCards/CircusMaximus.jpg");
	textureManager.loadTexture("The Colossus", "Resources/WonderCards/TheColossus.jpg");
	textureManager.loadTexture("The Great Library", "Resources/WonderCards/TheGreatLibrary.jpg");
	textureManager.loadTexture("The Great Lighthouse", "Resources/WonderCards/TheGreatLighthouse.jpg");
	textureManager.loadTexture("The Hanging Gardens", "Resources/WonderCards/TheHangingGardens.jpg");
	textureManager.loadTexture("The Mausoleum", "Resources/WonderCards/TheMausoleum.jpg");
	textureManager.loadTexture("Piraeus", "Resources/WonderCards/Piraeus.jpg");
	textureManager.loadTexture("The Pyramids", "Resources/WonderCards/ThePyramids.jpg");
	textureManager.loadTexture("The Sphinx", "Resources/WonderCards/TheSphinx.jpg");
	textureManager.loadTexture("The Statue of Zeus", "Resources/WonderCards/Zeus.jpg");
	textureManager.loadTexture("The Temple of Artemis", "Resources/WonderCards/TheTempleofArtemis.jpg");
	textureManager.loadTexture("Game Board", "Resources/BoardItems/gameboard.png");
	textureManager.loadTexture("GameStateStart Background", "Resources/Backgrounds/gamestartbackground.jpg");
	textureManager.loadTexture("GameStateStart Title", "Resources/Backgrounds/gamestarttitle.png");
	textureManager.loadTexture("GameStatePlaying Background", "Resources/Backgrounds/gameplayingbackgrounddark.jpg");
	textureManager.loadTexture("Age 1 Back", "Resources/CardImages/age1back.jpg");
	textureManager.loadTexture("Age 2 Back", "Resources/CardImages/age2back.jpg");
	textureManager.loadTexture("Age 3 Back", "Resources/CardImages/age3back.jpg");
	textureManager.loadTexture("Guild Back", "Resources/CardImages/guildback.jpg");
	textureManager.loadTexture("Academy", "Resources/CardImages/academy.jpg");
	textureManager.loadTexture("Altar", "Resources/CardImages/altar.jpg");
	textureManager.loadTexture("Apothecary", "Resources/CardImages/apothecary.jpg");
	textureManager.loadTexture("Aqueduct", "Resources/CardImages/aqueduct.jpg");
	textureManager.loadTexture("Archery Range", "Resources/CardImages/archeryrange.jpg");
	textureManager.loadTexture("Arena", "Resources/CardImages/arena.jpg");
	textureManager.loadTexture("Armory", "Resources/CardImages/armory.jpg");
	textureManager.loadTexture("Arsenal", "Resources/CardImages/arsenal.jpg");
	textureManager.loadTexture("Barracks", "Resources/CardImages/barracks.jpg");
	textureManager.loadTexture("Baths", "Resources/CardImages/baths.jpg");
	textureManager.loadTexture("Brewery", "Resources/CardImages/brewery.jpg");
	textureManager.loadTexture("Brickyard", "Resources/CardImages/brickyard.jpg");
	textureManager.loadTexture("Builders Guild", "Resources/CardImages/buildersguild.jpg");
	textureManager.loadTexture("Caravansery", "Resources/CardImages/caravansery.jpg");
	textureManager.loadTexture("Chamber of Commerce", "Resources/CardImages/chamberofcommerce.jpg");
	textureManager.loadTexture("Circus", "Resources/CardImages/circus.jpg");
	textureManager.loadTexture("Clay Pit", "Resources/CardImages/claypit.jpg");
	textureManager.loadTexture("Clay Pool", "Resources/CardImages/claypool.jpg");
	textureManager.loadTexture("Clay Reserve", "Resources/CardImages/clayreserve.jpg");
	textureManager.loadTexture("Courthouse", "Resources/CardImages/courthouse.jpg");
	textureManager.loadTexture("Customs House", "Resources/CardImages/customshouse.jpg");
	textureManager.loadTexture("Dispensary", "Resources/CardImages/dispensary.jpg");
	textureManager.loadTexture("Drying Room", "Resources/CardImages/dryingroom.jpg");
	textureManager.loadTexture("Fortifications", "Resources/CardImages/fortifications.jpg");
	textureManager.loadTexture("Forum", "Resources/CardImages/forum.jpg");
	textureManager.loadTexture("Gardens", "Resources/CardImages/gardens.jpg");
	textureManager.loadTexture("Garrison", "Resources/CardImages/garrison.jpg");
	textureManager.loadTexture("Glass-Blower", "Resources/CardImages/glassblower.jpg");
	textureManager.loadTexture("Glassworks", "Resources/CardImages/glassworks.jpg");
	textureManager.loadTexture("Guard Tower", "Resources/CardImages/guardtower.jpg");
	textureManager.loadTexture("Horse Breeders", "Resources/CardImages/horsebreeders.jpg");
	textureManager.loadTexture("Laboratory", "Resources/CardImages/laboratory.jpg");
	textureManager.loadTexture("Library", "Resources/CardImages/library.jpg");
	textureManager.loadTexture("Lighthouse", "Resources/CardImages/lighthouse.jpg");
	textureManager.loadTexture("Logging Camp", "Resources/CardImages/loggingcamp.jpg");
	textureManager.loadTexture("Lumber Yard", "Resources/CardImages/lumberyard.jpg");
	textureManager.loadTexture("Magistrates Guild", "Resources/CardImages/magistratesguild.jpg");
	textureManager.loadTexture("Merchants Guild", "Resources/CardImages/merchantsguild.jpg");
	textureManager.loadTexture("Moneylenders Guild", "Resources/CardImages/moneylendersguild.jpg");
	textureManager.loadTexture("Obelisk", "Resources/CardImages/obelisk.jpg");
	textureManager.loadTexture("Observatory", "Resources/CardImages/observatory.jpg");
	textureManager.loadTexture("Palace", "Resources/CardImages/palace.jpg");
	textureManager.loadTexture("Palisade", "Resources/CardImages/palisade.jpg");
	textureManager.loadTexture("Pantheon", "Resources/CardImages/pantheon.jpg");
	textureManager.loadTexture("Parade Ground", "Resources/CardImages/paradeground.jpg");
	textureManager.loadTexture("Pharmacist", "Resources/CardImages/pharmacist.jpg");
	textureManager.loadTexture("Port", "Resources/CardImages/port.jpg");
	textureManager.loadTexture("Press", "Resources/CardImages/press.jpg");
	textureManager.loadTexture("Quarry", "Resources/CardImages/quarry.jpg");
	textureManager.loadTexture("Rostrum", "Resources/CardImages/rostrum.jpg");
	textureManager.loadTexture("Sawmill", "Resources/CardImages/sawmill.jpg");
	textureManager.loadTexture("School", "Resources/CardImages/school.jpg");
	textureManager.loadTexture("Scientists Guild", "Resources/CardImages/scientistsguild.jpg");
	textureManager.loadTexture("Scriptorium", "Resources/CardImages/scriptorium.jpg");
	textureManager.loadTexture("Senate", "Resources/CardImages/senate.jpg");
	textureManager.loadTexture("Shelf Quarry", "Resources/CardImages/shelfquarry.jpg");
	textureManager.loadTexture("Shipowners Guild", "Resources/CardImages/shipownersguild.jpg");
	textureManager.loadTexture("Siege Workshop", "Resources/CardImages/siegeworkshop.jpg");
	textureManager.loadTexture("Stable", "Resources/CardImages/stable.jpg");
	textureManager.loadTexture("Statue", "Resources/CardImages/statue.jpg");
	textureManager.loadTexture("Stone Pit", "Resources/CardImages/stonepit.jpg");
	textureManager.loadTexture("Stone Reserve", "Resources/CardImages/stonereserve.jpg");
	textureManager.loadTexture("Study", "Resources/CardImages/study.jpg");
	textureManager.loadTexture("Tacticians Guild", "Resources/CardImages/tacticiansguild.jpg");
	textureManager.loadTexture("Tavern", "Resources/CardImages/tavern.jpg");
	textureManager.loadTexture("Temple", "Resources/CardImages/temple.jpg");
	textureManager.loadTexture("Theater", "Resources/CardImages/theater.jpg");
	textureManager.loadTexture("Town Hall", "Resources/CardImages/townhall.jpg");
	textureManager.loadTexture("Tribunal", "Resources/CardImages/tribunal.jpg");
	textureManager.loadTexture("University", "Resources/CardImages/university.jpg");
	textureManager.loadTexture("Walls", "Resources/CardImages/walls.jpg");
	textureManager.loadTexture("Wood Reserve", "Resources/CardImages/woodreserve.jpg");
	textureManager.loadTexture("Workshop", "Resources/CardImages/workshop.jpg");

	//load Progress Token textures
	textureManager.loadTexture("Agriculture", "Resources/ProgressTokens/agriculture.png");
	textureManager.loadTexture("Architecture", "Resources/ProgressTokens/architecture.png");
	textureManager.loadTexture("Economy", "Resources/ProgressTokens/economy.png");
	textureManager.loadTexture("Law", "Resources/ProgressTokens/law.png");
	textureManager.loadTexture("Masonry", "Resources/ProgressTokens/masonry.png");
	textureManager.loadTexture("Mathematics", "Resources/ProgressTokens/mathematics.png");
	textureManager.loadTexture("Philosophy", "Resources/ProgressTokens/philosophy.png");
	textureManager.loadTexture("Strategy", "Resources/ProgressTokens/strategy.png");
	textureManager.loadTexture("Theology", "Resources/ProgressTokens/theology.png");
	textureManager.loadTexture("Urbanism", "Resources/ProgressTokens/urbanism.png");
	

	textureManager.loadTexture("Conflict Pawn", "Resources/BoardItems/conflictpawn.png");

	textureManager.loadTexture("Victory Background", "Resources/Backgrounds/victoryBackground.jpg");
	textureManager.loadTexture("Science Background", "Resources/Backgrounds/scienceBackground.jpg");
	textureManager.loadTexture("Civilian Background", "Resources/Backgrounds/civilianBackground.jpg");

	textureManager.loadTexture("Military Token 2", "Resources/BoardItems/MilitaryToken_2CoinDestruction.jpg");
	textureManager.loadTexture("Military Token 5", "Resources/BoardItems/MilitaryToken_5CoinDestruction.jpg");

	textureManager.loadTexture("Wood", "Resources/Icons/wood.png");
	textureManager.loadTexture("Stone", "Resources/Icons/stone.png");
	textureManager.loadTexture("Clay", "Resources/Icons/clay.png");
	textureManager.loadTexture("Paper", "Resources/Icons/paper.png");
	textureManager.loadTexture("Glass", "Resources/Icons/glass.png");
	textureManager.loadTexture("Wild Basic", "Resources/Icons/wildbasic.png");
	textureManager.loadTexture("Wild Adv", "Resources/Icons/wildadv.png");
	textureManager.loadTexture("Coin", "Resources/Icons/coin.png");
	textureManager.loadTexture("Coin Big", "Resources/Icons/coinbig.png");
	textureManager.loadTexture("Coin One", "Resources/Icons/coinone.png");

	textureManager.loadTexture("Sci Arch", "Resources/Icons/sciarch.png");
	textureManager.loadTexture("Sci Mortar", "Resources/Icons/scimortar.png");
	textureManager.loadTexture("Sci Quill", "Resources/Icons/sciquill.png");
	textureManager.loadTexture("Sci Wheel", "Resources/Icons/sciwheel.png");
	textureManager.loadTexture("Sci Sundial", "Resources/Icons/scisundial.png");
	textureManager.loadTexture("Sci Globe", "Resources/Icons/sciglobe.png");
	textureManager.loadTexture("Sci Law", "Resources/Icons/scilaw.png");
}

void Game::loadFonts()
{
	/* It will be fine loading fonts at game creation since only a few will be needed. */
	fontManager.loadFont("Menu Font", "Resources/Fonts/americancaptain.ttf");
}

void Game::loadSounds()
{
	soundManager.loadSound("Game Start", "Resources/Sounds/gamestart.ogg");
	soundManager.loadSound("Build Card", "Resources/Sounds/buildcard.ogg");
	soundManager.loadSound("Discard Card", "Resources/Sounds/discardcard.ogg");
	soundManager.loadSound("Age 2", "Resources/Sounds/age2.ogg");
	soundManager.loadSound("Age 3", "Resources/Sounds/age3.ogg");
	soundManager.loadSound("Build Wonder", "Resources/Sounds/buildwonder.ogg");
	soundManager.loadSound("Build Progress Token", "Resources/Sounds/buildprogresstoken.ogg");
	soundManager.loadSound("Science Victory", "Resources/Sounds/sciencevictory.ogg");
	soundManager.loadSound("Civilian Victory", "Resources/Sounds/civilianvictory.ogg");
	soundManager.loadSound("Military Victory", "Resources/Sounds/militaryvictory.ogg");
}





