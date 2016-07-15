#ifndef KFTEST_HPP
#define KFTEST_HPP

#include "structs.hpp"

using namespace std;
// cost function
double cost (con_levels&, exp_data&);

// helper functions for conditions 
void find_peaks_troughs (con_levels&, peak_trough&, int);
void get_wtf_index(int, int*);
int test_average_period (peak_trough&, sim_data&, double *);
int test_sustained_amplitude(sim_data&, peak_trough&, con_levels&, int);
void calculate_p2t(peak_trough&, con_levels&, int, double*, double*, double*);
double calculate_average_amplitude(peak_trough&, con_levels&, int);
double calculate_average_period(peak_trough&, sim_data&);
int check_wildtype_behavior(peak_trough&, con_levels&, sim_data&, wildtype_feats&, int);
int check_shorter_period_behavior(peak_trough&, con_levels&, sim_data&, wildtype_feats&, int);
int check_longer_period_behavior(peak_trough&, con_levels&, sim_data&, wildtype_feats&, int);
int check_shorter_amplitude_behavior(peak_trough&, con_levels&, sim_data&, wildtype_feats&, int);
int check_longer_amplitude_behavior(peak_trough&, con_levels&, sim_data&, wildtype_feats&, int);
int check_rythmic_behavior(sim_data&, peak_trough&, con_levels&, int);
int check_arythmic_behavior(sim_data&, peak_trough&, con_levels&, int);

// test functions for mutants
int test_wildtype_scn(con_levels&, sim_data&, wildtype_feats&);
int test_per1kn_scn(con_levels&, sim_data&, wildtype_feats&);
int test_per2kn_scn(con_levels&, sim_data&, wildtype_feats&);
int test_per3kn_scn(con_levels&, sim_data&, wildtype_feats&);
int test_cry1kn_scn(con_levels&, sim_data&, wildtype_feats&);
int test_cry2kn_scn(con_levels&, sim_data&, wildtype_feats&);
int test_bmalkn_scn(con_levels&, sim_data&, wildtype_feats&);
int test_npas2kn_scn(con_levels&, sim_data&, wildtype_feats&);
int test_c1c2kn_scn(con_levels&, sim_data&, wildtype_feats&);

//test functions for mutants FIB
int test_wildtype_fib(con_levels&, sim_data&, wildtype_feats&);
int test_per1kn_fib(con_levels&, sim_data&, wildtype_feats&);
int test_per2kn_fib(con_levels&, sim_data&, wildtype_feats&);
int test_per3kn_fib(con_levels&, sim_data&, wildtype_feats&);
int test_cry1kn_fib(con_levels&, sim_data&, wildtype_feats&);
int test_cry2kn_fib(con_levels&, sim_data&, wildtype_feats&);
int test_bmalkn_fib(con_levels&, sim_data&, wildtype_feats&);
int test_npas2kn_fib(con_levels&, sim_data&, wildtype_feats&);
int test_c1c2kn_fib(con_levels&, sim_data&, wildtype_feats&);
int test_p2c1kn_fib(con_levels&, sim_data&, wildtype_feats&);
int test_p2c2kn_fib(con_levels&, sim_data&, wildtype_feats&);
int test_rkn_fib(con_levels&, sim_data&, wildtype_feats&);
#endif
