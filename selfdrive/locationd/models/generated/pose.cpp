#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_297086807638649028) {
   out_297086807638649028[0] = delta_x[0] + nom_x[0];
   out_297086807638649028[1] = delta_x[1] + nom_x[1];
   out_297086807638649028[2] = delta_x[2] + nom_x[2];
   out_297086807638649028[3] = delta_x[3] + nom_x[3];
   out_297086807638649028[4] = delta_x[4] + nom_x[4];
   out_297086807638649028[5] = delta_x[5] + nom_x[5];
   out_297086807638649028[6] = delta_x[6] + nom_x[6];
   out_297086807638649028[7] = delta_x[7] + nom_x[7];
   out_297086807638649028[8] = delta_x[8] + nom_x[8];
   out_297086807638649028[9] = delta_x[9] + nom_x[9];
   out_297086807638649028[10] = delta_x[10] + nom_x[10];
   out_297086807638649028[11] = delta_x[11] + nom_x[11];
   out_297086807638649028[12] = delta_x[12] + nom_x[12];
   out_297086807638649028[13] = delta_x[13] + nom_x[13];
   out_297086807638649028[14] = delta_x[14] + nom_x[14];
   out_297086807638649028[15] = delta_x[15] + nom_x[15];
   out_297086807638649028[16] = delta_x[16] + nom_x[16];
   out_297086807638649028[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_9032889632036866791) {
   out_9032889632036866791[0] = -nom_x[0] + true_x[0];
   out_9032889632036866791[1] = -nom_x[1] + true_x[1];
   out_9032889632036866791[2] = -nom_x[2] + true_x[2];
   out_9032889632036866791[3] = -nom_x[3] + true_x[3];
   out_9032889632036866791[4] = -nom_x[4] + true_x[4];
   out_9032889632036866791[5] = -nom_x[5] + true_x[5];
   out_9032889632036866791[6] = -nom_x[6] + true_x[6];
   out_9032889632036866791[7] = -nom_x[7] + true_x[7];
   out_9032889632036866791[8] = -nom_x[8] + true_x[8];
   out_9032889632036866791[9] = -nom_x[9] + true_x[9];
   out_9032889632036866791[10] = -nom_x[10] + true_x[10];
   out_9032889632036866791[11] = -nom_x[11] + true_x[11];
   out_9032889632036866791[12] = -nom_x[12] + true_x[12];
   out_9032889632036866791[13] = -nom_x[13] + true_x[13];
   out_9032889632036866791[14] = -nom_x[14] + true_x[14];
   out_9032889632036866791[15] = -nom_x[15] + true_x[15];
   out_9032889632036866791[16] = -nom_x[16] + true_x[16];
   out_9032889632036866791[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5386858994733697605) {
   out_5386858994733697605[0] = 1.0;
   out_5386858994733697605[1] = 0.0;
   out_5386858994733697605[2] = 0.0;
   out_5386858994733697605[3] = 0.0;
   out_5386858994733697605[4] = 0.0;
   out_5386858994733697605[5] = 0.0;
   out_5386858994733697605[6] = 0.0;
   out_5386858994733697605[7] = 0.0;
   out_5386858994733697605[8] = 0.0;
   out_5386858994733697605[9] = 0.0;
   out_5386858994733697605[10] = 0.0;
   out_5386858994733697605[11] = 0.0;
   out_5386858994733697605[12] = 0.0;
   out_5386858994733697605[13] = 0.0;
   out_5386858994733697605[14] = 0.0;
   out_5386858994733697605[15] = 0.0;
   out_5386858994733697605[16] = 0.0;
   out_5386858994733697605[17] = 0.0;
   out_5386858994733697605[18] = 0.0;
   out_5386858994733697605[19] = 1.0;
   out_5386858994733697605[20] = 0.0;
   out_5386858994733697605[21] = 0.0;
   out_5386858994733697605[22] = 0.0;
   out_5386858994733697605[23] = 0.0;
   out_5386858994733697605[24] = 0.0;
   out_5386858994733697605[25] = 0.0;
   out_5386858994733697605[26] = 0.0;
   out_5386858994733697605[27] = 0.0;
   out_5386858994733697605[28] = 0.0;
   out_5386858994733697605[29] = 0.0;
   out_5386858994733697605[30] = 0.0;
   out_5386858994733697605[31] = 0.0;
   out_5386858994733697605[32] = 0.0;
   out_5386858994733697605[33] = 0.0;
   out_5386858994733697605[34] = 0.0;
   out_5386858994733697605[35] = 0.0;
   out_5386858994733697605[36] = 0.0;
   out_5386858994733697605[37] = 0.0;
   out_5386858994733697605[38] = 1.0;
   out_5386858994733697605[39] = 0.0;
   out_5386858994733697605[40] = 0.0;
   out_5386858994733697605[41] = 0.0;
   out_5386858994733697605[42] = 0.0;
   out_5386858994733697605[43] = 0.0;
   out_5386858994733697605[44] = 0.0;
   out_5386858994733697605[45] = 0.0;
   out_5386858994733697605[46] = 0.0;
   out_5386858994733697605[47] = 0.0;
   out_5386858994733697605[48] = 0.0;
   out_5386858994733697605[49] = 0.0;
   out_5386858994733697605[50] = 0.0;
   out_5386858994733697605[51] = 0.0;
   out_5386858994733697605[52] = 0.0;
   out_5386858994733697605[53] = 0.0;
   out_5386858994733697605[54] = 0.0;
   out_5386858994733697605[55] = 0.0;
   out_5386858994733697605[56] = 0.0;
   out_5386858994733697605[57] = 1.0;
   out_5386858994733697605[58] = 0.0;
   out_5386858994733697605[59] = 0.0;
   out_5386858994733697605[60] = 0.0;
   out_5386858994733697605[61] = 0.0;
   out_5386858994733697605[62] = 0.0;
   out_5386858994733697605[63] = 0.0;
   out_5386858994733697605[64] = 0.0;
   out_5386858994733697605[65] = 0.0;
   out_5386858994733697605[66] = 0.0;
   out_5386858994733697605[67] = 0.0;
   out_5386858994733697605[68] = 0.0;
   out_5386858994733697605[69] = 0.0;
   out_5386858994733697605[70] = 0.0;
   out_5386858994733697605[71] = 0.0;
   out_5386858994733697605[72] = 0.0;
   out_5386858994733697605[73] = 0.0;
   out_5386858994733697605[74] = 0.0;
   out_5386858994733697605[75] = 0.0;
   out_5386858994733697605[76] = 1.0;
   out_5386858994733697605[77] = 0.0;
   out_5386858994733697605[78] = 0.0;
   out_5386858994733697605[79] = 0.0;
   out_5386858994733697605[80] = 0.0;
   out_5386858994733697605[81] = 0.0;
   out_5386858994733697605[82] = 0.0;
   out_5386858994733697605[83] = 0.0;
   out_5386858994733697605[84] = 0.0;
   out_5386858994733697605[85] = 0.0;
   out_5386858994733697605[86] = 0.0;
   out_5386858994733697605[87] = 0.0;
   out_5386858994733697605[88] = 0.0;
   out_5386858994733697605[89] = 0.0;
   out_5386858994733697605[90] = 0.0;
   out_5386858994733697605[91] = 0.0;
   out_5386858994733697605[92] = 0.0;
   out_5386858994733697605[93] = 0.0;
   out_5386858994733697605[94] = 0.0;
   out_5386858994733697605[95] = 1.0;
   out_5386858994733697605[96] = 0.0;
   out_5386858994733697605[97] = 0.0;
   out_5386858994733697605[98] = 0.0;
   out_5386858994733697605[99] = 0.0;
   out_5386858994733697605[100] = 0.0;
   out_5386858994733697605[101] = 0.0;
   out_5386858994733697605[102] = 0.0;
   out_5386858994733697605[103] = 0.0;
   out_5386858994733697605[104] = 0.0;
   out_5386858994733697605[105] = 0.0;
   out_5386858994733697605[106] = 0.0;
   out_5386858994733697605[107] = 0.0;
   out_5386858994733697605[108] = 0.0;
   out_5386858994733697605[109] = 0.0;
   out_5386858994733697605[110] = 0.0;
   out_5386858994733697605[111] = 0.0;
   out_5386858994733697605[112] = 0.0;
   out_5386858994733697605[113] = 0.0;
   out_5386858994733697605[114] = 1.0;
   out_5386858994733697605[115] = 0.0;
   out_5386858994733697605[116] = 0.0;
   out_5386858994733697605[117] = 0.0;
   out_5386858994733697605[118] = 0.0;
   out_5386858994733697605[119] = 0.0;
   out_5386858994733697605[120] = 0.0;
   out_5386858994733697605[121] = 0.0;
   out_5386858994733697605[122] = 0.0;
   out_5386858994733697605[123] = 0.0;
   out_5386858994733697605[124] = 0.0;
   out_5386858994733697605[125] = 0.0;
   out_5386858994733697605[126] = 0.0;
   out_5386858994733697605[127] = 0.0;
   out_5386858994733697605[128] = 0.0;
   out_5386858994733697605[129] = 0.0;
   out_5386858994733697605[130] = 0.0;
   out_5386858994733697605[131] = 0.0;
   out_5386858994733697605[132] = 0.0;
   out_5386858994733697605[133] = 1.0;
   out_5386858994733697605[134] = 0.0;
   out_5386858994733697605[135] = 0.0;
   out_5386858994733697605[136] = 0.0;
   out_5386858994733697605[137] = 0.0;
   out_5386858994733697605[138] = 0.0;
   out_5386858994733697605[139] = 0.0;
   out_5386858994733697605[140] = 0.0;
   out_5386858994733697605[141] = 0.0;
   out_5386858994733697605[142] = 0.0;
   out_5386858994733697605[143] = 0.0;
   out_5386858994733697605[144] = 0.0;
   out_5386858994733697605[145] = 0.0;
   out_5386858994733697605[146] = 0.0;
   out_5386858994733697605[147] = 0.0;
   out_5386858994733697605[148] = 0.0;
   out_5386858994733697605[149] = 0.0;
   out_5386858994733697605[150] = 0.0;
   out_5386858994733697605[151] = 0.0;
   out_5386858994733697605[152] = 1.0;
   out_5386858994733697605[153] = 0.0;
   out_5386858994733697605[154] = 0.0;
   out_5386858994733697605[155] = 0.0;
   out_5386858994733697605[156] = 0.0;
   out_5386858994733697605[157] = 0.0;
   out_5386858994733697605[158] = 0.0;
   out_5386858994733697605[159] = 0.0;
   out_5386858994733697605[160] = 0.0;
   out_5386858994733697605[161] = 0.0;
   out_5386858994733697605[162] = 0.0;
   out_5386858994733697605[163] = 0.0;
   out_5386858994733697605[164] = 0.0;
   out_5386858994733697605[165] = 0.0;
   out_5386858994733697605[166] = 0.0;
   out_5386858994733697605[167] = 0.0;
   out_5386858994733697605[168] = 0.0;
   out_5386858994733697605[169] = 0.0;
   out_5386858994733697605[170] = 0.0;
   out_5386858994733697605[171] = 1.0;
   out_5386858994733697605[172] = 0.0;
   out_5386858994733697605[173] = 0.0;
   out_5386858994733697605[174] = 0.0;
   out_5386858994733697605[175] = 0.0;
   out_5386858994733697605[176] = 0.0;
   out_5386858994733697605[177] = 0.0;
   out_5386858994733697605[178] = 0.0;
   out_5386858994733697605[179] = 0.0;
   out_5386858994733697605[180] = 0.0;
   out_5386858994733697605[181] = 0.0;
   out_5386858994733697605[182] = 0.0;
   out_5386858994733697605[183] = 0.0;
   out_5386858994733697605[184] = 0.0;
   out_5386858994733697605[185] = 0.0;
   out_5386858994733697605[186] = 0.0;
   out_5386858994733697605[187] = 0.0;
   out_5386858994733697605[188] = 0.0;
   out_5386858994733697605[189] = 0.0;
   out_5386858994733697605[190] = 1.0;
   out_5386858994733697605[191] = 0.0;
   out_5386858994733697605[192] = 0.0;
   out_5386858994733697605[193] = 0.0;
   out_5386858994733697605[194] = 0.0;
   out_5386858994733697605[195] = 0.0;
   out_5386858994733697605[196] = 0.0;
   out_5386858994733697605[197] = 0.0;
   out_5386858994733697605[198] = 0.0;
   out_5386858994733697605[199] = 0.0;
   out_5386858994733697605[200] = 0.0;
   out_5386858994733697605[201] = 0.0;
   out_5386858994733697605[202] = 0.0;
   out_5386858994733697605[203] = 0.0;
   out_5386858994733697605[204] = 0.0;
   out_5386858994733697605[205] = 0.0;
   out_5386858994733697605[206] = 0.0;
   out_5386858994733697605[207] = 0.0;
   out_5386858994733697605[208] = 0.0;
   out_5386858994733697605[209] = 1.0;
   out_5386858994733697605[210] = 0.0;
   out_5386858994733697605[211] = 0.0;
   out_5386858994733697605[212] = 0.0;
   out_5386858994733697605[213] = 0.0;
   out_5386858994733697605[214] = 0.0;
   out_5386858994733697605[215] = 0.0;
   out_5386858994733697605[216] = 0.0;
   out_5386858994733697605[217] = 0.0;
   out_5386858994733697605[218] = 0.0;
   out_5386858994733697605[219] = 0.0;
   out_5386858994733697605[220] = 0.0;
   out_5386858994733697605[221] = 0.0;
   out_5386858994733697605[222] = 0.0;
   out_5386858994733697605[223] = 0.0;
   out_5386858994733697605[224] = 0.0;
   out_5386858994733697605[225] = 0.0;
   out_5386858994733697605[226] = 0.0;
   out_5386858994733697605[227] = 0.0;
   out_5386858994733697605[228] = 1.0;
   out_5386858994733697605[229] = 0.0;
   out_5386858994733697605[230] = 0.0;
   out_5386858994733697605[231] = 0.0;
   out_5386858994733697605[232] = 0.0;
   out_5386858994733697605[233] = 0.0;
   out_5386858994733697605[234] = 0.0;
   out_5386858994733697605[235] = 0.0;
   out_5386858994733697605[236] = 0.0;
   out_5386858994733697605[237] = 0.0;
   out_5386858994733697605[238] = 0.0;
   out_5386858994733697605[239] = 0.0;
   out_5386858994733697605[240] = 0.0;
   out_5386858994733697605[241] = 0.0;
   out_5386858994733697605[242] = 0.0;
   out_5386858994733697605[243] = 0.0;
   out_5386858994733697605[244] = 0.0;
   out_5386858994733697605[245] = 0.0;
   out_5386858994733697605[246] = 0.0;
   out_5386858994733697605[247] = 1.0;
   out_5386858994733697605[248] = 0.0;
   out_5386858994733697605[249] = 0.0;
   out_5386858994733697605[250] = 0.0;
   out_5386858994733697605[251] = 0.0;
   out_5386858994733697605[252] = 0.0;
   out_5386858994733697605[253] = 0.0;
   out_5386858994733697605[254] = 0.0;
   out_5386858994733697605[255] = 0.0;
   out_5386858994733697605[256] = 0.0;
   out_5386858994733697605[257] = 0.0;
   out_5386858994733697605[258] = 0.0;
   out_5386858994733697605[259] = 0.0;
   out_5386858994733697605[260] = 0.0;
   out_5386858994733697605[261] = 0.0;
   out_5386858994733697605[262] = 0.0;
   out_5386858994733697605[263] = 0.0;
   out_5386858994733697605[264] = 0.0;
   out_5386858994733697605[265] = 0.0;
   out_5386858994733697605[266] = 1.0;
   out_5386858994733697605[267] = 0.0;
   out_5386858994733697605[268] = 0.0;
   out_5386858994733697605[269] = 0.0;
   out_5386858994733697605[270] = 0.0;
   out_5386858994733697605[271] = 0.0;
   out_5386858994733697605[272] = 0.0;
   out_5386858994733697605[273] = 0.0;
   out_5386858994733697605[274] = 0.0;
   out_5386858994733697605[275] = 0.0;
   out_5386858994733697605[276] = 0.0;
   out_5386858994733697605[277] = 0.0;
   out_5386858994733697605[278] = 0.0;
   out_5386858994733697605[279] = 0.0;
   out_5386858994733697605[280] = 0.0;
   out_5386858994733697605[281] = 0.0;
   out_5386858994733697605[282] = 0.0;
   out_5386858994733697605[283] = 0.0;
   out_5386858994733697605[284] = 0.0;
   out_5386858994733697605[285] = 1.0;
   out_5386858994733697605[286] = 0.0;
   out_5386858994733697605[287] = 0.0;
   out_5386858994733697605[288] = 0.0;
   out_5386858994733697605[289] = 0.0;
   out_5386858994733697605[290] = 0.0;
   out_5386858994733697605[291] = 0.0;
   out_5386858994733697605[292] = 0.0;
   out_5386858994733697605[293] = 0.0;
   out_5386858994733697605[294] = 0.0;
   out_5386858994733697605[295] = 0.0;
   out_5386858994733697605[296] = 0.0;
   out_5386858994733697605[297] = 0.0;
   out_5386858994733697605[298] = 0.0;
   out_5386858994733697605[299] = 0.0;
   out_5386858994733697605[300] = 0.0;
   out_5386858994733697605[301] = 0.0;
   out_5386858994733697605[302] = 0.0;
   out_5386858994733697605[303] = 0.0;
   out_5386858994733697605[304] = 1.0;
   out_5386858994733697605[305] = 0.0;
   out_5386858994733697605[306] = 0.0;
   out_5386858994733697605[307] = 0.0;
   out_5386858994733697605[308] = 0.0;
   out_5386858994733697605[309] = 0.0;
   out_5386858994733697605[310] = 0.0;
   out_5386858994733697605[311] = 0.0;
   out_5386858994733697605[312] = 0.0;
   out_5386858994733697605[313] = 0.0;
   out_5386858994733697605[314] = 0.0;
   out_5386858994733697605[315] = 0.0;
   out_5386858994733697605[316] = 0.0;
   out_5386858994733697605[317] = 0.0;
   out_5386858994733697605[318] = 0.0;
   out_5386858994733697605[319] = 0.0;
   out_5386858994733697605[320] = 0.0;
   out_5386858994733697605[321] = 0.0;
   out_5386858994733697605[322] = 0.0;
   out_5386858994733697605[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5161447794257487535) {
   out_5161447794257487535[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5161447794257487535[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5161447794257487535[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5161447794257487535[3] = dt*state[12] + state[3];
   out_5161447794257487535[4] = dt*state[13] + state[4];
   out_5161447794257487535[5] = dt*state[14] + state[5];
   out_5161447794257487535[6] = state[6];
   out_5161447794257487535[7] = state[7];
   out_5161447794257487535[8] = state[8];
   out_5161447794257487535[9] = state[9];
   out_5161447794257487535[10] = state[10];
   out_5161447794257487535[11] = state[11];
   out_5161447794257487535[12] = state[12];
   out_5161447794257487535[13] = state[13];
   out_5161447794257487535[14] = state[14];
   out_5161447794257487535[15] = state[15];
   out_5161447794257487535[16] = state[16];
   out_5161447794257487535[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1949735280217155384) {
   out_1949735280217155384[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1949735280217155384[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1949735280217155384[2] = 0;
   out_1949735280217155384[3] = 0;
   out_1949735280217155384[4] = 0;
   out_1949735280217155384[5] = 0;
   out_1949735280217155384[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1949735280217155384[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1949735280217155384[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1949735280217155384[9] = 0;
   out_1949735280217155384[10] = 0;
   out_1949735280217155384[11] = 0;
   out_1949735280217155384[12] = 0;
   out_1949735280217155384[13] = 0;
   out_1949735280217155384[14] = 0;
   out_1949735280217155384[15] = 0;
   out_1949735280217155384[16] = 0;
   out_1949735280217155384[17] = 0;
   out_1949735280217155384[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1949735280217155384[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1949735280217155384[20] = 0;
   out_1949735280217155384[21] = 0;
   out_1949735280217155384[22] = 0;
   out_1949735280217155384[23] = 0;
   out_1949735280217155384[24] = 0;
   out_1949735280217155384[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1949735280217155384[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1949735280217155384[27] = 0;
   out_1949735280217155384[28] = 0;
   out_1949735280217155384[29] = 0;
   out_1949735280217155384[30] = 0;
   out_1949735280217155384[31] = 0;
   out_1949735280217155384[32] = 0;
   out_1949735280217155384[33] = 0;
   out_1949735280217155384[34] = 0;
   out_1949735280217155384[35] = 0;
   out_1949735280217155384[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1949735280217155384[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1949735280217155384[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1949735280217155384[39] = 0;
   out_1949735280217155384[40] = 0;
   out_1949735280217155384[41] = 0;
   out_1949735280217155384[42] = 0;
   out_1949735280217155384[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1949735280217155384[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1949735280217155384[45] = 0;
   out_1949735280217155384[46] = 0;
   out_1949735280217155384[47] = 0;
   out_1949735280217155384[48] = 0;
   out_1949735280217155384[49] = 0;
   out_1949735280217155384[50] = 0;
   out_1949735280217155384[51] = 0;
   out_1949735280217155384[52] = 0;
   out_1949735280217155384[53] = 0;
   out_1949735280217155384[54] = 0;
   out_1949735280217155384[55] = 0;
   out_1949735280217155384[56] = 0;
   out_1949735280217155384[57] = 1;
   out_1949735280217155384[58] = 0;
   out_1949735280217155384[59] = 0;
   out_1949735280217155384[60] = 0;
   out_1949735280217155384[61] = 0;
   out_1949735280217155384[62] = 0;
   out_1949735280217155384[63] = 0;
   out_1949735280217155384[64] = 0;
   out_1949735280217155384[65] = 0;
   out_1949735280217155384[66] = dt;
   out_1949735280217155384[67] = 0;
   out_1949735280217155384[68] = 0;
   out_1949735280217155384[69] = 0;
   out_1949735280217155384[70] = 0;
   out_1949735280217155384[71] = 0;
   out_1949735280217155384[72] = 0;
   out_1949735280217155384[73] = 0;
   out_1949735280217155384[74] = 0;
   out_1949735280217155384[75] = 0;
   out_1949735280217155384[76] = 1;
   out_1949735280217155384[77] = 0;
   out_1949735280217155384[78] = 0;
   out_1949735280217155384[79] = 0;
   out_1949735280217155384[80] = 0;
   out_1949735280217155384[81] = 0;
   out_1949735280217155384[82] = 0;
   out_1949735280217155384[83] = 0;
   out_1949735280217155384[84] = 0;
   out_1949735280217155384[85] = dt;
   out_1949735280217155384[86] = 0;
   out_1949735280217155384[87] = 0;
   out_1949735280217155384[88] = 0;
   out_1949735280217155384[89] = 0;
   out_1949735280217155384[90] = 0;
   out_1949735280217155384[91] = 0;
   out_1949735280217155384[92] = 0;
   out_1949735280217155384[93] = 0;
   out_1949735280217155384[94] = 0;
   out_1949735280217155384[95] = 1;
   out_1949735280217155384[96] = 0;
   out_1949735280217155384[97] = 0;
   out_1949735280217155384[98] = 0;
   out_1949735280217155384[99] = 0;
   out_1949735280217155384[100] = 0;
   out_1949735280217155384[101] = 0;
   out_1949735280217155384[102] = 0;
   out_1949735280217155384[103] = 0;
   out_1949735280217155384[104] = dt;
   out_1949735280217155384[105] = 0;
   out_1949735280217155384[106] = 0;
   out_1949735280217155384[107] = 0;
   out_1949735280217155384[108] = 0;
   out_1949735280217155384[109] = 0;
   out_1949735280217155384[110] = 0;
   out_1949735280217155384[111] = 0;
   out_1949735280217155384[112] = 0;
   out_1949735280217155384[113] = 0;
   out_1949735280217155384[114] = 1;
   out_1949735280217155384[115] = 0;
   out_1949735280217155384[116] = 0;
   out_1949735280217155384[117] = 0;
   out_1949735280217155384[118] = 0;
   out_1949735280217155384[119] = 0;
   out_1949735280217155384[120] = 0;
   out_1949735280217155384[121] = 0;
   out_1949735280217155384[122] = 0;
   out_1949735280217155384[123] = 0;
   out_1949735280217155384[124] = 0;
   out_1949735280217155384[125] = 0;
   out_1949735280217155384[126] = 0;
   out_1949735280217155384[127] = 0;
   out_1949735280217155384[128] = 0;
   out_1949735280217155384[129] = 0;
   out_1949735280217155384[130] = 0;
   out_1949735280217155384[131] = 0;
   out_1949735280217155384[132] = 0;
   out_1949735280217155384[133] = 1;
   out_1949735280217155384[134] = 0;
   out_1949735280217155384[135] = 0;
   out_1949735280217155384[136] = 0;
   out_1949735280217155384[137] = 0;
   out_1949735280217155384[138] = 0;
   out_1949735280217155384[139] = 0;
   out_1949735280217155384[140] = 0;
   out_1949735280217155384[141] = 0;
   out_1949735280217155384[142] = 0;
   out_1949735280217155384[143] = 0;
   out_1949735280217155384[144] = 0;
   out_1949735280217155384[145] = 0;
   out_1949735280217155384[146] = 0;
   out_1949735280217155384[147] = 0;
   out_1949735280217155384[148] = 0;
   out_1949735280217155384[149] = 0;
   out_1949735280217155384[150] = 0;
   out_1949735280217155384[151] = 0;
   out_1949735280217155384[152] = 1;
   out_1949735280217155384[153] = 0;
   out_1949735280217155384[154] = 0;
   out_1949735280217155384[155] = 0;
   out_1949735280217155384[156] = 0;
   out_1949735280217155384[157] = 0;
   out_1949735280217155384[158] = 0;
   out_1949735280217155384[159] = 0;
   out_1949735280217155384[160] = 0;
   out_1949735280217155384[161] = 0;
   out_1949735280217155384[162] = 0;
   out_1949735280217155384[163] = 0;
   out_1949735280217155384[164] = 0;
   out_1949735280217155384[165] = 0;
   out_1949735280217155384[166] = 0;
   out_1949735280217155384[167] = 0;
   out_1949735280217155384[168] = 0;
   out_1949735280217155384[169] = 0;
   out_1949735280217155384[170] = 0;
   out_1949735280217155384[171] = 1;
   out_1949735280217155384[172] = 0;
   out_1949735280217155384[173] = 0;
   out_1949735280217155384[174] = 0;
   out_1949735280217155384[175] = 0;
   out_1949735280217155384[176] = 0;
   out_1949735280217155384[177] = 0;
   out_1949735280217155384[178] = 0;
   out_1949735280217155384[179] = 0;
   out_1949735280217155384[180] = 0;
   out_1949735280217155384[181] = 0;
   out_1949735280217155384[182] = 0;
   out_1949735280217155384[183] = 0;
   out_1949735280217155384[184] = 0;
   out_1949735280217155384[185] = 0;
   out_1949735280217155384[186] = 0;
   out_1949735280217155384[187] = 0;
   out_1949735280217155384[188] = 0;
   out_1949735280217155384[189] = 0;
   out_1949735280217155384[190] = 1;
   out_1949735280217155384[191] = 0;
   out_1949735280217155384[192] = 0;
   out_1949735280217155384[193] = 0;
   out_1949735280217155384[194] = 0;
   out_1949735280217155384[195] = 0;
   out_1949735280217155384[196] = 0;
   out_1949735280217155384[197] = 0;
   out_1949735280217155384[198] = 0;
   out_1949735280217155384[199] = 0;
   out_1949735280217155384[200] = 0;
   out_1949735280217155384[201] = 0;
   out_1949735280217155384[202] = 0;
   out_1949735280217155384[203] = 0;
   out_1949735280217155384[204] = 0;
   out_1949735280217155384[205] = 0;
   out_1949735280217155384[206] = 0;
   out_1949735280217155384[207] = 0;
   out_1949735280217155384[208] = 0;
   out_1949735280217155384[209] = 1;
   out_1949735280217155384[210] = 0;
   out_1949735280217155384[211] = 0;
   out_1949735280217155384[212] = 0;
   out_1949735280217155384[213] = 0;
   out_1949735280217155384[214] = 0;
   out_1949735280217155384[215] = 0;
   out_1949735280217155384[216] = 0;
   out_1949735280217155384[217] = 0;
   out_1949735280217155384[218] = 0;
   out_1949735280217155384[219] = 0;
   out_1949735280217155384[220] = 0;
   out_1949735280217155384[221] = 0;
   out_1949735280217155384[222] = 0;
   out_1949735280217155384[223] = 0;
   out_1949735280217155384[224] = 0;
   out_1949735280217155384[225] = 0;
   out_1949735280217155384[226] = 0;
   out_1949735280217155384[227] = 0;
   out_1949735280217155384[228] = 1;
   out_1949735280217155384[229] = 0;
   out_1949735280217155384[230] = 0;
   out_1949735280217155384[231] = 0;
   out_1949735280217155384[232] = 0;
   out_1949735280217155384[233] = 0;
   out_1949735280217155384[234] = 0;
   out_1949735280217155384[235] = 0;
   out_1949735280217155384[236] = 0;
   out_1949735280217155384[237] = 0;
   out_1949735280217155384[238] = 0;
   out_1949735280217155384[239] = 0;
   out_1949735280217155384[240] = 0;
   out_1949735280217155384[241] = 0;
   out_1949735280217155384[242] = 0;
   out_1949735280217155384[243] = 0;
   out_1949735280217155384[244] = 0;
   out_1949735280217155384[245] = 0;
   out_1949735280217155384[246] = 0;
   out_1949735280217155384[247] = 1;
   out_1949735280217155384[248] = 0;
   out_1949735280217155384[249] = 0;
   out_1949735280217155384[250] = 0;
   out_1949735280217155384[251] = 0;
   out_1949735280217155384[252] = 0;
   out_1949735280217155384[253] = 0;
   out_1949735280217155384[254] = 0;
   out_1949735280217155384[255] = 0;
   out_1949735280217155384[256] = 0;
   out_1949735280217155384[257] = 0;
   out_1949735280217155384[258] = 0;
   out_1949735280217155384[259] = 0;
   out_1949735280217155384[260] = 0;
   out_1949735280217155384[261] = 0;
   out_1949735280217155384[262] = 0;
   out_1949735280217155384[263] = 0;
   out_1949735280217155384[264] = 0;
   out_1949735280217155384[265] = 0;
   out_1949735280217155384[266] = 1;
   out_1949735280217155384[267] = 0;
   out_1949735280217155384[268] = 0;
   out_1949735280217155384[269] = 0;
   out_1949735280217155384[270] = 0;
   out_1949735280217155384[271] = 0;
   out_1949735280217155384[272] = 0;
   out_1949735280217155384[273] = 0;
   out_1949735280217155384[274] = 0;
   out_1949735280217155384[275] = 0;
   out_1949735280217155384[276] = 0;
   out_1949735280217155384[277] = 0;
   out_1949735280217155384[278] = 0;
   out_1949735280217155384[279] = 0;
   out_1949735280217155384[280] = 0;
   out_1949735280217155384[281] = 0;
   out_1949735280217155384[282] = 0;
   out_1949735280217155384[283] = 0;
   out_1949735280217155384[284] = 0;
   out_1949735280217155384[285] = 1;
   out_1949735280217155384[286] = 0;
   out_1949735280217155384[287] = 0;
   out_1949735280217155384[288] = 0;
   out_1949735280217155384[289] = 0;
   out_1949735280217155384[290] = 0;
   out_1949735280217155384[291] = 0;
   out_1949735280217155384[292] = 0;
   out_1949735280217155384[293] = 0;
   out_1949735280217155384[294] = 0;
   out_1949735280217155384[295] = 0;
   out_1949735280217155384[296] = 0;
   out_1949735280217155384[297] = 0;
   out_1949735280217155384[298] = 0;
   out_1949735280217155384[299] = 0;
   out_1949735280217155384[300] = 0;
   out_1949735280217155384[301] = 0;
   out_1949735280217155384[302] = 0;
   out_1949735280217155384[303] = 0;
   out_1949735280217155384[304] = 1;
   out_1949735280217155384[305] = 0;
   out_1949735280217155384[306] = 0;
   out_1949735280217155384[307] = 0;
   out_1949735280217155384[308] = 0;
   out_1949735280217155384[309] = 0;
   out_1949735280217155384[310] = 0;
   out_1949735280217155384[311] = 0;
   out_1949735280217155384[312] = 0;
   out_1949735280217155384[313] = 0;
   out_1949735280217155384[314] = 0;
   out_1949735280217155384[315] = 0;
   out_1949735280217155384[316] = 0;
   out_1949735280217155384[317] = 0;
   out_1949735280217155384[318] = 0;
   out_1949735280217155384[319] = 0;
   out_1949735280217155384[320] = 0;
   out_1949735280217155384[321] = 0;
   out_1949735280217155384[322] = 0;
   out_1949735280217155384[323] = 1;
}
void h_4(double *state, double *unused, double *out_7866192863446445032) {
   out_7866192863446445032[0] = state[6] + state[9];
   out_7866192863446445032[1] = state[7] + state[10];
   out_7866192863446445032[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3567160268827400744) {
   out_3567160268827400744[0] = 0;
   out_3567160268827400744[1] = 0;
   out_3567160268827400744[2] = 0;
   out_3567160268827400744[3] = 0;
   out_3567160268827400744[4] = 0;
   out_3567160268827400744[5] = 0;
   out_3567160268827400744[6] = 1;
   out_3567160268827400744[7] = 0;
   out_3567160268827400744[8] = 0;
   out_3567160268827400744[9] = 1;
   out_3567160268827400744[10] = 0;
   out_3567160268827400744[11] = 0;
   out_3567160268827400744[12] = 0;
   out_3567160268827400744[13] = 0;
   out_3567160268827400744[14] = 0;
   out_3567160268827400744[15] = 0;
   out_3567160268827400744[16] = 0;
   out_3567160268827400744[17] = 0;
   out_3567160268827400744[18] = 0;
   out_3567160268827400744[19] = 0;
   out_3567160268827400744[20] = 0;
   out_3567160268827400744[21] = 0;
   out_3567160268827400744[22] = 0;
   out_3567160268827400744[23] = 0;
   out_3567160268827400744[24] = 0;
   out_3567160268827400744[25] = 1;
   out_3567160268827400744[26] = 0;
   out_3567160268827400744[27] = 0;
   out_3567160268827400744[28] = 1;
   out_3567160268827400744[29] = 0;
   out_3567160268827400744[30] = 0;
   out_3567160268827400744[31] = 0;
   out_3567160268827400744[32] = 0;
   out_3567160268827400744[33] = 0;
   out_3567160268827400744[34] = 0;
   out_3567160268827400744[35] = 0;
   out_3567160268827400744[36] = 0;
   out_3567160268827400744[37] = 0;
   out_3567160268827400744[38] = 0;
   out_3567160268827400744[39] = 0;
   out_3567160268827400744[40] = 0;
   out_3567160268827400744[41] = 0;
   out_3567160268827400744[42] = 0;
   out_3567160268827400744[43] = 0;
   out_3567160268827400744[44] = 1;
   out_3567160268827400744[45] = 0;
   out_3567160268827400744[46] = 0;
   out_3567160268827400744[47] = 1;
   out_3567160268827400744[48] = 0;
   out_3567160268827400744[49] = 0;
   out_3567160268827400744[50] = 0;
   out_3567160268827400744[51] = 0;
   out_3567160268827400744[52] = 0;
   out_3567160268827400744[53] = 0;
}
void h_10(double *state, double *unused, double *out_8914684835339347467) {
   out_8914684835339347467[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8914684835339347467[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8914684835339347467[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8297533820426425377) {
   out_8297533820426425377[0] = 0;
   out_8297533820426425377[1] = 9.8100000000000005*cos(state[1]);
   out_8297533820426425377[2] = 0;
   out_8297533820426425377[3] = 0;
   out_8297533820426425377[4] = -state[8];
   out_8297533820426425377[5] = state[7];
   out_8297533820426425377[6] = 0;
   out_8297533820426425377[7] = state[5];
   out_8297533820426425377[8] = -state[4];
   out_8297533820426425377[9] = 0;
   out_8297533820426425377[10] = 0;
   out_8297533820426425377[11] = 0;
   out_8297533820426425377[12] = 1;
   out_8297533820426425377[13] = 0;
   out_8297533820426425377[14] = 0;
   out_8297533820426425377[15] = 1;
   out_8297533820426425377[16] = 0;
   out_8297533820426425377[17] = 0;
   out_8297533820426425377[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8297533820426425377[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8297533820426425377[20] = 0;
   out_8297533820426425377[21] = state[8];
   out_8297533820426425377[22] = 0;
   out_8297533820426425377[23] = -state[6];
   out_8297533820426425377[24] = -state[5];
   out_8297533820426425377[25] = 0;
   out_8297533820426425377[26] = state[3];
   out_8297533820426425377[27] = 0;
   out_8297533820426425377[28] = 0;
   out_8297533820426425377[29] = 0;
   out_8297533820426425377[30] = 0;
   out_8297533820426425377[31] = 1;
   out_8297533820426425377[32] = 0;
   out_8297533820426425377[33] = 0;
   out_8297533820426425377[34] = 1;
   out_8297533820426425377[35] = 0;
   out_8297533820426425377[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8297533820426425377[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8297533820426425377[38] = 0;
   out_8297533820426425377[39] = -state[7];
   out_8297533820426425377[40] = state[6];
   out_8297533820426425377[41] = 0;
   out_8297533820426425377[42] = state[4];
   out_8297533820426425377[43] = -state[3];
   out_8297533820426425377[44] = 0;
   out_8297533820426425377[45] = 0;
   out_8297533820426425377[46] = 0;
   out_8297533820426425377[47] = 0;
   out_8297533820426425377[48] = 0;
   out_8297533820426425377[49] = 0;
   out_8297533820426425377[50] = 1;
   out_8297533820426425377[51] = 0;
   out_8297533820426425377[52] = 0;
   out_8297533820426425377[53] = 1;
}
void h_13(double *state, double *unused, double *out_8554417247847522799) {
   out_8554417247847522799[0] = state[3];
   out_8554417247847522799[1] = state[4];
   out_8554417247847522799[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6779434094159733545) {
   out_6779434094159733545[0] = 0;
   out_6779434094159733545[1] = 0;
   out_6779434094159733545[2] = 0;
   out_6779434094159733545[3] = 1;
   out_6779434094159733545[4] = 0;
   out_6779434094159733545[5] = 0;
   out_6779434094159733545[6] = 0;
   out_6779434094159733545[7] = 0;
   out_6779434094159733545[8] = 0;
   out_6779434094159733545[9] = 0;
   out_6779434094159733545[10] = 0;
   out_6779434094159733545[11] = 0;
   out_6779434094159733545[12] = 0;
   out_6779434094159733545[13] = 0;
   out_6779434094159733545[14] = 0;
   out_6779434094159733545[15] = 0;
   out_6779434094159733545[16] = 0;
   out_6779434094159733545[17] = 0;
   out_6779434094159733545[18] = 0;
   out_6779434094159733545[19] = 0;
   out_6779434094159733545[20] = 0;
   out_6779434094159733545[21] = 0;
   out_6779434094159733545[22] = 1;
   out_6779434094159733545[23] = 0;
   out_6779434094159733545[24] = 0;
   out_6779434094159733545[25] = 0;
   out_6779434094159733545[26] = 0;
   out_6779434094159733545[27] = 0;
   out_6779434094159733545[28] = 0;
   out_6779434094159733545[29] = 0;
   out_6779434094159733545[30] = 0;
   out_6779434094159733545[31] = 0;
   out_6779434094159733545[32] = 0;
   out_6779434094159733545[33] = 0;
   out_6779434094159733545[34] = 0;
   out_6779434094159733545[35] = 0;
   out_6779434094159733545[36] = 0;
   out_6779434094159733545[37] = 0;
   out_6779434094159733545[38] = 0;
   out_6779434094159733545[39] = 0;
   out_6779434094159733545[40] = 0;
   out_6779434094159733545[41] = 1;
   out_6779434094159733545[42] = 0;
   out_6779434094159733545[43] = 0;
   out_6779434094159733545[44] = 0;
   out_6779434094159733545[45] = 0;
   out_6779434094159733545[46] = 0;
   out_6779434094159733545[47] = 0;
   out_6779434094159733545[48] = 0;
   out_6779434094159733545[49] = 0;
   out_6779434094159733545[50] = 0;
   out_6779434094159733545[51] = 0;
   out_6779434094159733545[52] = 0;
   out_6779434094159733545[53] = 0;
}
void h_14(double *state, double *unused, double *out_8346226165818047963) {
   out_8346226165818047963[0] = state[6];
   out_8346226165818047963[1] = state[7];
   out_8346226165818047963[2] = state[8];
}
void H_14(double *state, double *unused, double *out_484371836532028448) {
   out_484371836532028448[0] = 0;
   out_484371836532028448[1] = 0;
   out_484371836532028448[2] = 0;
   out_484371836532028448[3] = 0;
   out_484371836532028448[4] = 0;
   out_484371836532028448[5] = 0;
   out_484371836532028448[6] = 1;
   out_484371836532028448[7] = 0;
   out_484371836532028448[8] = 0;
   out_484371836532028448[9] = 0;
   out_484371836532028448[10] = 0;
   out_484371836532028448[11] = 0;
   out_484371836532028448[12] = 0;
   out_484371836532028448[13] = 0;
   out_484371836532028448[14] = 0;
   out_484371836532028448[15] = 0;
   out_484371836532028448[16] = 0;
   out_484371836532028448[17] = 0;
   out_484371836532028448[18] = 0;
   out_484371836532028448[19] = 0;
   out_484371836532028448[20] = 0;
   out_484371836532028448[21] = 0;
   out_484371836532028448[22] = 0;
   out_484371836532028448[23] = 0;
   out_484371836532028448[24] = 0;
   out_484371836532028448[25] = 1;
   out_484371836532028448[26] = 0;
   out_484371836532028448[27] = 0;
   out_484371836532028448[28] = 0;
   out_484371836532028448[29] = 0;
   out_484371836532028448[30] = 0;
   out_484371836532028448[31] = 0;
   out_484371836532028448[32] = 0;
   out_484371836532028448[33] = 0;
   out_484371836532028448[34] = 0;
   out_484371836532028448[35] = 0;
   out_484371836532028448[36] = 0;
   out_484371836532028448[37] = 0;
   out_484371836532028448[38] = 0;
   out_484371836532028448[39] = 0;
   out_484371836532028448[40] = 0;
   out_484371836532028448[41] = 0;
   out_484371836532028448[42] = 0;
   out_484371836532028448[43] = 0;
   out_484371836532028448[44] = 1;
   out_484371836532028448[45] = 0;
   out_484371836532028448[46] = 0;
   out_484371836532028448[47] = 0;
   out_484371836532028448[48] = 0;
   out_484371836532028448[49] = 0;
   out_484371836532028448[50] = 0;
   out_484371836532028448[51] = 0;
   out_484371836532028448[52] = 0;
   out_484371836532028448[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_297086807638649028) {
  err_fun(nom_x, delta_x, out_297086807638649028);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_9032889632036866791) {
  inv_err_fun(nom_x, true_x, out_9032889632036866791);
}
void pose_H_mod_fun(double *state, double *out_5386858994733697605) {
  H_mod_fun(state, out_5386858994733697605);
}
void pose_f_fun(double *state, double dt, double *out_5161447794257487535) {
  f_fun(state,  dt, out_5161447794257487535);
}
void pose_F_fun(double *state, double dt, double *out_1949735280217155384) {
  F_fun(state,  dt, out_1949735280217155384);
}
void pose_h_4(double *state, double *unused, double *out_7866192863446445032) {
  h_4(state, unused, out_7866192863446445032);
}
void pose_H_4(double *state, double *unused, double *out_3567160268827400744) {
  H_4(state, unused, out_3567160268827400744);
}
void pose_h_10(double *state, double *unused, double *out_8914684835339347467) {
  h_10(state, unused, out_8914684835339347467);
}
void pose_H_10(double *state, double *unused, double *out_8297533820426425377) {
  H_10(state, unused, out_8297533820426425377);
}
void pose_h_13(double *state, double *unused, double *out_8554417247847522799) {
  h_13(state, unused, out_8554417247847522799);
}
void pose_H_13(double *state, double *unused, double *out_6779434094159733545) {
  H_13(state, unused, out_6779434094159733545);
}
void pose_h_14(double *state, double *unused, double *out_8346226165818047963) {
  h_14(state, unused, out_8346226165818047963);
}
void pose_H_14(double *state, double *unused, double *out_484371836532028448) {
  H_14(state, unused, out_484371836532028448);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
