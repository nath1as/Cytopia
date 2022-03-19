#ifndef GAME_HXX_
#define GAME_HXX_

#ifndef VERSION
#define VERSION 0
#endif

#include "Scripting/ScriptEngine.hxx"
#include "engine/MessageQueue.hxx"
#include "util/Meta.hxx"
#include "GameService.hxx"
#ifdef USE_AUDIO
#include "services/AudioMixer.hxx"
#endif
#include "services/Randomizer.hxx"
#include "services/GameClock.hxx"
#include "services/ResourceManager.hxx"
#include "LOG.hxx"
#include "Exception.hxx"
#include "../game/GamePlay.hxx"

#include <thread>

using Thread = std::thread;
using RuntimeError = std::runtime_error;

class Game
{
public:
  /**
   * @brief Creates a game
   * @details Initializes all GameServices and starts the threads
   */
  Game();

  /**
   * @brief Destroy a game
   */
  virtual ~Game() = default;

  /** @brief starts setting up the game
    * starts game initialization.
    */
  virtual bool initialize();

  /** @brief begins the game
    * starts running the game
    * @param SkipMenu if the main menu should be skipped or not
    */
  virtual void run(bool SkipMenu = false);

  /** @brief ends the game
    * shuts down the game
    */
  virtual void shutdown();

  /** @brief initializes and displays the main menu
    * initializes and displays the main menu
    * @return true in case game has been quit, otherwise false.
    */
  virtual bool mainMenu();

private:
  /* Game context */
  using GameContext = GameService::ServiceTuple;
  GameContext m_GameContext;

  void quit();

  /* Services */
  ResourceManager m_ResourceManager;
#ifdef USE_AUDIO
  AudioMixer m_AudioMixer;
#endif
  GamePlay m_GamePlay;
};

#endif
