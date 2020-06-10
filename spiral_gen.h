

#ifndef SPIRAL_GEN_H
#define SPIRAL_GEN_H


#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include <array>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iterator>
#include <sstream>

#include "sg_dbg_util.h"
//include "sg_file_utils.h"

#include <climits>
#include <gmpxx.h>

//typedef mpz_class sg_big_int_t;
//typedef mpf_class sg_big_float_t;
typedef long sg_big_int_t;
typedef double sg_big_float_t;

#define sg_string_t std::string

#define sg_k_pi 3.14159265

typedef sg_big_int_t sg_um_length_t;
typedef std::list<sg_string_t> sg_str_list_t;

//using namespace std;

class spiral_printer {
public:
	sg_string_t prg_nm;
	sg_str_list_t orig_args;
	sg_str_list_t work_args;
	bool args_orig_has_compl = false;
	
	sg_big_float_t inner = 4; // mm
	sg_big_float_t width = 2; // mm
	sg_big_float_t gap = 1; // mm
	sg_big_int_t turns = 20;
	sg_big_int_t sides = 8;
	bool clk_wise = true;
	sg_big_float_t x_center = 152.0; // mm
	sg_big_float_t y_center = 101.0; // mm
	sg_string_t layer;
	sg_string_t net;
	
	sg_big_float_t current_radius;
	sg_big_float_t current_angle;
	sg_big_float_t current_center_x;
	sg_big_float_t current_center_y;
	sg_big_float_t inc_angle;
	
	spiral_printer(){
		inner = 4;
		width = 2;
		gap = 1;
		turns = 20;
		sides = 8;
		clk_wise = true;
		x_center = 152.0;
		y_center = 101.0;
		layer = "F.Cu";
		net = "0";
	}
	
	sg_big_float_t  get_x(sg_big_float_t angle);
	sg_big_float_t  get_y(sg_big_float_t angle);

	void args_get_list(int argc, char *argv[]);
	void dec_args(sg_str_list_t& lt_args, int num_dec = 1);

	void print_half_turn(bool first_half);
	int print_spiral(sg_str_list_t& lt_args);
	bool get_args(sg_str_list_t& lt_args);
	void print_help();
};


#endif // SPIRAL_GEN_H

