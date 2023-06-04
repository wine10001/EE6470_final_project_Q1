#include <cmath>
#include <systemc>
#ifndef NATIVE_SYSTEMC
#include "stratus_hls.h"
#endif


#include "Filter.h"

Filter::Filter( sc_module_name n ): sc_module( n )
{
#ifndef NATIVE_SYSTEMC
#endif
	SC_THREAD( do_propagation );
	sensitive << i_clk.pos();
	dont_initialize();
	reset_signal_is(i_rst, false);
        
#ifndef NATIVE_SYSTEMC
	i_rgb.clk_rst(i_clk, i_rst);
  	o_result.clk_rst(i_clk, i_rst);
#endif
}

Filter::~Filter() {}

void Filter::do_propagation() {
	{
#ifndef NATIVE_SYSTEMC
		HLS_DEFINE_PROTOCOL("main_reset");
		i_rgb.reset();
		o_result.reset();
#endif
		wait();
	}

	cnt = 0;
loop_0:
	for (unsigned int i=0; i<OUTPUT_SIZE; i++){
		output[i] = bias2[i];
	}
while_1:
	while (true) {
		// Read data 
		custom_float element;
#ifndef NATIVE_SYSTEMC
		{
			HLS_DEFINE_PROTOCOL("input");
			element = i_rgb.get();
			wait();
		}
#else
		element = i_rgb.read();
#endif
		custom_float max = 0;
		signal_out max_index = 0;

		element += bias1[cnt]; // Addd bias
		if (element<0) element = 0; // ReLU
loop_1:
		for (unsigned int i=0; i<OUTPUT_SIZE; i++){
			output[i] += element*weights2[cnt][i];
		}

		if (cnt==HIDDEN_SIZE-1){	
loop_2:		// Sorted and find the max index
			for (unsigned int i=0; i<OUTPUT_SIZE; i++){
				if (output[i]>max){
					max = output[i];
					max_index = i; // Record the max index
				}
			}
		} else {
			max_index = 10; // if cnt is not the last one, set max_index to 10
		}
		cnt++;
#ifndef NATIVE_SYSTEMC
		{
			HLS_DEFINE_PROTOCOL("output");
			o_result.put(max_index);
			wait();
		}
#else
		o_result.write(max_index);
#endif
	}
}
