//for string processing
#include <cerrno> // Needed for errno, EEXIST
#include <cstdio> // Needed for fopen, fclose, fseek, ftell, rewind
#include <sys/stat.h> // Needed for mkdir
#include <unistd.h> // Needed for read, write, close
#include <stdio.h>
#include <string.h>

#include "io.hpp"
#include "main.hpp"
#include "macros.hpp"
extern terminal* term;
/* copy string from value to field.
 * Used in accept_input_params (init.cpp) to store users' input files names into corresponding field in ip
 * Ex: store_filename(&(ip.passed_file_name), value)
 * Params: field: pointers to an array of characters, most likely pointers to a field in ip
 * 		   value: an array of char (from users' arguments)
 */
void store_filename (char** field, const char* value) {
	strcpy(*field, value);
}

/* Read parameters from pipe, and store into pr structure. Used when sres sends parameters into simulation. 
 * Params: pr: structure declared in main (main.cpp) to store parameters
 * 		   ip: input params created and modified in main (main.cpp), containing file descriptors to get input (ip.pipe)in)
 * Notes: in sres, the first number we pipe in it the total number of rates, so the first number we check here
 * is also the number of rates, if this number is not NUM_RATES (macros.hpp), program will be frozen. 
 * in sres, the second number piped in is the number of param set (1), so the second number we read from pipe is the number of param sets,
 * stored in ip.num_sets
 * Next, we read the parameters.
 */
void read_pipe (parameters& pr, input_params& ip) {
	// Read how many rates per set will be piped in
	int num_pars = 0;
	read_pipe_int(ip.pipe_in, &num_pars);
	if (num_pars != NUM_RATES) {
		cout << term->red << "An incorrect number of rates will be piped in! This simulation requires " << NUM_RATES << " rates per set but the sampler is sending " << num_pars << " per set." << term->reset << endl;
		exit(EXIT_INPUT_ERROR);
	}

	// Read how many sets will be piped in
	int num_sets = 0;
	read_pipe_int(ip.pipe_in, &num_sets);
	if (num_sets < ip.num_sets) {
		cout << term->red << "The number of num_sets provided by pipe is " << num_sets << ", but you specified " << ip.num_sets << " sets. "<< term->reset << endl;
		exit(EXIT_INPUT_ERROR);
	}
	
	// Read every set and store into pr.data
	for (int i = 0; i < ip.num_sets; i++) {
		if (read(ip.pipe_in, pr.data[i], sizeof(double) * NUM_RATES) == -1){
			term->failed_pipe_read();
			exit(EXIT_PIPE_READ_ERROR);
		}
	}
}

/* read int from file descriptor fd and store that number into int pointer address
 * Helper function of read_pipe (io.cpp)
 * params: fd: file descriptor, most likely ip.pipe_in
 * 		
 */
void read_pipe_int (int fd, int* address) {
	if (read(fd, address, sizeof(int)) == -1) {
		term->failed_pipe_read();
		exit(EXIT_PIPE_READ_ERROR);
	}
}

/* Put the file's content into input_data* ifd.buffer
 * Called in read_experiment_data, read_sim_data (init.cpp) to read users' file input
 * Params: input_data* structure declared in main(main.cpp)
 */
void read_file (input_data* ifd) {
	cout << term->blue << "Reading file " << term->reset << ifd->filename << " . . . ";
	// Open the file for reading
	FILE* file = fopen(ifd->filename, "r");
	if (file == NULL) {
		cout << term->red << "Couldn't open " << ifd->filename << "!" << term->reset << endl;
		exit(EXIT_FILE_READ_ERROR);
	}
	
	// Seek to the end of the file, grab its size, and then rewind
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	ifd->size = size;
	rewind(file);
	// Allocate enough memory to contain the whole file
	ifd->buffer = (char*)mallocate(sizeof(char) * size + 1);
	// Copy the file's contents into the buffer
	long result = fread(ifd->buffer, 1, size, file);
	if (result != size) {
		cout << term->red << "Couldn't read from " << ifd->filename << term->reset << endl;
		exit(EXIT_FILE_READ_ERROR);
	}
	ifd->buffer[size] = '\0';
	
	// Close the file
	if (fclose(file) != 0) {
		cout << term->red << "Couldn't close " << ifd->filename << term->reset << endl;
		exit(EXIT_FILE_READ_ERROR);
	}
	term->done();
}

/* parse_param_line reads a line in the given parameter sets buffer and stores it in the given array of doubles
	parameters:
		params: the array of doubles to store the parameters in
		buffer_line: the buffer with the line to read
		index_buffer: the index of the buffer to start from
	returns: true if a line was found, false if the end of the file was reached without finding a valid line
	notes:
		The buffer should contain one parameter set per line, each set containing comma-separated floating point parameters.
		Blank lines and lines starting with # will be ignored.
		Each line must contain the correct number of parameters or the program will exit.
		index_buffer is a reference, allowing this function to store where it finished parsing.
	todo:
*/
bool parse_param_line (parameters& pr, int j, char* buffer_line, int& index_buffer) {
	static const char* usage_message = "There was an error reading the given parameter sets file.";
	int index_params = 0; // Current index in params
	int index_digits = index_buffer; // Index of the start of the digits to read
	int i = index_buffer; // Current index in buffer_line
	int line_start = i; // The start of the line, used to tell whether or not a line is empty
	for (; not_EOL(buffer_line[i]); i++) {
		if (buffer_line[i] == '#') { // Skip any lines starting with #
			for(; not_EOL(buffer_line[i]); i++);
			line_start = i + 1; 
			index_digits = i + 1;
			i++;
		} else if (buffer_line[i] == ',' ) { // Indicates the end of the digits to read
			if (sscanf(buffer_line + index_digits, "%lf", &pr.data[j][index_params++]) < 1) { // Convert the string of digits to a double when storing it in params
				usage(usage_message);
			}
			index_digits = i + 1;
		}
	}
	index_buffer = i + 1;
	if (i - line_start > 0) { // This line has content
		if (sscanf(buffer_line + index_digits, "%lf", &pr.data[j][index_params++]) < 1) {
			usage(usage_message);
		}
		if (index_params != NUM_RATES) {
			cout << term->red << "The given parameter sets file contains sets with an incorrect number of rates! This simulation requires " << NUM_RATES << " per set but at least one line contains " << index_params << " per set." << term->reset << endl;
			exit(EXIT_INPUT_ERROR);
		}
		return true;
	} else if (buffer_line[index_buffer] != '\0' && buffer_line[index_buffer] != '\n') { // There are more lines to try to parse
		return parse_param_line(pr, j, buffer_line, index_buffer);
	} else { // The end of the buffer was found
		return false;
	}
}

/* 
 * Get the number of species and time steps that we have experimental data for in experimental data file
 * Store into int* cons, int* steps
 * Params: ip, exp: the input_data containing experimental data file declared in main(main.cpp), 
 * 		   cons and steps: pointers to int to store the size of experimental data sets, which will be used to declare the size of expermental_data structure
 * 		   in main (main.cpp). 
 * Called in read_exp_data (init.cpp)
 */
void parse_experiment_data_size(input_params& ip, input_data& exp, int* cons, int* steps){
	static const char* usage_message = "There was an error reading the SIZE of the given experimental data set file.";
	int i = exp.index;
	int line_start = i;
	//The first line is to store num_cons to compare
	for (;not_EOL(exp.buffer[i]); i++){
		if (exp.buffer[i] == '#'){ //Skip any lines starting with #
			for (;not_EOL(exp.buffer[i]); i++){}
			i++;
			line_start = i; 
			exp.index = i; 
		}
	}
	
	//scan the number of species and put into cons
	if (sscanf(exp.buffer + line_start, "%d", cons) < 1){
		usage(usage_message);
	}
	exp.index = i + 1;
	line_start = i + 1;
	i = i + 1;

	
	//The second line is to store num_time_steps to compare
	for (;not_EOL(exp.buffer[i]); i++){
		if (exp.buffer[i] == '#'){ //Skip any lines starting with #
			for (;not_EOL(exp.buffer[i]); i++){}
			i++;
			line_start = i; 
			exp.index = i; 
		}
	}
	//scan the number of time steps and put into steps
	if (sscanf(exp.buffer + line_start, "%d", steps) < 1){
		usage(usage_message);
	}
	exp.index = i + 1;
}

/* Parse the third line in experimental data file, which contains the name and order of species we have data for. 
 * The indices of species that we have experimental data for will be stored in ed.con_index (arrays of indices)
 * Called by read_experimental_data (init.cpp)
 */
void parse_experiment_data_title(input_data& exp, exp_data& ed){
	static const char* usage_message = "There was an error reading the TITLE LINE of the given experimental data set file.";
	int i = exp.index;
	int start_read = i;
	char* title_line = new char [1000]; // the title line in experimental data file
	char * title_name; // the name of the species we process
	int j = 0; // index of the concentrations we will put into ed.con_index 
	for (; not_EOL(exp.buffer[i]); i ++){
		if (exp.buffer[i] == '#'){ //Skip any lines starting with #
			for (;not_EOL(exp.buffer[i]); i++){}
			i++;
			start_read = i; 
			exp.index = i; 
		}
	}
	
	exp.index = i + 1; // the beginning of next line
	
	if (i > start_read){
		if (sscanf(exp.buffer + start_read, "%s", title_line) < 1){
			usage(usage_message);
		}
		title_name = strtok(title_line, ",");
		// The first term in the title line should be TIME.
		if (strcmp(title_name, "TIME") != 0){
			cout << term->red << "The first term in your experiment_data file should be TIME"<< term->reset<< endl;
			exit(EXIT_INPUT_ERROR);
		} 
		// calling strtok to get each of the species' name separated from each other by ','
		while(title_name != NULL){
			title_name = strtok(NULL, ", \n" );
			if (title_name != NULL){
				get_experiment_data_title(title_name, ed, j);//to get the index of the species from the title name.
				j ++;
			}
		}
	}
	if (j != ed.num_cons){
		cout << term->red << "The number of concentrations found in title line of your experimental data input(" << term->reset << j << term->red << "), which does not match with your provided experimental data num of concentrations("<< term->reset << ed.num_cons << term->red << ")" << term->reset << endl;
		exit(EXIT_INPUT_ERROR); 
	}
	// Delete strings stored on heap
	delete [] title_line;
	delete title_name;
}

/* Helper function for parse_experiment_data (io.cpp)
 * Params: content_name: the string (array of char s) that is the name of the species
 * 		   ed: the exp_data structure to store the index into ed.con_index
 * 		   j: the index of where to store the index of the species in ed.con_index
 * Notes: Right now we only support some species, see the code and README for details
 * 		  if need be adding new experimental data species, have to add into this function
 */
void get_experiment_data_title(char* content_name, exp_data& ed, int j){
	if (strcmp(content_name, "MNPO") == 0){
		ed.con_index[j] = MNPO;
	}
	else if (strcmp(content_name, "MCPO") == 0){
		ed.con_index[j] = MCPO;
	}
	else if (strcmp(content_name, "MNPT") == 0){
		ed.con_index[j] = MNPT;
	}
	else if (strcmp(content_name, "MCPT") == 0){
		ed.con_index[j] = MCPT;
	}
	else if (strcmp(content_name, "MNRO") == 0){
		ed.con_index[j] = MNRO;
	}
	else if (strcmp(content_name, "MCRO") == 0){
		ed.con_index[j] = MCRO;
	}
	else if (strcmp(content_name, "MNRT") == 0){
		ed.con_index[j] = MNRT;
	}
	else if (strcmp(content_name, "MCRT") == 0){
		ed.con_index[j] = MCRT;
	}
	else if (strcmp(content_name, "MNB") == 0){
		ed.con_index[j] = MNB;
	}
	else if (strcmp(content_name, "MCB") == 0){
		ed.con_index[j] = MCB;
	}
	else if (strcmp(content_name, "MNNP") == 0){
		ed.con_index[j] = MNNP;
	}
	else if (strcmp(content_name, "MCNP") == 0){
		ed.con_index[j] = MCNP;
	}
	else if (strcmp(content_name, "MNREV") == 0){
		ed.con_index[j] = MNREV;
	}
	else if (strcmp(content_name, "MCREV") == 0){
		ed.con_index[j] = MCREV;
	}
	else if (strcmp(content_name, "X10000") == 0){
		ed.con_index[j] = X10000;
	}
	else if (strcmp(content_name, "X30000") == 0){
		ed.con_index[j] = X30000;
	}
	else if (strcmp(content_name, "X01000") == 0){
		ed.con_index[j] = X01000;
	}
	else if (strcmp(content_name, "X01010") == 0){
		ed.con_index[j] = X01010;
	}
	else if (strcmp(content_name, "X02000") == 0){
		ed.con_index[j] = X02000;
	}
	else if (strcmp(content_name, "X02010") == 0){
		ed.con_index[j] = X02010;
	}
	else {
		cout << term->red << "Did not recognize concentration name: " << term->reset << content_name << ". Bye!"<< endl ;
		exit(EXIT_INPUT_ERROR);
	}
}

/* Read each line containing experimental data, put into ed.data (2D array containing concentrations of different species at different times), and ed.sim_time_steps
 * Called in read_experimental_data (init.cpp) for each line of data.
 * params: 
 * 		ip
 * 		exp: input_data storing the content of experimental data file, declared in main (main.cpp), filled in read_file
 * 		ed: structure to store experimental data, declared in main (main.cpp), filled in read_experimental_data (init.cpp)
 * 		line_index: the index of the time step (The first line with read experimental data has line_index 0, but in the file, it should be line number 4, since the first three lines specify size and titles)
 * 		
 */
void parse_experiment_data_line(input_params& ip, input_data& exp, exp_data& ed, int line_index){
	static const char* usage_message = "There was an error reading a LINE of given experiment data set file.";
	int start_read = exp.index;
	int i = exp.index; 
	int c_index = 0; // the index of things found in a line of exp_data file (Ex: 30,45.5,0.123 then c_index would be 0,1,2. Where c_index 0 always indicates the time, c_index 1 would lead to species index 0 in ed.con_index and ed.data)
	double time;
	for (; not_EOL(exp.buffer[i]); i ++){
		if (exp.buffer[i] == '#'){
			for (;not_EOL(exp.buffer[i]); i ++) {}// skip any lines starting with #
			//onto the next line
			i ++;
			start_read = i; 
			exp.index = i;
		}
		else if (exp.buffer[i] == ','){
			if (c_index == 0){
				//Scan real time (the first number in the line)
				if (sscanf(exp.buffer + start_read, "%lf", &time) < 1){
					usage(usage_message);
				}
				// Calculate the corresponding time step index in our simulation to store into ed.sim_time_steps 
				process_experiment_time(ip, ed, time, line_index);
			}
			else if (c_index < (ed.num_cons + 1)){ // ed.num_cons + 1 because c_index also includes time as the first number in the line
				if (sscanf(exp.buffer + start_read, "%lf", &ed.data[c_index - 1][line_index]) < 1){
					usage(usage_message);
				}
			}
			else{
				cout << term->red << "The number of concentrations in experiment_data file (line " << term->reset << line_index + 4 << term->red << ") is more than the number of concentrations specified in the first two lines of the file" << term->reset<< endl;
				exit (EXIT_INPUT_ERROR);
			}
			c_index ++; 
			start_read = i + 1; 
			exp.index = i + 1;
		}
	}
	// save this to read the next line next time this function is called
	exp.index = i + 1; 
	
	if (i > start_read){
		// This line only specifies the time
		if (c_index == 0){
			cout << term->red << "Line " << term->reset << line_index + 4 << term->red << " in experiment data file only specifies the time." << term->reset<< endl;
			exit(EXIT_INPUT_ERROR);
		}
		// Parse the last concentration in the line (after the last ',')
		else if (c_index < ed.num_cons + 1){
			if (sscanf(exp.buffer + start_read, "%lf", &ed.data[c_index - 1][line_index]) < 1){
				usage(usage_message);
			}	
		}
		// Found more than the specified number of concentrations levels specified at the beginning of the file
		else {
			cout << term->red << "The number of concentrations in experiment_data file (line " << term->reset << line_index + 4 << term->red << ") is more than the number of concentrations specified in the first two lines of the file" << term->reset<< endl;
			exit (EXIT_INPUT_ERROR);
		}
		// c_index not incremented here, since it is the last thing in the line, does not matter if we increment it or not. 
	}
	if (c_index != (ed.num_cons)){
		cout << term->red << "The number of concentrations in experiment_data file (line " << term->reset << line_index + 4 << term->red << ") is " << term->reset << c_index << term->red <<". This is different from the number of concentrations specified in the first two lines of the file" << term->reset<< endl;
		exit (EXIT_INPUT_ERROR);
	}
	
}

/*
 * Calculate the simulate time_step based on real time of experimental data, and store into ed.sim_time_steps
 * Params:
 * 		ip
 * 		ed: experimental data struct, declared in main (main.cpp), filled in read_experimental_data(init.cpp)
 * 		time: the time read from file, processed from parse_experiment_data_line
 * 		line_index: index of the time step to store into ed.sim_time_steps
 * Called in parse_experiment_data_line(io.cpp) 
 */
void process_experiment_time (input_params& ip, exp_data& ed, double time, int line_index){
	if (time < 0){
		cout << term->red << "The time specified in line : " << term->reset << line_index + 4 << term->red << " is smaller than 0 : " << term->reset << time << endl;
		exit (EXIT_INPUT_ERROR);
	}
	int max_steps = ip.time_total / (ip.step_size * ip.big_gran);
	int sim_time_step = (int) (time / (ip.step_size * ip.big_gran)); // Compare exp data with data from big_cl, so time step should be corresponding to what it is in big_cl, rounding down.
	if (sim_time_step >= max_steps){
		cout << term->red << "The time specified in line: " << term->reset << line_index + 4 << term->red << " is larger than the maximum time of simulation: " << term->reset << time << endl;
		exit(EXIT_INPUT_ERROR);
	}
	ed.sim_time_steps[line_index] = sim_time_step;
}

/* parse_ranges_file reads the given buffer and stores every range found in the given ranges array
	parameters:
		ranges: the array of pairs in which to store the lower and upper bounds of each range
		buffer: the buffer with the ranges to read
	returns: nothing
	notes:
		The buffer should contain one range per line, starting the name of the parameter followed by the bracked enclosed lower and then upper bound optionally followed by comments.
		e.g. 'msh1 [30, 65] comment'
		The name of the parameter is so humans can conveniently read the file and has no semantic value to this parser.
		Blank lines and lines starting with # will be ignored. Anything after the upper bound is ignored.
	todo:
*/
void parse_ranges_file (pair <double, double> ranges[], char* buffer) {
	int i = 0;
	int rate = 0;
	for (; buffer[i] != '\0'; i++) {
		// Ignore lines starting with #
		while (buffer[i] == '#') {
			while (buffer[i] != '\n' && buffer[i] != '\0') {i++;}
			i++;			
		}
		
		// Ignore whitespace before the opening bracket
		while (buffer[i] != '[' && buffer[i] != '\0') {i++;}
		if (buffer[i] == '\0') {break;}
		i++;
		
		// Read the bounds
		ranges[rate].first = atof(buffer + i);
		while (buffer[i] != ',') {i++;}
		i++;
		ranges[rate].second = atof(buffer + i);
		if (ranges[rate].first < 0 || ranges[rate].second < 0) { // If the ranges are invalid then set them to 0
			ranges[rate].first = 0;
			ranges[rate].second = 0;
		}
		rate++;
		// Skip any comments until the end of the line
		while (buffer[i] != '\n' && buffer[i] != '\0') {i++;}
	}
}

/* open_file opens the file with the given name and stores it in the given output file stream
	parameters:
		file_pointer: a pointer to the output file stream to open the file with
		file_name: the path and name of the file to open
		append: if true, the file will appended to, otherwise any existing data will be overwritten
	returns: nothing
	notes:
	todo:
*/
void open_file (ofstream* file_pointer, char* file_name, bool append) {
	try {
		if (append) {
			cout << term->blue << "Opening " << term->reset << file_name << " . . . ";
			file_pointer->open(file_name, fstream::app);
		} else {
			cout << term->blue << "Creating " << term->reset << file_name << " . . . ";
			file_pointer->open(file_name, fstream::out);
		}
	} catch (ofstream::failure) {
		cout << term->red << "Couldn't write to " << file_name << "!" << term->reset << endl;
		exit(EXIT_FILE_WRITE_ERROR);
	}
	term->done();
}

/* close_if_open closes the given output file stream if it is open
	parameters:
		file: a pointer to the output file stream to close
	returns: nothing
	notes:
	todo:
*/
void close_if_open (ofstream* file) {
	if (file->is_open()) {
		file->close();
	}
}

/* print_concentrations prints the concentration values of every cell at every time step of the given mutant for the given run
	parameters:
		ip: the program's input parameters
		sd: the current simulation's data
		cl: the current simulation's concentration levels
		md: mutant data
		filename_cons: the path and name of the file in which to store the concentration levels
		set_num: the index of the parameter set whose concentration levels are being printed
	returns: nothing
	notes:
		The first number in the line is real time (in hours), then MNPO, MCPO, MNPT, MCPT, MNPH, MCPH, MNB, MCB
		we only print out concentrations that we tests for conditions
	called in simulate_param_set (sim.cpp)
*/
void print_concentrations (input_params& ip, sim_data& sd, con_levels& big_cl, int set_num, int mutant_index) {
	double ** data = big_cl.data;
	if (ip.print_cons) { // Print the concentrations only if the user specified it
		
		// create the filename to print, based on the set index, mutant, cell type
		char* filename_set = create_concentrations_file_name(ip, set_num, mutant_index); 
		
		cout << "    "; // Offset the open_file message to preserve horizontal spacing
		ofstream file_cons;
		open_file(&file_cons, filename_set, true);
	
		free(filename_set);
		
		int print_steps = sd.steps_total / sd.big_gran;
		double time_interval = sd.step_size * sd.big_gran;
		double time = 0;
		double con;
		if (ip.binary_cons_output) {
			for (int j = 0; j < print_steps; j++) {
				time = j * time_interval;
				file_cons.write((char*)(&time), sizeof(double));
				con = data[MNPO][j];
				file_cons.write((char*)(&con), sizeof(double));
				con = data[MCPO][j];
				file_cons.write((char*)(&con), sizeof(double));
				con = data[MNPT][j];
				file_cons.write((char*)(&con), sizeof(double));
				con = data[MCPT][j];
				file_cons.write((char*)(&con), sizeof(double));
				con = data[MNPH][j];
				file_cons.write((char*)(&con), sizeof(double));
				con = data[MCPH][j];
				file_cons.write((char*)(&con), sizeof(double));
				con = data[MNB][j];
				file_cons.write((char*)(&con), sizeof(double));
				con = data[MCB][j];
				file_cons.write((char*)(&con), sizeof(double));
				file_cons << "\n";
			}
			
		} else {
			for (int j = 0; j < print_steps; j++) {
				time = j * time_interval;
				file_cons << time << " ";
				file_cons << data[MNPO][j] << " ";
				file_cons << data[MCPO][j] << " ";
				file_cons << data[MNPT][j] << " ";
				file_cons << data[MCPT][j] << " ";
				file_cons << data[MNPH][j] << " ";
				file_cons << data[MCPH][j] << " ";
				file_cons << data[MNB][j] << " ";
				file_cons << data[MCB][j] << " ";
				file_cons << "\n";
			}
		}
	}
}

/* Return the relative file name to store the concentrations files to open the file in print_concentrations
 * The file name should b ./set_setIndex_scnORfib/mutantFileName
 * called in print_concentrations.
 */
char * create_concentrations_file_name(input_params& ip, int set_num, int mutant_index){
	//store set index as string to copy into file name later
	int strlen_set_num = INT_STRLEN(set_num); // How many bytes the ASCII representation of set_num takes
	char* str_set_num = (char*)mallocate(sizeof(char) * (strlen_set_num + 1));
	sprintf(str_set_num, "%d", set_num);
	
	//declare filename_set
	char* filename_set = NULL;
	// SCN
	if (ip.cell_type == SCN){
		if (mutant_index == WT){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_SCN) + strlen(WT_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_SCN, WT_FNAME);
		}
		else if (mutant_index == P1){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_SCN) + strlen(P1_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_SCN, P1_FNAME);
		}
	
		else if (mutant_index == P2){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_SCN) + strlen(P2_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_SCN, P2_FNAME);
		}
	
		else if (mutant_index == P3){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_SCN) + strlen(P3_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_SCN, P3_FNAME);
		}
		else if (mutant_index == C1){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_SCN) + strlen(C1_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_SCN, C1_FNAME);
		}
		else if (mutant_index == C2){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_SCN) + strlen(C2_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_SCN, C2_FNAME);
		}
		else if (mutant_index == BM){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_SCN) + strlen(BM_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_SCN, BM_FNAME);
		}
		else if (mutant_index == NP){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_SCN) + strlen(NP_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_SCN, NP_FNAME);
		}
		else if (mutant_index == C1C2){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_SCN) + strlen(C1C2_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_SCN, C1C2_FNAME);
		}
	}
	//FIB
	else if (ip.cell_type == FIB){
		if (mutant_index == WT){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_FIB) + strlen(WT_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_FIB, WT_FNAME);
		}
		else if (mutant_index == P1){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_FIB) + strlen(P1_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_FIB, P1_FNAME);
		}
	
		else if (mutant_index == P2){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_FIB) + strlen(P2_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_FIB, P2_FNAME);
		}
	
		else if (mutant_index == P3){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_FIB) + strlen(P3_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_FIB, P3_FNAME);
		}
		else if (mutant_index == C1){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_FIB) + strlen(C1_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_FIB, C1_FNAME);
		}
		else if (mutant_index == C2){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_FIB) + strlen(C2_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_FIB, C2_FNAME);
		}
		else if (mutant_index == BM){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_FIB) + strlen(BM_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_FIB, BM_FNAME);
		}
		else if (mutant_index == NP){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_FIB) + strlen(NP_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_FIB, NP_FNAME);
		}
		else if (mutant_index == C1C2){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_FIB) + strlen(C1C2_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_FIB, C1C2_FNAME);
		}
		else if (mutant_index == P2C1){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_FIB) + strlen(P2C1_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_FIB, P2C1_FNAME);
		}
		else if (mutant_index == P2C2){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_FIB) + strlen(P2C2_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_FIB, P2C2_FNAME);
		}
		else if (mutant_index == R){
			filename_set = (char*)mallocate(sizeof(char) * ( strlen("./set_") + strlen_set_num + strlen("_") + strlen(DIR_NAME_FIB) + strlen(R_FNAME) + 1));
			sprintf(filename_set, "./set_%s_%s/%s", str_set_num, DIR_NAME_FIB, R_FNAME);
		}
	}

	// Free what we located, filename-set will be freed in print_concentrations(io.cpp) after it is used
	free(str_set_num);
	return filename_set;
}

/* not_EOL returns whether or not a given character is the end of a line or file (i.e. '\n' or '\0', respectively)
	parameters:
		c: the character to check
	returns: true if c is the end of a line or file, false otherwise
	notes:
		When reading input file strings, use this instead of a straight newline check to avoid EOF (end of file) issues.
	todo:
*/
bool not_EOL (char c) {
	return (c != '\n' && c != '\0' && c != EOF);
}


/* write_pipe writes run scores to a pipe created by a program interacting with this one
	parameters:
		score: the array of scores to send
		ip: the program's input parameters
		sd: the current simulation's data
	returns: nothing
	notes:
		This function assumes that fd points to a valid pipe and will exit with an error if it does not.
		we pipe 3 types of scores: (1) absolute score used by SRES with WEIGHT_CONDITIONS % * condition score + WEIGHT_COST % * cost (deviation from experimental data)
		(2) condition score (MAX_COND_SCORE - condition score) (3) cost. sres reads these three score, and print these three scores when we find a good set below our acceptable theshold
	todo:
*/
void write_pipe (double * score,  double * cond_score, double * exp_score, input_params& ip, sim_data& sd) {
	if (write(ip.pipe_out, score, sizeof(double)) == -1) {
		term->failed_pipe_write();
		exit(EXIT_PIPE_WRITE_ERROR);
	}
	
	if (write(ip.pipe_out, cond_score, sizeof(double)) == -1){
		term->failed_pipe_write();
		exit(EXIT_PIPE_WRITE_ERROR);
	}
	
	if (write(ip.pipe_out, exp_score, sizeof(double)) == -1){
		term->failed_pipe_write();
		exit(EXIT_PIPE_WRITE_ERROR);
	}
	
	term->done();
	// Close the pipe
	if (close(ip.pipe_out) == -1) {
		term->failed_pipe_write();
		exit(EXIT_PIPE_WRITE_ERROR);
	}
}

/* write_pipe_int writes the given integer to the given pipe
	parameters:
		fd: the file descriptor identifying the pipe
		value: the integer to write to the pipe
	returns: nothing
	notes:
		This function assumes that fd points to a valid pipe and will exit with an error if it does not.
	todo:
*/
void write_pipe_double (int fd, double value) {
	if (write(fd, &value, sizeof(double)) == -1) {
		term->failed_pipe_write();
		exit(EXIT_PIPE_WRITE_ERROR);
	}
}

/*
 * Create directory set_setIndex_scnORfib inside simulation. this directory contains concentrations files. 
 * Called in simulate_all_params(sim.cpp)
 * params:
 * 		set_index: index of the current param set (found in simulate_all_params)
 * 		ip
 */
void create_set_directory (int set_index, input_params& ip){
	char * dir_name = new char[20];
	if (ip.cell_type == SCN){
		cout << term->blue << "Creating set_" << set_index << "_scn" << " directory if necessary . . . " << endl;
		sprintf(dir_name, "set_%d_%s", set_index, DIR_NAME_SCN);
		if (mkdir(dir_name, 0775) != 0 && errno != EEXIST){
			cout << term->red << "Couldn't create '" << dir_name << "' directory!" << term->reset << endl;
			delete [] dir_name;
			exit(EXIT_FILE_WRITE_ERROR);
		}
	}
	else if (ip.cell_type == FIB){
		cout << term->blue << "Creating set_" << set_index << "_fib" << " directory if necessary . . . " << endl;
		sprintf(dir_name, "set_%d_%s", set_index, DIR_NAME_FIB);
		if (mkdir(dir_name, 0775) != 0 && errno != EEXIST){
			cout << term->red << "Couldn't create '" << dir_name << "' directory!" << term->reset << endl;
			delete [] dir_name;
			exit(EXIT_FILE_WRITE_ERROR);
		}
	}
	delete [] dir_name;
}

/* create_passed_file creates a file to store parameter sets that passed
	parameters:
		ip: the program's input parameters
	returns: a pointer to the file output stream
	notes:
	todo:
*/
void create_passed_file (input_params& ip) {
	if (ip.print_passed) { // Print the passed sets only if the user specified it
		open_file(ip.passed_stream, ip.passed_file, false);
	}
}

/* print the parameter sets into ip.passed_stream, which is created in create_passed_file (called in main.cpp if users specify)
 * called in simulate_all_params(sim.cpp)
 * notes: the checking whethere to print a parameter set or not is done in simulate_all_params, not in this function.
 * this function only prints parameters into ip.passed_stream
 */
void print_good_set(input_params& ip, parameters& pr, int set_num){
	if (ip.print_passed){
		cout << term->blue << "Printing set "<< term->reset << set_num << term->blue << " into passed file"<< term->reset << endl;
		for (int i = 0; i < (NUM_RATES - 1); i ++){
			*ip.passed_stream << pr.data[set_num][i] <<  ","; 
		}
		*ip.passed_stream << pr.data[set_num][NUM_RATES - 1] << endl;
		term->done();
	}
}
