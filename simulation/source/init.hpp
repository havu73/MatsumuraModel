
#ifndef INIT_HPP
#define INIT_HPP

#include "structs.hpp"

using namespace std;

void init_terminal();
inline bool option_set (const char* , const char* , const char* );
void ensure_nonempty (const char*, const char*);
void accept_input_params (int, char**, input_params& );
void get_mutant_data(input_params&, char*);
void calculate_max_cond_score (input_params&);
void get_cell_type(input_params&, char*);
void init_verbosity (input_params&);
void check_input_params (input_params&);
void init_seeds (input_params& , int , bool , bool);
void read_sim_params (input_params& , input_data& , parameters& , input_data& ); 
double random_double (pair<double, double>);
void delete_file (ofstream*);
void delete_sets (double**, input_params& );
void free_terminal ();
void reset_cout (input_params&);
int generate_seed ();
void update_initial_conditions(con_levels&);
void read_experiment_data(input_params&, input_data&, exp_data&);
#endif
