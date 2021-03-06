#include "calculation.hpp"
#include "debug.hpp"
#include "macros.hpp"

/* 
 * Calculate concentrations calls all the find* functions to calculate concentrations
 * Limit changes to this file as much as we can, since it is really easy to mess up the system.
 * This function is called in simulate_param_set in sim.cpp
 * Params:
 * 		ip
 * 		cl: the cl that contains concentrations of species for ip.big_gran time steps, used for direct calculation
 * 		big_cl: the con_levels structures that store concentrations over simulation time. If ip.step_size is 0.001 and ip.time_total is 100,
 * 				-->sd.steps_total = 10000. If big_gran is 10, then cl has size 10 time-steps, and big_cl has size 10000/ 10 = 1000 time steps,
 * 				Meaning we only record concentrations every 0.1 hours instead of 0.001, eventhough we still use 0.001 as step size for the sake of 
 * 				accurate calculations.
 * 		rs: structs to store the parameter sets passed in by users/ parameter estimation program
 * 		sd: simulation data
 */
bool calculate_concentrations(input_params& ip, con_levels& cl, con_levels& big_cl, rates& rs, sim_data& sd){
	double * sim_rates = rs.rates_base;
	bool valid = true; // valid turns to false if we find a concentration that is either negative, or NaN
	int check_index;
	for (int j = 1 ; j< sd.steps_total; j++){
		check_index = j % cl.big_gran; // Necessary to check for nan later
		
		findGRB(sim_rates, cl, j, sd.step_size);
		findG(sim_rates, cl, j, sd.step_size);
		findGRSRB(sim_rates, cl, j, sd.step_size);
		findGRS(sim_rates, cl, j, sd.step_size);
		findGCR (sim_rates, cl, j, sd.step_size);
		findGC(sim_rates, cl, j, sd.step_size);
		findGBR(sim_rates, cl, j, sd.step_size);
		findGB(sim_rates, cl, j, sd.step_size);
		findGBRB(sim_rates, cl, j, sd.step_size);
		findGBB(sim_rates, cl, j, sd.step_size);
		findMNPO(sim_rates, cl, j, ip.time_total, sd.step_size);
		findMCPO(sim_rates, cl, j, sd.step_size);
		findMNPT(sim_rates, cl, j, sd.step_size);
		findMCPT(sim_rates, cl, j, ip.time_total, sd.step_size);
		findMNRT(sim_rates, cl, j, sd.step_size);
		findMCRT(sim_rates, cl, j, sd.step_size);
		findMNREV(sim_rates, cl, j, sd.step_size);
		findMCREV(sim_rates, cl, j, sd.step_size);
		findMNRO(sim_rates, cl, j, sd.step_size);
		findMCRO(sim_rates, cl, j, sd.step_size);
		findMNB(sim_rates, cl, j, sd.step_size);
		findMCB(sim_rates, cl, j, sd.step_size);
		findMNNP(sim_rates, cl, j, sd.step_size);
		findMCNP(sim_rates, cl, j, sd.step_size);
		findB(sim_rates, cl, j, sd.step_size);
		findCL(sim_rates, cl, j, sd.step_size);
		findBC(sim_rates, cl, j, sd.step_size);
		findCYREV(sim_rates, cl, j, sd.step_size);
		findREVN(sim_rates, cl, j, sd.step_size);
		findCYREVG(sim_rates, cl, j, sd.step_size);
		findREVNG(sim_rates, cl, j, sd.step_size);
		findCYREVGP(sim_rates, cl, j, sd.step_size);
		findREVNGP(sim_rates, cl, j, sd.step_size);
		findCYREVP(sim_rates, cl, j, sd.step_size);
		findREVNP(sim_rates, cl, j, sd.step_size);
		findGTO (sim_rates, cl, j, sd.step_size);
		findX00001(sim_rates, cl, j, sd.step_size);
		findX00011(sim_rates, cl, j, sd.step_size);
		findX00100(sim_rates, cl, j, sd.step_size);
		findX00110(sim_rates, cl, j, sd.step_size);	
		findX00200(sim_rates, cl, j, sd.step_size);	
		findX00210(sim_rates, cl, j, sd.step_size);	
		findX01000(sim_rates, cl, j, sd.step_size);
		findX01010(sim_rates, cl, j, sd.step_size);	
		findX01011(sim_rates, cl, j,sd.step_size);
		findX02000(sim_rates, cl, j, sd.step_size);
		findX02010(sim_rates, cl, j, sd.step_size);
		findX02011(sim_rates, cl, j, sd.step_size);
		findX10000(sim_rates, cl, j, sd.step_size);
		findX10100(sim_rates, cl, j, sd.step_size);
		findX20000(sim_rates, cl, j, sd.step_size);
		findX20010(sim_rates, cl, j, sd.step_size);
		findX20011(sim_rates, cl, j, sd.step_size);
		findX20100(sim_rates, cl, j, sd.step_size);
		findX20110(sim_rates, cl, j, sd.step_size);
		findX20111(sim_rates, cl, j, sd.step_size);
		findX21000(sim_rates, cl, j, sd.step_size);
		findX21010(sim_rates, cl, j, sd.step_size);
		findX21011(sim_rates, cl, j, sd.step_size);
		findX21100(sim_rates, cl, j, sd.step_size);
		findX21110(sim_rates, cl, j, sd.step_size);
		findX21111(sim_rates, cl, j, sd.step_size);
		findX22000(sim_rates, cl, j, sd.step_size);
		findX22010(sim_rates, cl, j, sd.step_size);
		findX22011(sim_rates, cl, j, sd.step_size);
		findX22100(sim_rates, cl, j, sd.step_size);
		findX22110(sim_rates, cl, j, sd.step_size);
		findX22111(sim_rates, cl, j, sd.step_size);
		findX30000(sim_rates, cl, j, sd.step_size);
		findX30100(sim_rates, cl, j, sd.step_size);
		findX30200(sim_rates, cl, j, sd.step_size);
		findX30300(sim_rates, cl, j, sd.step_size);
		findX40000(sim_rates, cl, j, sd.step_size);
		findX40010(sim_rates, cl, j, sd.step_size);
		findX40011(sim_rates, cl, j, sd.step_size);
		findX40100(sim_rates, cl, j, sd.step_size);
		findX40110(sim_rates, cl, j, sd.step_size);
		findX40111(sim_rates, cl, j, sd.step_size);
		findX40200(sim_rates, cl, j, sd.step_size);
		findX40210(sim_rates, cl, j, sd.step_size);
		findX40211(sim_rates, cl, j, sd.step_size);
		findX40300(sim_rates, cl, j, sd.step_size);
		findX40310(sim_rates, cl, j, sd.step_size);
		findX40311(sim_rates, cl, j, sd.step_size);
		findX41000(sim_rates, cl, j, sd.step_size);
		findX41010(sim_rates, cl, j, sd.step_size);
		findX41011(sim_rates, cl, j, sd.step_size);
		findX41100(sim_rates, cl, j, sd.step_size);
		findX41110(sim_rates, cl, j, sd.step_size);
		findX41111(sim_rates, cl, j, sd.step_size);
		findX41200(sim_rates, cl, j, sd.step_size);
		findX41210(sim_rates, cl, j, sd.step_size);
		findX41211(sim_rates, cl, j, sd.step_size);
		findX41300(sim_rates, cl, j, sd.step_size);
		findX41310(sim_rates, cl, j, sd.step_size);
		findX41311(sim_rates, cl, j, sd.step_size);
		findX42000(sim_rates, cl, j, sd.step_size);
		findX42010(sim_rates, cl, j, sd.step_size);
		findX42011(sim_rates, cl, j, sd.step_size);
		findX42100(sim_rates, cl, j, sd.step_size);
		findX42110(sim_rates, cl, j, sd.step_size);
		findX42111(sim_rates, cl, j, sd.step_size);
		findX42200(sim_rates, cl, j, sd.step_size);
		findX42210(sim_rates, cl, j, sd.step_size);
		findX42211(sim_rates, cl, j, sd.step_size);
		findX42300(sim_rates, cl, j, sd.step_size);
		findX42310(sim_rates, cl, j, sd.step_size);
		findX42311(sim_rates, cl, j, sd.step_size);
		findX50000(sim_rates, cl, j, sd.step_size);
		findX50010(sim_rates, cl, j, sd.step_size);
		findX50011(sim_rates, cl, j, sd.step_size);
		findX50100(sim_rates, cl, j, sd.step_size);
		findX50110(sim_rates, cl, j, sd.step_size);
		findX50111(sim_rates, cl, j, sd.step_size);
		findX50200(sim_rates, cl, j, sd.step_size);
		findX50210(sim_rates, cl, j, sd.step_size);
		findX50211(sim_rates, cl, j, sd.step_size);
		findX50300(sim_rates, cl, j, sd.step_size);
		findX50310(sim_rates, cl, j, sd.step_size);
		findX50311(sim_rates, cl, j, sd.step_size);
		findX51000(sim_rates, cl, j, sd.step_size);
		findX51010(sim_rates, cl, j, sd.step_size);
		findX51011(sim_rates, cl, j, sd.step_size);
		findX51100(sim_rates, cl, j, sd.step_size);
		findX51110(sim_rates, cl, j, sd.step_size);
		findX51111(sim_rates, cl, j, sd.step_size);
		findX51200(sim_rates, cl, j, sd.step_size);
		findX51210(sim_rates, cl, j, sd.step_size);
		findX51211(sim_rates, cl, j, sd.step_size);
		findX51300(sim_rates, cl, j, sd.step_size);
		findX51310(sim_rates, cl, j, sd.step_size);
		findX51311(sim_rates, cl, j, sd.step_size);
		findX52000(sim_rates, cl, j, sd.step_size);
		findX52010(sim_rates, cl, j, sd.step_size);
		findX52011(sim_rates, cl, j, sd.step_size);
		findX52100(sim_rates, cl, j, sd.step_size);
		findX52110(sim_rates, cl, j, sd.step_size);
		findX52111(sim_rates, cl, j, sd.step_size);
		findX52200(sim_rates, cl, j, sd.step_size);
		findX52210(sim_rates, cl, j, sd.step_size);
		findX52211(sim_rates, cl, j, sd.step_size);
		findX52300(sim_rates, cl, j, sd.step_size);
		findX52310(sim_rates, cl, j, sd.step_size);
		findX52311(sim_rates, cl, j, sd.step_size);
		findX60000(sim_rates, cl, j, sd.step_size);
		findX60010(sim_rates, cl, j, sd.step_size);
		findX60011(sim_rates, cl, j, sd.step_size);
		findX60100(sim_rates, cl, j, sd.step_size);
		findX60110(sim_rates, cl, j, sd.step_size);
		findX60111(sim_rates, cl, j, sd.step_size);
		findX60200(sim_rates, cl, j, sd.step_size);
		findX60210(sim_rates, cl, j, sd.step_size);
		findX60211(sim_rates, cl, j, sd.step_size);
		findX60300(sim_rates, cl, j, sd.step_size);
		findX60310(sim_rates, cl, j, sd.step_size);
		findX60311(sim_rates, cl, j, sd.step_size);
		findX61000(sim_rates, cl, j, sd.step_size);
		findX61010(sim_rates, cl, j, sd.step_size);
		findX61011(sim_rates, cl, j, sd.step_size);
		findX61100(sim_rates, cl, j, sd.step_size);
		findX61110(sim_rates, cl, j, sd.step_size);
		findX61111(sim_rates, cl, j, sd.step_size);
		findX61200(sim_rates, cl, j, sd.step_size);
		findX61210(sim_rates, cl, j, sd.step_size);
		findX61211(sim_rates, cl, j, sd.step_size);
		findX61300(sim_rates, cl, j, sd.step_size);
		findX61310(sim_rates, cl, j, sd.step_size);
		findX61311(sim_rates, cl, j, sd.step_size);
		findX62000(sim_rates, cl, j, sd.step_size);
		findX62010(sim_rates, cl, j, sd.step_size);
		findX62011(sim_rates, cl, j, sd.step_size);
		findX62100(sim_rates, cl, j, sd.step_size);
		findX62110(sim_rates, cl, j, sd.step_size);
		findX62111(sim_rates, cl, j, sd.step_size);
		findX62200(sim_rates, cl, j, sd.step_size);
		findX62210(sim_rates, cl, j, sd.step_size);
		findX62211(sim_rates, cl, j, sd.step_size);
		findX62300(sim_rates, cl, j, sd.step_size);
		findX62310(sim_rates, cl, j, sd.step_size);
		findX62311(sim_rates, cl, j, sd.step_size);
		findMNPH(sim_rates, cl, j, sd.step_size);
		findMCPH(sim_rates, cl, j, sd.step_size);
		findGPH(sim_rates, cl, j, sd.step_size);
		findGPHR(sim_rates, cl, j, sd.step_size);
		findX70000(sim_rates, cl, j, sd.step_size);
		findX80000(sim_rates, cl, j, sd.step_size);
		findX80100(sim_rates, cl, j, sd.step_size);
		findX90000(sim_rates, cl, j, sd.step_size);
		findX90010(sim_rates, cl, j, sd.step_size);
		findX90011(sim_rates, cl, j, sd.step_size);
		findX90100(sim_rates, cl, j, sd.step_size);
		findX90110(sim_rates, cl, j, sd.step_size);
		findX90111(sim_rates, cl, j, sd.step_size);
		findXA0000(sim_rates, cl, j, sd.step_size);
		findXA0010(sim_rates, cl, j, sd.step_size);
		findXA0011(sim_rates, cl, j, sd.step_size);
		findXA1010(sim_rates, cl, j, sd.step_size);
		findXA1011(sim_rates, cl, j, sd.step_size);
		findXA2010(sim_rates, cl, j, sd.step_size);
		findXA2011(sim_rates, cl, j, sd.step_size);
		findGPOR(sim_rates, cl, j, sd.step_size);
		findGPO(sim_rates, cl, j, sd.step_size);
		findGPTR(sim_rates, cl, j, sd.step_size);
		findGPT(sim_rates, cl, j, sd.step_size);
		findGBN(sim_rates, cl, j, sd.step_size);
		findGBRN(sim_rates, cl, j, sd.step_size);
		findX01002(sim_rates, cl, j, sd.step_size);
		findX02002(sim_rates, cl, j, sd.step_size);
			
		for (int i = 0; i< NUM_CONS; i++ ){
			//// Check for nan value/////
			if (isnan(cl.data[i][check_index])){
				valid = false;
				break;
			}	 
		}
		if (!valid){
			break;
		}
		else if (valid && ((check_index) == 0)){
			transfer_data(cl, big_cl, j);
		}
	}
	
	return valid;
}

void transfer_data(con_levels& cl, con_levels& big_cl, int t){
	int big_t = t / cl.big_gran;
	int small_t = t % cl.big_gran; // Should always be 0
	for (int i = 0; i < cl.num_con_levels; i ++){
		big_cl.data[i][big_t] = cl.data[i][small_t];
	}
}

void findGRB (double* rs, con_levels& cl, int c, double ss){
	int p = (c - 1) % cl.big_gran; 
	c = c % cl.big_gran;
	double prev_GRB = cl.data[GRB][p];
	double prev_G = cl.data[G][p];
	double prev_x01011 = cl.data[X01011][p];
	double prev_x02011 = cl.data[X02011][p];
	cl.data[GRB][c] = ss * (-(rs[UNBIN] * prev_GRB) 
							+ rs[BIN] * (1 - prev_G - prev_GRB) * (prev_x01011 + prev_x02011))
							+ prev_GRB;
}

void findG (double * rs, con_levels& cl, int c, double ss){
	int p = (c - 1)% cl.big_gran;
	c = c % cl.big_gran;
	double prev_G = cl.data[G][p];
	double prev_GRB = cl.data [GRB][p];
	cl.data[G][c]= ss * (- rs[UNBIN] * prev_G
							+ rs[BIN] * (1 - prev_G - prev_GRB) * cl.data[X00011][p])
							+ prev_G;
}

void findGRSRB (double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_grsrb = cl.data[GRSRB][p];
	cl.data[GRSRB][c] = ss * (-(rs[UNBINR] * p_grsrb)
					+ rs[BINR]* (1 - cl.data[GRS][p] - p_grsrb) * (cl.data[X01011][p] + cl.data[X02011][p]))
					+ p_grsrb;
}

void findGRS(double * rs, con_levels& cl , int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_grs = cl.data[GRS][p];
	cl.data[GRS][c] = ss * (-(rs[UNBINR] * p_grs)
					+ rs[BINR] * (1 - p_grs- cl.data[GRSRB][p])* cl.data[X00011][p])
					+ p_grs;
}

void findGCR (double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_gcr = cl.data[GCR][p];
	cl.data[GCR][c] = ss * (-(rs[UNBINC] * p_gcr)
					+ rs[BINC] * (1 - cl.data[GC][p] - p_gcr) * (cl.data[X01011][p] + cl.data[X02011][p]))
					+ p_gcr;
}

void findGC(double* rs, con_levels& cl, int c, double ss){
	int p= (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_gc = cl.data[GC][p];
	cl.data[GC][c] = ss * (- (rs[UNBINC] * p_gc)
					+ rs[BINC] * (1 - p_gc - cl.data[GCR][p]) * cl.data[X00011][p])
					+ p_gc;
}

void findGBR(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_gbr = cl.data[GBR][p];
	cl.data[GBR][c] = ss * (- (rs[UNBINREV] * p_gbr)
					+ rs[BINREV]* cl.data[GB][p]*(cl.data[REVN][p] + cl.data[REVNG][p] + cl.data[REVNGP][p] + cl.data[REVNP][p]))
					+ p_gbr;
}

void findGB(double* rs, con_levels& cl , int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_gb= cl.data[GB][p];
	cl.data[GB][c] = ss * (rs[UNBINREV] * cl.data[GBR][p]
					- rs[BINREV] * p_gb * (cl.data[REVN][p] + cl.data[REVNG][p] + cl.data[REVNGP][p] + cl.data[REVNP][p]))
					+ p_gb;
}

void findGBRB(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_gbrb = cl.data[GBRB][p];
	cl.data[GBRB][c] = ss * (- (rs[UNBINREVB] * p_gbrb)
					+ rs[BINREVB] * cl.data[GBB][p] * (cl.data[REVN][p] + cl.data[REVNG][p] + cl.data[REVNGP][p] + cl.data[REVNP][p]))
					+ p_gbrb;
}

void findGBB(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_gbb = cl.data[GBB][p];
	cl.data[GBB][c] = ss * (rs[UNBINREVB] * cl.data[GBRB][p] 
					- rs[BINREVB] * p_gbb * (cl.data[REVN][p] + cl.data[REVNG][p] + cl.data[REVNGP][p] + cl.data[REVNP][p]))
					+ p_gbb;
}

void findMNPO(double* rs, con_levels& cl, int c, int time, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mnpo = cl.data[MNPO][p];
	cl.data[MNPO][c] = ss * (rs[TRPO] * cl.data[GPO][p]
					- rs[TMC] * p_mnpo
					- rs[UMPO] * p_mnpo)
					+ p_mnpo;
}

void findMCPO(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mcpo= cl.data[MCPO][p];
	cl.data[MCPO][c] = ss * (- (rs[UMPO] * p_mcpo)
					+ rs[TMC] * cl.data[MNPO][p])
					+ p_mcpo;
}

void findMNPT(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mnpt = cl.data[MNPT][p];
	cl.data[MNPT][c] = ss * (rs[TRPT] * cl.data[GPT][p]
					- rs[TMC] * p_mnpt
					- rs[UMPT] * p_mnpt)
					+ p_mnpt;
}

void findMCPT(double* rs, con_levels& cl, int c, int time, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mcpt = cl.data[MCPT][p];
	cl.data[MCPT][c] = ss * (- (rs[UMPT] * p_mcpt)
					+ rs[TMC] * cl.data[MNPT][p])
					+ p_mcpt;
}

void findMNRT(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mnrt = cl.data[MNRT][p];
	cl.data[MNRT][c] = ss * (rs[TRRT] * cl.data[GC][p] 
					- rs[TMC] * p_mnrt 
					- rs[UMRT] * p_mnrt)
					+ p_mnrt;
}

void findMCRT(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mcrt = cl.data[MCRT][p];
	cl.data[MCRT][c] = ss * (- (rs[UMRT] * p_mcrt)
					+ rs[TMC] * cl.data[MNRT][p])
					+ p_mcrt;
}

void findMNREV(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mnrev = cl.data[MNREV][p];
	cl.data[MNREV][c] = ss * (- rs[TMCREV] * p_mnrev
						- rs[UMREV] * p_mnrev
						+ rs[TRREV] * cl.data[GRS][p] * cl.data[X00011][p])
						+ p_mnrev;
}

void findMCREV(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mcrev = cl.data[MCREV][p];
	cl.data[MCREV][c] = ss * (- rs[UMREV] * p_mcrev
						+ rs[TMCREV] * cl.data[MNREV][p])
						+ p_mcrev;
}

void findMNRO(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mnro = cl.data[MNRO][p];
	cl.data[MNRO][c] = ss * (rs[TRRO] * cl.data[G][p] * cl.data[GB][p]
					- rs[TMC] * p_mnro
					- rs[UMRO] * p_mnro)
					+ p_mnro;
}

void findMCRO(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mcro = cl.data[MCRO][p];
	cl.data[MCRO][c] = ss * (- (rs[UMRO] * p_mcro)
						+ rs[TMC] * cl.data[MNRO][p])
						+ p_mcro;
}

void findMNB(double *rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mnb = cl.data[MNB][p];
	cl.data[MNB][c] = ss * (rs[TRB] * cl.data[GBB][p]
					- rs[TMC] * p_mnb
					- rs[UMB] * p_mnb) 
					+ p_mnb;
}

void findMCB(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mcb = cl.data[MCB][p];
	cl.data[MCB][c] = ss * (- (rs[UMB] * p_mcb)
					+ rs[TMC] * cl.data[MNB][p])
					+ p_mcb;
}

void findMNNP(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mnnp = cl.data[MNNP][p];
	cl.data[MNNP][c] = ss * (rs[TRNP] * cl.data[GBN][p]
					- rs[TMC] * p_mnnp
					- rs[UMNP] * p_mnnp)
					+ p_mnnp;
}

void findMCNP(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double p_mcnp = cl.data[MCNP][p];
	cl.data[MCNP][c] = ss * (- (rs[UMNP] * p_mcnp)
					+ rs[TMC] * cl.data[MNNP][p])
					+ p_mcnp;
}

void findB(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double pb = cl.data[B][p];
	cl.data[B][c] = ss * (- (rs[UB] * pb) 
					+ rs[UNCBIN] * cl.data[BC][p] 
					- rs[CBIN] * pb * cl.data[CL][p]
					+ rs[TLB] * cl.data[MCB][p])
					+ pb;
}

void findCL (double* rs, con_levels& cl, int c,double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double pcl = cl.data[CL][p];
	cl.data[CL][c] = ss * (rs[TLC] 
					+ rs[UNCBIN] * cl.data[BC][p]
					- rs[UC] *	pcl
					- rs[CBIN] * cl.data[B][p] * pcl
					+ rs[TLNP] * cl.data[MCNP][p])
					+ pcl;
}

void findBC(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double pbc = cl.data[BC][p];
	cl.data[BC][c] = ss * (- (rs[PHOS] * pbc)
					- (rs[UBC] * pbc)
					- (rs[UNCBIN] * pbc)
					+ rs[CBIN] * cl.data[B][p] * cl.data[CL][p]
					- rs[BINCRYB] * pbc * (cl.data[X01000][p] + cl.data[X02000][p])
					+ rs[UNBINCRYB] * (cl.data[X01002][p] + cl.data[X02002][p]))
					+ pbc;
}

void findCYREV(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double pcyrev = cl.data[CYREV][p];
	cl.data[CYREV][c] = ss * (- ((rs[NLREV] + rs[UREV]) * pcyrev)
						+ rs[DG] * cl.data[CYREVG][p] 
						+ rs[TLREV] * cl.data[MCREV][p]
						+ rs[NEREV] * cl.data[REVN][p] 
						- rs[AG] * pcyrev * cl.data[X00200][p])
						+ pcyrev;
}

void findREVN(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double prevn = cl.data[REVN][p];
	cl.data[REVN][c] = ss * (rs[NLREV] * cl.data[CYREV][p]
					- (rs[NEREV] + rs[UREV]) * prevn 
					+ rs[DG] * cl.data[REVNG][p] 
					- rs[AG] * rs[NF] * prevn * cl.data[X00210][p])
					+ prevn;
}

void findCYREVG(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double pcyrevg = cl.data[CYREVG][p];
	cl.data[CYREVG][c] = ss * (- (pcyrevg * (rs[DG] + rs[NLREV] + rs[UREV] + cl.data[GTO][p]))
						+ rs[NEREV] * cl.data[REVNG][p] 
						+ rs[AG] * cl.data[CYREV][p] * cl.data[X00200][p])
						+ pcyrevg;
}

void findREVNG(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double prevng = cl.data[REVNG][p];
	cl.data[REVNG][c] = ss * (rs[NLREV] * cl.data[CYREVG][p]
						- (rs[DG] + rs[NEREV] + rs[UREV] + cl.data[GTO][p]) * prevng 
						+ rs[AG] * rs[NF] * cl.data[REVN][p] * cl.data[X00210][p])
						+ prevng;
}

void findCYREVGP(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double pcyrevgp = cl.data[CYREVGP][p];
	cl.data[CYREVGP][c] = ss * (- ((rs[DG] + rs[NLREV] + rs[UPREV]) * pcyrevgp)
						+ cl.data[CYREVG][p] * cl.data[GTO][p] 
						+ rs[NEREV] * cl.data[REVNGP][p])
						+ pcyrevgp;
}

void findREVNGP(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double prevngp = cl.data[REVNGP][p];
	cl.data[REVNGP][c] = ss * (rs[NLREV] * cl.data[CYREVGP][p] 
						+ cl.data[GTO][p] * cl.data[REVNG][p]
						- (rs[DG] + rs[NEREV] + rs[UPREV]) * prevngp)
						+ prevngp;
}

void findCYREVP(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double pcyrevp = cl.data[CYREVP][p];
	cl.data[CYREVP][c] = ss * (rs[DG] * cl.data[CYREVGP][p] 
						- (rs[NLREV] + rs[UPREV]) * pcyrevp
						+ rs[NEREV] * cl.data[REVNP][p])
						+ pcyrevp;
}

void findREVNP(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double prevnp = cl.data[REVNP][p];
	cl.data[REVNP][c] = ss * (rs[NLREV] * cl.data[CYREVP][p]
						+ rs[DG] * cl.data[REVNGP][p]
						- (rs[NEREV] + rs[UPREV]) * prevnp)
						+ prevnp;
}

void findGTO(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double pgto = cl.data[GTO][p];
	cl.data[GTO][c] = ss * (rs[TRGTO] * cl.data[G][p] * cl.data[GB][p]
					- rs[UGTO] * pgto)
					+ pgto;
					
}

void findX00001(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X00001][p];
	cl.data[X00001][c] = ss * (rs[PHOS] * cl.data[BC][p]
						- rs[NLBC] * px 
						- rs[UBC] * px)
						+ px;
}

void findX00011(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X00011][p];
	cl.data[X00011][c] = ss * (rs[NLBC] * cl.data[X00001][p]
						- rs[UBC] * px
						+ rs[URO] * cl.data[X01011][p]
						- rs[CBBIN] * rs[NF] * px * (cl.data[X01010][p] + cl.data[X02010][p])
						+ rs[URT] * cl.data[X02011][p] 
						+ rs[UNCBBIN] * (cl.data[X01011][p] + cl.data[X02011][p])
						+ rs[UPTG] * (cl.data[X50011][p] + cl.data[X50111][p] + cl.data[X50211][p] + cl.data[X50311][p])
						+ rs[UPO] * (cl.data[X20011][p] + cl.data[X20111][p])
						+ rs[UPTC] * (cl.data[X40011][p] + cl.data[X40111][p] + cl.data[X40211][p] + cl.data[X40311][p])
						+ rs[UPTCG] * (cl.data[X60011][p] + cl.data[X60111][p] + cl.data[X60211][p] + cl.data[X60311][p])
						+ rs[UPOH] * (cl.data[X90011][p] + cl.data[X90111][p]) //A
						+ rs[UPH] * cl.data[XA0011][p] //A
						- rs[BBIN] * rs[NF] * px * (cl.data[X20010][p] + cl.data[X20110][p] + cl.data[X21010][p] + cl.data[X21110][p] + cl.data[X22010][p] + cl.data[X22110][p]
									+ cl.data[X40010][p] + cl.data[X40110][p] + cl.data[X40210][p] + cl.data[X40310][p]
									+ cl.data[X41010][p] + cl.data[X41110][p] + cl.data[X41210][p] + cl.data[X41310][p]
									+ cl.data[X42010][p] + cl.data[X42110][p] + cl.data[X42210][p] + cl.data[X42310][p]
									+ cl.data[X50010][p] + cl.data[X50110][p] + cl.data[X50210][p] + cl.data[X50310][p]
									+ cl.data[X51010][p] + cl.data[X51110][p] + cl.data[X51210][p] + cl.data[X51310][p]
									+ cl.data[X52010][p] + cl.data[X52110][p] + cl.data[X52210][p] + cl.data[X52310][p]
									+ cl.data[X60010][p] + cl.data[X60110][p] + cl.data[X60210][p] + cl.data[X60310][p]
									+ cl.data[X61010][p] + cl.data[X61110][p] + cl.data[X61210][p] + cl.data[X61310][p]
									+ cl.data[X62010][p] + cl.data[X62110][p] + cl.data[X62210][p] + cl.data[X62310][p]
									+ cl.data[X90010][p] + cl.data[X90110][p] //A
									+ cl.data[XA0010][p] //A
									+ cl.data[XA1010][p] //A 
									+ cl.data[XA2010][p]) //A
						+ rs[UNBBIN] * (cl.data[X20011][p]+ cl.data[X20111][p]
									+ cl.data[X21011][p] + cl.data[X21111][p]
									+ cl.data[X22011][p] + cl.data[X22111][p]
									+ cl.data[X40011][p] + cl.data[X40111][p] + cl.data[X40211][p] + cl.data[X40311][p]
									+ cl.data[X41011][p] + cl.data[X41111][p] + cl.data[X41211][p] + cl.data[X41311][p]
									+ cl.data[X42011][p] + cl.data[X42111][p] + cl.data[X42211][p] + cl.data[X42311][p]
									+ cl.data[X50011][p] + cl.data[X50111][p] + cl.data[X50211][p] + cl.data[X50311][p]
									+ cl.data[X51011][p] + cl.data[X51111][p] + cl.data[X51211][p] + cl.data[X51311][p]
									+ cl.data[X52011][p] + cl.data[X52111][p] + cl.data[X52211][p] + cl.data[X52311][p]
									+ cl.data[X60011][p] + cl.data[X60111][p] + cl.data[X60211][p] + cl.data[X60311][p]
									+ cl.data[X61011][p] + cl.data[X61111][p] + cl.data[X61211][p] + cl.data[X61311][p]
									+ cl.data[X62011][p] + cl.data[X62111][p] + cl.data[X62211][p] + cl.data[X62311][p]
									+ cl.data[X90011][p] + cl.data[X90111][p] //A
									+ cl.data[XA0011][p] //A
									+ cl.data[XA1011][p] //A
									+ cl.data[XA2011][p])) //A
						+ px;
}

void findX00100 (double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X00100][p];
	cl.data[X00100][c] = ss * (rs[LNE] * cl.data[X00110][p]
						+ rs[UPUO] * cl.data[X10100][p] 
						+ rs[UPUT] * (cl.data[X30100][p] + cl.data[X30300][p])
						+ rs[UPTG] * (cl.data[X50100][p] + cl.data[X50300][p])
						+ rs[UPUOH] * cl.data[X80100][p] //A
						+ rs[UPO] * cl.data[X20100][p] 
						+ rs[UPTC] * (cl.data[X40100][p] + cl.data[X40300][p])
						+ rs[UPTCG] * (cl.data[X60100][p] + cl.data[X60300][p])
						+ rs[UPOH] * cl.data[X90100][p] //A
						- rs[AC] * px * (cl.data[X10000][p] + cl.data[X30000][p]
										+ cl.data[X20000][p] + cl.data[X21000][p] + cl.data[X22000][p] 
										+ cl.data[X40000][p] + cl.data[X41000][p] + cl.data[X42000][p]
										+ cl.data[X50000][p] + cl.data[X51000][p] + cl.data[X52000][p]
										+ cl.data[X60000][p] + cl.data[X61000][p] + cl.data[X62000][p]
										+ cl.data[X80000][p] + cl.data[X90000][p])//A
						+ rs[DC] * (cl.data[X10100][p] + cl.data[X30100][p]
									+ cl.data[X20100][p] + cl.data[X21100][p] + cl.data[X22100][p]
									+ cl.data[X40100][p] + cl.data[X41100][p] + cl.data[X42100][p]
									+ cl.data[X50100][p] + cl.data[X51100][p] + cl.data[X52100][p]
									+ cl.data[X60100][p] + cl.data[X61100][p] + cl.data[X62100][p]
									+ cl.data[X80100][p] //A
									+ cl.data[X90100][p])//A
						- rs[AC] * px * (cl.data[X30200][p]
										+ cl.data[X40200][p] + cl.data[X41200][p] + cl.data[X42200][p]
										+ cl.data[X50200][p] + cl.data[X51200][p] + cl.data[X52200][p]
										+ cl.data[X60200][p] + cl.data[X61200][p] + cl.data[X62200][p])
						+ rs[DC] * (cl.data[X30300][p]
									+ cl.data[X40300][p] + cl.data[X41300][p] + cl.data[X42300][p]
									+ cl.data[X50300][p] + cl.data[X51300][p] + cl.data[X52300][p]
									+ cl.data[X60300][p] + cl.data[X61300][p] + cl.data[X62300][p]))
						+ px;
}

void findX00110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X00110][p];
	cl.data[X00110][c] = ss * (- rs[LNE] * px
						+ rs[UPTG] * (cl.data[X50110][p] + cl.data[X50111][p] 
									+ cl.data[X50310][p] + cl.data[X50311][p])
						+ rs[UPO] * (cl.data[X20110][p] + cl.data[X20111][p])
						+ rs[UPTC] * (cl.data[X40110][p] + cl.data[X40111][p] + cl.data[X40310][p] + cl.data[X40311][p])
						+ rs[UPTCG] * (cl.data[X60110][p] + cl.data[X60111][p] + cl.data[X60310][p] + cl.data[X60311][p])
						+ rs[UPOH] * (cl.data[X90110][p] + cl.data[X90111][p]) //A
						- rs[AC] * rs[NF] * px * (cl.data[X20010][p] + cl.data[X21010][p] + cl.data[X22010][p]
												+ cl.data[X40010][p] + cl.data[X41010][p] + cl.data[X42010][p]
												+ cl.data[X50010][p] + cl.data[X51010][p] + cl.data[X52010][p]
												+ cl.data[X60010][p] + cl.data[X61010][p] + cl.data[X62010][p]
												+ cl.data[X90010][p]) //A
						- rs[AC] * rs[NF] * px * (cl.data[X20011][p] + cl.data[X21011][p] + cl.data[X22011][p]
												+ cl.data[X40011][p] + cl.data[X41011][p] + cl.data[X42011][p]
												+ cl.data[X50011][p] + cl.data[X51011][p] + cl.data[X52011][p]
												+ cl.data[X60011][p] + cl.data[X61011][p] + cl.data[X62011][p]
												+ cl.data[X90011][p]) //A
						+ rs[DC] * (cl.data[X20110][p] + cl.data[X21110][p] + cl.data[X22110][p]
									+ cl.data[X40110][p] + cl.data[X41110][p] + cl.data[X42110][p]
									+ cl.data[X50110][p] + cl.data[X51110][p] + cl.data[X52110][p]
									+ cl.data[X60110][p] + cl.data[X61110][p] + cl.data[X62110][p]
									+ cl.data[X90110][p])//A
									
						+ rs[DC] * (cl.data[X20111][p] + cl.data[X21111][p] + cl.data[X22111][p]
									+ cl.data[X40111][p] + cl.data[X41111][p] + cl.data[X42111][p]
									+ cl.data[X50111][p] + cl.data[X51111][p] + cl.data[X52111][p]
									+ cl.data[X60111][p] + cl.data[X61111][p] + cl.data[X62111][p]
									+ cl.data[X90111][p])//A
									
						- rs[AC] * rs[NF] * px * (cl.data[X40210][p] + cl.data[X41210][p] + cl.data[X42210][p]
												+ cl.data[X50210][p] + cl.data[X51210][p] + cl.data[X52210][p]
												+ cl.data[X60210][p] + cl.data[X61210][p] + cl.data[X62210][p])
												
						- rs[AC] * rs[NF] * px * (cl.data[X40211][p] + cl.data[X41211][p] + cl.data[X42211][p]
												+ cl.data[X50211][p] + cl.data[X51211][p] + cl.data[X52211][p]
												+ cl.data[X60211][p] + cl.data[X61211][p] + cl.data[X62211][p])
						
						+ rs[DC] * (cl.data[X40310][p] + cl.data[X41310][p] + cl.data[X42310][p]
									+ cl.data[X50310][p] + cl.data[X51310][p] + cl.data[X52310][p]
									+ cl.data[X60310][p] + cl.data[X61310][p] + cl.data[X62310][p])
						
						+ rs[DC] * (cl.data[X40311][p] + cl.data[X41311][p] + cl.data[X42311][p]
									+ cl.data[X50311][p] + cl.data[X51311][p] + cl.data[X52311][p]
									+ cl.data[X60311][p] + cl.data[X61311][p] + cl.data[X62311][p]))
						
						+ px;
}

void findX00200(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X00200][p];
	cl.data[X00200][c] = ss * (rs[DG] * cl.data[CYREVG][p]
						+ rs[UREV] * cl.data[CYREVG][p]
						+ rs[DG] * cl.data[CYREVGP][p]
						+ rs[UPREV] * cl.data[CYREVGP][p]
						- rs[AG] * cl.data[CYREV][p] * px 
						+ rs[LNE] * cl.data[X00210][p] 
						+ rs[UPUT] * (cl.data[X30200][p] + cl.data[X30300][p])
						+ rs[UPTG] * (cl.data[X50200][p] + cl.data[X50300][p])
						+ rs[UPTC] * (cl.data[X40200][p] + cl.data[X40300][p]) 
						+ rs[UPTCG] * (cl.data[X60200][p] + cl.data[X60300][p])
						- rs[AGP] * px * (cl.data[X30000][p] + cl.data[X30100][p]
						
										+ cl.data[X40000][p] + cl.data[X40100][p] 
										+ cl.data[X41000][p] + cl.data[X41100][p]
										+ cl.data[X42000][p] + cl.data[X42100][p]
										
										+ cl.data[X50000][p] + cl.data[X50100][p] 
										+ cl.data[X51000][p] + cl.data[X51100][p]
										+ cl.data[X52000][p] + cl.data[X52100][p]
										
										+ cl.data[X60000][p] + cl.data[X60100][p] 
										+ cl.data[X61000][p] + cl.data[X61100][p]
										+ cl.data[X62000][p] + cl.data[X62100][p])
						
						+ rs[DG] * (cl.data[X30200][p] + cl.data[X30300][p]
						
									+ cl.data[X40200][p] + cl.data[X40300][p] 
									+ cl.data[X41200][p] + cl.data[X41300][p]
									+ cl.data[X42200][p] + cl.data[X42300][p]
										
									+ cl.data[X50200][p] + cl.data[X50300][p] 
									+ cl.data[X51200][p] + cl.data[X51300][p]
									+ cl.data[X52200][p] + cl.data[X52300][p]
										
									+ cl.data[X60200][p] + cl.data[X60300][p] 
									+ cl.data[X61200][p] + cl.data[X61300][p]
									+ cl.data[X62200][p] + cl.data[X62300][p]))
						
						+ px;
}

void findX00210(double* rs, con_levels& cl, int c, double ss) {
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X00210][p];
	cl.data[X00210][c] = ss * (rs[DG] * cl.data[REVNG][p]
						+ rs[UREV] * cl.data[REVNG][p]
						+ rs[DG] * cl.data[REVNGP][p] 
						+ rs[UPREV] * cl.data[REVNGP][p]
						- rs[LNE] * cl.data[X00210][p]
						- rs[AG] * rs[NF] * cl.data[REVN][p] * px
						+ rs[UPTG] * (cl.data[X50210][p] + cl.data[X50211][p] + cl.data[X50310][p] + cl.data[X50311][p])
						+ rs[UPTC] * (cl.data[X40210][p] + cl.data[X40211][p] + cl.data[X40310][p] + cl.data[X40311][p])
						+ rs[UPTCG] * (cl.data[X60210][p] + cl.data[X60211][p] + cl.data[X60310][p] + cl.data[X60311][p]) 
						- rs[AGP] * rs[NF] * px * (cl.data[X40010][p] + cl.data[X40011][p] + cl.data[X40110][p] + cl.data[X40111][p]
												+ cl.data[X41010][p] + cl.data[X41011][p] + cl.data[X41110][p] + cl.data[X41111][p]
												+ cl.data[X42010][p] + cl.data[X42011][p] + cl.data[X42110][p] + cl.data[X42111][p]
												
												+ cl.data[X50010][p] + cl.data[X50011][p] + cl.data[X50110][p] + cl.data[X50111][p]
												+ cl.data[X51010][p] + cl.data[X51011][p] + cl.data[X51110][p] + cl.data[X51111][p]
												+ cl.data[X52010][p] + cl.data[X52011][p] + cl.data[X52110][p] + cl.data[X52111][p]
												
												+ cl.data[X60010][p] + cl.data[X60011][p] + cl.data[X60110][p] + cl.data[X60111][p]
												+ cl.data[X61010][p] + cl.data[X61011][p] + cl.data[X61110][p] + cl.data[X61111][p]
												+ cl.data[X62010][p] + cl.data[X62011][p] + cl.data[X62110][p] + cl.data[X62111][p])
												
						+ rs[DG] * (cl.data[X40210][p] + cl.data[X40211][p] + cl.data[X40310][p] + cl.data[X40311][p]
									+ cl.data[X41210][p] + cl.data[X41211][p] + cl.data[X41310][p] + cl.data[X41311][p]
									+ cl.data[X42210][p] + cl.data[X42211][p] + cl.data[X42310][p] + cl.data[X42311][p]
									
									+ cl.data[X50210][p] + cl.data[X50211][p] + cl.data[X50310][p] + cl.data[X50311][p]
									+ cl.data[X51210][p] + cl.data[X51211][p] + cl.data[X51310][p] + cl.data[X51311][p]
									+ cl.data[X52210][p] + cl.data[X52211][p] + cl.data[X52310][p] + cl.data[X52311][p]
									
									+ cl.data[X60210][p] + cl.data[X60211][p] + cl.data[X60310][p] + cl.data[X60311][p]
									+ cl.data[X61210][p] + cl.data[X61211][p] + cl.data[X61310][p] + cl.data[X61311][p]
									+ cl.data[X62210][p] + cl.data[X62211][p] + cl.data[X62310][p] + cl.data[X62311][p]))
						+ px;
}

void findX01000(double* rs, con_levels& cl, int c, double ss) {
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X01000][p];
	cl.data[X01000][c] = ss * (rs[TLRO] * cl.data[MCRO][p] 
					- rs[URO] * px
					- rs[AR] * px * (cl.data[X20000][p] + cl.data[X20100][p]
									+ cl.data[X40000][p] + cl.data[X40100][p] + cl.data[X40200][p] + cl.data[X40300][p]
									+ cl.data[X50000][p] + cl.data[X50100][p] + cl.data[X50200][p] + cl.data[X50300][p]
									+ cl.data[X60000][p] + cl.data[X60100][p] + cl.data[X60200][p] + cl.data[X60300][p]) //A
									
					+ rs[DR] * (cl.data[X21000][p] + cl.data[X21100][p]
								+ cl.data[X41000][p] + cl.data[X41100][p] + cl.data[X41200][p] + cl.data[X41300][p]
								+ cl.data[X51000][p] + cl.data[X51100][p] + cl.data[X51200][p] + cl.data[X51300][p]
								+ cl.data[X61000][p] + cl.data[X61100][p] + cl.data[X61200][p] + cl.data[X61300][p])//A
					
					- rs[BINCRYB] * cl.data[BC][p] * px
					+ rs[UNBINCRYB] * cl.data[X01002][p])
					+ px;
}

void findX01010(double* rs, con_levels& cl, int c, double ss) {
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X01010][p];
	cl.data[X01010][c] = ss * (- rs[URO] * px
						- rs[CBBIN] * rs[NF] * cl.data[X00011][p] * px
						+ rs[UNCBBIN] * cl.data[X01011][p]
						- rs[AR] * rs[NF] * px * (cl.data[X20010][p] + cl.data[X20110][p]
											+ cl.data[X40010][p] + cl.data[X40110][p] + cl.data[X40210][p] + cl.data[X40310][p]
											+ cl.data[X50010][p] + cl.data[X50110][p] + cl.data[X50210][p] + cl.data[X50310][p]
											+ cl.data[X60010][p] + cl.data[X60110][p] + cl.data[X60210][p] + cl.data[X60310][p]
											+ cl.data[XA0010][p]) //A
						- rs[AR] * rs[NF] * px * (cl.data[X20011][p] + cl.data[X20111][p]
											+ cl.data[X40011][p] + cl.data[X40111][p] + cl.data[X40211][p] + cl.data[X40311][p]
											+ cl.data[X50011][p] + cl.data[X50111][p] + cl.data[X50211][p] + cl.data[X50311][p]
											+ cl.data[X60011][p] + cl.data[X60111][p] + cl.data[X60211][p] + cl.data[X60311][p]
											+ cl.data[XA0011][p]) //A
						
						+ rs[DR] * (cl.data[X21010][p] + cl.data[X21110][p]
									+ cl.data[X41010][p] + cl.data[X41110][p] + cl.data[X41210][p] + cl.data[X41310][p]
									+ cl.data[X51010][p] + cl.data[X51110][p] + cl.data[X51210][p] + cl.data[X51310][p]
									+ cl.data[X61010][p] + cl.data[X61110][p] + cl.data[X61210][p] + cl.data[X61310][p]
									+ cl.data[XA1010][p]) //A
									
						+ rs[DR] * (cl.data[X21011][p] + cl.data[X21111][p]
									+ cl.data[X41011][p] + cl.data[X41111][p] + cl.data[X41211][p] + cl.data[X41311][p]
									+ cl.data[X51011][p] + cl.data[X51111][p] + cl.data[X51211][p] + cl.data[X51311][p]
									+ cl.data[X61011][p] + cl.data[X61111][p] + cl.data[X61211][p] + cl.data[X61311][p]
									+ cl.data[XA1011][p])) //A
						+ px;
}

void findX01011(double* rs, con_levels& cl, int c, double ss) {
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X01011][p];
	cl.data[X01011][c] = ss * (rs[CBBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X01010][p]
						- rs[UNCBBIN] * px
						- rs[URO] * px
						- rs[AR] * rs[NF] * px * (cl.data[X20010][p] + cl.data[X20110][p]
											+ cl.data[X40010][p] + cl.data[X40110][p] + cl.data[X40210][p] + cl.data[X40310][p]
											+ cl.data[X50010][p] + cl.data[X50110][p] + cl.data[X50210][p] + cl.data[X50310][p]
											+ cl.data[X60010][p] + cl.data[X60110][p] + cl.data[X60210][p] + cl.data[X60310][p]
											+ cl.data[XA0010][p])//A
						
						+ rs[DR] * (cl.data[X21011][p] + cl.data[X21111][p]
									+ cl.data[X41011][p] + cl.data[X41111][p] + cl.data[X41211][p] + cl.data[X41311][p]
									+ cl.data[X51011][p] + cl.data[X51111][p] + cl.data[X51211][p] + cl.data[X51311][p]
									+ cl.data[X61011][p] + cl.data[X61111][p] + cl.data[X61211][p] + cl.data[X61311][p]
									+ cl.data[XA1011][p]))//A
						
						+ px;
}

void findX02000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X02000][p];
	cl.data[X02000][c] = ss * (rs[TLRT] * cl.data[MCRT][p]
						- rs[URT] * px
						- rs[AR] * px * (cl.data[X20000][p] + cl.data[X20100][p]
									+ cl.data[X40000][p] + cl.data[X40100][p] + cl.data[X40200][p] + cl.data[X40300][p]
									+ cl.data[X50000][p] + cl.data[X50100][p] + cl.data[X50200][p] + cl.data[X50300][p]
									+ cl.data[X60000][p] + cl.data[X60100][p] + cl.data[X60200][p] + cl.data[X60300][p])//A
						+ rs[DR] * (cl.data[X22000][p] + cl.data[X22100][p]
									+ cl.data[X42000][p] + cl.data[X42100][p] + cl.data[X42200][p] + cl.data[X42300][p]
									+ cl.data[X52000][p] + cl.data[X52100][p] + cl.data[X52200][p] + cl.data[X52300][p]
									+ cl.data[X62000][p] + cl.data[X62100][p] + cl.data[X62200][p] + cl.data[X62300][p])//A
						- rs[BINCRYB] * cl.data[BC][p] * px
						+ rs[UNBINCRYB] * cl.data[X02002][p])
						+ px;
}

void findX02010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X02010][p];
	cl.data[X02010][c] = ss * (- rs[URT] * px
						- rs[CBBIN] * rs[NF] * cl.data[X00011][p] * px
						+ rs[UNCBBIN] * cl.data[X02011][p] 
						- rs[AR] * rs[NF] * px * (cl.data[X20010][p] + cl.data[X20110][p]
											+ cl.data[X40010][p] + cl.data[X40110][p] + cl.data[X40210][p] + cl.data[X40310][p]
											+ cl.data[X50010][p] + cl.data[X50110][p] + cl.data[X50210][p] + cl.data[X50310][p]
											+ cl.data[X60010][p] + cl.data[X60110][p] + cl.data[X60210][p] + cl.data[X60310][p]
											+ cl.data[XA0010][p])//A
						
						- rs[AR] * rs[NF] * px * (cl.data[X20011][p] + cl.data[X20111][p]
											+ cl.data[X40011][p] + cl.data[X40111][p] + cl.data[X40211][p] + cl.data[X40311][p]
											+ cl.data[X50011][p] + cl.data[X50111][p] + cl.data[X50211][p] + cl.data[X50311][p]
											+ cl.data[X60011][p] + cl.data[X60111][p] + cl.data[X60211][p] + cl.data[X60311][p]
											+ cl.data[XA0011][p])//A
											
						+ rs[DR] * (cl.data[X22010][p] + cl.data[X22110][p]
									+ cl.data[X42010][p] + cl.data[X42110][p] + cl.data[X42210][p] + cl.data[X42310][p]
									+ cl.data[X52010][p] + cl.data[X52110][p] + cl.data[X52210][p] + cl.data[X52310][p]
									+ cl.data[X62010][p] + cl.data[X62110][p] + cl.data[X62210][p] + cl.data[X62310][p]
									+ cl.data[XA2010][p]) //A
									
						+ rs[DR] * (cl.data[X22011][p] + cl.data[X22111][p]
									+ cl.data[X42011][p] + cl.data[X42111][p] + cl.data[X42211][p] + cl.data[X42311][p]
									+ cl.data[X52011][p] + cl.data[X52111][p] + cl.data[X52211][p] + cl.data[X52311][p]
									+ cl.data[X62011][p] + cl.data[X62111][p] + cl.data[X62211][p] + cl.data[X62311][p]
									+ cl.data[XA2011][p]))//A
						+ px;
}

void findX02011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X02011][p];
	cl.data[X02011][c] = ss * (rs[CBBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X02010][p]
						- rs[UNCBBIN] * px
						- rs[URT] * px
						- rs[AR] * rs[NF] * px *  (cl.data[X20010][p] + cl.data[X20110][p]
											+ cl.data[X40010][p] + cl.data[X40110][p] + cl.data[X40210][p] + cl.data[X40310][p]
											+ cl.data[X50010][p] + cl.data[X50110][p] + cl.data[X50210][p] + cl.data[X50310][p]
											+ cl.data[X60010][p] + cl.data[X60110][p] + cl.data[X60210][p] + cl.data[X60310][p]
											+ cl.data[XA0010][p])//A
											
						+ rs[DR] * (cl.data[X22011][p] + cl.data[X22111][p]
									+ cl.data[X42011][p] + cl.data[X42111][p] + cl.data[X42211][p] + cl.data[X42311][p]
									+ cl.data[X52011][p] + cl.data[X52111][p] + cl.data[X52211][p] + cl.data[X52311][p]
									+ cl.data[X62011][p] + cl.data[X62111][p] + cl.data[X62211][p] + cl.data[X62311][p]
									+ cl.data[XA2011][p]))//A
						+ px;
}

void findX10000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X10000][p];
	cl.data[X10000][c] = ss * (rs[TLPO] * cl.data[MCPO][p]
						- rs[UPUO] * px
						- rs[AC] * cl.data[X00100][p] * px
						+ rs[DC] * cl.data[X10100][p]
						- rs[AN] * cl.data[X70000][p] * px
						+ rs[DN] * cl.data[X80000][p])
						+ px;
}

void findX10100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X10100][p];
	cl.data[X10100][c] = ss * (rs[AC] * cl.data[X00100][p] * cl.data[X10000][p]
						- rs[DC] * px
						- rs[HOO] * px
						- rs[UPUO] * px)
						+ px;
}

void findX20000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X20000][p];
	cl.data[X20000][c] = ss * (- rs[NL] * px 
						- rs[UPO] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X20010][p] 
						+ rs[DC] * cl.data[X20100][p]
						+ rs[DR] * (cl.data[X21000][p] + cl.data[X22000][p])
						- rs[AN] * cl.data[X20000][p] * cl.data[XA0000][p]
						+ rs[DN] * cl.data[X90000][p])
						+ px ;
}

void findX20010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X20010][p];
	cl.data[X20010][c] = ss * (rs[NL] * cl.data[X20000][p] 
						- rs[NE] * px
						- rs[UPO] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X20011][p]
						+ rs[UNBBIN] * cl.data[X20011][p]
						+ rs[DC] * cl.data[X20110][p]
						+ rs[DR] * (cl.data[X21010][p] + cl.data[X22010][p])
						+ rs[DR] * (cl.data[X21011][p] + cl.data[X22011][p])
						- rs[AN] * rs[NF] * px * (cl.data[XA0010][p] + cl.data[XA0011][p])
						+ rs[DN] * (cl.data[X90010][p] + cl.data[X90011][p]))
						+ px;
}

void findX20011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X20011][p];
	cl.data[X20011][c] = ss * (rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X20010][p]
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPO] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DC] * cl.data[X20111][p]
						+ rs[DR] * (cl.data[X21011][p] + cl.data[X22011][p])
						- rs[AN] * rs[NF] * px * cl.data[XA0010][p]
						+ rs[DN] * cl.data[X90011][p])
						+ px;
}

void findX20100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X20100][p];
	cl.data[X20100][c] = ss * (rs[HOO] * cl.data[X10100][p] 
						+ rs[AC] * cl.data[X00100][p] * cl.data[X20000][p]
						- rs[DC] * px
						- rs[NL] * px
						- rs[UPO] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X20110][p]
						+ rs[DR] * (cl.data[X21100][p] + cl.data[X22100][p]))
						+ px;
}

void findX20110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X20110][p];
	cl.data[X20110][c] = ss * (rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X20010][p] 
						+ rs[NL] * cl.data[X20100][p] 
						- rs[DC] * px
						- rs[NE] * px
						- rs[UPO] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X20111][p]
						+ rs[UNBBIN] * cl.data[X20111][p]
						+ rs[DR] * (cl.data[X21110][p] + cl.data[X22110][p])
						+ rs[DR] * (cl.data[X21111][p] + cl.data[X22111][p])) 
						+ px;
}

void findX20111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X20111][p];
	cl.data[X20111][c] = ss * (rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X20011][p] 
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X20110][p]
						- rs[DC] * px
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPO] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DR] * (cl.data[X21111][p] + cl.data[X22111][p]))
						+ px;
}

void findX21000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X21000][p];
	cl.data[X21000][c] = ss * (rs[AR] * cl.data[X01000][p] * cl.data[X20000][p] 
						- rs[DR] * px
						- rs[NL] * px
						- rs[AC] * cl.data[X00100][p] * px
						+ rs[NE] * cl.data[X21010][p]
						+ rs[DC] * cl.data[X21100][p])
						+ px;
}

void findX21010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X21010][p];
	cl.data[X21010][c] = ss * (rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X20010][p]
						+ rs[NL] * cl.data[X21000][p]
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[UNBBIN] * cl.data[X21011][p]
						+ rs[DC] * cl.data[X21110][p])
						+ px;
}

void findX21011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X21011][p];
	cl.data[X21011][c] = ss * (rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X20010][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X20011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X21010][p]
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[DC] * cl.data[X21111][p])
						+ px;
}

void findX21100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X21100][p];
	cl.data[X21100][c] = ss * (rs[AR] * cl.data[X01000][p] * cl.data[X20100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X21000][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[NL] * px
						+ rs[NE] * cl.data[X21110][p])
						+ px;
}

void findX21110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X21110][p];
	cl.data[X21110][c] = ss * (rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X20110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X21010][p]
						+ rs[NL] * cl.data[X21100][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						+ rs[UNBBIN] * cl.data[X21111][p])
						+ px;
}

void findX21111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X21111][p];
	cl.data[X21111][c] = ss * (rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X20110][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X20111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X21011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X21110][p]
						- rs[DC] * px
						- rs[DR] * px * 2
						- rs[UNBBIN] * px)
						+ px;
}

void findX22000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X22000][p];
	cl.data[X22000][c] = ss * (rs[AR] * cl.data[X02000][p] * cl.data[X20000][p]
						- rs[DR] * px
						- rs[NL] * px
						- rs[AC] * cl.data[X00100][p] * px
						+ rs[NE] * cl.data[X22010][p]
						+ rs[DC] * cl.data[X22100][p])
						+ px;
}

void findX22010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X22010][p];
	cl.data[X22010][c] = ss * (rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X20010][p]
						+ rs[NL] * cl.data[X22000][p]
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[UNBBIN] * cl.data[X22011][p]
						+ rs[DC] * cl.data[X22110][p])
						+ px;
}

void findX22011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X22011][p];
	cl.data[X22011][c] = ss * (rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X20010][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X20011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X22010][p]
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[DC] * cl.data[X22111][p])
						+ px;
}

void findX22100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X22100][p];
	cl.data[X22100][c] = ss * (rs[AR] * cl.data[X02000][p] * cl.data[X20100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X22000][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[NL] * px
						+ rs[NE] * cl.data[X22110][p])
						+ px;
}

void findX22110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X22110][p];
	cl.data[X22110][c] = ss * (rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X20110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X22010][p]
						+ rs[NL] * cl.data[X22100][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						+ rs[UNBBIN] * cl.data[X22111][p]) 
						+ px;
}

void findX22111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X22111][p];
	cl.data[X22111][c] = ss * (rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X20110][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X20111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X22011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X22110][p]
						- rs[DC] * px
						- rs[DR] * px * 2 
						- rs[UNBBIN] * px)
						+ px;
}


void findX30000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X30000][p];
	cl.data[X30000][c] = ss * (rs[TLPT] * cl.data[MCPT][p]
						- rs[UPUT] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AGP] * cl.data[X00200][p] * px
						+ rs[DC] * cl.data[X30100][p]
						+ rs[DG] * cl.data[X30200][p])
						+ px;
}

void findX30100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X30100][p];
	cl.data[X30100][c] = ss * (rs[AC] * cl.data[X00100][p] * cl.data[X30000][p]
						- rs[DC] * px
						- rs[HTO] * px
						- rs[UPUT] * px
						- rs[AGP] * cl.data[X00200][p] * px
						+ rs[DG] * cl.data[X30300][p])
						+ px;
}

void findX30200(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X30200][p];
	cl.data[X30200][c] = ss * (rs[AGP] * cl.data[X00200][p] * cl.data[X30000][p]
						- rs[DG] * px
						- rs[UPUT] * px
						- cl.data[GTO][p] * px
						- rs[AC] * cl.data[X00100][p] * px
						+ rs[DC] * cl.data[X30300][p])
						+ px;
}

void findX30300(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X30300][p];
	cl.data[X30300][c] = ss * (rs[AGP] * cl.data[X00200][p] * cl.data[X30100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X30200][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[HTO] * px
						- rs[UPUT] * px
						- cl.data[GTO][p] * px)
						+ px;
}

void findX40000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X40000][p];
	cl.data[X40000][c] = ss * (- rs[NL] * px
						- rs[UPTC] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AGP] * cl.data[X00200][p] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X40010][p]
						+ rs[DC] * cl.data[X40100][p]
						+ rs[DG] * cl.data[X40200][p]
						+ rs[DR] * (cl.data[X41000][p] + cl.data[X42000][p])) 
						+ px;
}

void findX40010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X40010][p];
	cl.data[X40010][c] = ss * (rs[NL] * cl.data[X40000][p]
						- rs[NE] * px
						- rs[UPTC] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X40011][p]
						+ rs[UNBBIN] * cl.data[X40011][p]
						+ rs[DC] * cl.data[X40110][p]
						+ rs[DG] * cl.data[X40210][p]
						+ rs[DR] * (cl.data[X41010][p] + cl.data[X42010][p])
						+ rs[DR] * (cl.data[X41011][p] + cl.data[X42011][p]))
						+ px;
}

void findX40011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X40011][p];
	cl.data[X40011][c] = ss * (rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X40010][p]
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPTC] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DC] * cl.data[X40111][p]
						+ rs[DG] * cl.data[X40211][p]
						+ rs[DR] * (cl.data[X41011][p] + cl.data[X42011][p]))
						+ px; 
}

void findX40100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X40100][p];
	cl.data[X40100][c] = ss * (rs[HTO] * cl.data[X30100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X40000][p]
						- rs[DC] * px
						- rs[NL] * px
						- rs[UPTC] * px
						- rs[AGP] *  cl.data[X00200][p] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X40110][p]
						+ rs[DG] * cl.data[X40300][p]
						+ rs[DR] * (cl.data[X41100][p] + cl.data[X42100][p]))
						+ px;
}

void findX40110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X40110][p];
	cl.data[X40110][c] = ss * (rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X40010][p]
						+ rs[NL] * cl.data[X40100][p]
						- rs[DC] * px
						- rs[NE] * px
						- rs[UPTC] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X40111][p]
						+ rs[UNBBIN] * cl.data[X40111][p]
						+ rs[DG] * cl.data[X40310][p]
						+ rs[DR] * (cl.data[X41110][p] + cl.data[X42110][p])
						+ rs[DR] * (cl.data[X41111][p] + cl.data[X42111][p]))
						+ px;
						
}

void findX40111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X40111][p];
	cl.data[X40111][c] = ss * (rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X40011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X40110][p]
						- rs[DC] * px
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPTC] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DG] * cl.data[X40311][p]
						+ rs[DR] * (cl.data[X41111][p] + cl.data[X42111][p]))
						+ px;
}

void findX40200(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X40200][p];
	cl.data[X40200][c] = ss * (rs[AGP] *  cl.data[X00200][p] * cl.data[X40000][p]
						- rs[DG] * px
						- rs[NL] * px
						- rs[UPTC] * px
						- cl.data[GTO][p] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X40210][p]
						+ rs[DC] * cl.data[X40300][p]
						+ rs[DR] * (cl.data[X41200][p] + cl.data[X42200][p]))
						+ px;
}

void findX40210(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X40210][p];
	cl.data[X40210][c] = ss * (rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X40010][p]
						+ rs[NL] * cl.data[X40200][p]
						- rs[DG] * px
						- rs[NE] * px
						- rs[UPTC] * px
						- cl.data[GTO][p] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X40211][p]
						+ rs[UNBBIN] * cl.data[X40211][p]
						+ rs[DC] * cl.data[X40310][p]
						+ rs[DR] * (cl.data[X41210][p] + cl.data[X42210][p])
						+ rs[DR] * (cl.data[X41211][p] + cl.data[X42211][p]))
						+ px;
}

void findX40211(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X40211][p];
	cl.data[X40211][c] = ss * (rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X40011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X40210][p]
						- rs[DG] * px
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPTC] * px
						- cl.data[GTO][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DC] * cl.data[X40311][p]
						+ rs[DR] * (cl.data[X41211][p] + cl.data[X42211][p]))
						+ px;
}

void findX40300(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X40300][p];
	cl.data[X40300][c] = ss * (rs[HTO] * cl.data[X30300][p] 
						+ rs[AGP] *  cl.data[X00200][p] * cl.data[X40100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X40200][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[NL] * px
						- rs[UPTC] * px
						- cl.data[GTO][p] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X40310][p]
						+ rs[DR] * (cl.data[X41300][p] + cl.data[X42300][p]))
						+ px;
}	

void findX40310(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X40310][p];
	cl.data[X40310][c] = ss * (rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X40110][p]		
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X40210][p]
						+ rs[NL] * cl.data[X40300][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[NE] * px
						- rs[UPTC] * px
						- cl.data[GTO][p] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X40311][p]
						+ rs[UNBBIN] * cl.data[X40311][p]
						+ rs[DR] * (cl.data[X41310][p] + cl.data[X42310][p])
						+ rs[DR] * (cl.data[X41311][p] + cl.data[X42311][p]))
						+ px;
}		

void findX40311(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X40311][p];
	cl.data[X40311][c] = ss * (rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X40111][p]		
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X40211][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X40310][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPTC] * px
						- cl.data[GTO][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DR] * (cl.data[X41311][p] + cl.data[X42311][p]))
						+ px;
}	

void findX41000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X41000][p];
	cl.data[X41000][c] = ss * (rs[AR] * cl.data[X01000][p] * cl.data[X40000][p]
						- rs[DR] * px
						- rs[NL] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AGP] * cl.data[X00200][p] * px
						+ rs[NE] * cl.data[X41010][p] 
						+ rs[DC] * cl.data[X41100][p] 
						+ rs[DG] * cl.data[X41200][p] )
						+ px;
}

void findX41010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X41010][p];
	cl.data[X41010][c] = ss * (rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X40010][p]	
						+ rs[NL] * cl.data[X41000][p] 
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px	
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[UNBBIN] * cl.data[X41011][p]
						+ rs[DC] * cl.data[X41110][p] 
						+ rs[DG] * cl.data[X41210][p]) 
						+ px;
}

void findX41011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X41011][p];
	cl.data[X41011][c] = ss * (rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X40010][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X40011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X41010][p]
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[DC] * cl.data[X41111][p] 
						+ rs[DG] * cl.data[X41211][p]) 
						+ px;
}

void findX41100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X41100][p];
	cl.data[X41100][c] = ss * (rs[AR] * cl.data[X01000][p] * cl.data[X40100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X41000][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[NL] * px
						- rs[AGP] * cl.data[X00200][p] * px
						+ rs[NE] * cl.data[X41110][p] 
						+ rs[DG] * cl.data[X41300][p])  
						+ px;
}

void findX41110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X41110][p];
	cl.data[X41110][c] = ss * (rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X40110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X41010][p]
						+ rs[NL] * cl.data[X41100][p] 
						- rs[DC] * px
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X41110][p]
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[UNBBIN] * cl.data[X41111][p]
						+ rs[DG] * cl.data[X41310][p]) 
						+ px;
}

void findX41111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X41111][p];
	cl.data[X41111][c] = ss * (rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X40110][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X40111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X41011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X41110][p]
						- rs[DC] * px
						- rs[DR] * px *2
						- rs[UNBBIN] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[DG] * cl.data[X41311][p]) 
						+ px;
}

void findX41200(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X41200][p];
	cl.data[X41200][c] = ss * (rs[AR] * cl.data[X01000][p] * cl.data[X40200][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X41000][p]
						- rs[DG] * px
						- rs[DR] * px
						- rs[NL] * px
						- cl.data[GTO][p] * px
						- rs[AC] * cl.data[X00100][p] * px
						+ rs[NE] * cl.data[X41210][p] 
						+ rs[DC] * cl.data[X41300][p])
						+ px; 
}

void findX41210(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X41210][p];
	cl.data[X41210][c] = ss * (rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X40210][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X41010][p]
						+ rs[NL] * cl.data[X41200][p] 
						- rs[DG] * px
						- rs[DR] * px
						- rs[NE] * px
						- cl.data[GTO][p] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X41210][p]
						- rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X41210][p]
						+ rs[UNBBIN] * cl.data[X41211][p]
						+ rs[DC] * cl.data[X41310][p] )
						+ px;
}

void findX41211(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X41211][p];
	cl.data[X41211][c] = ss * (rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X40210][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X40211][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X41011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X41210][p]
						- rs[DG] * px
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- cl.data[GTO][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X41211][p]
						+ rs[DC] * cl.data[X41311][p]) 
						+ px;
}

void findX41300(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X41300][p];
	cl.data[X41300][c] = ss * (rs[AR] * cl.data[X01000][p] * cl.data[X40300][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X41100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X41200][p]
						- rs[DG] * px
						- rs[DR] * px 
						- rs[DC] * px 
						- rs[NL] * px
						- cl.data[GTO][p] * px
						+ rs[NE] * cl.data[X41310][p]) 
						+ px;
}

void findX41310(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X41310][p];
	cl.data[X41310][c] = ss * (rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X40310][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X41110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X41210][p]
						+ rs[NL] * cl.data[X41300][p]
						- rs[DG] * px
						- rs[DR] * px 
						- rs[DC] * px 
						- rs[NE] * px
						- cl.data[GTO][p] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X41310][p]
						+ rs[UNBBIN] * cl.data[X41311][p])
						+ px;
}

void findX41311(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X41311][p];
	cl.data[X41311][c] = ss * (rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X40310][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X40311][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X41111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X41211][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X41310][p]
						- rs[DG] * px
						- rs[DR] * px * 2
						- rs[DC] * px 
						- rs[UNBBIN] * px
						- cl.data[GTO][p] * px)
						+ px;
}

void findX42000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X42000][p];
	cl.data[X42000][c] = ss * (rs[AR] * cl.data[X02000][p] * cl.data[X40000][p]
						- rs[DR] * px
						- rs[NL] * px
						- rs[AC] * cl.data[X00100][p] * cl.data[X42000][p]
						- rs[AGP] * cl.data[X00200][p] * cl.data[X42000][p]
						+ rs[NE] * cl.data[X42010][p]
						+ rs[DC] * cl.data[X42100][p]
						+ rs[DG] * cl.data[X42200][p])
						+ px;
}

void findX42010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X42010][p];
	cl.data[X42010][c] = ss * (rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X40010][p]
						+ rs[NL] * cl.data[X42000][p]
						- rs[DR] * px 
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[UNBBIN] * cl.data[X42011][p]
						+ rs[DC] * cl.data[X42110][p]
						+ rs[DG] * cl.data[X42210][p])
						+ px;
}

void findX42011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X42011][p];
	cl.data[X42011][c] = ss * (rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X40010][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X40011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X42010][p]
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[DC] * cl.data[X42111][p]
						+ rs[DG] * cl.data[X42211][p])
						+ px;
}

void findX42100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X42100][p];
	cl.data[X42100][c] = ss * (rs[AR] * cl.data[X02000][p] * cl.data[X40100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X42000][p]
						- rs[DR] * px 
						- rs[DC] * px 
						- rs[NL] * px
						- rs[AGP] * cl.data[X00200][p] * px
						+ rs[NE] * cl.data[X42110][p]
						+ rs[DG] * cl.data[X42300][p])
						+ px;
} 

void findX42110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X42110][p];
	cl.data[X42110][c] = ss * (rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X40110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X42010][p]
						+ rs[NL] * cl.data[X42100][p]
						- rs[DR] * px 
						- rs[DC] * px 
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[UNBBIN] * cl.data[X42111][p]
						+ rs[DG] * cl.data[X42310][p])
						+ px;
}

void findX42111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X42111][p];
	cl.data[X42111][c] = ss * (rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X40110][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X40111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X42011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X42110][p]
						- rs[DR] * px * 2
						- rs[DC] * px 
						- rs[UNBBIN] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[DG] * cl.data[X42311][p])
						+ px;
}

void findX42200(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X42200][p];
	cl.data[X42200][c] = ss * (rs[AR] * cl.data[X02000][p] * cl.data[X40200][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X42000][p]
						- rs[DR] * px 
						- rs[DG] * px 
						- rs[NL] * px
						- cl.data[GTO][p] * px 
						- rs[AC] * cl.data[X00100][p] * px
						+ rs[NE] * cl.data[X42210][p]
						+ rs[DC] * cl.data[X42300][p])
						+ px;
}

void findX42210(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X42210][p];
	cl.data[X42210][c] = ss * (rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X40210][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X42010][p]
						+ rs[NL] * cl.data[X42200][p]
						- rs[DR] * px 
						- rs[DG] * px
						- rs[NE] * px
						- cl.data[GTO][p] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[UNBBIN] * cl.data[X42211][p]
						+ rs[DC] * cl.data[X42310][p])
						+ px;
}

void findX42211(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X42211][p];
	cl.data[X42211][c] = ss * (rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X40210][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X40211][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X42011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X42210][p]
						- rs[DR] * px * 2 
						- rs[DG] * px
						- rs[UNBBIN] * px
						- cl.data[GTO][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[DC] * cl.data[X42311][p]) 
						+ px;
}

void findX42300(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X42300][p];
	cl.data[X42300][c] = ss * (rs[AR] * cl.data[X02000][p] * cl.data[X40300][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X42100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X42200][p]
						- rs[DC] * px
						- rs[DR] * px 
						- rs[DG] * px
						- rs[NL] * px
						- cl.data[GTO][p] * px
						+ rs[NE] * cl.data[X42310][p])
						+ px;
}

void findX42310(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X42310][p];
	cl.data[X42310][c] = ss * (rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X40310][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X42110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X42210][p]
						+ rs[NL] * cl.data[X42300][p]
						- rs[DC] * px
						- rs[DR] * px 
						- rs[DG] * px
						- rs[NE] * px
						- cl.data[GTO][p] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X42310][p]
						+ rs[UNBBIN] * cl.data[X42311][p])
						+ px;
}

void findX42311(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X42311][p];
	cl.data[X42311][c] = ss * (rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X40310][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X40311][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X42111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X42211][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X42310][p]
						- rs[DC] * px
						- rs[DR] * px * 2
						- rs[DG] * px
						- rs[UNBBIN] * px
						- cl.data[GTO][p] * px)
						+ px;
}

void findX50000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X50000][p];
	cl.data[X50000][c] = ss * (- rs[NL] * px
						- rs[UPTG] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AGP] * cl.data[X00200][p] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X50010][p]
						+ rs[DC] * cl.data[X50100][p]
						+ rs[DG] * cl.data[X50200][p]
						+ rs[DR] * (cl.data[X51000][p] + cl.data[X52000][p]))
						+ px;
}

void findX50010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X50010][p];
	cl.data[X50010][c] = ss * (rs[NL] * cl.data[X50000][p]
						- rs[NE] * px
						- rs[UPTG] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X50011][p]
						+ rs[UNBBIN] * cl.data[X50011][p]
						+ rs[DC] * cl.data[X50110][p]
						+ rs[DG] * cl.data[X50210][p]
						+ rs[DR] * (cl.data[X51010][p] + cl.data[X52010][p])
						+ rs[DR] * (cl.data[X51011][p] + cl.data[X52011][p]))
						+ px;
}

void findX50011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X50011][p];
	cl.data[X50011][c] = ss * (rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X50010][p]
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPTG] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DC] * cl.data[X50111][p]
						+ rs[DG] * cl.data[X50211][p]
						+ rs[DR] * (cl.data[X51011][p] + cl.data[X52011][p]))
						+ px;
}

void findX50100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X50100][p];
	cl.data[X50100][c] = ss * (rs[AC] * cl.data[X00100][p] * cl.data[X50000][p]
						- rs[DC] * px
						- rs[HTO] * px
						- rs[NL] * px
						- rs[UPTG] * px
						- rs[AGP] * cl.data[X00200][p] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X50110][p]
						+ rs[DG] * cl.data[X50300][p]
						+ rs[DR] * (cl.data[X51100][p] + cl.data[X52100][p]))
						+ px;
}

void findX50110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X50110][p];
	cl.data[X50110][c] =  ss * (rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X50010][p]
						+ rs[NL] * cl.data[X50100][p]
						- rs[DC] * px
						- rs[HTO] * px
						- rs[NE] * px
						- rs[UPTG] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X50111][p]
						+ rs[UNBBIN] * cl.data[X50111][p]
						+ rs[DG] * cl.data[X50310][p]
						+ rs[DR] * (cl.data[X51110][p] + cl.data[X52110][p])
						+ rs[DR] * (cl.data[X51111][p] + cl.data[X52111][p]))
						+ px;
}

void findX50111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X50111][p];
	cl.data[X50111][c] =  ss * (rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X50011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X50110][p]
						- rs[DC] * px
						- rs[HTO] * px
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPTG] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DG] * cl.data[X50311][p]
						+ rs[DR] * (cl.data[X51111][p] + cl.data[X52111][p]))
						+ px;
}

void findX50200(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X50200][p];
	cl.data[X50200][c] = ss * (cl.data[GTO][p] * cl.data[X30200][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X50000][p]
						- rs[DG] * px
						- rs[NL] * px
						- rs[UPTG] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X50210][p]
						+ rs[DC] * cl.data[X50300][p]
						+ rs[DR] * (cl.data[X51200][p] + cl.data[X52200][p]))
						+ px;
}

void findX50210(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X50210][p];
	cl.data[X50210][c] = ss * (rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X50010][p]
						+ rs[NL] * cl.data[X50200][p]
						- rs[DG] * px
						- rs[NE] * px
						- rs[UPTG] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X50211][p]
						+ rs[UNBBIN] * cl.data[X50211][p]
						+ rs[DC] * cl.data[X50310][p]
						+ rs[DR] * (cl.data[X51210][p] + cl.data[X52210][p])
						+ rs[DR] * (cl.data[X51211][p] + cl.data[X52211][p]))
						+ px;
}

void findX50211(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X50211][p];
	cl.data[X50211][c] = ss * (rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X50011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X50210][p]
						- rs[DG] * px
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPTG] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X50211][p]
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DC] * cl.data[X50311][p]
						+ rs[DR] * (cl.data[X51211][p] + cl.data[X52211][p]))
						+ px;
} 

void findX50300(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X50300][p];
	cl.data[X50300][c] = ss * (cl.data[GTO][p] * cl.data[X30300][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X50100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X50200][p]
						- rs[DG] * px
						- rs[DC] * px
						- rs[HTO] * px
						- rs[NL] * px
						- rs[UPTG] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X50310][p]
						+ rs[DR] * (cl.data[X51300][p] + cl.data[X52300][p]))
						+ px;
}

void findX50310(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X50310][p];
	cl.data[X50310][c] = ss * (rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X50110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X50210][p]
						+ rs[NL] * cl.data[X50300][p]
						- rs[DG] * px
						- rs[DC] * px
						- rs[HTO] * px
						- rs[NE] * px
						- rs[UPTG] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X50311][p]
						+ rs[UNBBIN] * cl.data[X50311][p]
						+ rs[DR] * (cl.data[X51310][p] + cl.data[X52310][p])
						+ rs[DR] * (cl.data[X51311][p] + cl.data[X52311][p]))
						+ px;
}

void findX50311(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X50311][p];
	cl.data[X50311][c] = ss * (rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X50111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X50211][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X50310][p]
						- rs[DG] * px
						- rs[DC] * px
						- rs[HTO] * px
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPTG] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DR] * (cl.data[X51311][p] + cl.data[X52311][p]))
						+ px;
}

void findX51000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X51000][p];
	cl.data[X51000][c] = ss * (rs[AR] * cl.data[X01000][p] * cl.data[X50000][p]
						- rs[DR] * px
						- rs[NL] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AGP] * cl.data[X00200][p] * px
						+ rs[NE] * cl.data[X51010][p]
						+ rs[DC] * cl.data[X51100][p]
						+ rs[DG] * cl.data[X51200][p])
						+ px;
}

void findX51010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X51010][p];
	cl.data[X51010][c] = ss * (rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X50010][p]
						+ rs[NL] * cl.data[X51000][p]
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X51010][p]
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[UNBBIN] * cl.data[X51011][p]
						+ rs[DC] * cl.data[X51110][p]
						+ rs[DG] * cl.data[X51210][p])
						+ px;
}

void findX51011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X51011][p];
	cl.data[X51011][c] = ss * (rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X50010][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X50011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X51010][p]
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X51011][p]
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[DC] * cl.data[X51111][p]
						+ rs[DG] * cl.data[X51211][p])
						+ px;
}

void findX51100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X51100][p];
	cl.data[X51100][c] = ss * (rs[AR] * cl.data[X01000][p] * cl.data[X50100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X51000][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[NL] * px
						- rs[AGP] * cl.data[X00200][p] * px
						+ rs[NE] * cl.data[X51110][p]
						+ rs[DG] * cl.data[X51300][p])
						+ px;
}

void findX51110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X51110][p];
	cl.data[X51110][c] = ss * (rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X50110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X51010][p]
						+ rs[NL] * cl.data[X51100][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X51110][p]
						+ rs[UNBBIN] * cl.data[X51111][p]
						+ rs[DG] * cl.data[X51310][p])
						+ px;
}

void findX51111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X51111][p];
	cl.data[X51111][c] = ss * (rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X50110][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X50111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X51011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X51110][p]
						- rs[DC] * px
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[DG] * cl.data[X51311][p])
						+ px;
}

void findX51200(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X51200][p];
	cl.data[X51200][c] = ss * (rs[AR] * cl.data[X01000][p] * cl.data[X50200][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X51000][p]
						- rs[DG] * px
						- rs[DR] * px 
						- rs[NL] * px
						- rs[AC] * cl.data[X00100][p] * px
						+ rs[NE] * cl.data[X51210][p]
						+ rs[DC] * cl.data[X51300][p])
						+ px;
}

void findX51210(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X51210][p];
	cl.data[X51210][c] = ss * (rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X50210][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X51010][p]
						+ rs[NL] * cl.data[X51200][p]
						- rs[DG] * px
						- rs[DR] * px 
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[UNBBIN] * cl.data[X51211][p]
						+ rs[DC] * cl.data[X51310][p])
						+ px;
}

void findX51211(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X51211][p];
	cl.data[X51211][c] = ss * (rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X50210][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X50211][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X51011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X51210][p]
						- rs[DG] * px
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[DC] * cl.data[X51311][p])
						+ px;
}

void findX51300(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X51300][p];
	cl.data[X51300][c] = ss * (rs[AR] * cl.data[X01000][p] * cl.data[X50300][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X51100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X51200][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[DR] * px 
						- rs[NL] * px
						+ rs[NE] * cl.data[X51310][p])
						+ px;
}

void findX51310(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X51310][p];
	cl.data[X51310][c] = ss * (rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X50310][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X51110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X51210][p]
						+ rs[NL] * cl.data[X51300][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[DR] * px 
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						+ rs[UNBBIN] * cl.data[X51311][p])
						+ px;
}

void findX51311(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X51311][p];
	cl.data[X51311][c] = ss * (rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X50310][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X50311][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X51111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X51211][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X51310][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[DR] * px * 2
						- rs[UNBBIN] * px)
						+ px;
}

void findX52000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X52000][p];
	cl.data[X52000][c] = ss * (rs[AR] * cl.data[X02000][p] * cl.data[X50000][p]
						- rs[DR] * px
						- rs[NL] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AGP] * cl.data[X00200][p] * cl.data[X52000][p]
						+ rs[NE] * cl.data[X52010][p]
						+ rs[DC] * cl.data[X52100][p]
						+ rs[DG] * cl.data[X52200][p])
						+ px;
}

void findX52010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X52010][p];
	cl.data[X52010][c] = ss * (rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X50010][p]
						+ rs[NL] * cl.data[X52000][p]
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[UNBBIN] * cl.data[X52011][p]
						+ rs[DC] * cl.data[X52110][p]
						+ rs[DG] * cl.data[X52210][p])
						+ px;
}

void findX52011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X52011][p];
	cl.data[X52011][c] = ss * (rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X50010][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X50011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X52010][p]
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[DC] * cl.data[X52111][p]
						+ rs[DG] * cl.data[X52211][p])
						+ px;
}

void findX52100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X52100][p];
	cl.data[X52100][c] = ss * (rs[AR] * cl.data[X02000][p] * cl.data[X50100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X52000][p]
						- rs[DR] * px
						- rs[DC] * px
						- rs[NL] * px
						- rs[AGP] * cl.data[X00200][p] * cl.data[X52100][p]
						+ rs[NE] * cl.data[X52110][p]
						+ rs[DG] * cl.data[X52300][p])
						+ px;
}

void findX52110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X52110][p];
	cl.data[X52110][c] = ss * (rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X50110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X52010][p]
						+ rs[NL] * cl.data[X52100][p]
						- rs[DR] * px
						- rs[DC] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[UNBBIN] * cl.data[X52111][p]
						+ rs[DG] * cl.data[X52310][p])
						+ px;
}

void findX52111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X52111][p];
	cl.data[X52111][c] = ss * (rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X50110][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X50111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X52011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X52110][p]
						- rs[DR] * px * 2
						- rs[DC] * px
						- rs[UNBBIN] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[DG] * cl.data[X52311][p])
						+ px;
}

void findX52200(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X52200][p];
	cl.data[X52200][c] = ss * (rs[AR] * cl.data[X02000][p] * cl.data[X50200][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X52000][p]
						- rs[DR] * px
						- rs[DG] * px
						- rs[NL] * px
						- rs[AC] * cl.data[X00100][p] * px
						+ rs[NE] * cl.data[X52210][p]
						+ rs[DC] * cl.data[X52300][p])
						+ px;
}

void findX52210(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X52210][p];
	cl.data[X52210][c] = ss * (rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X50210][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X52010][p]
						+ rs[NL] * cl.data[X52200][p]
						- rs[DR] * px
						- rs[DG] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[UNBBIN] * cl.data[X52211][p]
						+ rs[DC] * cl.data[X52310][p])
						+ px;
}

void findX52211(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X52211][p];
	cl.data[X52211][c] = ss * (rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X50210][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X50211][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X52011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X52210][p]
						- rs[DR] * px * 2
						- rs[DG] * px
						- rs[UNBBIN] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[DC] * cl.data[X52311][p])
						+ px;
}

void findX52300(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X52300][p];
	cl.data[X52300][c] = ss * (rs[AR] * cl.data[X02000][p] * cl.data[X50300][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X52100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X52200][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[DG] * px
						- rs[NL] * px
						+ rs[NE] * cl.data[X52310][p])
						+ px;
}

void findX52310(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X52310][p];
	cl.data[X52310][c] = ss * (rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X50310][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X52110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X52210][p]
						+ rs[NL] * cl.data[X52300][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[DG] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						+ rs[UNBBIN] * cl.data[X52311][p])
						+ px;
}

void findX52311(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X52311][p];
	cl.data[X52311][c] = ss * (rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X50310][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X50311][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X52111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X52211][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X52310][p]
						- rs[DC] * px
						- rs[DR] * px * 2
						- rs[DG] * px
						- rs[UNBBIN] * px)
						+ px;
}

void findX60000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X60000][p];
	cl.data[X60000][c] = ss * (- rs[NL] * px
						- rs[UPTCG] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AGP] * cl.data[X00200][p] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X60010][p]
						+ rs[DC] * cl.data[X60100][p]
						+ rs[DG] * cl.data[X60200][p]
						+ rs[DR] * (cl.data[X61000][p] + cl.data[X62000][p]))
						+ px;
}

void findX60010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X60010][p];
	cl.data[X60010][c] = ss * (rs[NL] * cl.data[X60000][p]
						- rs[NE] * px
						- rs[UPTCG] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X60011][p]
						+ rs[UNBBIN] * cl.data[X60011][p]
						+ rs[DC] * cl.data[X60110][p]
						+ rs[DG] * cl.data[X60210][p]
						+ rs[DR] * (cl.data[X61010][p] + cl.data[X62010][p])
						+ rs[DR] * (cl.data[X61011][p] + cl.data[X62011][p]))
						+ px;
}

void findX60011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X60011][p];
	cl.data[X60011][c] = ss * (rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X60010][p]
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPTCG] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DC] * cl.data[X60111][p]
						+ rs[DG] * cl.data[X60211][p]
						+ rs[DR] * (cl.data[X61011][p] + cl.data[X62011][p]))
						+ px;
}

void findX60100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X60100][p];
	cl.data[X60100][c] = ss * (rs[HTO] * cl.data[X50100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X60000][p]
						- rs[DC] * px
						- rs[NL] * px
						- rs[UPTCG] * px
						- rs[AGP] * cl.data[X00200][p] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X60110][p]
						+ rs[DG] * cl.data[X60300][p]
						+ rs[DR] * (cl.data[X61100][p] + cl.data[X62100][p]))
						+ px;
}

void findX60110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X60110][p];
	cl.data[X60110][c] = ss * (rs[HTO] * cl.data[X50110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X60010][p]
						+ rs[NL] * cl.data[X60100][p]
						- rs[DC] * px
						- rs[NE] * px
						- rs[UPTCG] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X60111][p]
						+ rs[UNBBIN] * cl.data[X60111][p]
						+ rs[DG] * cl.data[X60310][p]
						+ rs[DR] * (cl.data[X61110][p] + cl.data[X62110][p])
						+ rs[DR] * (cl.data[X61111][p] + cl.data[X62111][p]))
						+ px;
}

void findX60111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X60111][p];
	cl.data[X60111][c] = ss * (rs[HTO] * cl.data[X50111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X60011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X60110][p]
						- rs[DC] * px
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPTCG] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X60111][p]
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DG] * cl.data[X60311][p]
						+ rs[DR] * (cl.data[X61111][p] + cl.data[X62111][p]))
						+ px;
}	

void findX60200(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X60200][p];
	cl.data[X60200][c] = ss * (cl.data[GTO][p] * cl.data[X40200][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X60000][p]
						- rs[DG] * px
						- rs[NL] * px
						- rs[UPTCG] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X60210][p]
						+ rs[DC] * cl.data[X60300][p]
						+ rs[DR] * (cl.data[X61200][p] + cl.data[X62200][p]))
						+ px;
}

void findX60210(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X60210][p];
	cl.data[X60210][c] = ss * (cl.data[GTO][p] * cl.data[X40210][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X60010][p]
						+ rs[NL] * cl.data[X60200][p]
						- rs[DG] * px
						- rs[NE] * px
						- rs[UPTCG] * px	
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X60211][p]
						+ rs[UNBBIN] * cl.data[X60211][p]
						+ rs[DC] * cl.data[X60310][p]
						+ rs[DR] * (cl.data[X61210][p] + cl.data[X62210][p])
						+ rs[DR] * (cl.data[X61211][p] + cl.data[X62211][p]))
						+ px;
}

void findX60211(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X60211][p];
	cl.data[X60211][c] = ss * (cl.data[GTO][p] * cl.data[X40211][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X60011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X60210][p]
						- rs[DG] * px
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPTCG] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DC] * cl.data[X60311][p]
						+ rs[DR] * (cl.data[X61211][p] + cl.data[X62211][p]))
						+ px;
}

void findX60300(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X60300][p];
	cl.data[X60300][c] = ss * (cl.data[GTO][p] * cl.data[X40300][p]
						+ rs[HTO] * cl.data[X50300][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X60100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X60200][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[NL] * px
						- rs[UPTCG] * px
						- rs[AR] * (cl.data[X01000][p] + cl.data[X02000][p]) * px
						+ rs[NE] * cl.data[X60310][p]
						+ rs[DR] * (cl.data[X61300][p] + cl.data[X62300][p]))
						+ px;
}

void findX60310(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X60310][p];
	cl.data[X60310][c] = ss * (cl.data[GTO][p] * cl.data[X40310][p]
						+ rs[HTO] * cl.data[X50310][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X60110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X60210][p]
						+ rs[NL] * cl.data[X60300][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[NE] * px
						- rs[UPTCG] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X60310][p]
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						- rs[AR] * rs[NF] * (cl.data[X01011][p] + cl.data[X02011][p]) * px
						+ rs[UBC] * cl.data[X60311][p]
						+ rs[UNBBIN] * cl.data[X60311][p]
						+ rs[DR] * (cl.data[X61310][p] + cl.data[X62310][p])
						+ rs[DR] * (cl.data[X61311][p] + cl.data[X62311][p]))
						+ px;
}

void findX60311(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X60311][p];
	cl.data[X60311][c] = ss * (cl.data[GTO][p] * cl.data[X40311][p]
						+ rs[HTO] * cl.data[X50311][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X60111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X60211][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X60310][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPTCG] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DR] * (cl.data[X61311][p] + cl.data[X62311][p]))
						+ px;
}

void findX61000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X61000][p];
	cl.data[X61000][c] = ss * (rs[AR] * cl.data[X01000][p] * cl.data[X60000][p]
						- rs[DR] * px
						- rs[NL] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AGP] * cl.data[X00200][p] * px
						+ rs[NE] * cl.data[X61010][p]
						+ rs[DC] * cl.data[X61100][p]
						+ rs[DG] * cl.data[X61200][p])
						+ px;
}

void findX61010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X61010][p];
	cl.data[X61010][c] = ss * (rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X60010][p]
						+ rs[NL] * cl.data[X61000][p]
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[UNBBIN] * cl.data[X61011][p]
						+ rs[DC] * cl.data[X61110][p]
						+ rs[DG] * cl.data[X61210][p])
						+ px;
}

void findX61011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X61011][p];
	cl.data[X61011][c] = ss * (rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X60010][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X60011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X61010][p]
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X61011][p]
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X61011][p]
						+ rs[DC] * cl.data[X61111][p]
						+ rs[DG] * cl.data[X61211][p])
						+ px;
}

void findX61100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X61100][p];
	cl.data[X61100][c] = ss * (rs[AR] * cl.data[X01000][p] * cl.data[X60100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X61000][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[NL] * px
						- rs[AGP] * cl.data[X00200][p] * px
						+ rs[NE] * cl.data[X61110][p]
						+ rs[DG] * cl.data[X61300][p])
						+ px;
}

void findX61110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X61110][p];
	cl.data[X61110][c] = ss * (rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X60110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X61010][p]
						+ rs[NL] * cl.data[X61100][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[UNBBIN] * cl.data[X61111][p]
						+ rs[DG] * cl.data[X61310][p])
						+ px;
}

void findX61111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X61111][p];
	cl.data[X61111][c] = ss * (rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X60110][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X60111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X61011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X61110][p]
						- rs[DC] * px
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[DG] * cl.data[X61311][p])
						+ px;
}

void findX61200(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X61200][p];
	cl.data[X61200][c] = ss * (cl.data[GTO][p] * cl.data[X41200][p]
						+ rs[AR] * cl.data[X01000][p] * cl.data[X60200][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X61000][p]
						- rs[DG] * px
						- rs[DR] * px
						- rs[NL] * px
						- rs[AC] * cl.data[X00100][p] * px
						+ rs[NE] * cl.data[X61210][p]
						+ rs[DC] * cl.data[X61300][p])
						+ px;
}

void findX61210(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X61210][p];
	cl.data[X61210][c] = ss * (cl.data[GTO][p] * cl.data[X41210][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X60210][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X61010][p]
						+ rs[NL] * cl.data[X61200][p]
						- rs[DG] * px
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[UNBBIN] * cl.data[X61211][p]
						+ rs[DC] * cl.data[X61310][p])
						+ px;
}

void findX61211(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X61211][p];
	cl.data[X61211][c] = ss * (cl.data[GTO][p] * cl.data[X41211][p]
						+ rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X60210][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X60211][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X61011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X61210][p]
						- rs[DG] * px
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[DC] * cl.data[X61311][p])
						+ px;
}

void findX61300(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X61300][p];
	cl.data[X61300][c] = ss * (cl.data[GTO][p] * cl.data[X41300][p]
						+ rs[AR] * cl.data[X01000][p] * cl.data[X60300][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X61100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X61200][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[DR] * px
						- rs[NL] * px
						+ rs[NE] * cl.data[X61310][p])
						+ px;
}

void findX61310(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X61310][p];
	cl.data[X61310][c] = ss * (cl.data[GTO][p] * cl.data[X41310][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X60310][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X61110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X61210][p]
						+ rs[NL] * cl.data[X61300][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						+ rs[UNBBIN] * cl.data[X61311][p])
						+ px;
}

void findX61311(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X61311][p];
	cl.data[X61311][c] = ss * (cl.data[GTO][p] * cl.data[X41311][p]
						+ rs[AR] * rs[NF] * cl.data[X01011][p] * cl.data[X60310][p]
						+ rs[AR] * rs[NF] * cl.data[X01010][p] * cl.data[X60311][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X61111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X61211][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X61310][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[DR] * px * 2
						- rs[UNBBIN] * px)
						+ px;
}

void findX62000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X62000][p];
	cl.data[X62000][c] = ss * (rs[AR] * cl.data[X02000][p] * cl.data[X60000][p]
						- rs[DR] * px
						- rs[NL] * px
						- rs[AC] * cl.data[X00100][p] * px
						- rs[AGP] * cl.data[X00200][p] * px
						+ rs[NE] * cl.data[X62010][p]
						+ rs[DC] * cl.data[X62100][p]
						+ rs[DG] * cl.data[X62200][p])
						+ px;
}

void findX62010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X62010][p];
	cl.data[X62010][c] = ss * (rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X60010][p]
						+ rs[NL] * cl.data[X62000][p]
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X62010][p]
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X62010][p]
						+ rs[UNBBIN] * cl.data[X62011][p]
						+ rs[DC] * cl.data[X62110][p]
						+ rs[DG] * cl.data[X62210][p])
						+ px;
}

void findX62011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X62011][p];
	cl.data[X62011][c] = ss * (rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X60010][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X60011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X62010][p]
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X62011][p]
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X62011][p]
						+ rs[DC] * cl.data[X62111][p]
						+ rs[DG] * cl.data[X62211][p])
						+ px;
}

void findX62100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X62100][p];
	cl.data[X62100][c] = ss * (rs[AR] * cl.data[X02000][p] * cl.data[X60100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X62000][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[NL] * px
						- rs[AGP] * cl.data[X00200][p] * px
						+ rs[NE] * cl.data[X62110][p]
						+ rs[DG] * cl.data[X62300][p])
						+ px;
}

void findX62110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X62110][p];
	cl.data[X62110][c] = ss * (rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X60110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X62010][p]
						+ rs[NL] * cl.data[X62100][p]
						- rs[DC] * px
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[UNBBIN] * cl.data[X62111][p]
						+ rs[DG] * cl.data[X62310][p])
						+ px;
}

void findX62111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X62111][p];
	cl.data[X62111][c] = ss * (rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X60110][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X60111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X62011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X62110][p]
						- rs[DC] * px
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AGP] * rs[NF] * cl.data[X00210][p] * px
						+ rs[DG] * cl.data[X62311][p])
						+ px;
}

void findX62200(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X62200][p];
	cl.data[X62200][c] = ss * (cl.data[GTO][p] * cl.data[X42200][p]
						+ rs[AR] * cl.data[X02000][p] * cl.data[X60200][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X62000][p]
						- rs[DG] * px
						- rs[DR] * px
						- rs[NL] * px
						- rs[AC] * cl.data[X00100][p] * px
						+ rs[NE] * cl.data[X62210][p]
						+ rs[DC] * cl.data[X62300][p])
						+ px;
}

void findX62210(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X62210][p];
	cl.data[X62210][c] = ss * (cl.data[GTO][p] * cl.data[X42210][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X60210][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X62010][p]
						+ rs[NL] * cl.data[X62200][p]
						- rs[DG] * px
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X62210][p]
						- rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X62210][p]
						+ rs[UNBBIN] * cl.data[X62211][p]
						+ rs[DC] * cl.data[X62310][p])
						+ px;
}

void findX62211(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X62211][p];
	cl.data[X62211][c] = ss * (cl.data[GTO][p] * cl.data[X42211][p]	
						+ rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X60210][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X60211][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X62011][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X62210][p]
						- rs[DG] * px
						- rs[DR] * px * 2
						- rs[UNBBIN] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X62211][p]
						+ rs[DC] * cl.data[X62311][p])
						+ px;
}

void findX62300(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X62300][p];
	cl.data[X62300][c] = ss * (cl.data[GTO][p] * cl.data[X42300][p]
						+ rs[AR] * cl.data[X02000][p] * cl.data[X60300][p]
						+ rs[AGP] * cl.data[X00200][p] * cl.data[X62100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X62200][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[DR] * px
						- rs[NL] * px
						+ rs[NE] * cl.data[X62310][p])
						+ px;
}

void findX62310(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X62310][p];
	cl.data[X62310][c] = ss * (cl.data[GTO][p] * cl.data[X42310][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X60310][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X62110][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X62210][p]
						+ rs[NL] * cl.data[X62300][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[DR] * px
						- rs[NE] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X62310][p]
						+ rs[UNBBIN] * cl.data[X62311][p])
						+ px;
}

void findX62311(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X62311][p];
	cl.data[X62311][c] = ss * (cl.data[GTO][p] * cl.data[X42311][p]
						+ rs[AR] * rs[NF] * cl.data[X02011][p] * cl.data[X60310][p]
						+ rs[AR] * rs[NF] * cl.data[X02010][p] * cl.data[X60311][p]
						+ rs[AGP] * rs[NF] * cl.data[X00210][p] * cl.data[X62111][p]
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X62211][p]
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X62310][p]
						- rs[DC] * px
						- rs[DG] * px
						- rs[DR] * px * 2
						- rs[UNBBIN] * px)
						+ px;
}

void findMNPH(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[MNPH][p];
	cl.data[MNPH][c] = ss * (rs[TRPH] * cl.data[GPH][p]
						- rs[TMC] * px
						- rs[UMPH] * px)
						+ px; 
}

void findMCPH(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[MCPH][p];
	cl.data[MCPH][c] = ss * (- rs[UMPH] * px
						+ rs[TMC] * cl.data[MNPH][p])
						+ px;
}

void findX70000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X70000][p];
	cl.data[X70000][c] = ss * (rs[TLPH] * cl.data[MCPH][p]
						- rs[UPUH] * px
						- rs[AN] * px * cl.data[X10000][p]
						+ rs[DN] * cl.data[X80000][p])
						+ px;
}

void findX80000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X80000][p];
	cl.data[X80000][c] = ss * (rs[AN] * cl.data[X70000][p] * cl.data[X10000][p]
						- rs[DN] * px
						- rs[AC] * cl.data[X00100][p] * px
						+ rs[DC] * cl.data[X80100][p]
						- rs[UPUOH] * px)
						+ px;
}

void findX80100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X80100][p];
	cl.data[X80100][c] = ss * (rs[AC] * cl.data[X00100][p] * cl.data[X80000][p]
						- rs[DC] * px
						- rs[HOHO] * px
						- rs[UPUOH] * px)
						+ px;
}

void findX90000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X90000][p];
	cl.data[X90000][c] = ss * (- rs[AC] * cl.data[X00100][p] * px
						+ rs[DC] * cl.data[X90100][p]
						- rs[UPOH] * px
						+ rs[AN] * cl.data[XA0000][p] * cl.data[X20000][p]
						- rs[DN] * px 
						- rs[NL] * px
						+ rs[NE] * cl.data[X90010][p])
						+ px;
}

void findX90010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X90010][p];
	cl.data[X90010][c] = ss * (rs[NL] * cl.data[X90000][p]
						- rs[NE] * px
						- rs[UPOH] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[UBC] * cl.data[X90011][p]
						+ rs[UNBBIN] * cl.data[X90011][p]
						+ rs[DC] * cl.data[X90110][p]
						+ rs[AN] * rs[NF] * cl.data[XA0010][p] * cl.data[X20010][p]
						- rs[DN] * px)
						+ px;
}

void findX90011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X90011][p];
	cl.data[X90011][c] = ss * (rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X90010][p]
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPOH] * px
						- rs[AC] * rs[NF] * cl.data[X00110][p] * px
						+ rs[DC] * cl.data[X90111][p]
						+ rs[AN] * rs[NF] * cl.data[X20010][p] * cl.data[XA0011][p]
						+ rs[AN] * rs[NF] * cl.data[X20011][p] * cl.data[XA0010][p]
						- rs[DN] * px * 2)
						+ px;
}


void findX90100(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X90100][p];
	cl.data[X90100][c] = ss * (rs[HOHO] * cl.data[X80100][p]
						+ rs[AC] * cl.data[X00100][p] * cl.data[X90000][p]
						- rs[DC] * px
						- rs[NL] * px
						- rs[UPOH] * px
						+ rs[NE] * cl.data[X90110][p])
						+ px;
}

void findX90110(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X90110][p];
	cl.data[X90110][c] = ss * (- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						+ rs[UNBBIN] * cl.data[X90111][p]
						+ rs[UBC] * cl.data[X90111][p]
						+ rs[NL] * cl.data[X90100][p]
						- rs[NE] * px
						+ rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X90010][p]
						- rs[DC] * px
						- rs[UPOH] * px)
						+ px;
}

void findX90111(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X90111][p];
	cl.data[X90111][c] = ss * (rs[AC] * rs[NF] * cl.data[X00110][p] * cl.data[X90011][p]
						- rs[DC] * px
						- rs[UBC] * px
						+ rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[X90110][p]
						- rs[UNBBIN] * px
						- rs[UPOH] * px)
						+ px;
}

void findGPHR(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[GPHR][p];
	cl.data[GPHR][c] = ss * (- rs[UNBINPH] * px
						+ rs[BINPH] * (1 - cl.data[GPH][p] - px) * (cl.data[X01011][p] + cl.data[X02011][p]))
						+ px;
}

void findGPH(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[GPH][p];
	cl.data[GPH][c] = ss * (- rs[UNBINPH] * px
					+ rs[BINPH] * (1 - px - cl.data[GPHR][p]) * cl.data[X00011][p])
					+ px;
}


void findXA0000(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[XA0000][p];
	cl.data[XA0000][c] = ss * (- rs[AN] * px * cl.data[X20000][p]
						+ rs[DN] * cl.data[X90000][p]
						- rs[UPH] * cl.data[XA0000][p]
						- rs[NL] * px
						+ rs[NE] * cl.data[XA0010][p])
						+ px;
}

void findXA0010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[XA0010][p];
	cl.data[XA0010][c] = ss * (- rs[AN] * rs[NF] * cl.data[X20010][p] * px
						- rs[AN] * rs[NF] * cl.data[X20011][p] * cl.data[XA0010][p]
						+ rs[DN] * cl.data[X90011][p]
						+ rs[DN] * cl.data[X90010][p]
						- rs[UPH] * px
						+ rs[NL] * cl.data[XA0000][p]
						- rs[NE] * px
						- rs[AR] * rs[NF] * px * (cl.data[X01010][p] + cl.data[X02010][p])
						- rs[AR] * rs[NF] * px * (cl.data[X01011][p] + cl.data[X02011][p])
						+ rs[DR] * (cl.data[XA1011][p] + cl.data[XA2011][p])
						+ rs[DR] * (cl.data[XA1010][p] + cl.data[XA2010][p])
						- rs[BBIN] * rs[NF] * px * cl.data[X00011][p]
						+ rs[UBC] * cl.data[XA0011][p]
						+ rs[UNBBIN] * cl.data[XA0011][p])
						+ px;
}

void findXA0011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[XA0011][p];
	cl.data[XA0011][c] = ss * (rs[BBIN] * rs[NF] * cl.data[XA0010][p] * cl.data[X00011][p]
						- rs[UBC] * px
						- rs[UNBBIN] * px
						- rs[UPH] * px
						- rs[AR] * rs[NF] * (cl.data[X01010][p] + cl.data[X02010][p]) * px
						+ rs[DR] * (cl.data[XA1011][p] + cl.data[XA2011][p])
						- rs[AN] * rs[NF] * cl.data[X20010][p] * px
						+ rs[DN] * cl.data[X90011][p])
						+ px;
}

void findXA1010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[XA1010][p];
	cl.data[XA1010][c] = ss * (rs[AR] * rs[NF] * cl.data[XA0010][p] * cl.data[X01010][p]
						- rs[DR] * px
						- rs[BBIN] * rs[NF] * cl.data[X00011][p] * px
						+ rs[UNBBIN] * cl.data[XA1011][p]) 
						+ px; 
}

void findXA1011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[XA1011][p];
	cl.data[XA1011][c] = ss * (rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[XA1010][p]
						- rs[UNBBIN] * px
						+ rs[AR] * rs[NF] * cl.data[XA0011][p] * cl.data[X01010][p]
						+ rs[AR] * rs[NF] * cl.data[XA0010][p] * cl.data[X01011][p]
						- rs[DR] * px
						- rs[DR] * px)
						+ px;
}

void findXA2010(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[XA2010][p];
	cl.data[XA2010][c] = ss * (rs[AR] * rs[NF] * cl.data[XA0010][p] * cl.data[X02010][p]
						- rs[DR] * px
						- rs[BBIN] * rs[NF] * px * cl.data[X00011][p]
						+ rs[UNBBIN] * cl.data[XA2011][p])
						+ px;
}

void findXA2011(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[XA2011][p];
	cl.data[XA2011][c] = ss * (rs[BBIN] * rs[NF] * cl.data[X00011][p] * cl.data[XA2010][p]
						- rs[UNBBIN] * px
						+ rs[AR] * rs[NF] * cl.data[XA0011][p] * cl.data[X02010][p]
						+ rs[AR] * rs[NF] * cl.data[XA0010][p] * cl.data[X02011][p]
						- rs[DR] * px
						- rs[DR] * px)
						+ px;
}

void findGPOR(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[GPOR][p];
	cl.data[GPOR][c] = ss * (- rs[UNBINPO] * px
						+ rs[BINPO] * (1 - cl.data[GPO][p] - px) * (cl.data[X01011][p] + cl.data[X02011][p]))
						+ px;
}

void findGPO(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[GPO][p];
	cl.data[GPO][c] = ss * (- rs[UNBINPO] * px
					+ rs[BINPO] * (1 - px - cl.data[GPOR][p]) * cl.data[X00011][p])
					+ px;
}

void findGPTR(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[GPTR][p];
	cl.data[GPTR][c] = ss * (- rs[UNBINPT] * px
						+ rs[BINPT] * (1 - cl.data[GPT][p] - px) * (cl.data[X01011][p] + cl.data[X02011][p]))
						+ px;
}

void findGPT(double * rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[GPT][p];
	cl.data[GPT][c] = ss * (- rs[UNBINPT] * px
					+ rs[BINPT] * (1 - px - cl.data[GPTR][p]) * cl.data[X00011][p])
					+ px;
}

void findGBN(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[GBN][p];
	cl.data[GBN][c] = ss * (rs[UNBINREVN] * cl.data[GBRN][p]
					- rs[BINREVN] * px * (cl.data[REVN][p] + cl.data[REVNG][p] + cl.data[REVNGP][p] + cl.data[REVNP][p]))
					+ px;
}

void findGBRN(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[GBRN][p];
	cl.data[GBRN][c] = ss * (- (rs[UNBINREVN] * px)
					+ rs[BINREVN]* cl.data[GBN][p]*(cl.data[REVN][p] + cl.data[REVNG][p] + cl.data[REVNGP][p] + cl.data[REVNP][p]))
					+ px;
}

void findX01002(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X01002][p];
	cl.data[X01002][c] = ss * (rs[BINCRYB] * cl.data[BC][p] * cl.data[X01000][p]
						- rs[UNBINCRYB] * px)
						+ px;		
}

void findX02002(double* rs, con_levels& cl, int c, double ss){
	int p = (c-1) % cl.big_gran;
	c = c % cl.big_gran;
	double px = cl.data[X02002][p];
	cl.data[X02002][c] = ss * (rs[BINCRYB] * cl.data[BC][p] * cl.data[X02000][p]
						- rs[UNBINCRYB] * px)
						+ px;
}
