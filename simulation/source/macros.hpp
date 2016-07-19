#ifndef MACROS_HPP
#define MACROS_HPP

#include <math.h>

#define GRB			0	//prob of per1, per2 and cry1 E-box being represssed (In literature: GR (R big))
#define	G			1	//prob of per1, per2 and cry1 E-box being activated
#define GRSRB		2 	//prob of rev-erbs E-box repressed (In literature: GrR)
#define GRS			3	//prob of rev-erbs E-box activated (In literature: Gr (r small))
#define GCR			4	//prob of cry2 E-box Repressed
#define GC			5	//prob of cry2 E-box activated
#define	GBR			6	//prob of cry1 RORE repressed
#define	GB			7	//prob of cry1 RORE activated
#define GBRB		8	//prob of Bmals RORE repressed
#define GBB			9	//prob of Bmals RORE activated
#define MNPO		10	//Per1mRNA in nu 
#define MCPO		11	//Per1mRNA in cy
#define	MNPT		12	//Per2mRNA in nu
#define MCPT		13	//Per2mRNA in cy
#define MNRT		14	//cry2mRNA in nu
#define MCRT		15	//cry2mRNA in cy
#define MNREV		16	//Rev-erbs mRNA in nu
#define MCREV		17	//Rev-erbs mRNA in cy
#define	MNRO		18	//cry1mRNA in nu
#define MCRO		19	//cry1mRNA in cy
#define MNB			20	//Bmals mRNA in nu
#define	MCB			21	//Bmals mRNA in cy
#define MNNP		22	//Npas2 mRNA in nu
#define MCNP		23	//Npas2 mRNA in cy
#define B			24 	//Bmals protein in cy
#define CL 			25	//Clock/NPAS2 protein in cy
#define	BC			26	//unphosphorylated Bmals-Clock/NPAS2 
#define CYREV		27	//unphosphorylated rev-erbs in cy
#define REVN		28	//unphosphorylated rev-erbs in nu
#define CYREVG		29	//unphosphorylated rev-erbs bound with GSK3beta in cy
#define	REVNG		30	//unphosphorylated rev-erbs bound with GSK3beta in nu
#define	CYREVGP		31	//phosphorylated rev-erbs bound with GSK3beta in cy
#define REVNGP		32	//phosphorylated rev-erbs bound with GSK3beta in nu
#define CYREVP		33	//phosphorylated rev-erbs in cy
#define REVNP		34	//phosphorylated rev-erbs in nu
#define GTO			35	//activity of GSK3beta
#define X00001		36	//no per, no cry, no kinases, phosphorylated Bmals--- phosphorylated CLK in cy
#define	X00011		37	//no per no cry no kinases p Bmals--pCLK in nu
#define	X00100		38	//no per no cry CKI no pBmal-pCLK in cy
#define	X00110		39
#define	X00200		40
#define	X00210		41
#define	X01000		42
#define	X01010		43
#define	X01011		44
#define X02000		45
#define	X02010		46
#define	X02011		47
#define	X10000		48
#define	X10100		49	
#define	X20000		50
#define	X20010		51
#define	X20011		52
#define	X20100		53	
#define	X20110		54	
#define	X20111		55
#define	X21000		56
#define	X21010		57
#define	X21011		58
#define	X21100		59
#define	X21110		60
#define	X21111		61
#define	X22000		62
#define	X22010		63
#define	X22011		64
#define X22100		65
#define X22110		66
#define	X22111		67
#define	X30000		68
#define	X30100		69
#define	X30200		70	
#define	X30300		71
#define	X40000		72
#define	X40010		73
#define	X40011		74	
#define	X40100		75
#define	X40110		76
#define	X40111		77
#define	X40200		78
#define	X40210		79	
#define	X40211		80
#define	X40300		81
#define	X40310		82
#define	X40311		83
#define	X41000		84
#define	X41010		85
#define	X41011		86
#define	X41100		87
#define	X41110		88
#define	X41111		89
#define	X41200		90	
#define	X41210		91
#define	X41211		92
#define	X41300		93
#define	X41310		94
#define	X41311		95
#define	X42000		96
#define	X42010		97
#define	X42011		98
#define	X42100		99
#define	X42110		100
#define	X42111		101
#define	X42200		102
#define	X42210		103
#define	X42211		104
#define	X42300		105
#define	X42310		106
#define	X42311		107
#define	X50000		108
#define	X50010		109
#define	X50011		110
#define	X50100		111
#define	X50110		112
#define	X50111		113
#define	X50200		114
#define	X50210		115
#define	X50211		116
#define	X50300		117
#define	X50310		118
#define	X50311		119
#define	X51000		120
#define	X51010		121
#define	X51011		122
#define	X51100		123
#define	X51110		124
#define	X51111		125
#define	X51200		126
#define	X51210		127
#define	X51211		128
#define	X51300		129
#define	X51310		130
#define	X51311		131
#define	X52000		132
#define	X52010		133
#define	X52011		134
#define	X52100		135
#define	X52110		136
#define	X52111		137
#define	X52200		138
#define	X52210		139
#define	X52211		140
#define	X52300		141
#define	X52310		142
#define	X52311		143
#define	X60000		144
#define	X60010		145
#define	X60011		146
#define	X60100		147
#define	X60110		148
#define	X60111		149
#define	X60200		150
#define	X60210		151
#define	X60211		152
#define	X60300		153
#define	X60310		154
#define	X60311		155
#define	X61000		156
#define	X61010		157
#define	X61011		158
#define	X61100		159
#define	X61110		160
#define	X61111		161
#define	X61200		162
#define	X61210		163
#define	X61211		164
#define	X61300		165
#define	X61310		166
#define	X61311		167
#define	X62000		168
#define	X62010		169
#define	X62011		170
#define	X62100		171
#define	X62110		172
#define	X62111		173
#define	X62200		174
#define	X62210		175
#define	X62211		176
#define	X62300		177
#define	X62310		178
#define	X62311		179

///////ADDED STATES COMPARED TO KIM AND FORGER'S MODEL
#define MNPH		180	// mPer3 in nu
#define MCPH		181	// mPer3 in cy
#define GPH			182	// Prob of Per3 D-box activation
#define	GPHR		183	// Prob of Per3 D-box repression
#define	X70000		184	// PER3 in cy
#define	X80000		185	// PER1-PER3 in cy
#define	X80100		186	// PER1-PER3-CKI in cy
#define	X90000		187	// PER1-PER3* in cy
#define	X90010		188	// PER1-PER3* in nu
#define	X90011		189	// PER1-PER3*-BMAL-CLK/NPAS2 in nu
#define X90100		190
#define X90110		191
#define X90111		192
#define XA0000		193
#define	XA0010		194
#define	XA0011		195
#define	XA1010		196
#define	XA1011		197
#define	XA2010		198
#define	XA2011		199
#define GPOR		200	// prob of Per1 E-box repression
#define GPO			201	// prob of Per1 E-box activation
#define GPTR		202	// prob of Per2 E-box repression
#define GPT			203	// prob of Per2 E-box activation
#define GBN			204	// prob of Npas2 RORE activated
#define GBRN		205	// prob of Npas2 RORE repressed
#define X01002		206 
#define X02002		207

#define NUM_CONS		208	//total number of things (mRNA, protein, complexes) in the system

#define NUM_FEATURE_CONS	202
		
		
#define	TRPO		0	//transcription rate for Per1. 
#define	TRPT		1	//Transcription rate for Per2.
#define	TRRO		2	//Transcription rate for Cry1
#define	TRRT		3	//Transcription rate for Cry2
#define	TRB			4	//Transcription rate for Bmal
#define	TRREV		5	//Transcription rate for Rev-erbs
#define TRNP		6	//Transcription rate for Npas2
#define	TLPO		7	//Translation rate for PER1
#define	TLRO		8	//Translation rate for CRY1
#define	TLB			9	//Translation rate for Bmal
#define	TLREV		10	//Translation rate for Rev-erbs
#define	TLC			11	//Translation rate for Clock
#define	TLNP		12	//Translation rate for NPAS2	
#define	AGP			13	//Binding rate for Per2-GSK3Beta
#define	DG			14	//Binding rate for Per2/Rev-erbs to GSK3Beta
#define	AC			15	//Binding rate for Per1/2-CKIepsilon/delta
#define	DC			16	//Unbinding rate for Per1/2-CKIepsilon/delta
#define	AR			17	//Binding rate for Per1/2-Cry1/2
#define	DR			18	//Unbinding rate for Per1/2-Cry1/2
#define	CBIN		19	//Binding rate for Bmal to clock/Npas2
#define	UNCBIN		20	//unbinidng rate for Bmal to Clock/Npas2
#define	BBIN		21	//Binding rate Per1/2to Bmal-Clock/Npas2
#define	UNBBIN		22	//Unbinding rate for  Per1/2to Bmal-Clock/Npas2
#define	CBBIN		23	//Binding rate for Cry1/2 to Bmal-Clock/Npas2
#define	UNCBBIN		24	//Unbinding rate for Cry1/2 to Bmal-Clock/Npas2
#define	AG			25	//Binding rate for Rev-erbs to GSK3Beta
#define	BIN			26	//Normalized binding rate for Bmal-Clock/Npas2 to Per1/2/Cry1 Ebox
#define	UNBIN		27	//Normalized unbinding rate for Bmal-Clock/Npas2 to Per1/2/Cry1 Ebox
#define	BINREV		28	//Normalized binding rate Rev-erbs to Cry1/Npas2 RORE
#define	UNBINREV 	29	//Normalized unbinding rate ------
#define	BINR		30	//Normalized binding rate Bmal-Clock/Npas2 to Rev-erbs Ebox
#define	UNBINR		31	//Normalized Unbinding rate Bmal-Clock/Npas2 to Rev-erbs Ebox
#define	BINC		32	//Normalized binding rate for Bmal-Clock/Npas2 to Cry2 ebox
#define	UNBINC		33	//Normalized unbinding rate for Bmal-Clock/Npas2 to Cry2 ebox
#define	BINREVB		34	//Normalized binding rate Rev-erbs to Bmal RORE
#define	UNBINREVB	35	//Normalized unbinding rate Rev-erbs to Bmal RORE
#define	TMC			36	//Rate for folding and nuclear export of Per1/2, Cry1/2, Bnak, Npas2 and mRNA
#define	TMCREV		37	//Folding and nu export of Rev-erbs mRNA	
#define	NL			38	//Nuclear localization rate for proteins bound to Per
#define	NE			39	//nucleat export rate for Protein boudn to Per
#define	NLREV		40	//Nuclear localization rate Rev-erbs and GSK3beta if bound
#define	NEREV		41	//Nu export rate Rev-erbs as well as GSK3beat if bound
#define	LNE			42	//nu export rate for unbound kinases GSK3beta and CKI
#define	NLBC		43	//Nu localization rate Bmal-clock/Npas2
#define	HOO			44	//CKE epsilon/delta phosphorylation rate Per1
#define	HTO			45	//---------------------------------------Per2
#define	PHOS		46	//Phos--- rate Bmal-Clock/Npas2
#define	TRGTO		47	//increate rate GSK3beta activity
#define	UGTO		48	//decrease-----------------------
#define	NF			49	//ratio of cy and nu compartment volume
#define	UPO			50	//-----------------CKI phosphorylated PER1
#define	URO			51	//-----------------CRY1
#define	URT			52	//-----------------CRY2
#define	UMNP		53	//-----------------Npas2
#define	UMPO		54	//Degradation rate Per1
#define	UMPT		55	//-----------------Per2
#define	UMRO		56	//-----------------Cry1
#define	UMRT		57	//-----------------Cry2
#define	UB			58	//-----------------BMAL
#define	UC			59	//-----------------CLOCK/NPAS2
#define	UBC			60	//-----------------BMAL-CLOCK/NPAS2
#define	UPUO		61	//-----------------unphosphorylated Per1
#define	UREV		62	//-----------------unphosphorylated REV_ERBS
#define	UPREV		63	//-----------------GSK3beta phosphorylated REV_ERBS
#define	UMB			64	//-----------------Bmal
#define	UMREV		65	//-----------------Rev-erbs

///////////ADDED PARAMETERS COMPARED TO KIM AND FORGER'S MODEL
#define TRPH		66	//This rates gets knocked out in Per3_knock out mutant. Any change to TRPH needs to be copied to P3_KN_INDEX
#define AN			67
#define DN			68
#define HOHO		69
#define UMPH		70
#define BINPO		71
#define UNBINPO		72
#define	BINPT		73
#define UNBINPT		74
#define BINPH		75
#define UNBINPH		76
#define BINREVN		77
#define UNBINREVN	78
#define UPTC		79 //degradation of CKI-phosphorylated PER2
#define UPUT		80 //degradation of unphosphorylated PER2
#define UPTG		81 //degradation of GSK-phosphorylated PER2
#define UPTCG		82 //degradation of CKI- and GSK-phosphorylated PER2
#define UPH			83 //degradation of CKI-phosphorylated PER3
#define UPUH		84 //degradation of unphosphorylated PER3
#define UPUOH		85 //degradation of unphosphorylated PER1-PER3
#define UPOH		86 //degradation of CKI-phosphorylated PER1-PER3
#define TLPT		87 //translation of PER2
#define TLPH		88 //translation of PER3
#define TLRT		89 //translation of CRY2
#define BINCRYB		90 //Binding of CRY-unphosphorylated BMAL-CLK
#define UNBINCRYB	91 //Unbinding of CRY-unphosphorylated BMAL-CLK

#define NUM_RATES	92

// Macros for commonly used functions small enough to inject directly into the code
#define INT_STRLEN(x) (log10((x) > 0 ? (x) : 1) + 1)

// Macros for testing peaks and troughs
#define MAX_PEAK_TROUGH			10

// Macros for filenames
#define WT_FNAME				"wildtype.txt"
#define P1_FNAME				"per1Knockout.txt"
#define P2_FNAME				"per2Knockout.txt"
#define P3_FNAME				"per3Knockout.txt"

// Macros for mutant index
#define	WT						0
#define	P1						1
#define	P2						2
#define	P3						3
#define C1						4
#define	C2						5
#define BM						6
#define NP						7
#define C1C2					8
#define NUM_SCN_MUTANTS			9

#define P2C1					9
#define P2C2					10
#define	R						11
#define NUM_MUTANTS				12

// Macros about the cell type
#define SCN						0
#define	FIB						1
#define MAX_TYPE				2

// Macros about maximum score of a cell
#define MAX_WT_SCN				6
#define MAX_P1_SCN				5
#define MAX_P2_SCN				1
#define MAX_P3_SCN				5
#define MAX_C1_SCN				2
#define MAX_C2_SCN				2
#define MAX_BM_SCN				1
#define MAX_NP_SCN				4
#define MAX_C1C2_SCN			1
#define MAX_P2C1_SCN			0
#define MAX_P2C2_SCN			0
#define MAX_R_SCN				0
#define MAX_SCN					27

#define MAX_WT_FIB				6
#define MAX_P1_FIB				5
#define MAX_P2_FIB				1
#define MAX_P3_FIB				2
#define MAX_C1_FIB				2
#define MAX_C2_FIB				3
#define MAX_BM_FIB				1
#define MAX_NP_FIB				4
#define MAX_C1C2_FIB			1
#define MAX_P2C1_FIB			1
#define MAX_P2C2_FIB			1
#define MAX_R_FIB				1
#define MAX_FIB					28

// Macros about max score for different behaviors
#define MAX_SUSTAINED_OSC_BEH	2
#define MAX_WT_BEH				4

// Macros for to test the bounds of period for sustained oscilation	
#define LOW_BOUND_NUM_PERIOD	3	// At least how many periods do we need to see in 100 hours of simulation
#define LOW_BOUND_NUM_AMP		3
#define MIN_PERIOD_SCN			23.8
#define MAX_PERIOD_SCN			24.6
#define MIN_PERIOD_FIB			23	
#define MAX_PERIOD_FIB			25
 
// Macros to check the error of period of wildtype behavior
#define LOW_WT_PER_ERROR		0.99
#define UP_WT_PER_ERROR			1.01

// Macros to check the error of amplitude of wildtype behavior
#define LOW_WT_AMP_ERROR		0.9
#define UP_WT_AMP_ERROR			1.1

// Macros to check the shorter/longer period/amplitude behavior
#define SHORT_PER_FACTOR		0.98
#define	LONG_PER_FACTOR			1.02
#define SHORT_AMP_FACTOR		0.75
#define LONG_AMP_FACTOR			1.25
#define SHORT_PER_THRES			3
#define LONG_PER_THRES			3

// Macros for shorter/longer period/ amplitude behavior for specific cases
#define SCN_C1_P2_SHORT_PER		1.2
#define SCN_C2_P2_LONG_PER		1.2
#define FIB_C2_P2_LONG_PER		1.8
#define FIB_P3_P2_SHORT_PER		1.5

// Macros to check arythimic behavior
#define LOW_AR_MID_LAST_RATIO	1.5

// Macros for bounds of ratio for period and amplitude between first, middle, last
#define LOW_BOUND_P2T			1.5
#define LOW_BOUND_M2L			0.5
#define	UP_BOUND_M2L			1.2

// Weight to calculate score
#define WEIGHT_CONDITIONS		0.8
#define WEIGHT_COST				0.2
// Exit statuses
#define EXIT_SUCCESS			0
#define EXIT_MEMORY_ERROR		1
#define EXIT_FILE_READ_ERROR	2
#define EXIT_FILE_WRITE_ERROR	3
#define EXIT_PIPE_READ_ERROR	4
#define EXIT_PIPE_WRITE_ERROR	5
#define EXIT_INPUT_ERROR		6

#endif
