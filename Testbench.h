#ifndef TESTBENCH_H_
#define TESTBENCH_H_

#include <string>
using namespace std;

#include <systemc>
using namespace sc_core;

#ifndef NATIVE_SYSTEMC
#include <cynw_p2p.h>
#endif

#include "defines.h"

class Testbench : public sc_module {
public:
	sc_in_clk i_clk;
	sc_out < bool >  o_rst;
#ifndef NATIVE_SYSTEMC
	cynw_p2p< custom_float >::base_out o_rgb;
	cynw_p2p< signal_out >::base_in i_result;
#else
	sc_fifo_out< custom_float > o_rgb;
	sc_fifo_in< signal_out > i_result;
#endif

  SC_HAS_PROCESS(Testbench);

  Testbench(sc_module_name n);
  ~Testbench();

private:
  const unsigned int output_rgb_raw_data_offset;

	unsigned int n_txn;
  unsigned int prediction;
  double throughput;
  double total_latency;
  double avg_latency;
	sc_time max_txn_time;
	sc_time min_txn_time;
	sc_time total_txn_time;
	sc_time total_start_time;
	sc_time total_run_time;
  sc_time feed_time;
  sc_time latency_time;

  void feed_image();
	void fetch_result();
  unsigned int clock_cycle( sc_time time );
};
#endif
