#include "System.h"
System::System( sc_module_name n, string input_bmp, string output_bmp ): sc_module( n ), 
	tb("tb"), filter("filter"), clk("clk", CLOCK_PERIOD, SC_NS), rst("rst"), _output_bmp(output_bmp)
{
	tb.i_clk(clk);
	tb.o_rst(rst);
	filter.i_clk(clk);
	filter.i_rst(rst);
	tb.o_rgb(rgb);
	tb.i_result(result);
	filter.i_rgb(rgb);
	filter.o_result(result);
}

System::~System() {
}
