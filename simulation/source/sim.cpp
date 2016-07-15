
#include "sim.hpp"

#include <string.h>
#include <iostream>
#include <fstream>
#include "debug.hpp"
#include "init.hpp"
#include "io.hpp"
#include "debug.hpp"
#include "kftest.hpp"
#include "calculation.hpp"
using namespace std;
extern terminal* term;

bool check_up_more_upu(input_params& ip, rates& rs){
	if (rs.rates_base[UP] > rs.rates_base[UPU]){
		return true;
	}
	else {
		if (ip.verbose){
			cout << term->red << "This parameter gets point 0 because UP is smaller than UPU" << term->reset << endl;
		}
		return false;
	}
}

void simulate_all_params(input_params& ip, rates& rs, sim_data& sd, parameters& pr, exp_data& ed){
	con_levels cl (NUM_CONS, sd.big_gran, sd.big_gran);//cl contains simulation data
	con_levels big_cl (NUM_CONS, sd.steps_total/sd.big_gran, sd.big_gran);
	double * score = new double[ip.num_sets];
	
	for (int i = 0; i < ip.num_sets; i++){
		if (ip.print_cons){
			create_set_directory(i);
		}

		memcpy(rs.rates_base, pr.data[i], sizeof(double) * NUM_RATES);
	
		if (ip.cell_type == SCN){
			score[i] = simulate_scn_param_set(i, ip, sd, rs, cl, big_cl, ed);
		}
		else if (ip.cell_type == FIB){
			score[i] = simulate_fib_param_set(i, ip, sd, rs, cl, big_cl, ed);
		}
		cout << "SCORE: " << score[i] << endl;
	}
	
	delete [] score;
	close_if_open(ip.passed_stream);
}

/*	1, init_seeds
 * 	2, Set up initial conditions for cl structures
 * 	3, calculate the concentrations of different species over time. If any negative number of nan: set fails the validity test
 * 	4, 
 */
double simulate_scn_param_set(int set_num, input_params& ip, sim_data& sd, rates& rs, con_levels& cl, con_levels& big_cl, exp_data& ed){
	cout << term->blue << "Simulating set " << term->reset << set_num << " . . ." << endl;
	
	double score = 0; // score is equal to condition_score_weight * cond_score + exp_score_weight * cost. When pass this score back to SRES, we want to minimize the score. 
	double cst = 0; // cost
	double cond_score = 0;
	bool valid;
	double revert_rate;
	double revert_rate_2;
	wildtype_feats wtf;
	for (int i = 0 ; i < ip.num_mutants; i++){
		cl.reset();
		big_cl.reset();
		update_initial_conditions(cl);
		transfer_data(cl, big_cl, 0);
		
		if (ip.mutants[i] == WT){
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid) {
				score += (double)test_wildtype_scn(big_cl, sd, wtf);
				//cout << "Score WT: " << score << endl;
				if (sd.verbose){
					cout << "WT MNPO: period: " << wtf.period[0] << "   amplitude: " << wtf.amplitude[0] << endl;
					cout << "WT MNPT: period: " << wtf.period[1] << "   amplitude: " << wtf.amplitude[1] << endl;
					cout << "WT MNB : period: " << wtf.period[2] << "   amplitude: " << wtf.amplitude[2] << endl;
				}
				if (ip.print_cons){
					print_concentrations(ip, sd, big_cl, set_num, i);
				}
			}
			//else{
				//cout<< term->blue << "Set " << term->reset << set_num << term->blue << " wild type failed because concentrations is negative or nan ..." << endl;
			//}
		}
		else if (ip.mutants[i] == P1){
			revert_rate = rs.rates_base[TRPO];
			rs.rates_base[TRPO] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double)test_per1kn_scn(big_cl, sd, wtf);
				//cout << "Score P1: " << score << endl;
				if (ip.print_cons){
					print_concentrations(ip, sd, big_cl, set_num, i);
				}
			}
			//else{
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Per 1 knock down failed because concentrations is negative or nan ..." << endl;
			//}
			rs.rates_base[TRPO] = revert_rate;
		}
		else if (ip.mutants[i] == P2){
			revert_rate = rs.rates_base[TRPT];
			rs.rates_base[TRPT] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double)test_per2kn_scn(big_cl, sd, wtf);
				//cout << "Score P2: " << score << endl;
				if (ip.print_cons){
					print_concentrations(ip, sd, big_cl, set_num, i);
				}
			}
			//else{
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Per 2 knock down failed because concentrations is negative or nan ..." << endl;
			//}
			rs.rates_base[TRPT] = revert_rate;
		}
		else if (ip.mutants[i] == P3){
			revert_rate = rs.rates_base[TRPH];
			rs.rates_base[TRPH] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double)test_per3kn_scn(big_cl, sd, wtf);
				//cout << "Score P3: " << score << endl;
				if (ip.print_cons){
					print_concentrations(ip, sd, big_cl, set_num, i);
				}
			}
			//else{
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Per 3 knock down failed because concentrations is negative or nan ..." << endl;
			//}
			rs.rates_base[TRPH] = revert_rate;
		}
		else if (ip.mutants[i] == C1){
			revert_rate = rs.rates_base[TRRO];
			rs.rates_base[TRRO] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_cry1kn_scn(big_cl, sd, wtf);
				//cout << "Score C1: " << score << endl;
			}
			//else{
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Cry 1 knock down failed because concentrations is negative or nan ..." << endl;
			//}
			rs.rates_base[TRRO] = revert_rate;
		}
		else if (ip.mutants[i] == C2){
			revert_rate = rs.rates_base[TRRT];
			rs.rates_base[TRRT] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_cry2kn_scn(big_cl, sd, wtf);
				//cout << "Score C2: " << score << endl;
			}
			//else {
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Cry 2 knock down failed because concentrations is negative or nan ..." << endl;
			//}
			rs.rates_base[TRRT] = revert_rate;
		}
		else if (ip.mutants[i] == BM){
			revert_rate = rs.rates_base[TRB];
			rs.rates_base[TRB] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_bmalkn_scn(big_cl, sd, wtf);
				//cout << "Score BM: " << score << endl;
			}
			//else {
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Bmal knock down failed because concentrations is negative or nan ..." << endl;				
			//}
			rs.rates_base[TRB] = revert_rate;
		}
		else if (ip.mutants[i] == NP){
			revert_rate = rs.rates_base[TRNP];
			rs.rates_base[TRNP] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_npas2kn_scn(big_cl, sd, wtf);
				//cout << "Score NP: " << score << endl;
			}
			//else {
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Npas2 knock down failed because concentrations is negative or nan ..." << endl;				
			//}
			rs.rates_base[TRNP] = revert_rate;
		}
		else if (ip.mutants[i] == C1C2){
			revert_rate = rs.rates_base[TRRO];
			rs.rates_base[TRRO] = 0;
			revert_rate_2 = rs.rates_base[TRRT];
			rs.rates_base[TRRT] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_c1c2kn_scn(big_cl, sd, wtf);
				//cout << "Score C1C2: " << score << endl;
			}
			//else {
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Cry1 Cry2 knock down failed because concentrations is negative or nan ..." << endl;				
			//}
			rs.rates_base[TRRO] = revert_rate;
			rs.rates_base[TRRT] = revert_rate_2;
		}
		
		//// COST//////
		if (ip.compare_exp_data && i == WT){
			cst = cost(big_cl, ed);
		}
	}
	
	cond_score = (double)ip.max_cond_score - score;
	score = WEIGHT_CONDITIONS * (cond_score) + WEIGHT_COST * cst;
	
	if (ip.piping){
		write_pipe(&score, &cond_score , &cst, ip, sd);
	}
	
	return score;
}

double simulate_fib_param_set(int set_num, input_params& ip, sim_data& sd, rates& rs, con_levels& cl, con_levels& big_cl, exp_data& ed){
	cout << term->blue << "Simulating set " << term->reset << set_num << " . . ." << endl;
	
	double score = 0; // score is equal to condition_score_weight * cond_score + exp_score_weight * cost. When pass this score back to SRES, we want to minimize the score. 
	double cst = 0; // cost
	double cond_score = 0;
	bool valid;
	double revert_rate;
	double revert_rate_2;
	wildtype_feats wtf;
	for (int i = 0 ; i < ip.num_mutants; i++){
		cl.reset();
		big_cl.reset();
		update_initial_conditions(cl);
		transfer_data(cl, big_cl, 0);
		
		if (ip.mutants[i] == WT){
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid) {
				score += (double)test_wildtype_fib(big_cl, sd, wtf);
				
				if (sd.verbose){
					cout << "Score WT: " << score << endl;
					cout << "WT MNPO: period: " << wtf.period[0] << "   amplitude: " << wtf.amplitude[0] << endl;
					cout << "WT MNPT: period: " << wtf.period[1] << "   amplitude: " << wtf.amplitude[1] << endl;
					cout << "WT MNB : period: " << wtf.period[2] << "   amplitude: " << wtf.amplitude[2] << endl;
				}
				if (ip.print_cons){
					print_concentrations(ip, sd, big_cl, set_num, i);
				}
			}
			//else{
				//cout<< term->blue << "Set " << term->reset << set_num << term->blue << " wild type failed because concentrations is negative or nan ..." << endl;
			//}
		}
		else if (ip.mutants[i] == P1){
			revert_rate = rs.rates_base[TRPO];
			rs.rates_base[TRPO] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double)test_per1kn_fib(big_cl, sd, wtf);
				//cout << "Score P1: " << score << endl;
				if (ip.print_cons){
					print_concentrations(ip, sd, big_cl, set_num, i);
				}
			}
			//else{
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Per 1 knock down failed because concentrations is negative or nan ..." << endl;
			//}
			rs.rates_base[TRPO] = revert_rate;
		}
		else if (ip.mutants[i] == P2){
			revert_rate = rs.rates_base[TRPT];
			rs.rates_base[TRPT] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double)test_per2kn_fib(big_cl, sd, wtf);
				//cout << "Score P2: " << score << endl;
				if (ip.print_cons){
					print_concentrations(ip, sd, big_cl, set_num, i);
				}
			}
			//else{
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Per 2 knock down failed because concentrations is negative or nan ..." << endl;
			//}
			rs.rates_base[TRPT] = revert_rate;
		}
		else if (ip.mutants[i] == P3){
			revert_rate = rs.rates_base[TRPH];
			rs.rates_base[TRPH] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double)test_per3kn_fib(big_cl, sd, wtf);
				//cout << "Score P3: " << score << endl;
				if (ip.print_cons){
					print_concentrations(ip, sd, big_cl, set_num, i);
				}
			}
			//else{
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Per 3 knock down failed because concentrations is negative or nan ..." << endl;
			//}
			rs.rates_base[TRPH] = revert_rate;
		}
		else if (ip.mutants[i] == C1){
			revert_rate = rs.rates_base[TRRO];
			rs.rates_base[TRRO] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_cry1kn_fib(big_cl, sd, wtf);
				//cout << "Score C1: " << score << endl;
			}
			//else{
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Cry 1 knock down failed because concentrations is negative or nan ..." << endl;
			//}
			rs.rates_base[TRRO] = revert_rate;
		}
		else if (ip.mutants[i] == C2){
			revert_rate = rs.rates_base[TRRT];
			rs.rates_base[TRRT] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_cry2kn_fib(big_cl, sd, wtf);
				//cout << "Score C2: " << score << endl;
			}
			//else {
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Cry 2 knock down failed because concentrations is negative or nan ..." << endl;
			//}
			rs.rates_base[TRRT] = revert_rate;
		}
		else if (ip.mutants[i] == BM){
			revert_rate = rs.rates_base[TRB];
			rs.rates_base[TRB] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_bmalkn_fib(big_cl, sd, wtf);
				//cout << "Score BM: " << score << endl;
			}
			//else {
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Bmal knock down failed because concentrations is negative or nan ..." << endl;				
			//}
			rs.rates_base[TRB] = revert_rate;
		}
		else if (ip.mutants[i] == NP){
			revert_rate = rs.rates_base[TRNP];
			rs.rates_base[TRNP] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_npas2kn_fib(big_cl, sd, wtf);
				//cout << "Score NP: " << score << endl;
			}
			//else {
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Npas2 knock down failed because concentrations is negative or nan ..." << endl;				
			//}
			rs.rates_base[TRNP] = revert_rate;
		}
		else if (ip.mutants[i] == C1C2){
			revert_rate = rs.rates_base[TRRO];
			rs.rates_base[TRRO] = 0;
			revert_rate_2 = rs.rates_base[TRRT];
			rs.rates_base[TRRT] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_c1c2kn_fib(big_cl, sd, wtf);
				//cout << "Score C1C2: " << score << endl;
			}
			//else {
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Cry1 Cry2 knock down failed because concentrations is negative or nan ..." << endl;				
			//}
			rs.rates_base[TRRO] = revert_rate;
			rs.rates_base[TRRT] = revert_rate_2;
		}
		else if (ip.mutants[i] == P2C1){
			revert_rate = rs.rates_base[TRPT];
			revert_rate_2 = rs.rates_base[TRRO];
			rs.rates_base[TRPT] = 0;
			rs.rates_base[TRRO] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_p2c1kn_fib(big_cl, sd, wtf);
				//cout << "Score P2C1: " << score << endl;
			}
			//else{
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Per2 Cry1 knock down failed because concentrations is negative or nan ..." << endl;							
			//}
			rs.rates_base[TRPT] = revert_rate;
			rs.rates_base[TRRO] = revert_rate_2;
		}
		else if (ip.mutants[i] == P2C2){
			revert_rate = rs.rates_base[TRPT];
			revert_rate_2 = rs.rates_base[TRRT];
			rs.rates_base[TRPT] = 0;
			rs.rates_base[TRRT] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_p2c2kn_fib(big_cl, sd, wtf);
				//cout << "Score P2C2: " << score << endl;
			}
			//else {
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Per2 Cry2 knock down failed because concentrations is negative or nan ..." << endl;												
			//}
			rs.rates_base[TRPT] = revert_rate;
			rs.rates_base[TRRT] = revert_rate_2;
		}
		else if (ip.mutants[i] == R){
			revert_rate = rs.rates_base[TRREV];
			rs.rates_base[TRREV] = 0;
			valid = calculate_concentrations(ip, cl, big_cl, rs, sd);
			if (valid){
				score += (double) test_rkn_fib(big_cl, sd, wtf);
				//cout << "Score R: " << score << endl;
			}
			//else {
				//cout << term->blue << "Set " << term->reset << set_num << term->blue << " mutant Rev-erb knock down failed because concentrations is negative or nan ..." << endl;															
			//}
			rs.rates_base[TRREV] = revert_rate;
		}
		//// COST//////
		if (ip.compare_exp_data && i == WT){
			cst = cost(big_cl, ed);
		}
	}
	
	cond_score = (double)ip.max_cond_score - score;
	score = WEIGHT_CONDITIONS * (cond_score) + WEIGHT_COST * cst;
	
	if (ip.piping){
		write_pipe(&score, &cond_score , &cst, ip, sd);
	}
	
	return score;
}








