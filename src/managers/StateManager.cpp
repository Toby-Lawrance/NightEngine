//
// Created by tobyl on 25/08/2024.
//

#include "managers/StateManager.h"

namespace NightEngine {
    StateManager::StateManager()
    {
    }

    StateManager::~StateManager()
    {
    }

    void StateManager::SetActiveState(std::string stateID)
    {
        assert(m_KnownStates.contains(stateID));

        m_ActiveState = m_KnownStates[stateID];
    }

    std::shared_ptr<IState> StateManager::GetActiveState()
    {
        return m_ActiveState;
    }

    bool StateManager::ActivateBackgroundState(std::string stateID)
    {
        return false;
    }

    bool StateManager::DeactivateBackgroundState(std::string stateID)
    {
        return false;
    }

    void StateManager::ClearBackgroundStates()
    {
        m_activeBackgroundStates.clear();
    }

    std::vector<std::shared_ptr<IState>> StateManager::GetBackgroundStates()
    {
        return m_activeBackgroundStates;
    }

    void StateManager::AddState(const std::shared_ptr<IState> &state)
    {
        assert(!m_KnownStates.contains(state->GetStateID()));
        m_KnownStates[state->GetStateID()] = state;
    }

    void StateManager::RemoveState(std::string stateID)
    {
    }

    bool StateManager::ContainsState(const std::string &stateID)
    {
        return m_KnownStates.contains(stateID);
    }

    void StateManager::Update(float deltaTime)
    {
        m_ActiveState->Update(deltaTime);
        for (const auto& state : m_activeBackgroundStates)
        {
            state->Update(deltaTime);
        }
    }

    void StateManager::Draw(float deltaTime)
    {
        m_ActiveState->Draw(deltaTime);
    }
} // NightEngine