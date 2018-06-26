#include "simple_navigation.h"

using namespace std;

namespace despot {

/* =============================================================================
 * SimpleState class
 * =============================================================================*/

SimpleState::SimpleState() {
}

SimpleState::~SimpleState() {
}

string SimpleState::text() const {
	return "robot position = " + to_string(robot_position);
}

/* =============================================================================
 * SimpleNavigation class
 * =============================================================================*/

SimpleNavigation::SimpleNavigation() {
}

/* ======
 * Action
 * ======*/

int SimpleNavigation::NumActions() const {
	return 5;
}

/* ==============================
 * Deterministic simulative model
 * ==============================*/

bool SimpleNavigation::Step(State& state, double rand_num, int action,
        double& reward, OBS_TYPE& obs) const {
    SimpleState& simple_state = static_cast < SimpleState& >(state);
    int& robot_position = simple_state.robot_position;
    //int& plan_status = simple_state.plan_status;

    if (action == A_MOVE_LEFT) {
    	if (robot_position == LEFT_U || robot_position == LEFT_L) {
    		reward = -100;
    		obs = O_DEFAULT;
    		return true; //move off the grid terminates the task
    	} else if (robot_position == MIDDLE_U) {
    		robot_position = LEFT_U;
    		reward = 0;
    		obs = O_DEFAULT;
    	} else if (robot_position == MIDDLE_L) {
    		robot_position = LEFT_L;
    		reward = 0;
    		obs = O_DEFAULT;
    	} else if (robot_position == RIGHT_L) {
    		robot_position = MIDDLE_L;
    		reward = 0;
    		obs = O_DEFAULT;
    	} else if (robot_position == RIGHT_U) {
    		return true;
    	}
    } else if (action == A_MOVE_RIGHT) {
    	if (robot_position == LEFT_U) {
    		robot_position = MIDDLE_U;
    		reward = 0;
    		obs = O_DEFAULT;
    	} else if (robot_position == MIDDLE_U) {
    		robot_position = RIGHT_U;
    		reward = 10;
    		obs = O_DEFAULT;
    		return true;
    	} else if (robot_position == LEFT_L) {
    		robot_position = MIDDLE_L;
    		reward = 0;
    		obs = O_DEFAULT;
    	} else if (robot_position == MIDDLE_L) {
    		robot_position = RIGHT_L;
    		reward = 0;
    		obs = O_DEFAULT;
    	} else if (robot_position == RIGHT_L) {
    		reward = -100;
    		obs = O_DEFAULT;
    		return true; //move off the grid terminates the task
    	} else if (robot_position == RIGHT_U) {
    		return true;
    	}
    } else if (action == A_MOVE_UP) {
    	if (robot_position == LEFT_U || robot_position == MIDDLE_U) {
    		reward = -100;
    		obs = O_DEFAULT;
    		return true; //move off the grid terminates the task
    	} else if (robot_position == LEFT_L) {
    		robot_position = LEFT_U;
    		reward = 0;
    		obs = O_DEFAULT;
    	} else if (robot_position == MIDDLE_L) {
    		robot_position = MIDDLE_U;
    		reward = 0;
    		obs = O_DEFAULT;
    	} else if (robot_position == RIGHT_L) {
    		robot_position = RIGHT_U;
    		reward = 10;
    		obs = O_DEFAULT;
    		return true;
    	} else if (robot_position == RIGHT_U) {
    		return true;
    	}
    } else if (action == A_MOVE_DOWN) {
    	if (robot_position == LEFT_L || robot_position == MIDDLE_L || robot_position == RIGHT_L) {
    		reward = -100;
    		obs = O_DEFAULT;
    		return true; //move off the grid terminates the task
    	} else if (robot_position == LEFT_U) {
    		robot_position = LEFT_L;
    		reward = 0;
    		obs = O_DEFAULT;
    	} else if (robot_position == MIDDLE_U) {
    		robot_position = MIDDLE_U;
    		reward = 0;
    		obs = O_DEFAULT;
    	} else if (robot_position == RIGHT_U) {
    		return true;
    	}
    } else if (action == A_OBSERVE) { //invoked when the belief is not certain
    	if (robot_position == LEFT_U) {
    		reward = 0;
    		obs = O_LU;
    	} else if (robot_position == MIDDLE_U) {
    		reward = 0;
    		obs = O_MU;
    	} else if (robot_position == RIGHT_U) {
    		return true;
    	} else if (robot_position == LEFT_L) {
    		reward = 0;
    		obs = O_LL;
    	} else if (robot_position == MIDDLE_L) {
    		reward = 0;
    		obs = O_ML;
    	} else if (robot_position == RIGHT_L) {
    		reward = 0;
    		obs = O_RL;
    	}
    }//robot_position is kept original (can be extended)
    return false;
}

/* ================================================
 * Functions related to beliefs and starting states
 * ================================================*/

double SimpleNavigation::ObsProb(OBS_TYPE obs, const State& state,
	int action) const {
	if (action == A_OBSERVE) {
		const SimpleState& simple_state = static_cast<const SimpleState&>(state);
		int robot_position = simple_state.robot_position;

		if (robot_position == LEFT_U) {
			return obs == O_LU;;
		} else if (robot_position == MIDDLE_U) {
			return obs == O_MU;
		} else if (robot_position == LEFT_L) {
			return obs == O_LL;
		} else if (robot_position == MIDDLE_L) {
			return obs == O_ML;
		} else if (robot_position == RIGHT_L) {
			return obs == O_RL;
		}
	}

	// when the actions are not A_OBSERVE, the robot does not receive any observations.
	// Assume it receives a default observation with probability 1.
	return obs == O_DEFAULT;
}

State* SimpleNavigation::CreateStartState(string type) const {
	return new SimpleState(LEFT_U);
}

Belief* SimpleNavigation::InitialBelief(const State* start, string type) const {

	if (type == "DEFAULT" || type == "PARTICLE") {
		vector<State*> particles;

		SimpleState* init_state_1 = static_cast<SimpleState*>(Allocate(-1, 1.0));
		init_state_1->robot_position = LEFT_U;	
		particles.push_back(init_state_1);

		return new ParticleBelief(particles, this);
	} else {
		cerr << "[SimpleRockSample::InitialBelief] Unsupported belief type: " << type << endl;
		exit(1);
	}
}

/* ========================
 * Bound-related functions.
 * ========================*/
/*
Note: in the following bound-related functions, only GetMaxReward() and 
GetMinRewardAction() functions are required to be implemented. The other 
functions (or classes) are for custom bounds. You don't need to write them
if you don't want to use your own custom bounds. However, it is highly 
recommended that you build the bounds based on the domain knowledge because
it often improves the performance. Read the tutorial for more details on how
to implement custom bounds.
*/
double SimpleNavigation::GetMaxReward() const {
	return 10;
}

ValuedAction SimpleNavigation::GetMinRewardAction() const {
	return ValuedAction(A_MOVE_RIGHT, 0);
}

/*class SimpleNavigationParticleUpperBound: public ParticleUpperBound {
protected:
	// upper_bounds_[pos][status]:
	//   max possible reward when rover_position = pos, and rock_status = status.
	vector<vector<double> > upper_bounds_;

public:
	SimpleNavigationParticleUpperBound(const DSPOMDP* model) {
		upper_bounds_.resize(3);
		upper_bounds_[0].push_back(Globals::Discount(1) * 10);
		upper_bounds_[0].push_back(10 + Globals::Discount(2) * 10);
		upper_bounds_[1].push_back(10);
		upper_bounds_[1].push_back(Globals::Discount(1) * 10 + Globals::Discount(3) * 10);
		if (upper_bounds_[1][1] < 10)
			upper_bounds_[1][1] = 10;
		upper_bounds_[2].push_back(0);
		upper_bounds_[2].push_back(0);
	}

	double Value(const State& s) const {
		const SimpleState& state = static_cast<const SimpleState&>(s);
		return upper_bounds_[state.robot_position];
	}
};*/

/*ScenarioUpperBound* SimpleNavigation::CreateScenarioUpperBound(string name,
	string particle_bound_name) const {
	ScenarioUpperBound* bound = NULL;
	if (name == "TRIVIAL" || name == "DEFAULT") {
		bound = new TrivialParticleUpperBound(this);
	} else if (name == "MAX") {
		bound = new SimpleNavigationSampleParticleUpperBound(this);
	} else {
		cerr << "Unsupported base upper bound: " << name << endl;
		exit(0);
	}
	return bound;
}*/


/*class SimpleNavigationEastPolicy: public Policy {
public:
	enum { // action
		A_OBSERVE = 0, A_MOVE_LEFT = 1, A_MOVE_RIGHT = 2, A_MOVE_UP = 3, A_MOVE_DOWN = 4
	};
	SimpleNavigationEastPolicy(const DSPOMDP* model, ParticleLowerBound* bound) :
		Policy(model, bound) {
	}

	int Action(const vector<State*>& particles, RandomStreams& streams,
		History& history) const {
		return A_MOVE_LEFT; // move east
	}
};*/

/*ScenarioLowerBound* SimpleNavigation::CreateScenarioLowerBound(string name,
	string particle_bound_name) const {
	ScenarioLowerBound* bound = NULL;
	if (name == "TRIVIAL" || name == "DEFAULT") {
		bound = new TrivialParticleLowerBound(this);
	} else if (name == "EAST") {
		bound = new SimpleRockSampleEastPolicy(this,
			CreateParticleLowerBound(particle_bound_name));
	} else {
		cerr << "Unsupported lower bound algorithm: " << name << endl;
		exit(0);
	}
	return bound;
}*/

/* =================
 * Memory management
 * =================*/

State* SimpleNavigation::Allocate(int state_id, double weight) const {
	SimpleState* state = memory_pool_.Allocate();
	state->state_id = state_id;
	state->weight = weight;
	return state;
}

State* SimpleNavigation::Copy(const State* particle) const {
	SimpleState* state = memory_pool_.Allocate();
	*state = *static_cast<const SimpleState*>(particle);
	state->SetAllocated();
	return state;
}

void SimpleNavigation::Free(State* particle) const {
	memory_pool_.Free(static_cast<SimpleState*>(particle));
}

int SimpleNavigation::NumActiveParticles() const {
	return memory_pool_.num_allocated();
}

/* =======
 * Display
 * =======*/

void SimpleNavigation::PrintState(const State& state, ostream& out) const {
	const SimpleState& simple_state = static_cast<const SimpleState&>(state);

	out << "Robot = " << simple_state.robot_position << endl;
}

void SimpleNavigation::PrintObs(const State& state, OBS_TYPE observation,
	ostream& out) const {
	//out << (observation ? "GOOD" : "BAD") << endl;
	if (observation == O_LU) {
		out << "O_LEFT_UP" << endl;
	} else if (observation == O_MU) {
		out << "O_MIDDLE_UP" << endl;
	} else if (observation == O_RU) {
		out << "O_RIGHT_UP" << endl;
	} else if (observation == O_LL) {
		out << "O_LEFT_L" << endl;
	} else if (observation == O_ML) {
		out << "O_MIDDLE_L" << endl;
	} else if (observation == O_RL) {
		out << "O_RIGHT_L" << endl;
	} else {
		out << "O_DEFAULT" << endl;
	}
}

void SimpleNavigation::PrintBelief(const Belief& belief, ostream& out) const {
	const vector<State*>& particles =
		static_cast<const ParticleBelief&>(belief).particles();

	//double rock_status = 0;
	vector<double> pos_probs(6);
	for (int i = 0; i < particles.size(); i++) {
		State* particle = particles[i];
		const SimpleState* state = static_cast<const SimpleState*>(particle);
		//rock_status += state->robot_position * particle->weight;
		pos_probs[state->robot_position] += particle->weight;
	}

	//out << "Robot belief: " << robot_status << endl;

	out << "Position belief:\n" << " LEFT_U" << ":" << pos_probs[0] << ", MIDDLE_U"
		<< ":" << pos_probs[1] << ", RIGHT_U" << ":" << pos_probs[2] << ", LEFT_L" << ":" << pos_probs[3]
		<< ", MIDDLE_L" << ":" << pos_probs[4] << ", RIGHT_L" << ":" << pos_probs[5] << endl;
}

void SimpleNavigation::PrintAction(int action, ostream& out) const {
	if (action == A_MOVE_LEFT)
		out << "Move Left" << endl;
	if (action == A_MOVE_RIGHT)
		out << "Move Right" << endl;
	if (action == A_MOVE_UP)
		out << "Move Up " << endl;
	if (action == A_MOVE_DOWN)
		out << "Move Down" << endl;
	if (action == A_OBSERVE)
		out << "Observe" << endl;
}

} // namespace despot
