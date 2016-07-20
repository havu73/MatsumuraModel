#include "main.hpp"
#include "init.hpp"
#include "sim.hpp"
#include "debug.hpp"
#include "io.hpp"
//namespace
using namespace std;
extern terminal * term;

int main(int argc, char ** argv){
	// Initialize the program's terminal functionality and input parameters
	input_params ip;
	init_terminal();
	accept_input_params (argc, argv, ip);
	check_input_params(ip);
	init_verbosity(ip);
	
	
	// Calculate the maximum conditional score that we can get
	if (ip.num_mutants != NUM_MUTANTS){ // Since the default is to run all mutants available, and ip.max_cond_score is default MAX_SCORE, we only need to calculate score when users specify something different. 
										// Dont worry about cases when users enter the same number of mutants but they are wrongly entered, because that gets checked in accept_input_params
		calculate_max_cond_score(ip);
	}
	
	// declare input_data objects based on users' input about input file names. The buffer of these objects is empty now, and will be filled in right after this declaration section
	input_data params_data(ip.params_file);
	input_data ranges_data(ip.ranges_file);
	
	
	// process parameters
	parameters pr(ip.num_sets);
	read_sim_params(ip, params_data, pr, ranges_data);

	// Initialize simulation data, rates (and their perturbations and gradients), and mutant data
	sim_data sd(ip);
	rates* rs = new rates();
	
	exp_data ed;
	if (ip.compare_exp_data){
		input_data experiment_data(ip.exp_data_file);
		read_experiment_data(ip, experiment_data, ed);
	}
	
	if (ip.print_passed){
		create_passed_file(ip);
	}
	//////////////SIMULATE///////////////
	
	simulate_all_params(ip, *rs, sd, pr, ed);

	////////////////////////////////////
	
	delete rs;
	//delete_file(file_passed);
	#if defined(MEMTRACK)
		print_heap_usage();
	#endif
	free_terminal();
	reset_cout(ip);
	return EXIT_SUCCESS;
}


void usage (const char* message) {
	cout << endl;
	bool error = message != NULL && message[0] != '\0';
	if (error) {
		cout << term->red << message << term->reset << endl << endl;
	}
	cout << "Usage: [-option [value]]. . . [--option [value]]. . ." << endl;
	cout << "-i, --params-file        [filename]   : the relative filename of the parameter sets input file, default=none" << endl;
	cout << "-o, --print-passed       [filename]   : the relative filename of the passed sets output file, default=none" << endl;
	cout << "-t, --print-cons         [N/A]        : print concentration values to the specified output directory, default=unused" << endl;
	cout << "-B, --binary-cons-output [N/A]        : print concentration values as binary numbers rather than ASCII, default=unused" << endl;
	cout << "-D, --directory-path     [directory]  : the relative directory where concentrations or anterior oscillation features files will be printed, default=none" << endl;
	cout << "-ce,--compare-exp-data   [filename]   : the relative filename of the experimental data input file, default=none"<< endl;
	cout << "-th,--diff-threshold     [float]      : the threshold for the average difference between simulation data and experimental data. Default=2.0"<< endl;
	cout << "-pp,--print-passed       [filename]   : the relative filename of the file that records all parameter sets that pass all the conditions"<< endl;
	cout << "-ct,--cell-type          [string]     : the name of cell type that we study ('scn', 'lung', 'fibroblasts', 'liver', 'cornea', 'fat', 'bone')"<< endl;
	cout << "-M, --mutants			  [string]     : the list of mutants to simulate and determine conditions. Ex: \"0 1 2 3\" or \"wt p1 p2\" (Please refer to the README for details)"<< endl;
	cout << "-b, --big-granularity    [int]        : the granularity in time steps with which to store data, min=1, default=100" << endl;
	cout << "-S, --step-size          [float]      : the size of the timestep to be used for solving the DDEs using Euler's method, default=0.0001" << endl;
	cout << "-m, --total-time         [int]        : the number of minutes to simulate before ending, min=1, default=1200" << endl;
	cout << "-p, --parameter-sets     [int]        : the number of parameters for which to simulate the model, min=1, default=1" << endl;
	cout << "-s, --seed               [int]        : the seed to generate random numbers, min=1, default=generated from the time and process ID" << endl;
	cout << "-X, --reset-seed         [N/A]        : reset the seed after each parameter set so the initial seed is used each time, default=unused" << endl;
	cout << "-d, --parameters-seed    [int]        : the seed to generate random parameter sets, min=1, default=generated from the time and process ID" << endl;
	cout << "-e, --print-seeds        [filename]   : the relative filename of the seed output file, default=none" << endl;
	cout << "-a, --max-con-threshold  [float]      : the concentration threshold at which to fail the simulation, min=1, default=infinity" << endl;
	cout << "-C, --short-circuit      [N/A]        : stop simulating a parameter set after a mutant fails, default=unused" << endl;
	cout << "-M, --mutants            [int]        : the number of mutants to run for each parameter set, min=1, default= 1" << endl;
	cout << "-I, --pipe-in            [file desc.] : the file descriptor to pipe data from (usually passed by the sampler), default=none" << endl;
	cout << "-O, --pipe-out           [file desc.] : the file descriptor to pipe data into (usually passed by the sampler), default=none" << endl;
	cout << "-c, --no-color           [N/A]        : disable coloring the terminal output, default=unused" << endl;
	cout << "-v, --verbose            [N/A]        : print detailed messages about the program and simulation state, default=unused" << endl;
	cout << "-q, --quiet              [N/A]        : hide the terminal output, default=unused" << endl;
	cout << "-l, --licensing          [N/A]        : view licensing information (no simulations will be run)" << endl;
	cout << "-h, --help               [N/A]        : view usage information (i.e. this)" << endl;
	cout << endl << term->blue << "Example: ./simulation -i parameters.csv --parameters 10 -m 2000 --no-color" << term->reset << endl << endl;
	if (error) {
		exit(EXIT_INPUT_ERROR);
	} else {
		exit(EXIT_SUCCESS);
	}
}

void licensing () {
	cout << endl;
	cout << "Simulation for -----------" << endl;
	cout << "Copyright (C) 2016 ---------------" << endl;
	cout << "This program comes with ABSOLUTELY NO WARRANTY" << endl;
	cout << "This is free software, and you are welcome to redistribute it under certain conditions;" << endl;
	cout << "You can use this code and modify it as you wish under the condition that you refer to the article: \"Short-lived Her proteins drive robust synchronized oscillations in the zebrafish segmentation clock\" (Development 2013 140:3244-3253; doi:10.1242/dev.093278)" << endl;
	cout << endl;
	exit(EXIT_SUCCESS);
}
