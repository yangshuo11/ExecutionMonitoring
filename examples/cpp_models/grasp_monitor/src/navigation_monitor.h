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
	int robot_position; // positions are numbered 0, 1, 2, 3 from left to right
	int belief_status; // 1 denotes certain belief, and 0 denotes uncertain belief

	SimpleState();
	SimpleState(int _robot_position, int _belief_status):
		robot_position(_robot_position),
		belief_status(_belief_status) {
	}
	~SimpleState();

	std::string text() const;
};

/* =============================================================================
 * NavigationMonitor class
 * =============================================================================*/

class NavigationMonitor: public DSPOMDP {
protected:
	mutable MemoryPool<SimpleState> memory_pool_;

	std::vector<SimpleState*> states_;

	Belief* simulate_belief; // for acquire belief status only, not involve with belief update and planning

	std::vector<SimpleState*> simulate_states_; //

	mutable std::vector<ValuedAction> mdp_policy_;

public:
	enum { // action
		A_OBSERVE = 0, A_EAST = 1, A_WEST = 2
	};
	enum { // observation regarding to robot position
		O_L = 0, O_M_1 = 1, O_M_2 = 2, O_R = 3, O_DEFAULT = 4
	};
	enum { // belief status
		B_UNCERTAIN = 0, B_CERTAIN = 1
	};
	enum { // robot position
		LEFT = 0, MIDDLE_1 = 1, MIDDLE_2 = 2, RIGHT = 3
	};

public:
	NavigationMonitor();

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

	/*Check belief status*/ // user-defined functions
	int CheckBeliefStatus(const Belief& belief) const;
	int RetrieveExactPositionFromBelief(const Belief& belief) const;
	int UpdateBeliefStatus(const Belief& belief, int action, OBS_TYPE obs) const;
	double TransitionFunction(const State& pre_state, int action, const State& post_state) const;
	int ReceiveObservation() const; 

	/* Display.*/
	void PrintState(const State& state, std::ostream& out = std::cout) const;
	void PrintBelief(const Belief& belief, std::ostream& out = std::cout) const;
	void PrintObs(const State& state, OBS_TYPE observation,
		std::ostream& out = std::cout) const;
	void PrintAction(int action, std::ostream& out = std::cout) const;
};

} // namespace despot

#endif
