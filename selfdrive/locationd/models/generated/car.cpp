#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_8404996647874417762) {
   out_8404996647874417762[0] = delta_x[0] + nom_x[0];
   out_8404996647874417762[1] = delta_x[1] + nom_x[1];
   out_8404996647874417762[2] = delta_x[2] + nom_x[2];
   out_8404996647874417762[3] = delta_x[3] + nom_x[3];
   out_8404996647874417762[4] = delta_x[4] + nom_x[4];
   out_8404996647874417762[5] = delta_x[5] + nom_x[5];
   out_8404996647874417762[6] = delta_x[6] + nom_x[6];
   out_8404996647874417762[7] = delta_x[7] + nom_x[7];
   out_8404996647874417762[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1791025172801481948) {
   out_1791025172801481948[0] = -nom_x[0] + true_x[0];
   out_1791025172801481948[1] = -nom_x[1] + true_x[1];
   out_1791025172801481948[2] = -nom_x[2] + true_x[2];
   out_1791025172801481948[3] = -nom_x[3] + true_x[3];
   out_1791025172801481948[4] = -nom_x[4] + true_x[4];
   out_1791025172801481948[5] = -nom_x[5] + true_x[5];
   out_1791025172801481948[6] = -nom_x[6] + true_x[6];
   out_1791025172801481948[7] = -nom_x[7] + true_x[7];
   out_1791025172801481948[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3424526375464747894) {
   out_3424526375464747894[0] = 1.0;
   out_3424526375464747894[1] = 0.0;
   out_3424526375464747894[2] = 0.0;
   out_3424526375464747894[3] = 0.0;
   out_3424526375464747894[4] = 0.0;
   out_3424526375464747894[5] = 0.0;
   out_3424526375464747894[6] = 0.0;
   out_3424526375464747894[7] = 0.0;
   out_3424526375464747894[8] = 0.0;
   out_3424526375464747894[9] = 0.0;
   out_3424526375464747894[10] = 1.0;
   out_3424526375464747894[11] = 0.0;
   out_3424526375464747894[12] = 0.0;
   out_3424526375464747894[13] = 0.0;
   out_3424526375464747894[14] = 0.0;
   out_3424526375464747894[15] = 0.0;
   out_3424526375464747894[16] = 0.0;
   out_3424526375464747894[17] = 0.0;
   out_3424526375464747894[18] = 0.0;
   out_3424526375464747894[19] = 0.0;
   out_3424526375464747894[20] = 1.0;
   out_3424526375464747894[21] = 0.0;
   out_3424526375464747894[22] = 0.0;
   out_3424526375464747894[23] = 0.0;
   out_3424526375464747894[24] = 0.0;
   out_3424526375464747894[25] = 0.0;
   out_3424526375464747894[26] = 0.0;
   out_3424526375464747894[27] = 0.0;
   out_3424526375464747894[28] = 0.0;
   out_3424526375464747894[29] = 0.0;
   out_3424526375464747894[30] = 1.0;
   out_3424526375464747894[31] = 0.0;
   out_3424526375464747894[32] = 0.0;
   out_3424526375464747894[33] = 0.0;
   out_3424526375464747894[34] = 0.0;
   out_3424526375464747894[35] = 0.0;
   out_3424526375464747894[36] = 0.0;
   out_3424526375464747894[37] = 0.0;
   out_3424526375464747894[38] = 0.0;
   out_3424526375464747894[39] = 0.0;
   out_3424526375464747894[40] = 1.0;
   out_3424526375464747894[41] = 0.0;
   out_3424526375464747894[42] = 0.0;
   out_3424526375464747894[43] = 0.0;
   out_3424526375464747894[44] = 0.0;
   out_3424526375464747894[45] = 0.0;
   out_3424526375464747894[46] = 0.0;
   out_3424526375464747894[47] = 0.0;
   out_3424526375464747894[48] = 0.0;
   out_3424526375464747894[49] = 0.0;
   out_3424526375464747894[50] = 1.0;
   out_3424526375464747894[51] = 0.0;
   out_3424526375464747894[52] = 0.0;
   out_3424526375464747894[53] = 0.0;
   out_3424526375464747894[54] = 0.0;
   out_3424526375464747894[55] = 0.0;
   out_3424526375464747894[56] = 0.0;
   out_3424526375464747894[57] = 0.0;
   out_3424526375464747894[58] = 0.0;
   out_3424526375464747894[59] = 0.0;
   out_3424526375464747894[60] = 1.0;
   out_3424526375464747894[61] = 0.0;
   out_3424526375464747894[62] = 0.0;
   out_3424526375464747894[63] = 0.0;
   out_3424526375464747894[64] = 0.0;
   out_3424526375464747894[65] = 0.0;
   out_3424526375464747894[66] = 0.0;
   out_3424526375464747894[67] = 0.0;
   out_3424526375464747894[68] = 0.0;
   out_3424526375464747894[69] = 0.0;
   out_3424526375464747894[70] = 1.0;
   out_3424526375464747894[71] = 0.0;
   out_3424526375464747894[72] = 0.0;
   out_3424526375464747894[73] = 0.0;
   out_3424526375464747894[74] = 0.0;
   out_3424526375464747894[75] = 0.0;
   out_3424526375464747894[76] = 0.0;
   out_3424526375464747894[77] = 0.0;
   out_3424526375464747894[78] = 0.0;
   out_3424526375464747894[79] = 0.0;
   out_3424526375464747894[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7947974357195965766) {
   out_7947974357195965766[0] = state[0];
   out_7947974357195965766[1] = state[1];
   out_7947974357195965766[2] = state[2];
   out_7947974357195965766[3] = state[3];
   out_7947974357195965766[4] = state[4];
   out_7947974357195965766[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7947974357195965766[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7947974357195965766[7] = state[7];
   out_7947974357195965766[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3444669517522862391) {
   out_3444669517522862391[0] = 1;
   out_3444669517522862391[1] = 0;
   out_3444669517522862391[2] = 0;
   out_3444669517522862391[3] = 0;
   out_3444669517522862391[4] = 0;
   out_3444669517522862391[5] = 0;
   out_3444669517522862391[6] = 0;
   out_3444669517522862391[7] = 0;
   out_3444669517522862391[8] = 0;
   out_3444669517522862391[9] = 0;
   out_3444669517522862391[10] = 1;
   out_3444669517522862391[11] = 0;
   out_3444669517522862391[12] = 0;
   out_3444669517522862391[13] = 0;
   out_3444669517522862391[14] = 0;
   out_3444669517522862391[15] = 0;
   out_3444669517522862391[16] = 0;
   out_3444669517522862391[17] = 0;
   out_3444669517522862391[18] = 0;
   out_3444669517522862391[19] = 0;
   out_3444669517522862391[20] = 1;
   out_3444669517522862391[21] = 0;
   out_3444669517522862391[22] = 0;
   out_3444669517522862391[23] = 0;
   out_3444669517522862391[24] = 0;
   out_3444669517522862391[25] = 0;
   out_3444669517522862391[26] = 0;
   out_3444669517522862391[27] = 0;
   out_3444669517522862391[28] = 0;
   out_3444669517522862391[29] = 0;
   out_3444669517522862391[30] = 1;
   out_3444669517522862391[31] = 0;
   out_3444669517522862391[32] = 0;
   out_3444669517522862391[33] = 0;
   out_3444669517522862391[34] = 0;
   out_3444669517522862391[35] = 0;
   out_3444669517522862391[36] = 0;
   out_3444669517522862391[37] = 0;
   out_3444669517522862391[38] = 0;
   out_3444669517522862391[39] = 0;
   out_3444669517522862391[40] = 1;
   out_3444669517522862391[41] = 0;
   out_3444669517522862391[42] = 0;
   out_3444669517522862391[43] = 0;
   out_3444669517522862391[44] = 0;
   out_3444669517522862391[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3444669517522862391[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3444669517522862391[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3444669517522862391[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3444669517522862391[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3444669517522862391[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3444669517522862391[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3444669517522862391[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3444669517522862391[53] = -9.8000000000000007*dt;
   out_3444669517522862391[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3444669517522862391[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3444669517522862391[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3444669517522862391[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3444669517522862391[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3444669517522862391[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3444669517522862391[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3444669517522862391[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3444669517522862391[62] = 0;
   out_3444669517522862391[63] = 0;
   out_3444669517522862391[64] = 0;
   out_3444669517522862391[65] = 0;
   out_3444669517522862391[66] = 0;
   out_3444669517522862391[67] = 0;
   out_3444669517522862391[68] = 0;
   out_3444669517522862391[69] = 0;
   out_3444669517522862391[70] = 1;
   out_3444669517522862391[71] = 0;
   out_3444669517522862391[72] = 0;
   out_3444669517522862391[73] = 0;
   out_3444669517522862391[74] = 0;
   out_3444669517522862391[75] = 0;
   out_3444669517522862391[76] = 0;
   out_3444669517522862391[77] = 0;
   out_3444669517522862391[78] = 0;
   out_3444669517522862391[79] = 0;
   out_3444669517522862391[80] = 1;
}
void h_25(double *state, double *unused, double *out_3658247299564185893) {
   out_3658247299564185893[0] = state[6];
}
void H_25(double *state, double *unused, double *out_98454274524743783) {
   out_98454274524743783[0] = 0;
   out_98454274524743783[1] = 0;
   out_98454274524743783[2] = 0;
   out_98454274524743783[3] = 0;
   out_98454274524743783[4] = 0;
   out_98454274524743783[5] = 0;
   out_98454274524743783[6] = 1;
   out_98454274524743783[7] = 0;
   out_98454274524743783[8] = 0;
}
void h_24(double *state, double *unused, double *out_8067381454378439147) {
   out_8067381454378439147[0] = state[4];
   out_8067381454378439147[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1511482522563152620) {
   out_1511482522563152620[0] = 0;
   out_1511482522563152620[1] = 0;
   out_1511482522563152620[2] = 0;
   out_1511482522563152620[3] = 0;
   out_1511482522563152620[4] = 1;
   out_1511482522563152620[5] = 0;
   out_1511482522563152620[6] = 0;
   out_1511482522563152620[7] = 0;
   out_1511482522563152620[8] = 0;
   out_1511482522563152620[9] = 0;
   out_1511482522563152620[10] = 0;
   out_1511482522563152620[11] = 0;
   out_1511482522563152620[12] = 0;
   out_1511482522563152620[13] = 0;
   out_1511482522563152620[14] = 1;
   out_1511482522563152620[15] = 0;
   out_1511482522563152620[16] = 0;
   out_1511482522563152620[17] = 0;
}
void h_30(double *state, double *unused, double *out_4234692195320337466) {
   out_4234692195320337466[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4429242055602864415) {
   out_4429242055602864415[0] = 0;
   out_4429242055602864415[1] = 0;
   out_4429242055602864415[2] = 0;
   out_4429242055602864415[3] = 0;
   out_4429242055602864415[4] = 1;
   out_4429242055602864415[5] = 0;
   out_4429242055602864415[6] = 0;
   out_4429242055602864415[7] = 0;
   out_4429242055602864415[8] = 0;
}
void h_26(double *state, double *unused, double *out_9210378610728368505) {
   out_9210378610728368505[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3643049044349312441) {
   out_3643049044349312441[0] = 0;
   out_3643049044349312441[1] = 0;
   out_3643049044349312441[2] = 0;
   out_3643049044349312441[3] = 0;
   out_3643049044349312441[4] = 0;
   out_3643049044349312441[5] = 0;
   out_3643049044349312441[6] = 0;
   out_3643049044349312441[7] = 1;
   out_3643049044349312441[8] = 0;
}
void h_27(double *state, double *unused, double *out_3029958153030496395) {
   out_3029958153030496395[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2205647984418921198) {
   out_2205647984418921198[0] = 0;
   out_2205647984418921198[1] = 0;
   out_2205647984418921198[2] = 0;
   out_2205647984418921198[3] = 1;
   out_2205647984418921198[4] = 0;
   out_2205647984418921198[5] = 0;
   out_2205647984418921198[6] = 0;
   out_2205647984418921198[7] = 0;
   out_2205647984418921198[8] = 0;
}
void h_29(double *state, double *unused, double *out_7209289174596148371) {
   out_7209289174596148371[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3919010711288472231) {
   out_3919010711288472231[0] = 0;
   out_3919010711288472231[1] = 1;
   out_3919010711288472231[2] = 0;
   out_3919010711288472231[3] = 0;
   out_3919010711288472231[4] = 0;
   out_3919010711288472231[5] = 0;
   out_3919010711288472231[6] = 0;
   out_3919010711288472231[7] = 0;
   out_3919010711288472231[8] = 0;
}
void h_28(double *state, double *unused, double *out_322048604781809227) {
   out_322048604781809227[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1955380439723145980) {
   out_1955380439723145980[0] = 1;
   out_1955380439723145980[1] = 0;
   out_1955380439723145980[2] = 0;
   out_1955380439723145980[3] = 0;
   out_1955380439723145980[4] = 0;
   out_1955380439723145980[5] = 0;
   out_1955380439723145980[6] = 0;
   out_1955380439723145980[7] = 0;
   out_1955380439723145980[8] = 0;
}
void h_31(double *state, double *unused, double *out_8017661547795014787) {
   out_8017661547795014787[0] = state[8];
}
void H_31(double *state, double *unused, double *out_129100236401704211) {
   out_129100236401704211[0] = 0;
   out_129100236401704211[1] = 0;
   out_129100236401704211[2] = 0;
   out_129100236401704211[3] = 0;
   out_129100236401704211[4] = 0;
   out_129100236401704211[5] = 0;
   out_129100236401704211[6] = 0;
   out_129100236401704211[7] = 0;
   out_129100236401704211[8] = 1;
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

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_8404996647874417762) {
  err_fun(nom_x, delta_x, out_8404996647874417762);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1791025172801481948) {
  inv_err_fun(nom_x, true_x, out_1791025172801481948);
}
void car_H_mod_fun(double *state, double *out_3424526375464747894) {
  H_mod_fun(state, out_3424526375464747894);
}
void car_f_fun(double *state, double dt, double *out_7947974357195965766) {
  f_fun(state,  dt, out_7947974357195965766);
}
void car_F_fun(double *state, double dt, double *out_3444669517522862391) {
  F_fun(state,  dt, out_3444669517522862391);
}
void car_h_25(double *state, double *unused, double *out_3658247299564185893) {
  h_25(state, unused, out_3658247299564185893);
}
void car_H_25(double *state, double *unused, double *out_98454274524743783) {
  H_25(state, unused, out_98454274524743783);
}
void car_h_24(double *state, double *unused, double *out_8067381454378439147) {
  h_24(state, unused, out_8067381454378439147);
}
void car_H_24(double *state, double *unused, double *out_1511482522563152620) {
  H_24(state, unused, out_1511482522563152620);
}
void car_h_30(double *state, double *unused, double *out_4234692195320337466) {
  h_30(state, unused, out_4234692195320337466);
}
void car_H_30(double *state, double *unused, double *out_4429242055602864415) {
  H_30(state, unused, out_4429242055602864415);
}
void car_h_26(double *state, double *unused, double *out_9210378610728368505) {
  h_26(state, unused, out_9210378610728368505);
}
void car_H_26(double *state, double *unused, double *out_3643049044349312441) {
  H_26(state, unused, out_3643049044349312441);
}
void car_h_27(double *state, double *unused, double *out_3029958153030496395) {
  h_27(state, unused, out_3029958153030496395);
}
void car_H_27(double *state, double *unused, double *out_2205647984418921198) {
  H_27(state, unused, out_2205647984418921198);
}
void car_h_29(double *state, double *unused, double *out_7209289174596148371) {
  h_29(state, unused, out_7209289174596148371);
}
void car_H_29(double *state, double *unused, double *out_3919010711288472231) {
  H_29(state, unused, out_3919010711288472231);
}
void car_h_28(double *state, double *unused, double *out_322048604781809227) {
  h_28(state, unused, out_322048604781809227);
}
void car_H_28(double *state, double *unused, double *out_1955380439723145980) {
  H_28(state, unused, out_1955380439723145980);
}
void car_h_31(double *state, double *unused, double *out_8017661547795014787) {
  h_31(state, unused, out_8017661547795014787);
}
void car_H_31(double *state, double *unused, double *out_129100236401704211) {
  H_31(state, unused, out_129100236401704211);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
