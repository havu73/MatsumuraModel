#ifndef STRUCTS_HPP
#define STRUCTS_HPP
///INCLUDE HEADER FILES
#include <cstdlib> // Needed for cmath
#include <cstring> // Needed for strlen, memset, memcpy
#include <iostream> // Needed for cout
#include <bitset> // Needed for bitset
#include <fstream> // Needed for ofstream
#include <string>
#include <vector> // Needed for peak_trough
#include <map> // Needed for map
#include "macros.hpp"
#include "memory.hpp"


//use standard name_space here
using namespace std;

/*
 * This struct contains repeated used phrases and colors to print onto terminal in our program
 */
struct terminal {
	// Escape codes
	const char* code_blue;
	const char* code_red;
	const char* code_reset;
	
	// Colors
	char * blue;
	char * red;
	char * reset;
	
	// Verbose stream
	streambuf* verbose_streambuf;
	ostream* verbose_stream;
	
	terminal () {
		this->code_blue = "\x1b[34m";
		this->code_red = "\x1b[31m";
		this->code_reset = "\x1b[0m";
		this->blue = new char [10];
		this->red = new char [10];
		this->reset = new char [10];
		strcpy(this->blue, this->code_blue);
		strcpy(this->red, this->code_red);
		strcpy(this->reset, this->code_reset);
		this->verbose_stream = new ostream(cout.rdbuf());
	}
	
	~terminal () {
		delete []this->blue;
		delete []this->red;
		delete []this->reset;
		delete verbose_stream;
	}
	
	// Indicates a task is done (pass terminal->verbose() into this function to print only with verbose mode on)
	void done (ostream& stream) {
		stream << this->blue << "Done" << this->reset << endl;
	}
	
	// Indicates a task is done
	void done () {
		done(cout);
	}
	
	// Indicates the program is out of memory
	void no_memory () {
		cout << this->red << "Not enough memory!" << this->reset << endl;
	}
	
	// Indicates the program couldn't read from a pipe
	void failed_pipe_read () {
		cout << this->red << "Couldn't read from the pipe!" << this->reset << endl;
	}
	
	// Indicates the program couldn't write to a pipeinput_params
	void failed_pipe_write () {
		cout << this->red << "Couldn't write to the pipe!" << this->reset << endl;
	}
	
	// Returns the verbose stream that prints only when verbose mode is on
	ostream& verbose () {
		return *(this->verbose_stream);
	}
	
	// Sets the stream buffer for verbose mode
	void set_verbose_streambuf (streambuf* sb) {
		this->verbose_stream->rdbuf(sb);
		this->verbose_streambuf = this->verbose_stream->rdbuf();
	}
};

/*
 * This struct contains data to store experimental data to compare with our simulated data.
 * It is used in caculation of cost function (kftest.cpp). 
 * Please read the README file to understand the structure of a experimental data file as input to our program
 */
struct exp_data{
	bool initialized; // is this struct initialized or not? It is initialized when we can access the file containing experimental data(ex: 'KFdata.txt'), and get the number of time steps and concentrations contained in this file
	int num_cons; // The number of concentrations of mRNAs, proteins, etc. stored in the file of experimental data (For example: an exp_data file only contains data of cons of Per1 mRNA and Per2mRNA in cy --> num_cons = 2). This number should be specified at the first line of the exp_data file passed in as parameter from user
	int num_time_steps; // The number of time_steps that we have to compare between exp_data and sim_data (Ex: we collected data at 10 time points throughout simulation--> 10). This should be specified at the second line of the exp_data file
	int* sim_time_steps; // The corresponding time_steps of simulation that we have to compare with the real time points (Ex: time = [0.5, 1, 1.5] --> sim_time_steps = [50, 100, 150]-- given that the step_size to record into big_cl is 0.01)
	int* con_index; // The corresponding index that we look up based on the third line in the exp_data file (Ex: 'time, p1mrnaCy, p1mrnaNu, p2mrnaCy, p2mrnaNu' --> con_index = [MNPO, MCPO, MNPT, MCPT]). (README for info about a valid exp_data file format)
	double** data; // the data of concentrations extracted from the file
	
	exp_data(){
		this->initialized = false;
	}
	
	void initialize(int cons, int steps){
		if (this->initialized && this->num_cons <= cons && this->num_time_steps <= steps){
			this->reset();
		}else{
			if (this->initialized){
				this->clear();
			}
			this->initialized = true;
			this->num_cons = cons;
			this->num_time_steps = steps;
			this->sim_time_steps =  new int[steps];
			this->con_index = new int[cons];
			this->data = new double* [cons];
			for (int i = 0; i < cons; i++){
				this->data[i] = new double[steps];
				for (int j = 0; j < steps; j++){
					this->data[i][j] = 0;
				}
			}
		}
	}
	
	void reset(){
		if (this->initialized){
			for (int i = 0; i < this->num_cons; i ++){
				this->con_index[i] = 0;
				for (int j = 0; j < this->num_time_steps; j ++){
					this->data[i][j] = 0;
				}
			}
			
			for (int j = 0; j < this->num_time_steps; j++) {
				this->sim_time_steps = 0;
			}
		}
	}
	
	void clear(){
		if (this->initialized){
			for (int i = 0; i < this->num_cons; i ++){
				delete[] this->data[i];
			}
			delete[] this->data;
			delete[] this->sim_time_steps;
			delete[] this->con_index;
			this->initialized = false;
		}
	}
	
	~exp_data(){
		this->clear();
	}
};


struct input_params {
	// Input and output files' paths and names (either absolute or relative)
	char* params_file; // The path and name of the parameter sets file, default=input.params
	bool read_params; // Whether or not the read the parameter sets file, default=false
	char* ranges_file; // The path and name of the parameter ranges file, default=none
	bool read_ranges; // Whether or not to read the ranges file, default=false
	char* passed_file; // The path and name of the passed file, default=output.passed
	ofstream* passed_stream; // The ofstream of the file that contains all parameter sets that pass all conditions 
	bool print_passed; // Whether or not to print the passed file, default=false
	char* dir_path; // The path of the output directory for concentrations or oscillation features, default=none
	bool print_cons; // Whether or not to print concentrations, default=false
	bool binary_cons_output; // Whether or not to print the binary or ASCII value of numbers in the concentrations output files
	char* features_file; // The path and file of the features file, default=none
	bool print_features; // Whether or not to print general features file, default=false
	
	// Sets
	int num_sets; // The number of parameter sets to simulate, default=1
	

	// Time
	int time_total; // The number of minutes to run each simulation for, default=1200
	double step_size; // The time step in minutes used for Euler's method, default=0.01
	int big_gran; // The granularity in time steps with which to store data, default=1
	int small_gran; // The granularit in time steps with which to simulate data, default=1
	
	//Seed
	int seed; // The seed, used for generating random numbers, default=generated from the time and process ID
	bool reset_seed; // Whether or not to reset the seed after each parameter set, default=false
	int pseed; // The seed, used for generating random parameter sets, default=generated from the time and process ID
	bool store_pseed; // Whether or not to store the parameter generation seed, pseed, default=false
	char* seed_file; // Default=none
	bool print_seeds; // Whether or not to print the seeds used to the seed file
	
	//mutant management
	bool short_circuit; // Whether or not to stop simulating a parameter set after a mutant fails
	int num_active_mutants;
	
	// Piping data
	bool piping; // Whether or not input and output should be piped (as opposed to written to disk), default=false
	int pipe_in; // The file descriptor to pipe data from, default=none (0)
	int pipe_out; // The file descriptor to pipe data into, default=none (0)
	
	// Output stream data
	bool verbose; // Whether or not the program is verbose, i.e. prints many messages about program and simulation state, default=false
	bool quiet; // Whether or not the program is quiet, i.e. redirects cout to /dev/null, default=false
	streambuf* cout_orig; // cout's original buffer to be restored at program completion
	ofstream* null_stream; // A stream to /dev/null that cout is redirected to if quiet mode is set

	// Experimental data- related items (can be used for testing purposes)
	bool compare_exp_data; // whether we have to compare simulation data with experiment data or not
	char* exp_data_file;	// name of path to the file that contains exp_data. README for info about the formats of exp_data_file
	double exp_diff_thres;	// If the cost of difference between the sim_data and exp_data is below this threshold, the simulation pass this test of fitness with experimental data. Default = 2.0 
	
	// Data about mutants
	int max_cond_score;
	int* mutants;
	int num_mutants;
	
	// Data about the cell we are working on
	int cell_type;
	
	input_params () {
		//input and output files
		this->params_file = new char[30];
		this->read_params = false;
		this->ranges_file = new char [30];
		this->read_ranges = false;
		this->passed_file = new char [30];
		this->print_passed = false;
		this->passed_stream = new ofstream();
		this->print_passed = false;
		this->dir_path = new char [30];
		this->print_cons = false;
		this->binary_cons_output = false;
		this->features_file = new char [30];
		this->print_features = false;
		
		//timing
		this->num_sets = 1;
		this->step_size = 0.001;
		this->time_total = 100;
		this->big_gran = 1000;
		
		//seeds
		this->seed = 0;
		this->reset_seed = false;
		this->pseed = 0;
		this->store_pseed = false;
		this->seed_file = new char [30];
		this->print_seeds = false;
		
		//mutant management
		this->short_circuit = false;
		this->num_active_mutants = 1;
		
		//piping data
		this->piping = false;
		this->pipe_in = 0;
		this->pipe_out = 0;
		
		//output stream data
		this->verbose = false;
		this->quiet = false;
		this->cout_orig = NULL;
		this->null_stream = new ofstream("/dev/null");
		
		// Experimental data- related items (can be used for testing purposes)
		this->compare_exp_data = false;
		this->exp_data_file = new char [30];
		this->exp_diff_thres = 2;
		
		// Data about mutants
		this->max_cond_score = MAX_SCN;
		this->mutants = new int [NUM_MUTANTS];
		for (int i = 0; i < NUM_MUTANTS; i++){
			this->mutants[i] = i;
		}
		this->num_mutants = NUM_MUTANTS;
		
		// Data about cell type
		this->cell_type = SCN;
	}
	
	~input_params () {
		delete [] this->params_file;
		delete [] this->passed_file;
		delete [] this->dir_path;
		delete [] this->features_file;
		delete [] this->seed_file;
		delete this->null_stream;
		delete this->passed_stream;
		delete [] this->exp_data_file;
	}
};

struct rates {
	//rates bases and rates for mutants
	double* rates_base;  // Base rates taken from the current parameter set
	double* factors_perturb;  // Perturbations (as percentages with 1=100%) taken from the perturbations input file
	
	explicit rates () {
		this->rates_base = new double [NUM_RATES];
		this->factors_perturb = new double [NUM_RATES];
		memset(this->rates_base, 0, sizeof(double) * NUM_RATES);
		memset(this->factors_perturb, 0, sizeof(double) * NUM_RATES);
	}
	
	void clear (){
		delete [](this->rates_base);
		delete [](this->factors_perturb);
	}
	
	~rates () {
		delete [](this->rates_base);
		delete [](this->factors_perturb);
	}
};

struct con_levels {
	bool initialized; // Whether or not this struct's data have been initialized
	int num_con_levels; // The number of concentration levels this struct stores (not necessarily the total number of concentration levels)
	int big_gran; // The number of steps to store in cl.data for simulation purposes. This has to be equal to ip.big_gran
	int time_steps; // The number of time steps this struct stores concentrations for (will be equal to sd.steps_total / ip.big_gran)
	double ** data; // A two dimensional array that stores [concentration levels][# time_steps = big_gran] in that order (read readme file about big_gran to understand the functionality of data and big_data)
	
	con_levels () {
		this->initialized = false;
	}
	
	con_levels (int num_con_levels, int time_steps, int big_gran) {
		this->initialized = false;
		initialize(num_con_levels, time_steps, big_gran);
	}
	
	// Initializes the struct with the given number of concentration levels, time steps, and cells
	void initialize (int num_con_levels, int time_steps, int big_gran) {
		// If the current size is big enough to fit the new size then reuse the memory, otherwise allocate the required memory
		if (this->initialized && this->num_con_levels >= num_con_levels && this->time_steps >= time_steps) {
			this->reset();
		} else {
			this->num_con_levels = num_con_levels;
			this->time_steps = time_steps;
			this->big_gran = big_gran;
			this->data = new double* [num_con_levels];
			
			for (int i = 0; i < num_con_levels; i++) {
				this->data[i] = new double[time_steps];
				for (int j = 0; j < this->time_steps; j++){
					this->data[i][j] = 0;
				}
			}
			
			this->initialized = true;
		}
	}
	
	// Sets every value in the struct to 0 but does not free any memory
	void reset () {
		if (this->initialized) {
			for (int i = 0; i < this->num_con_levels; i++) {
				for (int j = 0; j <this->time_steps; j++){
					this->data[i][j] = 0;
				}
			}
		}
	}
	
	// Frees the memory used by the struct
	void clear () {
		if (this->initialized) {
			for (int i = 0; i < this->num_con_levels; i++) {
				delete[] this->data[i];
			}
			delete[] this->data;
			this->initialized = false;
		}
	}
	
	~con_levels () {
		this->clear();
	}
};




struct sim_data {
	// Times and timing
	double step_size; // The step size in minutes
	int time_total; // The number of minutes to run for
	int steps_total; // The number of time steps to simulate (total time / step size)
	
	// Granularities
	int big_gran; // The granularity in time steps with which to analyze and store data
	
	// Mutants and condition scores
	int num_active_mutants; // The number of mutants to simulate for each parameter set
	
	//verbosity
	bool verbose;
	
	// cell_type
	int cell_type;
	explicit sim_data (input_params& ip) {
		//timing
		this->step_size = ip.step_size;
		this->time_total = ip.time_total;
		this->steps_total = ip.time_total / ip.step_size;
		
		//granularities
		this->big_gran = ip.big_gran;
		
		//mutants and conditions scores
		this->num_active_mutants = ip.num_active_mutants;
		
		// verbosity
		this->verbose = ip.verbose;
		
		// cell type
		this->cell_type = ip.cell_type;
	}
};

struct features {
	double period[NUM_FEATURE_CONS];
	double amplitude[NUM_FEATURE_CONS];
	
	features () {
		memset(period, 0, sizeof(period));
		memset(amplitude, 0, sizeof(amplitude));
	}
	
	void reset () {
		memset(period, 0, sizeof(period));
		memset(amplitude, 0, sizeof(amplitude));
	}
};


struct mutant_data {
	int index; // The index, i.e. how many mutants run before this one
	char* print_name; // The mutant's name for printing output
	char* dir_name; // The mutant's name for making its directory
	int num_knockouts; // The number of knockouts required to achieve this mutant
	int knockouts[2]; // The indices of the concentrations to knockout (num_knockouts determines how many indices to knockout)
	features feat; // The oscillation features this mutant produced when run
	int print_con; // The index of the concentration that should be printed (usually mh1)
	
	mutant_data () {
		this->index = 0;
		this->print_name = NULL;
		this->dir_name = NULL;
		this->num_knockouts = 0;
	}
	
	~mutant_data () {
		free(this->print_name);
		free(this->dir_name);
	}
};

struct input_data {
	char* filename; // The path and name of the file
	char* buffer; // A buffer to store the file's contents
	int size; // The number of bytes the file's contents take up
	int index; // The current index to access the buffer from
	
	explicit input_data (char* filename) {
		this->filename = filename;
		this->buffer = NULL;
		this->size = 0;
		this->index = 0;
	}
	void clear(){
		free(this->buffer);
	}
	
	~input_data () {
		free(this->buffer);
	}
};


struct parameters {
	//rates bases and rates for mutants
	double** data;  // Base rates taken from the current parameter set
	int num_sets; 
	explicit parameters (int num_sets) {
		this->num_sets = num_sets;
		this->data = new double* [num_sets];
		for (int i = 0; i < num_sets; i ++){
			this->data[i] = new double[NUM_RATES];
			memset(this->data[i], 0, sizeof(double) * NUM_RATES);
		}
	}
	
	void clear (){
		for (int i = 0; i < this->num_sets; i++) {
				delete[] this->data[i];
		}
		delete[] this->data;
	}
	
	~parameters () {
		this->clear();
	}
};

struct growin_array {
	int* array; // The array of integers
	int size; // The size of the array

	growin_array() {}

	void initialize(int size) {
		array = new int[size];
		this->size = size;
	}
	
	explicit growin_array (int size) {
		this->initialize(size);
	}

	int& operator[] (int index) {
		if (index >= this->size) {
			int* new_array = new int[2 * this->size];
			for (int i = 0; i < this->size; i++) {
				new_array[i] = array[i];
			}
			delete[] array;
			this->size = 2 * this->size;
			array = new_array;
		}
		return array[index];
	}
	
	void reset(int new_size) {
		this->size = new_size;
	}
	
	int get_size() {
		return this->size;
	}
	
	~growin_array () {
		delete[] array;
	}
};

struct peak_trough {
	std::vector<int> peaks;
	std::vector<int> troughs;
	
	void initialize(){
		this->peaks.clear();
		this->troughs.clear();
	}
	
	explicit peak_trough(){
		this->initialize();
	}
	
	void reset(){
		initialize();
	}
};

struct wildtype_feats{
	double * period;	// an array storing average wild type period of species we care about
	double * amplitude; // an array storing average wild type amplitude of species we care about
	int * species_index; // an array storing the index of species we care about, which should corresponds to period and amplitude
	int num_species; // total number of species we care about
	explicit wildtype_feats(){
		this->num_species = 3; // we care about MNPO, MNPT, MNB
		this->species_index = new int [3];
		this->species_index[0] = MNPO;
		this->species_index[1] = MNPT;
		this->species_index[2] = MNB;
		this->period = new double[3];
		memset(this->period, 0, sizeof(double) * 3);
		this->amplitude = new double [3];
		memset(this->amplitude, 0, sizeof(double) * 3);
	}
	
	void reset(){
		memset(this->period, 0, sizeof(double) * 3);
		memset(this->amplitude, 0, sizeof(double) * 3);
	}
	
	~wildtype_feats(){
		delete[] this->period;
		delete[] this->amplitude;
		delete[] this->species_index;
	}
};
#endif
