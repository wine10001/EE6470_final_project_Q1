#ifndef FILTER_H_
#define FILTER_H_
#include <systemc>
using namespace sc_core;

#ifndef NATIVE_SYSTEMC
#include <cynw_p2p.h>

#endif

//#include "filter_def.h"
#include "weights.h"


class Filter: public sc_module
{
public:
	sc_in_clk i_clk;
	sc_in < bool >  i_rst;
#ifndef NATIVE_SYSTEMC
	cynw_p2p< custom_float >::in i_rgb;
	cynw_p2p< signal_out >::out o_result;
#else
	sc_fifo_in< custom_float > i_rgb;
	sc_fifo_out< signal_out > o_result;
#endif

	SC_HAS_PROCESS( Filter );
	Filter( sc_module_name n );
	~Filter();
private:
	void do_propagation();
	sc_uint<6> cnt; 
	custom_float output[OUTPUT_SIZE];
};
#endif
