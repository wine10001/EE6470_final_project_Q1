#ifndef SYSTEM_H_
#define SYSTEM_H_
#include <systemc>
using namespace sc_core;

#include "Testbench.h"
//#include "filter_def.h"
#include "defines.h"
#ifndef NATIVE_SYSTEMC
#include "Filter_wrap.h"
#else
#include "Filter.h"
#endif

class System: public sc_module
{
public:
	SC_HAS_PROCESS( System );
	System( sc_module_name n, std::string input_bmp, std::string output_bmp );
	~System();
private:
  Testbench tb;
#ifndef NATIVE_SYSTEMC
	Filter_wrapper filter;
#else
	Filter filter;
#endif
	sc_clock clk;
	sc_signal<bool> rst;
#ifndef NATIVE_SYSTEMC
	cynw_p2p< custom_float > rgb;
	cynw_p2p< signal_out > result;
#else
	sc_fifo< custom_float > rgb;
	sc_fifo< signal_out > result;
#endif

	std::string _output_bmp;
};
#endif
