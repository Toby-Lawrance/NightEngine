//
// Created by tobyl on 24/08/2024.
//

#include "Engine.h"

#include <utility>
namespace NightEngine {
    Engine* Engine::GetInstance()
    {
        return Engine::m_Instance;
    }

    void Engine::ProcessCommandLineArgs(int args, char* argv[])
    {
    }

    void Engine::Quit(const int exitCode)
    {
        m_Running = false;
        Cleanup();
        exit(exitCode);
    }

    void Engine::HandleCleanup()
    {
    }

    int Engine::Run() {

        m_Running = true;

        assert(m_StateManager.GetActiveState() != nullptr);

        m_UpdateThread = std::thread(&Engine::UpdateLoop, this);

        InitRenderer();

        RenderLoop();

        HandleCleanup();

        Cleanup();

        m_Running = false;

        return m_ExitCode;
    }

    bool Engine::IsRunning() const {
        return m_Running;
    }

    Engine::Engine(std::string title) :
    m_Title(std::move(title)),
    m_WindowStyle(sf::Style::Default),
    m_Running(false),
    m_ExitCode(0)
    {
        //Only a single instance and it's accessible
        assert(Engine::m_Instance == nullptr);
        m_Instance = this;
    }

    void Engine::UpdateLoop() {
        sf::Clock updateClock;

        const float targetUPS = 60.0f;
        const float targetDT = 1.f / targetUPS;
        const sf::Time targetDeltaTime = sf::seconds(targetDT);
        while (IsRunning()) {
            const auto deltaTime = updateClock.restart();

            m_StateManager.Update(deltaTime.asSeconds());

            const auto dtPostUpdate = updateClock.getElapsedTime();
            const auto sleepTime = targetDeltaTime - dtPostUpdate;
            sleep(sleepTime);
        }
    }

    void Engine::RenderLoop() {

        sf::Clock renderClock;

        while (IsRunning()) {
            const float deltaTime = renderClock.restart().asSeconds();
            if(const auto activeState = m_StateManager.GetActiveState()) {
                ProcessInput(activeState);
            }

            m_Window.clear(sf::Color::Black);

            m_StateManager.Draw(deltaTime);

            m_Window.display();
        }
    }

    void Engine::ProcessInput(std::shared_ptr<IState> activeState) {
        while(const std::optional event = m_Window.pollEvent()) {
            if(const auto evt = event->getIf<sf::Event::Closed>())
            {
                Quit(0);
            }
            if(event.has_value()) {
                activeState->HandleEvents(event.value());
            }
        }
    }

    void Engine::InitRenderer()
    {
        sf::VideoMode videoMode;
        videoMode.size.x = DEFAULT_SCREEN_WIDTH;
        videoMode.size.y = DEFAULT_SCREEN_HEIGHT;
        videoMode.bitsPerPixel = DEFAULT_COLOR_DEPTH;

        m_Window.create(videoMode, m_Title, m_WindowStyle);
        m_Window.setVerticalSyncEnabled(true);
    }

    void Engine::Cleanup() {
        m_UpdateThread.join();

        if(m_Window.isOpen()) {
            m_Window.setMouseCursorVisible(true);
            m_Window.close();
        }
    }
}

