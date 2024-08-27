//
// Created by tobyl on 25/08/2024.
//

#pragma once
#include <SFML/Graphics.hpp>

namespace NightEngine {
	class IState {
	public:
		explicit IState(std::string stateID);

		virtual ~IState() = default;

		[[nodiscard]] const std::string& GetStateID() const;

		//Draw is called on a separate thread to updates
		//Draw with time since last draw call
		virtual void Draw(float deltaTime);

		//Update with time since last update.
		virtual void Update(float deltaTime);

		//Informs whether the State is ready
		virtual bool IsReady();

		virtual void HandleEvents(sf::Event event);

		void Cleanup();

		//No copying
		IState(const IState &) = delete;

		IState &operator=(const IState &) = delete;

	protected:
		virtual void HandleCleanup();

	private:
		const std::string m_StateID;

		bool m_CleanupRequested;
	};
}
