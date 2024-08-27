//
// Created by tobyl on 25/08/2024.
//

#pragma once
#include <memory>
#include <vector>
#include <interfaces/IState.h>

namespace NightEngine {
	class StateManager {
public:
	StateManager();
	virtual ~StateManager();

	void SetActiveState(std::string stateID);
	std::shared_ptr<IState> GetActiveState();

	//Note if the state to be activated is the active state. This will return false
	bool ActivateBackgroundState(std::string stateID);
	bool DeactivateBackgroundState(std::string stateID);
	void ClearBackgroundStates();
	std::vector<std::shared_ptr<IState>> GetBackgroundStates();

	void AddState(const std::shared_ptr<IState> &state);
	void RemoveState(std::string stateID);
	bool ContainsState(const std::string &stateID);

	void Update(float deltaTime);
	void Draw(float deltaTime);

	StateManager(const StateManager&) = delete;
	StateManager& operator=(const StateManager&) = delete;
	private:
		//The active State will draw and update
		std::shared_ptr<IState> m_ActiveState;
		//Active background States will update but not draw
		std::vector<std::shared_ptr<IState>> m_activeBackgroundStates;
		std::unordered_map<std::string,std::shared_ptr<IState>> m_KnownStates;
};

} // NightEngine
