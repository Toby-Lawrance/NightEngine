//
// Created by tobyl on 24/08/2024.
//
#pragma once
#include <thread>
#include <SFML/Graphics.hpp>

#include "managers/StateManager.h"

namespace NightEngine
{
    class Engine
    {
    public:
        //Get instance if it exists, else null
        static Engine* GetInstance();

        virtual ~Engine() = default;

        std::string m_Title;

        unsigned long m_WindowStyle;

        sf::RenderWindow m_Window;

        sf::ContextSettings m_ContextSettings;

        StateManager m_StateManager;

        virtual void ProcessCommandLineArgs(int args, char* argv[]);

        int Run();

        bool IsRunning() const;

        void Quit(int exitCode = 0);

        static constexpr unsigned int DEFAULT_SCREEN_WIDTH = 640;
        static constexpr unsigned int DEFAULT_SCREEN_HEIGHT = 480;
        static constexpr unsigned int DEFAULT_COLOR_DEPTH = 32;

        Engine(const Engine &) = delete;

        Engine &operator=(const Engine &) = delete;

    protected:
        explicit Engine(std::string title = "NightEngine Application");

        virtual void GameLoop();

        virtual void ProcessInput(std::shared_ptr<IState> activeState);

        virtual void HandleCleanup();

    private:
        inline static Engine* m_Instance = nullptr;
        bool m_Running;

        void InitRenderer();

        int m_ExitCode;

        void Cleanup();
    };
}
