#ifndef IO_HPP
#define IO_HPP

#include "structs.hpp"
void store_filename (char**,const char*);
void read_pipe (parameters& , input_params&);
void read_pipe_int (int, int* );
void read_pipe_set (int, double[]);
void read_file (input_data* ifd);
bool parse_param_line (parameters&, int, char*, int& );
void parse_experiment_data_size(input_params&, input_data&, int*, int*); 
void parse_experiment_data_title(input_data&, exp_data&);
void parse_experiment_data_line(input_params&, input_data&, exp_data&, int);
void process_experiment_time (input_params&, exp_data&, double, int);
void get_experiment_data_title(char*, exp_data&, int);
void parse_ranges_file (pair <double, double> [], char* );
void open_file (ofstream*, char* , bool);
void close_if_open (ofstream*);
void print_concentrations (input_params&, sim_data&, con_levels& , int, int);
char * create_concentrations_file_name(input_params&, int, int);
bool not_EOL (char);
void write_pipe (double*, double*, double*, input_params&, sim_data&);
void write_pipe_double (int, double);
void create_set_directory (int, input_params&);
void create_passed_file (input_params&);
void print_good_set(input_params&, parameters&, int);
#endif
