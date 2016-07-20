
#include <cmath>

#include "kftest.hpp"
#include "main.hpp"
#include "macros.hpp"
extern terminal* term;

double cost(con_levels& big_cl, exp_data& ed){
	double diff= 0; 
	int t_index;
	int c_index;
	double sim;
	double exp;
	for (int i = 0; i < ed.num_cons; i++){
		c_index = ed.con_index[i];
		for (int j = 0; j < ed.num_time_steps; j++){
			t_index = ed.sim_time_steps[j];
			sim = big_cl.data[c_index][t_index];
			exp = ed.data[i][j];
			diff += (sim - exp) * (sim - exp);
		}
	}
	int total_points = ed.num_cons * ed.num_time_steps;
	diff /= total_points;
	diff = sqrt(diff);
	cout << "Cost compared to experimental data: " << diff<< endl;
	return diff;
}

void find_peaks_troughs (con_levels& big_cl, peak_trough& pt, int index){
	for (int i = 1; i < (big_cl.time_steps - 1); i ++){
		//Peak
		if ((big_cl.data[index][i] > big_cl.data[index][i + 1]) 
				&& (big_cl.data[index][i] > big_cl.data[index][i - 1])){
			pt.peaks.push_back(i);
		}
		//Trough
		else if ((big_cl.data[index][i] < big_cl.data[index][i + 1]) 
				&& (big_cl.data[index][i] < big_cl.data[index][i - 1])){
			pt.troughs.push_back(i);
		}
	}
}

void get_wtf_index(int con_index, int* wtf_index){
	if (con_index == MNPO){
		*wtf_index = 0;
	}
	else if (con_index == MNPT){
		*wtf_index = 1;
	}
	else if (con_index == MNB){
		*wtf_index = 2;
	}
	else { // this should never happen
		cout << term->red << "The species index:  " << term->reset << con_index << term->red << "is not supported in our species checking list (MNPO, MNPT, MNB)" << term->reset << endl;
		exit(EXIT_FAILURE); 
	}
}

double calculate_average_period(peak_trough& pt, sim_data& sd){
	double per = 0;
	for (int i = 1 ; i < pt.peaks.size(); i ++){
		per += (double)(pt.peaks[i] - pt.peaks[i - 1]);
	}
	
	per *= (sd.step_size * sd.big_gran);
	per /= (pt.peaks.size() - 1);
	
	return per;
}
/*
 * Test the average period of oscillation. If we have the average period to be between MIN_PERIOD and MAX_PERIOD (defined in macros.hpp)
 * Then we pass this test
 */
int test_average_period (peak_trough & pt, sim_data& sd, double * report){
	int score = 0;
	
		//If we could not find enough peaks and troughs to make the simulation reasonable --> score = 0
	if (pt.peaks.size() < LOW_BOUND_NUM_PERIOD) {
		if (sd.verbose){
			term->verbose() << term->red << "	Failed average period test: " << term->reset << endl;
		}
		return 0;
	}
	
	double total_period = 0;
	
	for (int i = 1 ; i < pt.peaks.size(); i ++){
		total_period += (double)(pt.peaks[i] - pt.peaks[i - 1]);
	}
	
	total_period *= (sd.step_size * sd.big_gran);
	total_period /= (pt.peaks.size() - 1);
	
	if (sd.cell_type == SCN){
		if (MIN_PERIOD_SCN <= total_period  && total_period <= MAX_PERIOD_SCN){
			score += MAX_AVG_PER_BEH;
		}
		else {
			if (sd.verbose){
				term->verbose() << term->red << "	Failed average period test: " << term->reset << total_period << endl;
			}
		}
	}
	else if (sd.cell_type == FIB){
		if (MIN_PERIOD_FIB < total_period  && total_period < MAX_PERIOD_FIB){
			score += MAX_AVG_PER_BEH;
		}
		else {
			if (sd.verbose){
				term->verbose() << term->red << "	Failed average period test: " << term->reset << total_period << endl;
			}
		}
	}
	
	* report = total_period;
	return score;
}

void calculate_p2t(peak_trough& pt, con_levels& big_cl, int con_index, double* first_p2t, double* mid_p2t, double* last_p2t){
	if (pt.peaks[0] < pt.troughs[0]){
		double peak_con_1 = big_cl.data[con_index][pt.peaks[0]];
		double peak_con_2 = big_cl.data[con_index][pt.peaks[1]];
		double trough_con = big_cl.data[con_index][pt.troughs[0]];
		*first_p2t = ((peak_con_1 + peak_con_2)/2) / trough_con;
	}
	else if (pt.peaks[0] > pt.troughs[0]){
		double tr_con_1 = big_cl.data[con_index][pt.troughs[0]];
		double tr_con_2 = big_cl.data[con_index][pt.troughs[1]];
		double peak_con = big_cl.data[con_index][pt.peaks[0]];
		*first_p2t = peak_con / ((tr_con_1 + tr_con_2) / 2);
	}
	
	
	int mid_peak = pt.peaks.size() / 2;
	int mid_trough = pt.troughs.size() / 2;
	if (mid_peak == mid_trough && pt.peaks.size() > pt.troughs.size()){
		double peak_con = big_cl.data[con_index][pt.peaks[mid_peak]];
		double tr_con_1 = big_cl.data[con_index][pt.troughs[mid_trough]];
		double tr_con_2 = big_cl.data[con_index][pt.troughs[mid_trough - 1]];
		*mid_p2t = peak_con / ((tr_con_1 + tr_con_2) / 2);
	}
	else if (mid_peak == mid_trough && pt.peaks.size() < pt.troughs.size()){
		double tr_con = big_cl.data[con_index][pt.troughs[mid_trough]];
		double peak_1 = big_cl.data[con_index][pt.peaks[mid_peak]];
		double peak_2 = big_cl.data[con_index][pt.peaks[mid_peak - 1]];
		*mid_p2t = ((peak_1 + peak_2) / 2) / tr_con;
	}
	else if (mid_peak == mid_trough && pt.peaks.size() == pt.troughs.size() && (pt.peaks.size() % 2 == 0)){
		double peak_1 = big_cl.data[con_index][pt.peaks[mid_peak - 1]];
		double peak_2 = big_cl.data[con_index][pt.peaks[mid_peak]];
		double tr_1 = big_cl.data[con_index][pt.troughs[mid_trough - 1]];
		double tr_2 = big_cl.data[con_index][pt.troughs[mid_trough]];
		*mid_p2t = ((peak_1 + peak_2) / 2) / ((tr_1 + tr_2) / 2);
	}
	else if (mid_peak == mid_trough && pt.peaks.size() == pt.troughs.size() && (pt.peaks.size() % 2 == 1)){
		double peak = big_cl.data[con_index][pt.peaks[mid_peak]];
		double tr = big_cl.data[con_index][pt.troughs[mid_trough]];
		*mid_p2t = peak / tr;
	}
	else if (mid_peak > mid_trough){
		double tr_con = big_cl.data[con_index][pt.troughs[mid_trough]];
		double peak_1 = big_cl.data[con_index][pt.peaks[mid_peak]];
		double peak_2 = big_cl.data[con_index][pt.peaks[mid_peak - 1]];
		*mid_p2t = ((peak_1 + peak_2) / 2) / tr_con;
	}
	else if (mid_peak < mid_trough){
		double tr_1 = big_cl.data[con_index][pt.troughs[mid_trough]];
		double tr_2 = big_cl.data[con_index][pt.troughs[mid_trough - 1]];
		double peak = big_cl.data[con_index][pt.peaks[mid_peak]];
		*mid_p2t = peak / ((tr_1 + tr_2) / 2);
	}
	
	if (pt.peaks[pt.peaks.size() - 1] < pt.troughs[pt.troughs.size() - 1]){
		double peak = big_cl.data[con_index][pt.peaks[pt.peaks.size() - 1]];
		double tr_1 = big_cl.data[con_index][pt.troughs[pt.troughs.size() - 2]];
		double tr_2 = big_cl.data[con_index][pt.troughs[pt.troughs.size() - 1]];
		*last_p2t = peak / ((tr_1 + tr_2) / 2);
	}else{
		double peak_1 = big_cl.data[con_index][pt.peaks[pt.peaks.size() - 2]];
		double peak_2 = big_cl.data[con_index][pt.peaks[pt.peaks.size() - 1]];
		double tr = big_cl.data[con_index][pt.troughs[pt.troughs.size() - 1]];
		*last_p2t = ((peak_1 + peak_2) / 2) / tr;
	}
}

int test_sustained_amplitude(sim_data& sd, peak_trough& pt, con_levels& big_cl, int con_index){
	double first_p2t = 0;
	double mid_p2t = 0;
	double last_p2t = 0;
	
	//If we could not find enough peaks and troughs to make the simulation reasonable --> score = 0
	if (pt.peaks.size() < LOW_BOUND_NUM_AMP) {
		if (sd.verbose){
			term->verbose()<< term->red << "	Failed test_sustained_amplitude: " << term->reset << con_index << endl;
		}
		return 0;
	}
	
	calculate_p2t(pt, big_cl, con_index, &first_p2t, &mid_p2t, &last_p2t);


	if (mid_p2t < LOW_BOUND_P2T || last_p2t < LOW_BOUND_P2T || (mid_p2t / last_p2t) > UP_BOUND_M2L){
		if (sd.verbose){
			term->verbose()<< term->red << "	Failed test_sustained_amplitude: " << term->reset << con_index << "  " << mid_p2t << "  " << last_p2t << endl;
		}
		return 0;
	}
	
	
	return MAX_SUSTAINED_AMP_BEH;
}

double calculate_average_amplitude(peak_trough& pt, con_levels& big_cl, int con_index){
	double avg_trough = 0;
	double avg_peak = 0;
	int step;
	for (int i = 0; i < pt.peaks.size(); i ++){
		step = pt.peaks[i];
		avg_peak += big_cl.data[con_index][step];
	}
	avg_peak /= pt.peaks.size();
	
	for (int i = 0; i < pt.troughs.size(); i++){
		step = pt.troughs[i];
		avg_trough += big_cl.data[con_index][step];
	}
	avg_trough /= pt.troughs.size();
	double result = avg_peak - avg_trough;
	return result;
}

/*
 * Maximum score : 2
 */
int check_wildtype_behavior(peak_trough& pt, con_levels& big_cl, sim_data& sd, wildtype_feats& wtf, int con_index){
	int wtf_index;
	get_wtf_index(con_index, &wtf_index);
	
	int score = 0;
	double per;
	double amp;
	
	// sustained 
	int s_osc = test_sustained_amplitude(sd, pt, big_cl, con_index);
	if (s_osc != MAX_SUSTAINED_AMP_BEH){
		return 0;
	}
	
	double wt_per = wtf.period[wtf_index];
	double wt_amp = wtf.amplitude[wtf_index];
	per = calculate_average_period(pt, sd);
	amp = calculate_average_amplitude(pt, big_cl, con_index);
	// period of mt is 1% error from period wt
	if (per <= (UP_WT_PER_ERROR * wt_per) && per >= (LOW_WT_PER_ERROR * wt_per)){
		score += 1;
	}
	else {
		if (sd.verbose){
			term->verbose() << term->red << "	Failed period 1% error condition WT behavior " << term->reset << con_index << "  " << per << endl;
		}
	}
	// amplitude of mt i 20 % error from amplitude wt
	if (amp <= (UP_WT_AMP_ERROR * wt_amp) && amp >= (LOW_WT_AMP_ERROR * wt_amp)){
		score += 1;
	}
	else {
		if (sd.verbose){
			term->verbose() << term->red << "	Failed amplitude 10% error condition WT behavior: " << term->reset << con_index << "  " << amp << endl;
		} 
	}
	
	return score;
}

/*
 * Maximum: 2
 */
int check_shorter_period_behavior(peak_trough& pt, con_levels& big_cl, sim_data& sd, wildtype_feats& wtf, int con_index){
	int score = 0;
	int wtf_index;
	get_wtf_index(con_index, &wtf_index);
	
	if (pt.peaks.size() >= LOW_BOUND_NUM_PERIOD){
		double per = calculate_average_period(pt, sd);
		if ((per <= (wtf.period[wtf_index] * SHORT_PER_FACTOR)) && (per > (wtf.period[wtf_index] - SHORT_PER_THRES))){
			score += MAX_SHORT_PER_BEH;
		}
		else {
			if (sd.verbose){
				term->verbose() << term->red << "	Failed the shorter period conditon : " << term->reset  << con_index << "  " << per << endl;
			}
		}
	}
	else {
		if (sd.verbose){
			term->verbose() << term->red << "	Failed the shorter period conditon : " << term->reset  << con_index << endl;
		}
	}
	
	return score;
}

/*
 * Maximum: 2
 */
int check_longer_period_behavior(peak_trough& pt, con_levels& big_cl, sim_data& sd, wildtype_feats& wtf, int con_index){
	int score = 0;
	int wtf_index;
	get_wtf_index(con_index, &wtf_index);
	
	if (pt.peaks.size() >= LOW_BOUND_NUM_PERIOD){
		double per = calculate_average_period(pt, sd);
		if ((per >= (wtf.period[wtf_index] * LONG_PER_FACTOR)) && (per < (wtf.period[wtf_index] + LONG_PER_THRES))){
			score += MAX_LONG_PER_BEH;
		}
		else{
			if (sd.verbose){
				term->verbose() << term->red << "	Failed the shorter period conditon" << term->reset << con_index << "  " << per << endl;
			}
		}
	}
	else{
		if (sd.verbose){
			term->verbose() << term->red << "	Failed the shorter period conditon " << term->reset << con_index << endl;
		}
	}
	
	return score;
}

/*
 * Maximum: 2
 */
int check_shorter_amplitude_behavior(peak_trough& pt, con_levels& big_cl, sim_data& sd, wildtype_feats& wtf, int con_index){
	int score = 0;
	int wtf_index;
	get_wtf_index(con_index, &wtf_index);
	
	if (pt.peaks.size() >= LOW_BOUND_NUM_PERIOD){
		double amp = calculate_average_amplitude(pt, big_cl, con_index);
		if (amp <= (wtf.amplitude[wtf_index] * SHORT_AMP_FACTOR)){
			score += MAX_SHORT_AMP_BEH;
		}
		else {
			if (sd.verbose){
				term->verbose() << term->red << "	Failed the shorter amplitude condition" << term->reset << con_index  << "  " << amp << endl;
			}
		}
	}
	else {
		if (sd.verbose){
			term->verbose() << term->red << "	Failed the shorter amplitude condition" << term->reset << con_index << endl;
		}
	}
	
	return score;
}

/*
 * Maximum: 2
 */
int check_longer_amplitude_behavior(peak_trough& pt, con_levels& big_cl, sim_data& sd, wildtype_feats& wtf, int con_index){
	int score = 0;
	int wtf_index;
	get_wtf_index(con_index, &wtf_index);
	
	if (pt.peaks.size() >= LOW_BOUND_NUM_PERIOD){
		double amp = calculate_average_amplitude(pt, big_cl, con_index);
		if (amp >= (wtf.amplitude[wtf_index] * LONG_AMP_FACTOR)){
			score += MAX_LONG_AMP_BEH;
		}
		else {
			if (sd.verbose){
				term->verbose() << term->red << "	Failed the shorter amplitude condition" << term->reset << con_index << "  " << amp << endl;
			}
		}
	}
	else {
		if (sd.verbose){
			term->verbose() << term->red << "	Failed the longer amplitude condition" << term->reset << con_index << endl;
		}	
	}
	
	
	return score;
}

/*
 * Maximum: 2
 */
int check_arythmic_behavior(sim_data& sd, peak_trough& pt, con_levels& big_cl, int con_index){
	double first_p2t = 0;
	double mid_p2t = 0;
	double last_p2t = 0 ;
	if (pt.peaks.size() < LOW_BOUND_NUM_PERIOD){
		return MAX_ART_BEH;
	}
	
	calculate_p2t(pt, big_cl, con_index, &first_p2t, &mid_p2t, &last_p2t);
	
	double ratio = mid_p2t / last_p2t;
	if (ratio > LOW_AR_MID_LAST_RATIO){
		return MAX_ART_BEH;
	}
	else {
		if (sd.verbose){
			term->verbose() << term->red << "	Failed the arythimic condition " << term->reset << con_index << "  " << mid_p2t << "  " << last_p2t << endl;
		}
		return 0;
	}
}

/*
 * Maximum: 1
 */
int check_rythmic_behavior(sim_data& sd, peak_trough& pt, con_levels& big_cl, int con_index){
	int score = 0;
	score = test_sustained_amplitude(sd, pt, big_cl, con_index);
	return score;
}

/*
 * Test for sustained oscillations of mPer1, mPer2, mBmal
 * Maximum:  2*2 = 4
 */ 
int test_wildtype_scn(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	int score = 0;
	// the following indices MUST correspond to what we have in wtf.species_index
	int mnpt_index = 1;
	int mnb_index = 2; 
	peak_trough pt;
	
	find_peaks_troughs(big_cl, pt, MNPT);
	score += test_average_period(pt, sd, &wtf.period[mnpt_index]);
	score += test_sustained_amplitude(sd, pt, big_cl, MNPT);
	wtf.amplitude[mnpt_index] = calculate_average_amplitude(pt, big_cl, MNPT);
	pt.reset();
	
	find_peaks_troughs(big_cl, pt, MNB);
	score += test_average_period(pt, sd, &wtf.period[mnb_index]);
	score += test_sustained_amplitude(sd, pt, big_cl, MNB);
	wtf.amplitude[mnb_index] = calculate_average_amplitude(pt, big_cl, MNB);
	
	return score;
}


/*
 * maximum : 2 + 2 = 4
 */
int test_per1kn_scn (con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	int score = 0;
	peak_trough pt;
	//short period mBmal or arythmic mBmal
	find_peaks_troughs(big_cl, pt, MNB);
	score += check_shorter_period_behavior(pt, big_cl, sd, wtf, MNB);
	if (score < MAX_SHORT_PER_BEH){
		score += check_arythmic_behavior(sd, pt, big_cl, MNB);
	}
	
	pt.reset();
	// WT mPer2
	find_peaks_troughs(big_cl, pt, MNPT);
	score += check_wildtype_behavior(pt, big_cl, sd, wtf, MNPT); 
	
	
	return score;
}

/*
 * maximum: 4
 */
int test_per2kn_scn (con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){	
	peak_trough pt;
	// shorter period mBmal
	find_peaks_troughs(big_cl, pt, MNB);
	int score = check_shorter_period_behavior(pt, big_cl, sd, wtf, MNB);
	if (score == MAX_SHORT_PER_BEH){
		return MUTANT_SCN_SCORE;
	}
	else{
		return 0;
	}
}

/*
 * maximum: 4
 */
int test_per3kn_scn(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	peak_trough pt;
	int score = 0;
	// WT or shorter period mPer2
	find_peaks_troughs(big_cl, pt, MNPT);
	double per = calculate_average_period(pt, sd);
	if (per <= wtf.period[1] && per >= (wtf.period[1] - SCN_P3_P2_SHORT_PER)){
		score += MAX_SHORT_PER_BEH;
	}
	pt.reset();
	
	// short period mBmal
	find_peaks_troughs(big_cl, pt, MNB);
	score += check_shorter_period_behavior(pt, big_cl, sd, wtf, MNB);
	
	return score;
}

/*
 * Maximum: 4
 */
int test_cry1kn_scn(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	peak_trough pt;
	int score = 0;
	// shorter period mPer2
	find_peaks_troughs(big_cl, pt, MNPT);
	if (pt.peaks.size() >= LOW_BOUND_NUM_PERIOD){
		double per = calculate_average_period(pt, sd);
		if (per <= (wtf.period[1] - SCN_C1_P2_SHORT_PER)){
			score += MAX_SHORT_PER_BEH;
		}
		else{
			if (sd.verbose){
				term->verbose() << term->red << "	Failed the shorter period condition " << term->reset << MNPT  << "   " << per << endl;
			}
		}
	}
	else {
		if (sd.verbose){
			term->verbose() << term->red << "	Failed the shorter period condition " << term->reset << MNPT << endl;
		}
	}
	pt.reset();
	
	// short period mBmal
	find_peaks_troughs(big_cl, pt, MNB);
	score += check_shorter_period_behavior(pt, big_cl, sd, wtf, MNB);
	
	return score;
}

/*
 * Maximum: 4
 */
int test_cry2kn_scn(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	peak_trough pt;
	int score = 0;
	// long period mBmal
	find_peaks_troughs(big_cl, pt, MNB);
	score += check_longer_period_behavior(pt, big_cl, sd, wtf, MNB);
	pt.reset();
	
	// longer period mPer2
	find_peaks_troughs(big_cl, pt, MNPT);
	if (pt.peaks.size() >= LOW_BOUND_NUM_PERIOD){
		double per = calculate_average_period(pt, sd);
		if (per >= (wtf.period[1] + SCN_C2_P2_LONG_PER)){
			score += MAX_LONG_PER_BEH;
		}
		else{
			if (sd.verbose){
				term->verbose() << term->red << "	Failed the longer period condition " << term->reset << MNPT  << "  " << per << endl;
			}
		}
	}
	else {
		if (sd.verbose){
			term->verbose() << term->red << "	Failed the longer period condition " << term->reset << MNPT << endl;
		}
	}
	
	return score;
}

/*
 * Maximum: 4
 */
int test_bmalkn_scn(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	peak_trough pt;
	int score = 0;
	
	// AR mPer2
	find_peaks_troughs(big_cl, pt, MNPT);
	score = check_arythmic_behavior(sd, pt, big_cl, MNPT);
	if (score < MAX_ART_BEH){
		score = check_shorter_period_behavior(pt, big_cl, sd, wtf, MNPT);
	}
	if (score < MAX_SHORT_PER_BEH){
		return 0;
	}
	return MUTANT_SCN_SCORE;
}

/*
 * Maximum: 4
 */
int test_npas2kn_scn(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	peak_trough pt;
	// WT mBmal
	find_peaks_troughs(big_cl, pt, MNB);
	int score = check_wildtype_behavior(pt, big_cl, sd, wtf, MNB);
	if (score < MAX_WT_BEH){
		return 0;
	}
	
	return MUTANT_SCN_SCORE;
}

/*
 * Maximum: 4
 */
int test_c1c2kn_scn(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	peak_trough pt;
	//AR Bmal
	find_peaks_troughs(big_cl, pt, MNB);
	int score = check_arythmic_behavior(sd, pt, big_cl, MNB);
	if (score < MAX_ART_BEH){
		return 0;
	}
	return MUTANT_SCN_SCORE;
}

int test_wildtype_fib(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	return test_wildtype_scn(big_cl, sd, wtf);
}

/*
 * Maximum: 5
 */
int test_per1kn_fib(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	int score = 0;
	peak_trough pt;
	//AR mPer2
	find_peaks_troughs(big_cl, pt, MNPT);
	score += check_arythmic_behavior(sd, pt, big_cl, MNPT);
	pt.reset();
	
	// WT Bmal
	find_peaks_troughs(big_cl, pt, MNB);
	score += check_wildtype_behavior(pt, big_cl, sd, wtf, MNB);
	
	return score;
}

/*
 * Maximum: 1
 */
int test_per2kn_fib(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	int score = 0;
	peak_trough pt;
	// Short period Bmal
	find_peaks_troughs(big_cl, pt, MNB);
	score += check_shorter_period_behavior(pt, big_cl, sd, wtf, MNB);
	
	return score;
}

/*
 * Maximum: 2
 */
int test_per3kn_fib(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	int score = 0;
	peak_trough pt;
	
	// shorter period mPer2
	find_peaks_troughs(big_cl, pt, MNPT);
	if (pt.peaks.size() >= LOW_BOUND_NUM_PERIOD){
		double per = calculate_average_period(pt, sd);
		if (per <= (wtf.period[1] - FIB_P3_P2_SHORT_PER)){
			score += 1;
		}
		else {
			if (sd.verbose){
				term->verbose() << term->red << "	Failed the shorter period conditon : " << term->reset  << MNPT << "  " << per << endl;
			}
		}
	}else {
		if (sd.verbose){
			term->verbose() << term->red << "	Failed the shorter period conditon : " << term->reset  << MNPT << endl;
		}
	}
	pt.reset();
	
	// shorter period Bmal
	find_peaks_troughs(big_cl, pt, MNB);
	score += check_shorter_period_behavior(pt, big_cl, sd, wtf, MNB);
	
	return score;
}

int test_cry1kn_fib(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	int score = 0;
	peak_trough pt;
	
	//AR mPer2
	find_peaks_troughs(big_cl, pt, MNPT);
	score += check_arythmic_behavior(sd, pt, big_cl, MNPT);
	pt.reset();
	
	//AR Bmal
	find_peaks_troughs(big_cl, pt, MNB);
	score += check_arythmic_behavior(sd, pt, big_cl, MNB);
	
	return score;
}

/*
 * Maximum: 3
 */
int test_cry2kn_fib(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	int score = 0;
	peak_trough pt;
	
	// Longer period mPer2
	find_peaks_troughs(big_cl, pt, MNPT);
	if (pt.peaks.size() >= LOW_BOUND_NUM_PERIOD){
		double per = calculate_average_period(pt, sd);
		if (per <= (wtf.period[1] - FIB_C2_P2_LONG_PER)){
			score += 1;
		}
		else {
			if (sd.verbose){
				term->verbose() << term->red << "	Failed the longer period conditon : " << term->reset  << MNPT << "  " << per << endl;
			}
		}
	}else{
		if (sd.verbose){
			term->verbose() << term->red << "	Failed the longer period conditon : " << term->reset  << MNPT << endl;
		}
	}
	
	
	//increased amplitude mPer2
	score += check_longer_amplitude_behavior(pt, big_cl, sd, wtf, MNPT);
	pt.reset();
	
	//longer period Bmal
	find_peaks_troughs(big_cl, pt, MNB);
	score += check_longer_period_behavior(pt, big_cl, sd, wtf, MNB);
	
	return score;
}

/*
 * Maximum: 1
 */
int test_bmalkn_fib(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	int score = 0;
	peak_trough pt;
	// AR mPer2
	find_peaks_troughs(big_cl, pt, MNPT);
	score += check_arythmic_behavior(sd, pt, big_cl, MNPT);
	
	return score;
}

/*
 * Maximum: 4
 */
int test_npas2kn_fib(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	int score = 0;
	peak_trough pt;
	
	// WT Bmal
	find_peaks_troughs(big_cl, pt, MNB);
	score += check_wildtype_behavior(pt, big_cl, sd, wtf, MNB);
	
	return score;
}

/*
 * Maximum: 1
 */
int test_c1c2kn_fib(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	int score = 0;
	peak_trough pt;
	
	// AR Bmal
	find_peaks_troughs(big_cl, pt, MNB);
	score += check_arythmic_behavior(sd, pt, big_cl, MNB);
	
	return score;
}

/*
 * Maximum: 1
 */
int test_p2c1kn_fib(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	int score = 0;
	peak_trough pt;
	//AR in mPer 1
	find_peaks_troughs(big_cl, pt, MNPO);
	score += check_arythmic_behavior(sd, pt, big_cl, MNPO);
	
	return score;
}

/*
 * Maximum: 1
 */
int test_p2c2kn_fib(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){
	int score = 0;
	peak_trough pt;
	// rythmic mPer1
	find_peaks_troughs(big_cl, pt, MNPO);
	score += check_rythmic_behavior(sd, pt, big_cl, MNPO);
	
	return score;
}

/*
 * Maximum: 1
 */
int test_rkn_fib(con_levels& big_cl, sim_data& sd, wildtype_feats& wtf){	
	int score = 0;
	peak_trough pt;
	// WT Bmal or low amplitude Bmal
	find_peaks_troughs(big_cl, pt, MNB);
	score += check_wildtype_behavior(pt, big_cl, sd, wtf, MNB);
	if (score == 4){
		return 1;
	}
	else{
		score = check_shorter_amplitude_behavior(pt, big_cl, sd, wtf, MNB);
		if (score == 1){
			return 1;
		}
		else {
			return 0;
		}
	}
}

