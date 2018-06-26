#ifndef SIMPLENAVIGATION_H
#define SIMPLENAVIGATION_H

#include <despot/core/pomdp.h>
#include <despot/core/mdp.h>

namespace despot {

/* =============================================================================
 * SimpleState class
 * =============================================================================*/

class SimpleState: public State {
public:
	int robot_position; // positions are numbered 0, 1, 2 from left to right in 1st row, 3, 4, 5 in 2nd row
	//int plan_status; // 1 is success, and 0 is failure

	SimpleState();
	SimpleState(int _position):
		robot_position(_position){
	}
	~SimpleState();

	std::string text() const;
};

/* =============================================================================
 * SimpleRockSample class
 * =============================================================================*/

class SimpleNavigation: public DSPOMDP {
protected:
	mutable MemoryPool<SimpleState> memory_pool_;

	std::vector<SimpleState*> states_;

	mutable std::vector<ValuedAction> mdp_policy_;

public:
	enum { // action
		A_OBSERVE = 0, A_MOVE_LEFT = 1, A_MOVE_RIGHT = 2, A_MOVE_UP = 3, A_MOVE_DOWN = 4
	};
	enum { // observation
		O_LU = 0, O_MU = 1, O_RU = 2, O_LL = 3, O_ML = 4, O_RL = 5, O_DEFAULT = 6
	};
/*	enum { // plan status
		R_FAILURE = 0, R_SUCCESS = 1
	};*/
	enum { // robot position
		LEFT_U = 0, MIDDLE_U = 1, RIGHT_U = 2, LEFT_L = 3, MIDDLE_L = 4, RIGHT_L = 5
	};

public:
	SimpleNavigation();

	/* Returns total number of actions.*/
	int NumActions() const;

	/* Deterministic simulative model.*/
	bool Step(State& state, double rand_num, int action, double& reward,
		OBS_TYPE& obs) const;

	/* Functions related to beliefs and starting states.*/
	double ObsProb(OBS_TYPE obs, const State& state, int action) const;
	State* CreateStartState(std::string type = "DEFAULT") const;
	Belief* InitialBelief(const State* start, std::string type = "DEFAULT") const;

	/* Bound-related functions.*/
	double GetMaxReward() const;
/*	ScenarioUpperBound* CreateScenarioUpperBound(std::string name = "DEFAULT",
		std::string particle_bound_name = "DEFAULT") const;*/
	ValuedAction GetMinRewardAction() const;
/*	ScenarioLowerBound* CreateScenarioLowerBound(std::string name = "DEFAULT",
		std::string particle_bound_name = "DEFAULT") const;*/

	/* Memory management.*/
	State* Allocate(int state_id, double weight) const;
	State* Copy(const State* particle) const;
	void Free(State* particle) const;
	int NumActiveParticles() const;

	/* Display.*/
	void PrintState(const State& state, std::ostream& out = std::cout) const;
	void PrintBelief(const Belief& belief, std::ostream& out = std::cout) const;
	void PrintObs(const State& state, OBS_TYPE observation,
		std::ostream& out = std::cout) const;
	void PrintAction(int action, std::ostream& out = std::cout) const;
};

} // namespace despot

#endif
