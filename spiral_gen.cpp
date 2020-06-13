

#include <iostream>
#include <cstdlib>
#include <map>
#include <regex>
 
#include "spiral_gen.h"

void
spiral_printer::print_help(){
	fprintf(stderr, "%s [-r <inner_radius in um>] [-w <width in um>] [-g <gap in um>] [-s <num_sides>] [-t <num_turns>] [-c]\n", prg_nm.c_str());
}

void 
spiral_printer::args_get_list(int argc, char *argv[]){
	orig_args.resize(0);
	for(int aa = 0; aa < argc; aa++){
		sg_string_t pm = argv[aa];
		orig_args.push_back(pm);
	}
	work_args = orig_args;
}

void 
spiral_printer::dec_args(sg_str_list_t& lt_args, int num_dec){
	for(; num_dec > 0; num_dec--){
		lt_args.pop_front();
	}
}

bool
spiral_printer::get_args(sg_str_list_t& lt_args){
	SG_CK(! lt_args.empty());
	
	sg_string_t the_arg;
	the_arg = lt_args.front(); dec_args(lt_args);
	prg_nm = the_arg;
	
	int tot_params = lt_args.size();
	if(tot_params == 0){
		print_help();
		return false;
	}

	bool did_some = true;
	while(did_some && ! lt_args.empty()){
		did_some = false;
		the_arg = lt_args.front();
		if((the_arg == "-r") && (lt_args.size() > 1)){
			dec_args(lt_args); did_some = true;

			the_arg = lt_args.front(); dec_args(lt_args);
			inner = atol(the_arg.c_str());
			inner /= 1000.0;
		}
		else if((the_arg == "-w") && (lt_args.size() > 1)){
			dec_args(lt_args); did_some = true;

			the_arg = lt_args.front(); dec_args(lt_args);
			width = atol(the_arg.c_str());
			width /= 1000.0;
		}
		else if((the_arg == "-g") && (lt_args.size() > 1)){
			dec_args(lt_args); did_some = true;

			the_arg = lt_args.front(); dec_args(lt_args);
			gap = atol(the_arg.c_str());
			gap /= 1000.0;
		}
		else if((the_arg == "-t") && (lt_args.size() > 1)){
			dec_args(lt_args); did_some = true;

			the_arg = lt_args.front(); dec_args(lt_args);
			turns = atol(the_arg.c_str());
			if(turns < 2){
				turns = 2;
				fprintf(stderr, "turns MUST be bigger than 2. Incrementing it to %ld. \n", turns);
			}
			if((turns % 2) != 0){
				turns++;
				fprintf(stderr, "turns MUST be a multiple of 2. Incrementing it to %ld. \n", turns);
			}
		}
		else if((the_arg == "-s") && (lt_args.size() > 1)){
			dec_args(lt_args); did_some = true;

			the_arg = lt_args.front(); dec_args(lt_args);
			sides = atol(the_arg.c_str());
			if(sides < 6){
				sides = 6;
				fprintf(stderr, "sides of polygon MUST be at least 6 sides. Incrementing sides to %ld. \n", sides);
			}
			if(sides > 100){
				sides = 100;
				fprintf(stderr, "sides of polygon MUST be at most 100 sides. Decrementing sides to %ld. \n", sides);
			}
		}
		else if(the_arg == "-c"){
			dec_args(lt_args); did_some = true;
			clk_wise = false;
		}
	}
	return true;
}

int
spiral_main(int argc, char *argv[]){
	spiral_printer pp;
	pp.args_get_list(argc, argv);
	pp.print_spiral(pp.work_args);
	return 0;
}

int
main(int argc, char *argv[]){
	return spiral_main(argc, argv);
}

int
spiral_printer::print_spiral(sg_str_list_t& lt_args){
	bool ok = get_args(lt_args);
	if(! ok){
		return 1;
	}
	sg_big_float_t kPI = sg_k_pi;
	inc_angle = (2.0 * kPI) / sides;
	
	if(clk_wise){
		inc_angle = -inc_angle;
	} 
	
	sg_big_float_t max_gap = (5 * width);
	if(gap > max_gap){
		gap = max_gap;
		fprintf(stderr, "gap MUST be at most (5 * width). Decrementing it to %f. \n", gap);
	}
	
	sg_big_float_t min_inner = (2 * (width + gap));
	if(inner < min_inner){
		inner = min_inner;
		fprintf(stderr, "inner MUST be at least (2 * (width + gap). Incrementing it to %f. \n", inner);
	}
	
	fprintf(stderr, "radius=%f mm, width=%f mm, gap=%f mm, sides=%ld, turns=%ld clk_wise=%d inc_angle=%f rad\n", 
			inner, width, gap, sides, turns, clk_wise, inc_angle);
	

	sg_big_float_t diff_r = (width / 2.0) + gap;
	sg_big_float_t x1 = x_center;
	sg_big_float_t x2 = x_center - diff_r;
	
	current_radius = inner;
	current_center_x = x1;
	current_center_y = y_center;
	for(long numt = 0; numt < turns; numt++){
		print_half_turn(true);
		current_center_x = x2;
		current_radius += diff_r;
		print_half_turn(false);
		current_center_x = x1;
		current_radius += diff_r;
	}	
	
	return 0;
}

sg_big_float_t
spiral_printer::get_x(sg_big_float_t angle){
	sg_big_float_t rel = cos(angle) * current_radius;
	return current_center_x + rel;
}

sg_big_float_t
spiral_printer::get_y(sg_big_float_t angle){
	sg_big_float_t rel = sin(angle) * current_radius;
	return current_center_y + rel;
}

void
spiral_printer::print_half_turn(bool first_half){
	sg_big_float_t kPI = sg_k_pi;

	current_angle = 0;
	if(! first_half){
		current_angle = kPI;
	}
	
	sg_big_float_t current_x = get_x(current_angle);
	sg_big_float_t current_y = get_y(current_angle);
	sg_big_float_t nxt_x = current_x;
	sg_big_float_t nxt_y = current_y;

	current_angle += inc_angle;
	
	long half_sides = sides / 2;
	long current_side = 0;
	for(current_side = 0; current_side < half_sides; current_side++){
		nxt_x = get_x(current_angle);
		nxt_y = get_y(current_angle);
		
		fprintf(stdout, "(segment (start %f %f) (end %f %f) (width %f) (layer %s) (net %s))\n", 
				current_x, current_y, nxt_x, nxt_y, width, layer.c_str(), net.c_str());
		
		current_x = nxt_x;
		current_y = nxt_y;
		current_angle += inc_angle;
	}
}

