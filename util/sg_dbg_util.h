

/*************************************************************

This file is part of hgen_net.

hgen_net is free software: you can redistribute it and/or modify
it under the terms of the version 3 of the GNU General Public 
License as published by the Free Software Foundation.

hgen_net is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with hgen_net.  If not, see <http://www.gnu.org/licenses/>.

------------------------------------------------------------

Copyright (C) 2020. QUIROGA BELTRAN, Jose Luis.
Id (cedula): 79523732 de Bogota - Colombia.
See https://github.com/hgen_net

hgen_net is free software thanks to The Glory of Our Lord 
	Yashua Melej Hamashiaj.
Our Resurrected and Living, both in Body and Spirit, 
	Prince of Peace.

------------------------------------------------------------

sg_dbg_util.h

func to print a stack trace.

--------------------------------------------------------------*/

#ifndef SG_DBG_UTIL_H
#define SG_DBG_UTIL_H

#include <string>

#define sg_null NULL

#define sg_c_decl extern "C"

#define SG_STRINGIFY(x) #x
#define SG_TOSTRING(x) SG_STRINGIFY(x)

#define SG_MAX_STR_SZ 300

// -----------------

#define SG_MAX_CALL_STACK_SZ 100
#define SG_PRT_SIZE_T "%lu"

#define SG_ABORT_MSG(msg) sg_cstr("ABORTING. '" msg "' at " __FILE__ "(" SG_TOSTRING(__LINE__) ")")

#define SG_INFO_STR "Passed " __FILE__ "(" SG_TOSTRING(__LINE__) ")"

#ifdef __cplusplus
sg_c_decl {
#endif

#ifdef FULL_DEBUG
#	define SG_DBG(prm) prm
#else
#	define SG_DBG(prm) /**/ 
#endif

#define SG_MARK_USED(X)  ((void)(&(X)))

#ifdef __cplusplus
}
#endif

std::string sg_get_stack_trace( const std::string & file, int line );
void sg_ptr_call_stack_trace(FILE* out_fp);
void sg_abort_func(bool prt_stk = false);

#define SG_STACK_STR sg_get_stack_trace(__FILE__, __LINE__)

const char* sg_get_ptd_log_fnam();
bool sg_call_assert(char* out_fnam, bool is_assert, bool prt_stck, bool vv_ck, 
				const char* file, int line, const char* ck_str, const char* fmt, ...);

#define sg_abort(...) \
{ \
	fprintf(stderr, "\nABORTING.\n"); \
	sg_ptr_call_stack_trace(sg_null); \
	fprintf(stderr, __VA_ARGS__); \
	sg_abort_func(); \
} \

// end_define

#define SG_CODE(cod) cod
#define SG_DBG_CODE(cod) SG_DBG(cod)

#define SG_CK(vv) SG_DBG( \
	sg_call_assert(sg_null, true, true, vv, __FILE__, __LINE__, #vv, sg_null))

//	(! vv)?(sg_call_assert(sg_null, true, true, vv, __FILE__, __LINE__, #vv, __VA_ARGS__), 0):(0))
//	sg_call_assert(sg_null, true, true, vv, __FILE__, __LINE__, #vv, __VA_ARGS__))

#define SG_CK_PRT(vv, ...) SG_DBG( \
	(! vv)?(sg_call_assert(sg_null, true, true, vv, __FILE__, __LINE__, #vv, __VA_ARGS__), 0):(0))

#define SG_CK_LOG(vv, ...) SG_DBG( \
	sg_call_assert(sg_get_ptd_log_fnam(), true, true, vv, __FILE__, __LINE__, #vv, __VA_ARGS__))

#define SG_COND_LOG(cond, ...) SG_DBG( \
	sg_call_assert(sg_get_ptd_log_fnam(), false, false, cond, __FILE__, __LINE__, #cond, __VA_ARGS__))

#define SG_LOG(...) SG_COND_LOG(true, __VA_ARGS__)

#define SG_COND_PRT(cond, ...) SG_DBG( \
	sg_call_assert(sg_null, false, false, cond, __FILE__, __LINE__, #cond, __VA_ARGS__))

#define SG_PRT(...) SG_COND_PRT(true, __VA_ARGS__)

#define SG_PRINTF(...) SG_DBG(printf(__VA_ARGS__))

#define SG_PRT_STACK(cond, ...) SG_DBG( \
	sg_call_assert(sg_null, false, true, cond, __FILE__, __LINE__, #cond, __VA_ARGS__))

#define SG_LOG_STACK(cond, ...) SG_DBG( \
	sg_call_assert(sg_get_ptd_log_fnam(), false, true, cond, __FILE__, __LINE__, #cond, __VA_ARGS__))


#endif		// SG_DBG_UTIL_H


