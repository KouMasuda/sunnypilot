#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_297086807638649028);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_9032889632036866791);
void pose_H_mod_fun(double *state, double *out_5386858994733697605);
void pose_f_fun(double *state, double dt, double *out_5161447794257487535);
void pose_F_fun(double *state, double dt, double *out_1949735280217155384);
void pose_h_4(double *state, double *unused, double *out_7866192863446445032);
void pose_H_4(double *state, double *unused, double *out_3567160268827400744);
void pose_h_10(double *state, double *unused, double *out_8914684835339347467);
void pose_H_10(double *state, double *unused, double *out_8297533820426425377);
void pose_h_13(double *state, double *unused, double *out_8554417247847522799);
void pose_H_13(double *state, double *unused, double *out_6779434094159733545);
void pose_h_14(double *state, double *unused, double *out_8346226165818047963);
void pose_H_14(double *state, double *unused, double *out_484371836532028448);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}