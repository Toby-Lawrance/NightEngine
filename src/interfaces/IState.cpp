//
// Created by tobyl on 25/08/2024.
//
#include <utility>

#include "interfaces/IState.h"

#include "Engine.h"

namespace NightEngine {
    IState::IState(std::string  stateID) :
    m_StateID(std::move(stateID)),
    m_CleanupRequested(false) {
    }

    const std::string & IState::GetStateID() const {
        return m_StateID;
    }

    void IState::Draw(float deltaTime)
    {
    }

    void IState::Update(float deltaTime)
    {
    }

    bool IState::IsReady()
    {
        return true;
    }

    void IState::HandleCleanup()
    {
    }

    void IState::HandleEvents(sf::Event event) {
        if(const auto* keyReleased = event.getIf<sf::Event::KeyReleased>()) {
           if(keyReleased->scancode == sf::Keyboard::Scancode::Escape) {
                Engine::GetInstance()->Quit(0);
           }
        }
    }

    void IState::Cleanup() {
        if(m_CleanupRequested) {
            HandleCleanup();

            m_CleanupRequested = false;
        }
    }
}
