#pragma once

#include "../States/State.h"
#include "../States/StateIdentifiers.h"

#include <functional>
#include <memory>
#include <utility>
#include <vector>
#include <map>

class StateManager
{
public:
	enum class Action : uint8_t
	{
		ADD,
		DELETE
	};

private:
	std::unique_ptr<State> create_state(ID stateID);
	void do_pending_actions(void);

private:
	struct PendingAction
	{
		Action m_action;
		ID m_stateID;
			
		explicit PendingAction(Action action, ID stateID = ID::NONE);
	};

private:
	std::vector<std::unique_ptr<State>> m_states;
	std::map<ID, std::function<std::unique_ptr<State>()>> m_stateConstructors;
	std::vector<PendingAction> m_pendingActions;
	State::Context m_context;

private:
	StateManager(const StateManager &manager) = delete;
	StateManager & operator=(const StateManager &manager) = delete;

public:
	explicit StateManager(State::Context context);

	template <typename T>
	inline void register_state(ID stateID);
		
	template <typename T1, typename T2>
	inline void register_state(ID stateID, T2 t2);

	void render(void);
	void update(float timestep);
	void handle_input(void);

	void add_state(ID stateID);
	void delete_state(void);
	bool is_empty(void) const;
};

template<typename T>
inline void StateManager::register_state(ID stateID)
{
	m_stateConstructors[stateID] = [this](void)
	{
		return std::unique_ptr<State>(new T(*this, m_context));
	};
}

template<typename T1, typename T2>
inline void StateManager::register_state(ID stateID, T2 t2)
{
	m_stateConstructors[stateID] = [this, t2](void)
	{
		return std::unique_ptr<State>(new T1(*this, m_context, t2));
	};
}