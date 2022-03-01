#include <GameController.hpp>
#include <Application.hpp>

GameController::GameController(sf::RenderWindow *window, Application *application) :
    application(application),
    inputRouter(&gameInputRouter),
    gameView(window, &model),
    headsUpDisplayView(window),
    gameInputRouter(gameLogic, this),
    gameLogic(&model),
    pauseMenuView(window, &pauseMenuState),
    pauseMenuInputRouter(&pauseMenuState, this)
{
    viewList.reserve(3);
    viewList.push_back(&gameView);
    viewList.push_back(&headsUpDisplayView);
}

void GameController::update()
{
    float continuousTime = continuousTimeClock.getElapsedTime().asSeconds();
    float elapsedTime = elapsedTimeClock.getElapsedTime().asSeconds();
    elapsedTimeClock.restart();

    if(model.getGameState() == Model::GameState::Paused) {
        continuousTime = 0.0f;
        elapsedTime = 0.0f;
    }

    inputRouter->pullEvents();
    gameLogic.update(elapsedTime);
    for(View* view : viewList) {
        view->draw(continuousTime);
    }
}

void GameController::startGame() {
    model.reset();
    gameLogic.init();
    headsUpDisplayView.setPlayer1(model.getPlayer(0));
    inputRouter = &gameInputRouter;

    gameView.setUp();
    headsUpDisplayView.setUp();
    pauseMenuView.setUp();

    elapsedTimeClock.restart();
    continuousTimeClock.restart();
}

void GameController::exitGame()
{
    viewList.pop_back();

    gameView.tearDown();
    headsUpDisplayView.tearDown();
    pauseMenuView.tearDown();

    application->exitGame();
}

void GameController::pauseGame()
{
    model.setGameState(Model::GameState::Paused);
    viewList.push_back(&pauseMenuView);
    inputRouter = &pauseMenuInputRouter;
}

void GameController::resumeGame()
{
    model.setGameState(Model::GameState::Running);
    viewList.pop_back();
    inputRouter = &gameInputRouter;
}
