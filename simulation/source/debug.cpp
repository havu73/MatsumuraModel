/* All functions in this file are not used in the simulation process. 
 * They can be used by coders to check whether data is inputed correctly.
 * Be advised that some functions are rather outdated, meaning they may not 
 * print out all rates or states existent in the system. 
 */
#include "debug.hpp"
#include "macros.hpp"
#include "io.hpp"
using namespace std;
/* Prints out  to terminal the concentrations of species at different step within cl (not big_cl)
 * This functions can be used to test whether intial conditions is entered correctly or 
 * Params: cl: the con_level structures conctaining concentrations. 
 * 		   t: index of the time step we want to check concentrations of
 * Notes: to check initial conditions, we input cl (not bit_cl), and t = 0
 * 		  also note that time step t differ depending on whether you use cl or big_cl
 * 		  To know more about cl and big_cl, look at sim.cpp
 */
void test_concentrations(con_levels& cl, int t){
	for (int i = 0; i< NUM_CONS; i++){
		if (i == GRB){
				cout << "GRB at time step " << t << " is : "<< cl.data[i][t]<< endl; 
			}
			else if (i == G){
				cout << "G at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == GRSRB){
				cout << "GRSRB at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == GRS){
				cout << "GRS at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == GCR){
				cout << "GCR at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == GC){
				cout << "GC at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == GBR){
				cout << "GBR at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == GB){
				cout << "GB at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == GBRB){
				cout << "GBRB at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == GBB){
				cout << "GBB at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MNPO){
				cout << "MNPO at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MCPO){
				cout << "MCPO at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MNPT){
				cout << "MNPT at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MCPT){
				cout << "MCPT at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MNRT){
				cout << "MNRT at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MCRT){
				cout << "MCRT at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MNREV){
				cout << "MNREV at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MCREV){
				cout << "MCREV at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MNRO){
				cout << "MNRO at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MCRO){
				cout << "MCRO at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MNB){
				cout << "MNB at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MCB){
				cout << "MCB at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MNNP){
				cout << "MNNP at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == MCNP){
				cout << "MCNP at time step " << t << " is : "<< cl.data[i][t]<< endl;
			} 
			else if (i == B){
				cout << "B at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == CL){
				cout << "CL at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == BC){
				cout << "BC at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == CYREV){
				cout << "CYREV at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == REVN){
				cout << "REVN at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == CYREVG){
				cout << "CYREVG at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == REVNG){
				cout << "REVNG at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == CYREVGP){
				cout << "CYREVGP at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == REVNGP){
				cout << "REVNGP at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == CYREVP){
				cout << "CYREVP at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == REVNP){
				cout << "REVNP at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == GTO){
				cout << "GTO at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X00001){
				cout << "X00001 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X00011){
				cout << "X00011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X00100){
				cout << "X00100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X00110){
				cout << "X00110 at time step " << t << " is : "<< cl.data[i][t]<< endl;	
			}
			else if (i == X00200){
				cout << "X00200 at time step " << t << " is : "<< cl.data[i][t]<< endl;	
			}
			else if (i == X00210){
				cout << "X00210 at time step " << t << " is : "<< cl.data[i][t]<< endl;	
			}
			else if (i == X01000){
				cout << "X01000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X01010){
				cout << "X01010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X01011){
				cout << "X01011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X02000){
				cout << "X02000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X02010){
				cout << "X02010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X02011){
				cout << "X02011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X10000){
				cout << "X10000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X10100){
				cout << "X10100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X20000){
				cout << "X20000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X20010){
				cout << "X20010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X20011){
				cout << "X20011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X20100){
				cout << "X20100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X20110){
				cout << "X20110 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X20111){
				cout << "X20111 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X21000){
				cout << "X21000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X21010){
				cout << "X21010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X21011){
				cout << "X21011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X21100){
				cout << "X21100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X21110){
				cout << "X21110 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X21111){
				cout << "X21111 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X22000){
				cout << "X22000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X22010){
				cout << "X22010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X22011){
				cout << "X22011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X22100){
				cout << "X22100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X22110){
				cout << "X22110 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X22111){
				cout << "X22111 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X30000){
				cout << "X30000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X30100){
				cout << "X30100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X30200){
				cout << "X30200 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X30300){
				cout << "X30300 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X40000){
				cout << "X40000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X40010){
				cout << "X40010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X40011){
				cout << "X40011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X40100){
				cout << "X40100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X40110){
				cout << "X40110 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X40111){
				cout << "X40111 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X40200){
				cout << "X40200 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X40210){
				cout << "X40210 at time step " << t << " is : "<< cl.data[i][t]<< endl;;
			}
			else if (i == X40211){
				cout << "X40211 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X40300){
				cout << "X40300 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X40310){
				cout << "X40310 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X40311){
				cout << "X40311 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X41000){
				cout << "X41000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X41010){
				cout << "X41010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X41011){
				cout << "X41011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X41100){
				cout << "X41100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X41110){
				cout << "X41110 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X41111){
				cout << "X41111 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X41200){
				cout << "X41200 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X41210){
				cout << "X41210 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X41211){
				cout << "X41211 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X41300){
				cout << "X41300 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X41310){
				cout << "X41310 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X41311){
				cout << "X41311 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42000){
				cout << "X42000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42010){
				cout << "X42010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42011){
				cout << "X42011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42100){
				cout << "X42100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42110){
				cout << "X42110 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42111){
				cout << "X42111 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42200){
				cout << "X42200 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42210){
				cout << "X42210 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42210){
				cout << "X42210 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42211){
				cout << "X42211 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42300){
				cout << "X42300 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42310){
				cout << "X42310 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X42311){
				cout << "X42311 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X50000){
				cout << "X50000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X50010){
				cout << "X50010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X50011){
				cout << "X50011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X50100){
				cout << "X50100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X50110){
				cout << "X50110 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X50111){
				cout << "X50111 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X50200){
				cout << "X50200 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X50210){
				cout << "X50210 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X50300){
				cout << "X50300 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X50310){
				cout << "X50310 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X50311){
				cout << "X50311 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X51000){
				cout << "X51000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X51010){
				cout << "X51010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X51011){
				cout << "X51011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X51100){
				cout << "X51100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X51110){
				cout << "X51110 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X51111){
				cout << "X51111 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X51200){
				cout << "X51200 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X51210){
				cout << "X51210 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X51211){
				cout << "X51211 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X51300){
				cout << "X51300 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X51310){
				cout << "X51310 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X51311){
				cout << "X51311 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X52000){
				cout << "X52000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X52010){
				cout << "X52010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X52011){
				cout << "X52011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X52100){
				cout << "X52100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X52110){
				cout << "X52110 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X52111){
				cout << "X52111 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X52200){
				cout << "X52200 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X52210){
				cout << "X52210 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X52211){
				cout << "X52211 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X52300){
				cout << "X52300 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X52310){
				cout << "X52310 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X52311){
				cout << "X52311 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X60000){
				cout << "X60000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X60010){
				cout << "X60010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X60011){
				cout << "X60011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X60100){
				cout << "X60100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X60110){
				cout << "X60110 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X60111){
				cout << "X60111 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X60200){
				cout << "X60200 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X60210){
				cout << "X60210 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X60300){
				cout << "X60300 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X60310){
				cout << "X60310 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X60311){
				cout << "X60311 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X61000){
				cout << "X61000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X61010){
				cout << "X61010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X61011){
				cout << "X61011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X61100){
				cout << "X61100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X61110){
				cout << "X61110 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X61111){
				cout << "X61111 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X61200){
				cout << "X61200 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X61210){
				cout << "X61210 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X61211){
				cout << "X61211 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X61300){
				cout << "X61300 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X61310){
				cout << "X61310 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X61311){
				cout << "X61311 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X62000){
				cout << "X62000 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X62010){
				cout << "X62010 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X62011){
				cout << "X62011 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X62100){
				cout << "X62100 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X62110){
				cout << "X62110 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X62111){
				cout << "X62111 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X62200){
				cout << "X62200 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X62210){
				cout << "X62210 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X62211){
				cout << "X62211 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X62300){
				cout << "X62300 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X62310){
				cout << "X62310 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
			else if (i == X62311){
				cout << "X62311 at time step " << t << " is : "<< cl.data[i][t]<< endl;
			}
	}
}

/* Prints out the parameters inputed to the model.
 * Use: Check whether input files for parameters are inputted correctly
 * Params: rs: the structures that contain live parameters
 */
void test_rates(rates& rs){
	double* r = rs.rates_base;
	for (int i = 0 ; i < NUM_RATES ; i++){
		if (i == TRPO){
			cout << "TRPO: " << r[i]<< endl;
		}
		else if (i == TRPT){
			cout << "TRPT: " << r[i]<< endl;
		}
		else if (i == TRRO){
			cout << "TRRO: " << r[i]<< endl;
		}
		else if (i == TRRT){
			cout << "TRRT: " << r[i]<< endl;
		}
		else if (i == TRB){
			cout << "TRB: " << r[i]<< endl;
		}
		else if (i == TRREV){
			cout << "TRREV: " << r[i]<< endl;
		}
		else if (i == TRNP){
			cout << "TRNP: " << r[i]<< endl;
		}
		else if (i == TLB){
			cout << "TLB: " << r[i]<< endl;
		}
		else if (i == TLREV){
			cout << "TLREV: " << r[i]<< endl;
		}
		else if (i == TLC){
			cout << "TLC: " << r[i]<< endl;
		}
		else if (i == TLNP){
			cout << "TLNP: " << r[i]<< endl;
		}
		else if (i == TRPT){
			cout << "TRPT: " << r[i]<< endl;
		}
		else if (i == AGP){
			cout << "AGP: " << r[i]<< endl;
		}
		else if (i == DG){
			cout << "DG: " << r[i]<< endl;
		}
		else if (i == AC){
			cout << "AC: " << r[i]<< endl;
		}
		else if (i == DC){
			cout << "DC: " << r[i]<< endl;
		}
		else if (i == AR){
			cout << "AR: " << r[i]<< endl;
		}
		else if (i == DR){
			cout << "DR: " << r[i]<< endl;
		}
		else if (i == CBIN){
			cout << "CBIN: " << r[i]<< endl;
		}
		else if (i == UNCBIN){
			cout << "UNCBIN: " << r[i]<< endl;
		}
		else if (i == BBIN){
			cout << "BBIN: " << r[i]<< endl;
		}
		else if (i == UNBBIN){
			cout << "UNBBIN: " << r[i]<< endl;
		}
		else if (i == CBBIN){
			cout << "CBBIN: " << r[i]<< endl;
		}
		else if (i == UNCBBIN){
			cout << "UNCBBIN: " << r[i]<< endl;
		}
		else if (i == AG){
			cout << "AG: " << r[i]<< endl;
		}
		else if (i == BIN){
			cout << "BIN: " << r[i]<< endl;
		}
		else if (i == UNBIN){
			cout << "UNBIN: " << r[i]<< endl;
		}
		else if (i == BINREV){
			cout << "BINREV: " << r[i]<< endl;
		}
		else if (i == UNBINREV){
			cout << "UNBINREV: " << r[i]<< endl;
		}
		else if (i == BINR){
			cout << "BINR: " << r[i]<< endl;
		}
		else if (i == UNBINR){
			cout << "UNBINR: " << r[i]<< endl;
		}
		else if (i == BINC){
			cout << "BINC: " << r[i]<< endl;
		}
		else if (i == UNBINC){
			cout << "UNBINC: " << r[i]<< endl;
		}
		else if (i == BINREVB){
			cout << "BINREVB: " << r[i]<< endl;
		}
		else if (i == UNBINREVB){
			cout << "UNBINREVB: " << r[i]<< endl;
		}
		else if (i == TMC){
			cout << "TMC: " << r[i]<< endl;
		}
		else if (i == TMCREV){
			cout << "TMCREV: " << r[i]<< endl;
		}
		else if (i == NL){
			cout << "NL: " << r[i]<< endl;
		}
		else if (i == NE){
			cout << "NE: " << r[i]<< endl;
		}
		else if (i == NLREV){
			cout << "NLREV: " << r[i]<< endl;
		}
		else if (i == NEREV){
			cout << "NEREV: " << r[i]<< endl;
		}
		else if (i == LNE){
			cout << "LNE: " << r[i]<< endl;
		}
		else if (i == NLBC){
			cout << "NLBC: " << r[i]<< endl;
		}
		else if (i == HOO){
			cout << "HOO: " << r[i]<< endl;
		}
		else if (i == HTO){
			cout << "HTO: " << r[i]<< endl;
		}
		else if (i == PHOS){
			cout << "PHOS: " << r[i]<< endl;
		}
		else if (i == TRGTO){
			cout << "TRGTO: " << r[i]<< endl;
		}
		else if (i == UGTO){
			cout << "UGTO: " << r[i]<< endl;
		}
		else if (i == NF){
			cout << "NF: " << r[i]<< endl;
		}
		else if (i == URO){
			cout << "URO: " << r[i]<< endl;
		}
		else if (i == URT){
			cout << "URT: " << r[i]<< endl;
		}
		else if (i == UMNP){
			cout << "UMNP: " << r[i]<< endl;
		}
		else if (i == UMPO){
			cout << "UMPO: " << r[i]<< endl;
		}
		else if (i == UMPT){
			cout << "UMPT: " << r[i]<< endl;
		}
		else if (i == UMRO){
			cout << "UMRO: " << r[i]<< endl;
		}
		else if (i == UMRT){
			cout << "UMRT: " << r[i]<< endl;
		}
		else if (i == UB){
			cout << "UB: " << r[i]<< endl;
		}
		else if (i == UC){
			cout << "UC: " << r[i]<< endl;
		}
		else if (i == UBC){
			cout << "UBC: " << r[i]<< endl;
		}

		else if (i == UREV){
			cout << "UREV: " << r[i]<< endl;
		}
		else if (i == UPREV){
			cout << "UPREV: " << r[i]<< endl;
		}
		else if (i == UMB){
			cout << "UMB: " << r[i]<< endl;
		}
		else if (i == UMREV){
			cout << "UMREV: " << r[i]<< endl;
		}
		else if (i == TRPH){
			cout << "TRPH: " << r[i] << endl;
		}
		else if (i == AN){
			cout << "AN: " << r[i] << endl;
		}
		else if (i == DN){
			cout << "DN: " << r[i] << endl;
		}
		else if (i == HOHO){
			cout << "HOHO: " << r[i] << endl;
		}
		else if (i == UMPH){
			cout << "UMPH: " << r[i] << endl;
		}
	}
}

/* Prints out the derivative into a file test_der.txt inside simulation folder
 * Here, derivative means the difference between the first compared to second step concentrations divided by stepsize
 * Output was originally compared with Kim and Forger 2012's code derivative to make sure that we converted 
 * their model correctly.
 * Params: cl: not big_cl
 * Notes: This function should be called in calculate_concentrations in calculation.cpp, at the second step (j == 2)
 * 
 */
void test_derivative(con_levels& cl){
	cout << "Into this function" << endl;
		ofstream test_der_file;
		char filename [50];
		strcpy(filename, "test_der.txt");
		cout << filename << endl;
		char* filename_set = (char*)mallocate(sizeof(char) * ( strlen(filename)));
		sprintf(filename_set, "%s", filename);
		open_file(&test_der_file, filename_set, true);
		free(filename_set);  
		
		for (int i = 0 ; i < NUM_CONS; i ++){
			double derivative = (cl.data[i][1] - cl.data[i][0])/0.001;
			if (i == GRB){
				test_der_file << "GRB_dot is: " << derivative << endl;
			}
			else if (i == G){
				test_der_file << "G_dot is: " << derivative << "\n";
			}
			else if (i == GRSRB){
				test_der_file << "GRSRB_dot is: " << derivative << "\n";
			}
			else if (i == GRS){
				test_der_file << "GRS_dot is: " << derivative << "\n";
			}
			else if (i == GCR){
				test_der_file << "GCR_dot is: " << derivative << "\n";
			}
			else if (i == GC){
				test_der_file << "GC_dot is: " << derivative << "\n"; 
			}
			else if (i == GBR){
				test_der_file << "GBR_dot is: " << derivative << "\n";
			}
			else if (i == GB){
				test_der_file << "GB_dot is: " << derivative << "\n";
			}
			else if (i == GBRB){
				test_der_file << "GBRB_dot is: " << derivative << "\n";
			}
			else if (i == GBB){
				test_der_file << "GBB_dot is: " << derivative << "\n";
			}
			else if (i == MNPO){
				test_der_file << "MNPO_dot is: " << derivative << "\n";
			}
			else if (i == MCPO){
				test_der_file << "MCPO_dot is: " << derivative << "\n";
			}
			else if (i == MNPT){
				test_der_file << "MNPT_dot is: " << derivative << "\n";
			}
			else if (i == MCPT){
				test_der_file << "MCPT_dot is: " << derivative << "\n";
			}
			else if (i == MNRT){
				test_der_file << "MNRT_dot is: " << derivative << "\n";
			}
			else if (i == MCRT){
				test_der_file << "MCRT_dot is: " << derivative << "\n";
			}
			else if (i == MNREV){
				test_der_file << "MNREV_dot is: " << derivative << "\n";
			}
			else if (i == MCREV){
				test_der_file << "MCREV_dot is: " << derivative << "\n";
			}
			else if (i == MNRO){
				test_der_file << "MNRO_dot is: " << derivative << "\n";
			}
			else if (i == MCRO){
				test_der_file << "MCRO_dot is: " << derivative << "\n";
			}
			else if (i == MNB){
				test_der_file << "MNB_dot is: " << derivative << "\n";
			}
			else if (i == MCB){
				test_der_file << "MCB_dot is: " << derivative << "\n";
			}
			else if (i == MNNP){
				test_der_file << "MNNP_dot is: " << derivative << "\n";
			}
			else if (i == MCNP){
				test_der_file << "MCNP_dot is: " << derivative << "\n";
			} 
			else if (i == B){
				test_der_file << "B_dot is: " << derivative << "\n";
			}
			else if (i == CL){
				test_der_file << "CL_dot is: " << derivative << "\n";
			}
			else if (i == BC){
				test_der_file << "BC_dot is: " << derivative << "\n";
			}
			else if (i == CYREV){
				test_der_file << "CYREV_dot is: " << derivative << "\n";
			}
			else if (i == REVN){
				test_der_file << "REVN_dot is: " << derivative << "\n";
			}
			else if (i == CYREVG){
				test_der_file << "CYREVG_dot is: " << derivative << "\n";
			}
			else if (i == REVNG){
				test_der_file << "REVNG_dot is: " << derivative << "\n";
			}
			else if (i == CYREVGP){
				test_der_file << "CYREVGP_dot is: " << derivative << "\n";
			}
			else if (i == REVNGP){
				test_der_file << "REVNGP_dot is: " << derivative << "\n";
			}
			else if (i == CYREVP){
				test_der_file << "CYREVP_dot is: " << derivative << "\n";
			}
			else if (i == REVNP){
				test_der_file << "REVNP_dot is: " << derivative << "\n";
			}
			else if (i == GTO){
				test_der_file << "GTO_dot is: " << derivative << "\n";
			}
			else if (i == X00001){
				test_der_file << "X00001_dot is: " << derivative << "\n";
			}
			else if (i == X00011){
				test_der_file << "X00011_dot is: " << derivative << "\n";
			}
			else if (i == X00100){
				test_der_file << "X00100_dot is: " << derivative << "\n";
			}
			else if (i == X00110){
				test_der_file << "X00110_dot is: " << derivative << "\n";
			}
			else if (i == X00200){
				test_der_file << "X00200_dot is: " << derivative << "\n";
			}
			else if (i == X00210){
				test_der_file << "X00210_dot is: " << derivative << "\n";
			}
			else if (i == X01000){
				test_der_file << "X01000_dot is: " << derivative << "\n";
			}
			else if (i == X01010){
				test_der_file << "X01010_dot is: " << derivative << "\n";
			}
			else if (i == X01011){
				test_der_file << "X01011_dot is: " << derivative << "\n";
			}
			else if (i == X02000){
				test_der_file << "X02000_dot is: " << derivative << "\n";
			}
			else if (i == X02010){
				test_der_file << "X02010_dot is: " << derivative << "\n";
			}
			else if (i == X02011){
				test_der_file << "X02011_dot is: " << derivative << "\n";
			}
			else if (i == X10000){
				test_der_file << "X10000_dot is: " << derivative << "\n";
			}
			else if (i == X10100){
				test_der_file << "X10100_dot is: " << derivative << "\n";
			}
			else if (i == X20000){
				test_der_file << "X20000_dot is: " << derivative << "\n";
			}
			else if (i == X20010){
				test_der_file << "X20010_dot is: " << derivative << "\n";
			}
			else if (i == X20011){
				test_der_file << "X20011_dot is: " << derivative << "\n";
			}
			else if (i == X20100){
				test_der_file << "X20100_dot is: " << derivative << "\n";
			}
			else if (i == X20110){
				test_der_file << "X20110_dot is: " << derivative << "\n";
			}
			else if (i == X20111){
				test_der_file << "X20111_dot is: " << derivative << "\n";
			}
			else if (i == X21000){
				test_der_file << "X21000_dot is: " << derivative << "\n";
			}
			else if (i == X21010){
				test_der_file << "X21010_dot is: " << derivative << "\n";
			}
			else if (i == X21011){
				test_der_file << "X21011_dot is: " << derivative << "\n";
			}
			else if (i == X21100){
				test_der_file << "X21100_dot is: " << derivative << "\n";
			}
			else if (i == X21110){
				test_der_file << "X21110_dot is: " << derivative << "\n";
			}
			else if (i == X21111){
				test_der_file << "X21111_dot is: " << derivative << "\n";
			}
			else if (i == X22000){
				test_der_file << "X22000_dot is: " << derivative << "\n";
			}
			else if (i == X22010){
				test_der_file << "X22010_dot is: " << derivative << "\n";
			}
			else if (i == X22011){
				test_der_file << "X22011_dot is: " << derivative << "\n";
			}
			else if (i == X22100){
				test_der_file << "X22100_dot is: " << derivative << "\n";
			}
			else if (i == X22110){
				test_der_file << "X22110_dot is: " << derivative << "\n";
			}
			else if (i == X22111){
				test_der_file << "X22111_dot is: " << derivative << "\n";
			}
			else if (i == X30000){
				test_der_file << "X30000_dot is: " << derivative << "\n";
			}
			else if (i == X30100){
				test_der_file << "X30100_dot is: " << derivative << "\n";
			}
			else if (i == X30200){
				test_der_file << "X30200_dot is: " << derivative << "\n";
			}
			else if (i == X30300){
				test_der_file << "X30300_dot is: " << derivative << "\n";
			}
			else if (i == X40000){
				test_der_file << "X40000_dot is: " << derivative << "\n";
			}
			else if (i == X40010){
				test_der_file << "X40010_dot is: " << derivative << "\n";
			}
			else if (i == X40011){
				test_der_file << "X40011_dot is: " << derivative << "\n";
			}
			else if (i == X40100){
				test_der_file << "X40100_dot is: " << derivative << "\n";
			}
			else if (i == X40110){
				test_der_file << "X40110_dot is: " << derivative << "\n";
			}
			else if (i == X40111){
				test_der_file << "X40111_dot is: " << derivative << "\n";
			}
			else if (i == X40200){
				test_der_file << "X40200_dot is: " << derivative << "\n";
			}
			else if (i == X40210){
				test_der_file << "X40210_dot is: " << derivative << "\n";
			}
			else if (i == X40211){
				test_der_file << "X40211_dot is: " << derivative << "\n";
			}
			else if (i == X40300){
				test_der_file << "X40300_dot is: " << derivative << "\n";
			}
			else if (i == X40310){
				test_der_file << "X40310_dot is: " << derivative << "\n";
			}
			else if (i == X40311){
				test_der_file << "X40311_dot is: " << derivative << "\n";
			}
			else if (i == X41000){
				test_der_file << "X41000_dot is: " << derivative << "\n";
			}
			else if (i == X41010){
				test_der_file << "X41010_dot is: " << derivative << "\n";
			}
			else if (i == X41011){
				test_der_file << "X41011_dot is: " << derivative << "\n";
			}
			else if (i == X41100){
				test_der_file << "X41100 _dot is: " << derivative << "\n";
			}
			else if (i == X41110){
				test_der_file << "X41110 _dot is: " << derivative << "\n";
			}
			else if (i == X41111){
				test_der_file << "X41111 _dot is: " << derivative << "\n";
			}
			else if (i == X41200){
				test_der_file << "X41200_dot is: " << derivative << "\n";
			}
			else if (i == X41210){
				test_der_file << "X41210_dot is: " << derivative << "\n";
			}
			else if (i == X41211){
				test_der_file << "X41211_dot is: " << derivative << "\n";
			}
			else if (i == X41300){
				test_der_file << "X41300_dot is: " << derivative << "\n";
			}
			else if (i == X41310){
				test_der_file << "X41310_dot is: " << derivative << "\n";
			}
			else if (i == X41311){
				test_der_file << "X41311_dot is: " << derivative << "\n";
			}
			else if (i == X42000){
				test_der_file << "X42000_dot is: " << derivative << "\n";
			}
			else if (i == X42010){
				test_der_file << "X42010_dot is: " << derivative << "\n";
			}
			else if (i == X42011){
				test_der_file << "X42011_dot is: " << derivative << "\n";
			}
			else if (i == X42100){
				test_der_file << "X42100_dot is: " << derivative << "\n";
			}
			else if (i == X42110){
				test_der_file << "X42110_dot is: " << derivative << "\n";
			}
			else if (i == X42111){
				test_der_file << "X42111_dot is: " << derivative << "\n";
			}
			else if (i == X42200){
				test_der_file << "X42200_dot is: " << derivative << "\n";
			}
			else if (i == X42210){
				test_der_file << "X42210_dot is: " << derivative << "\n";
			}
			else if (i == X42210){
				test_der_file << "X42210_dot is: " << derivative << "\n";
			}
			else if (i == X42211){
				test_der_file << "X42211_dot is: " << derivative << "\n";
			}
			else if (i == X42300){
				test_der_file << "X42300_dot is: " << derivative << "\n";
			}
			else if (i == X42310){
				test_der_file << "X42310_dot is: " << derivative << "\n";
			}
			else if (i == X42311){
				test_der_file << "X42311_dot is: " << derivative << "\n";
			}
			else if (i == X50000){
				test_der_file << "X50000_dot is: " << derivative << "\n";
			}
			else if (i == X50010){
				test_der_file << "X50010 _dot is: " << derivative << "\n";
			}
			else if (i == X50011){
				test_der_file << "X50011_dot is: " << derivative << "\n";
			}
			else if (i == X50100){
				test_der_file << "X50100_dot is: " << derivative << "\n";
			}
			else if (i == X50110){
				test_der_file << "X50110 _dot is: " << derivative << "\n";
			}
			else if (i == X50111){
				test_der_file << "X50111_dot is: " << derivative << "\n";
			}
			else if (i == X50200){
				test_der_file << "X50200_dot is: " << derivative << "\n";
			}
			else if (i == X50210){
				test_der_file << "X50210_dot is: " << derivative << "\n";
			}
			else if (i == X50211){
				test_der_file << "X50211_dot is: " << derivative << "\n";
			}
			else if (i == X50300){
				test_der_file << "X50300_dot is: " << derivative << "\n";
			}
			else if (i == X50310){
				test_der_file << "X50310 _dot is: " << derivative << "\n";
			}
			else if (i == X50311){
				test_der_file << "X50311_dot is: " << derivative << "\n";
			}
			else if (i == X51000){
				test_der_file << "X51000_dot is: " << derivative << "\n";
			}
			else if (i == X51010){
				test_der_file << "X51010_dot is: " << derivative << "\n";
			}
			else if (i == X51011){
				test_der_file << "X51011_dot is: " << derivative << "\n";
			}
			else if (i == X51100){
				test_der_file << "X51100_dot is: " << derivative << "\n";
			}
			else if (i == X51110){
				test_der_file << "X51110_dot is: " << derivative << "\n";
			}
			else if (i == X51111){
				test_der_file << "X51111_dot is: " << derivative << "\n";
			}
			else if (i == X51200){
				test_der_file << "X51200_dot is: " << derivative << "\n";
			}
			else if (i == X51210){
				test_der_file << "X51210_dot is: " << derivative << "\n";
			}
			else if (i == X51211){
				test_der_file << "X51211_dot is: " << derivative << "\n";
			}
			else if (i == X51300){
				test_der_file << "X51300_dot is: " << derivative << "\n";
			}
			else if (i == X51310){
				test_der_file << "X51310_dot is: " << derivative << "\n";
			}
			else if (i == X51311){
				test_der_file << "X51311_dot is: " << derivative << "\n";
			}
			else if (i == X52000){
				test_der_file << "X52000_dot is: " << derivative << "\n";
			}
			else if (i == X52010){
				test_der_file << "X52010_dot is: " << derivative << "\n";
			}
			else if (i == X52011){
				test_der_file << "X52011_dot is: " << derivative << "\n";
			}
			else if (i == X52100){
				test_der_file << "X52100_dot is: " << derivative << "\n";
			}
			else if (i == X52110){
				test_der_file << "X52110_dot is: " << derivative << "\n";
			}
			else if (i == X52111){
				test_der_file << "X52111_dot is: " << derivative << "\n";
			}
			else if (i == X52200){
				test_der_file << "X52200_dot is: " << derivative << "\n";
			}
			else if (i == X52210){
				test_der_file << "X52210_dot is: " << derivative << "\n";
			}
			else if (i == X52211){
				test_der_file << "X52211_dot is: " << derivative << "\n";
			}
			else if (i == X52300){
				test_der_file << "X52300_dot is: " << derivative << "\n";
			}
			else if (i == X52310){
				test_der_file << "X52310_dot is: " << derivative << "\n";
			}
			else if (i == X52311){
				test_der_file << "X52311_dot is: " << derivative << "\n";
			}
			else if (i == X60000){
				test_der_file << "X60000_dot is: " << derivative << "\n";
			}
			else if (i == X60010){
				test_der_file << "X60010_dot is: " << derivative << "\n";
			}
			else if (i == X60011){
				test_der_file << "X60011_dot is: " << derivative << "\n";
			}
			else if (i == X60100){
				test_der_file << "X60100_dot is: " << derivative << "\n";
			}
			else if (i == X60110){
				test_der_file << "X60110_dot is: " << derivative << "\n";
			}
			else if (i == X60111){
				test_der_file << "X60111_dot is: " << derivative << "\n";
			}
			else if (i == X60200){
				test_der_file << "X60200_dot is: " << derivative << "\n";
			}
			else if (i == X60210){
				test_der_file << "X60210_dot is: " << derivative << "\n";
			}
			else if (i == X60211){
				test_der_file << "X60211_dot is: " << derivative << "\n";
			}
			else if (i == X60300){
				test_der_file << "X60300 _dot is: " << derivative << "\n";
			}
			else if (i == X60310){
				test_der_file << "X60310_dot is: " << derivative << "\n";
			}
			else if (i == X60311){
				test_der_file << "X60311_dot is: " << derivative << "\n";
			}
			else if (i == X61000){
				test_der_file << "X61000_dot is: " << derivative << "\n";
			}
			else if (i == X61010){
				test_der_file << "X61010_dot is: " << derivative << "\n";
			}
			else if (i == X61011){
				test_der_file << "X61011_dot is: " << derivative << "\n";
			}
			else if (i == X61100){
				test_der_file << "X61100_dot is: " << derivative << "\n";
			}
			else if (i == X61110){
				test_der_file << "X61110_dot is: " << derivative << "\n";
			}
			else if (i == X61111){
				test_der_file << "X61111_dot is: " << derivative << "\n";
			}
			else if (i == X61200){
				test_der_file << "X61200_dot is: " << derivative << "\n";
			}
			else if (i == X61210){
				test_der_file << "X61210_dot is: " << derivative << "\n";
			}
			else if (i == X61211){
				test_der_file << "X61211_dot is: " << derivative << "\n";
			}
			else if (i == X61300){
				test_der_file << "X61300_dot is: " << derivative << "\n";
			}
			else if (i == X61310){
				test_der_file << "X61310_dot is: " << derivative << "\n";
			}
			else if (i == X61311){
				test_der_file << "X61311_dot is: " << derivative << "\n";
			}
			else if (i == X62000){
				test_der_file << "X62000_dot is: " << derivative << "\n";
			}
			else if (i == X62010){
				test_der_file << "X62010_dot is: " << derivative << "\n";
			}
			else if (i == X62011){
				test_der_file << "X62011 _dot is: " << derivative << "\n";
			}
			else if (i == X62100){
				test_der_file << "X62100_dot is: " << derivative << "\n";
			}
			else if (i == X62110){
				test_der_file << "X62110_dot is: " << derivative << "\n";
			}
			else if (i == X62111){
				test_der_file << "X62111 _dot is: " << derivative << "\n";
			}
			else if (i == X62200){
				test_der_file << "X62200_dot is: " << derivative << "\n";
			}
			else if (i == X62210){
				test_der_file << "X62210_dot is: " << derivative << "\n";
			}
			else if (i == X62211){
				test_der_file << "X62211_dot is: " << derivative << "\n";
			}
			else if (i == X62300){
				test_der_file << "X62300_dot is: " << derivative << "\n";
			}
			else if (i == X62310){
				test_der_file << "X62310_dot is: " << derivative << "\n";
			}
			else if (i == X62311){
				test_der_file << "X62311_dot is: " << derivative << "\n";
			}
		}
		close_if_open(&test_der_file);
}
