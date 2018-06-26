#include "navigation_monitor.h"

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
	return "robot position = " + to_string(robot_position) + " belief_status = " +
	to_string(belief_status);
}

/* =============================================================================
 * NavigationMonitor class
 * =============================================================================*/

NavigationMonitor::NavigationMonitor() {
}

/* ======
 * Action
 * ======*/

int NavigationMonitor::NumActions() const {
	return 3;
}

/* ==============================
 * Deterministic simulative model
 * ==============================*/

// when execute an underterministic action, an observation action is needed.
bool NavigationMonitor::Step(State& state, double rand_num, int action,
        double& reward, OBS_TYPE& obs) const {
    SimpleState& simple_state = static_cast < SimpleState& >(state);
    int& robot_position = simple_state.robot_position;
    int& belief_status = simple_state.belief_status;

    //simulate_belief = UpdateLocalBelief();

    //belief_status = CheckBeliefStatus(*local_belief);

    if (belief_status == 0) { // belif is uncertain
    	if (action == A_OBSERVE) {
    		reward = 10; // when belief is uncertain, select an observation action receives rewards.   		
    		//obs = ReceiveObservation(); // invoke sensor to gather real-world information
            obs = O_M_1; // -----------------------rand_num can be applied here to add stochasticity to observation probabilities----------------------
    		//belief_status = UpdateBeliefStatus(*local_belief, action, obs); // belief may be certain or remain uncertain
    		belief_status = 1;
            //belief_status = (update(action, obs) is certain) ? 1.0 : 0.0 // to be implemented
            //robot_position = robot_position; // observe action don't change robot position
    	
    	} else if (action == A_EAST) { // 
    		reward = -100; // when robot isn't certain about position, select movement actions receive large penety.
    		obs = O_DEFAULT;
    		belief_status = 0; //belief remains uncertain
    		
    		if (robot_position == LEFT) {
    			robot_position = MIDDLE_1;
    		} else if (robot_position == MIDDLE_1) {
    			robot_position = MIDDLE_2;
    		} else if (robot_position == MIDDLE_2) {
    			robot_position = RIGHT;
    			return true;
    		} else if (robot_position == RIGHT) {
    			robot_position = RIGHT;
    			return true;
    		}

    	} else if (action == A_WEST) {
    		reward = -100; // when robot isn't certain about position, select movement actions receive large penety
    		obs = O_DEFAULT;
    		belief_status = 0; //belief remains uncertain
    		
    		if (robot_position == LEFT) {
    			reward = -1000; //move off thr grid receives large penety
    			return true;
    		} else if (robot_position == MIDDLE_1) {
    			robot_position = LEFT;
    		} else if (robot_position == MIDDLE_2) {
    			robot_position = MIDDLE_1;
    		} else if (robot_position == RIGHT) {
    			return true;
    		}
    	}
    } else if (belief_status == 1) { // belief is certain
    	//robot_position = RetrieveExactPositionFromBelief(*local_belief); //get exact current position
        robot_position = simple_state.robot_position;
    	
    	if (action == A_OBSERVE) {
    		reward = -10; // when belief is certain, observation action is unnecessary
    		belief_status = 1;
    		obs = O_DEFAULT;
    	
    	} else if (action == A_EAST) { // --------------------------when an underterminsitic action executes, the belief_status becomes 0---may be another way of modelling belief status
    		//reward = 10;
    		if (robot_position == LEFT) {
    			reward = 100;
    			robot_position = (rand_num > 0.2) ? MIDDLE_1 : LEFT;
    			//std::cout << "robot_position: " << robot_position << endl;
    			obs = O_DEFAULT;
    			//belief_status = UpdateBeliefStatus(*local_belief, action, obs);
                belief_status = 0;
    		} else if (robot_position == MIDDLE_1) {
    			reward = 100;
    			robot_position = (rand_num > 0.2) ? MIDDLE_2 : MIDDLE_1;
                //robot_position = MIDDLE_2;
    			obs = O_DEFAULT;
    			//belief_status = UpdateBeliefStatus(*local_belief, action, obs);
                belief_status = 0;
    		} else if (robot_position == MIDDLE_2) {
    			reward = 100;
    			//robot_position = (rand_num > 0.2) ? RIGHT : MIDDLE_2;
                robot_position = RIGHT;
    			obs = O_DEFAULT;
    			//belief_status = UpdateBeliefStatus(*local_belief, action, obs);
                belief_status = 1;
    			return true;
    		} else if (robot_position == RIGHT) {
    			return true;
    		}
    	
    	} else if (action == A_WEST) {
    		
    		if (robot_position == LEFT) {
    			reward = -1000; //move off the grid, terminate the task, receives large penety.
                belief_status = 1;
    			return true;
    		} else if (robot_position == MIDDLE_1) {
    			reward = -100;
    			robot_position = LEFT;
    			obs = O_DEFAULT;
    			//belief_status = UpdateBeliefStatus(*local_belief, action, obs);
                belief_status = 1;
    		} else if (robot_position == MIDDLE_2) {
    			reward = -100;
    			robot_position = MIDDLE_1;
    			obs = O_DEFAULT;
    			//belief_status = UpdateBeliefStatus(*local_belief, action, obs);
                belief_status = 1;
    		} else if (robot_position == RIGHT) {
    			return true;
    		}
    	}
    }
    return false;
}

double NavigationMonitor::ObsProb(OBS_TYPE obs, const State& state,
    int action) const {
    if (action == A_OBSERVE) {
        const SimpleState& simple_state = static_cast<const SimpleState&>(state);
        int robot_position = simple_state.robot_position;
        //int belief_status = simple_state.belief_status;
        if (robot_position == LEFT) {
            if (obs == O_L)
                return 0.8;
            else if (obs == O_M_1)
                return 0.2;
            //obs = O_L;
        } else if (robot_position == MIDDLE_1) {
            if (obs == O_M_1)
                return 0.8;
            else if (obs == O_L)
                return 0.2;
            //obs = O_M_1;
        } else if (robot_position == MIDDLE_2) {
            obs = O_M_2;
        } else if (robot_position == RIGHT) {
            obs = O_R;
        }
    }
    // when the actions are not A_OBSERVE, the robot does not receive any observations.
    // Assume it receives a default observation with probability 1.
    return obs == O_DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////////////

int NavigationMonitor::ReceiveObservation() const {
	return O_DEFAULT;
}



// consider to modify this function to keep with the belief update function
int NavigationMonitor::UpdateBeliefStatus(const Belief& belief, int action, OBS_TYPE obs) const { // local function for this application example only

	const vector<State*>& particles = static_cast<const ParticleBelief&>(belief).particles();
	//vector<State*>& simulated_particles = static_cast<ParticleBelief&>(simulated_belief).particles();

	const SimpleState* state;
	//double belief_status = 0;
	double normalizer = 0;
	double sum = 0;
	vector<double> pos_probs(4); // current belief
	vector<double> new_pos_probs(4); // updated belief

	for (int i = 0; i < particles.size(); i++) {
		State* particle = particles[i];
		state = static_cast<const SimpleState*>(particle);
		pos_probs[state->robot_position] += particle->weight;
	}

	//printf("pos_probs[0]: " + pos_probs[0]);
	//std::cout << "pos_probs[0]: " << pos_probs[0] << endl;

    normalizer = pos_probs[0] * ObsProb(obs, *particles[0], action) + pos_probs[1]*ObsProb(obs, *particles[1], action) + 
						 pos_probs[2]*ObsProb(obs, *particles[2], action) + pos_probs[3]*ObsProb(obs, *particles[3], action); // states: LEFT, MIDDLE_1, MIDDLE_2, RIGHT
    for (int i = 0; i < 4; i++) { // for each state in the updated belief 
        sum = 0;
        for (int j = 0; j < 4; j++) { // iterate over each state in the current belief
        	sum += TransitionFunction(*particles[j], action, *particles[i]) * pos_probs[j];
        }

        new_pos_probs[i] = (ObsProb(obs, *particles[i], action) * sum) / normalizer;

        //simulated_particles[i] = new_pos_probs[i];  // update simulated belief
	}

	//PrintSimulatedBelief(new_pos_probs(4));

	// consider output the local belief along the execution process

	//std::cout << "Simulated position belief: \n" << " LEFT" << ":" << new_pos_probs[0] << ", MIDDLE_1" << ":" << new_pos_probs[1] << ", MIDDLE_2"
	//<< ":" << new_pos_probs[2] << ", RIGHT" << ":" << new_pos_probs[3] << endl;

    for (int i = 0; i < 4; i++) {
        if (new_pos_probs[i] == 1.0)
            return 1;
    }
    return 0;   	
}



double NavigationMonitor::TransitionFunction(const State& pre_state, int action, const State& post_state) const {
    double prob = 0.0;

	const SimpleState& simple_pre_state = static_cast<const SimpleState&>(pre_state);
	const SimpleState& simple_post_state = static_cast<const SimpleState&>(post_state);

    if (action == A_EAST) {
        if (simple_pre_state.robot_position == LEFT && simple_post_state.robot_position == MIDDLE_1)
            //prob = 1.0;
            prob = 0.8;
        else if (simple_pre_state.robot_position == LEFT && simple_post_state.robot_position == LEFT)
        	prob = 0.2;
        else if (simple_pre_state.robot_position == MIDDLE_1 && simple_post_state.robot_position == MIDDLE_2)
            prob = 0.8;
        else if (simple_pre_state.robot_position == MIDDLE_1 && simple_post_state.robot_position == MIDDLE_1)
        	prob = 0.2;
        else if (simple_pre_state.robot_position == MIDDLE_2 && simple_post_state.robot_position == RIGHT)
            prob = 0.8;
        else if (simple_pre_state.robot_position == MIDDLE_2 && simple_post_state.robot_position == MIDDLE_2)
        	prob = 0.2;
        else if (simple_pre_state.robot_position == RIGHT && simple_post_state.robot_position == RIGHT)
            prob = 1.0;
        else 
        	prob = 0.0;
        //prob = 0.0;
    } else if (action == A_WEST) {
        if (simple_pre_state.robot_position == LEFT && simple_post_state.robot_position == LEFT)
            prob = 1.0;
        else if (simple_pre_state.robot_position == MIDDLE_1 && simple_post_state.robot_position == LEFT) 
            prob = 1.0;
        else if (simple_pre_state.robot_position == MIDDLE_2 && simple_post_state.robot_position == MIDDLE_1)
            prob = 1.0;
        else if (simple_pre_state.robot_position == RIGHT && simple_post_state.robot_position == MIDDLE_2)
            prob = 1.0;
        else 
        	prob = 0.0;
    } else if (action == A_OBSERVE) {
        if (simple_pre_state.robot_position == LEFT && simple_post_state.robot_position == LEFT)
            prob = 1.0;
        else if (simple_pre_state.robot_position == MIDDLE_1 && simple_post_state.robot_position == MIDDLE_1)
            prob = 1.0;
        else if (simple_pre_state.robot_position == MIDDLE_2 && simple_post_state.robot_position == MIDDLE_2)
            prob = 1.0;
        else if (simple_pre_state.robot_position == RIGHT && simple_post_state.robot_position == RIGHT) 
            prob = 1.0;
        else 
        	prob = 0.0;
    }
    return prob;
}

int NavigationMonitor::CheckBeliefStatus(const Belief& belief) const {
	const vector<State*>& particles = static_cast<const ParticleBelief&>(belief).particles();

	int belief_status = 0;
	vector<double> pos_probs(4);
	for (int i = 0; i < particles.size(); i++) {
		State* particle = particles[i];
		const SimpleState* state = static_cast<const SimpleState*>(particle);
		pos_probs[state->robot_position] += particle->weight;

		if (pos_probs[state->robot_position] == 1.0) { // can also set a threshold x > 0.9/0.8, more practical
			belief_status = 1;
			break;
		}	
	}
	return belief_status;
}

int NavigationMonitor::RetrieveExactPositionFromBelief(const Belief& belief) const {
	const vector<State*>& particles = static_cast<const ParticleBelief&>(belief).particles();
	vector<double> pos_probs(4);
	for (int i = 0; i < particles.size(); i++) {
		State* particle = particles[i];
		const SimpleState* state = static_cast<const SimpleState*>(particle);
		pos_probs[state->robot_position] += particle->weight;
		if (pos_probs[state->robot_position] == 1.0) { // can also set a threshold x > 0.9/0.8, more practical
			return state->robot_position;
			break;
		}
	}
	return -1; // no robot position is assigned with 1.0
}

////////////////////////////////////////////////////////////////////////////////////////////

void NavigationMonitor::PrintBelief(const Belief& belief, ostream& out) const {
	const vector<State*>& particles =
		static_cast<const ParticleBelief&>(belief).particles();
	//double rock_status = 0;
    int belief_status = 1;
	vector<double> pos_probs(6);
	for (int i = 0; i < particles.size(); i++) {
		State* particle = particles[i];
		const SimpleState* state = static_cast<const SimpleState*>(particle);
		//rock_status += state->robot_position * particle->weight;
		pos_probs[state->robot_position] += particle->weight;
        belief_status = state->belief_status; //???
        out << "robot_position: " << state->robot_position << "; " << "belief status: " << state->belief_status << "; " << "particle -> weight: " << particle->weight << endl;
        //if (particle->weight == 1.0)
        //    belief_status = 1;
	}

	//out << "Position belief:\n" << " LEFT" << ":" << pos_probs[0] << ", MIDDLE_1"
	//	<< ":" << pos_probs[1] << ", MIDDLE_2" << ":" << pos_probs[2] << ", RIGHT" << ":" << pos_probs[3] << endl;
    //out << "Belief status: " << belief_status << endl;
}

// void NavigationMonitor::PrintSimulatedBelief(const Belief& belief, ostream& out) const {
// 	const vector<State*>& particles = static_cast<const ParticleBelief&>(belief).particles();

// 	vector<double> pos_probs(4);
// 	for (int i = 0; i < particles.size(); i++) {
// 		State* particle = particles[i];
// 		const SimpleState* state = static_cast<const SimpleState*>(particle);
// 		pos_probs[state->robot_position] += particle->weight;
// 	}
// 	out << "Simulated position belief: \n" << " LEFT" << ":" << pos_probs[0] << ", MIDDLE_1" << ":" << pos_probs[1] << ", MIDDLE_2" 
// 	<< ":" << pos_probs[2] << ", RIGHT" << ":" << pos_probs[3] << endl;

// }

/*void NavigationMonitor::PrintSimulatedBelief(const vector<double> probs, ostream& out) const {
	out << "Simulated position belief: \n" << " LEFT" << ":" << probs[0] << ", MIDDLE_1" << ":" << probs[1] << ", MIDDLE_2"
	<< ":" << probs[2] << ", RIGHT" << ":" << probs[3] << endl;

}*/

/* ================================================
 * Functions related to beliefs and starting states
 * ================================================*/


State* NavigationMonitor::CreateStartState(string type) const {
	//return new SimpleState(LEFT);
	//return new SimpleState(0, Random::RANDOM.NextInt(2));
	return new SimpleState(0,1);
}

Belief* NavigationMonitor::InitialBelief(const State* start, string type) const {

	if (type == "DEFAULT" || type == "PARTICLE") {
		vector<State*> particles;

		SimpleState* state_0 = static_cast<SimpleState*>(Allocate(-1, 1.0));
		state_0->robot_position = LEFT;	
        state_0->belief_status = 1;
		particles.push_back(state_0);

        SimpleState* state_1 = static_cast<SimpleState*>(Allocate(-1, 0.0));
        state_1->robot_position = MIDDLE_1;
        state_1->belief_status = 1;
        particles.push_back(state_1);

        SimpleState* state_2 = static_cast<SimpleState*>(Allocate(-1, 0.0));
        state_2->robot_position = MIDDLE_2;
        state_2->belief_status = 1;
        particles.push_back(state_2);

        SimpleState* state_3 = static_cast<SimpleState*>(Allocate(-1, 0.0));
        state_3->robot_position = RIGHT;
        state_3->belief_status = 1;
        particles.push_back(state_3);

        SimpleState* state_4 = static_cast<SimpleState*>(Allocate(-1, 0.0));
        state_4->robot_position = LEFT;
        state_4->belief_status = 0;
        particles.push_back(state_4);

        SimpleState* state_5 = static_cast<SimpleState*>(Allocate(-1, 0.0));
        state_5->robot_position = MIDDLE_1;
        state_5->belief_status = 0;
        particles.push_back(state_5);

        SimpleState* state_6 = static_cast<SimpleState*>(Allocate(-1, 0.0));
        state_6->robot_position = MIDDLE_2;
        state_6->belief_status = 0;
        particles.push_back(state_6);

        SimpleState* state_7 = static_cast<SimpleState*>(Allocate(-1, 0.0));
        state_7->robot_position = RIGHT;
        state_7->belief_status = 0;
        particles.push_back(state_7);

		//local_belief = new ParticleBelief(particles, this); //user-added
		//return local_belief; //user-added

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
double NavigationMonitor::GetMaxReward() const {
	return 10;
}

ValuedAction NavigationMonitor::GetMinRewardAction() const {
	return ValuedAction(A_EAST, 0);
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

State* NavigationMonitor::Allocate(int state_id, double weight) const {
	SimpleState* state = memory_pool_.Allocate();
	state->state_id = state_id;
	state->weight = weight;
	return state;
}

State* NavigationMonitor::Copy(const State* particle) const {
	SimpleState* state = memory_pool_.Allocate();
	*state = *static_cast<const SimpleState*>(particle);
	state->SetAllocated();
	return state;
}

void NavigationMonitor::Free(State* particle) const {
	memory_pool_.Free(static_cast<SimpleState*>(particle));
}

int NavigationMonitor::NumActiveParticles() const {
	return memory_pool_.num_allocated();
}

/* =======
 * Display
 * =======*/

void NavigationMonitor::PrintState(const State& state, ostream& out) const {
	const SimpleState& simple_state = static_cast<const SimpleState&>(state);

	out << "  Position = " << simple_state.robot_position << endl;
	out << "  Belief status = " << simple_state.belief_status << endl;
}

void NavigationMonitor::PrintObs(const State& state, OBS_TYPE observation,
	ostream& out) const {
	//out << (observation ? "GOOD" : "BAD") << endl;
	if (observation == O_L) {
		out << "O_L" << endl;
	} else if (observation == O_M_1) {
        out << "O_M_1" << endl;
    } else if (observation == O_M_2) {
        out << "O_M_2" << endl;
    } else if (observation == O_R) {
        out << "O_R" << endl;
    } else if (observation == O_DEFAULT) {
    	out << "O_DEFAULT" << endl;
    }
}

void NavigationMonitor::PrintAction(int action, ostream& out) const {
	if (action == A_OBSERVE)
		out << "Observe" << endl;
    if (action == A_EAST)
        out << "East" << endl;
    if (action == A_WEST) 
        out << "West" << endl;
}

} // namespace despot
