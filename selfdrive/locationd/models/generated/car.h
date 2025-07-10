#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_8404996647874417762);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1791025172801481948);
void car_H_mod_fun(double *state, double *out_3424526375464747894);
void car_f_fun(double *state, double dt, double *out_7947974357195965766);
void car_F_fun(double *state, double dt, double *out_3444669517522862391);
void car_h_25(double *state, double *unused, double *out_3658247299564185893);
void car_H_25(double *state, double *unused, double *out_98454274524743783);
void car_h_24(double *state, double *unused, double *out_8067381454378439147);
void car_H_24(double *state, double *unused, double *out_1511482522563152620);
void car_h_30(double *state, double *unused, double *out_4234692195320337466);
void car_H_30(double *state, double *unused, double *out_4429242055602864415);
void car_h_26(double *state, double *unused, double *out_9210378610728368505);
void car_H_26(double *state, double *unused, double *out_3643049044349312441);
void car_h_27(double *state, double *unused, double *out_3029958153030496395);
void car_H_27(double *state, double *unused, double *out_2205647984418921198);
void car_h_29(double *state, double *unused, double *out_7209289174596148371);
void car_H_29(double *state, double *unused, double *out_3919010711288472231);
void car_h_28(double *state, double *unused, double *out_322048604781809227);
void car_H_28(double *state, double *unused, double *out_1955380439723145980);
void car_h_31(double *state, double *unused, double *out_8017661547795014787);
void car_H_31(double *state, double *unused, double *out_129100236401704211);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}