#ifndef SIM_HPP
#define SIM_HPP

#include "structs.hpp"
using namespace std;
void simulate_all_params(input_params&, rates& , sim_data&, parameters& , exp_data&);
double simulate_scn_param_set(int, input_params&, sim_data&, rates&, con_levels&, con_levels&, exp_data&);
double simulate_fib_param_set(int, input_params&, sim_data&, rates&, con_levels&, con_levels&, exp_data&);

#endif
