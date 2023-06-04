#include <cstdio>
#include <cstdlib>
using namespace std;

#include "Testbench.h"


Testbench::Testbench(sc_module_name n) : sc_module(n), output_rgb_raw_data_offset(54) {
  SC_THREAD(feed_image);
  sensitive << i_clk.pos();
  dont_initialize();
  SC_THREAD(fetch_result);
  sensitive << i_clk.pos();
  dont_initialize();
}

Testbench::~Testbench() {
	cout << "Total run time = " << total_run_time << endl;
  cout << "Throught = " << throughput << " outputs/clock" << endl;
  cout << "Average latency = " << avg_latency << " clocks/output" << endl;
}



void Testbench::feed_image() {
  unsigned int i, image_idx; // for loop counter
#ifndef NATIVE_SYSTEMC
	o_rgb.reset();
#endif
	o_rst.write(false);
	wait(5);
	o_rst.write(true);
	wait(1);

  // Read input image
  image_idx = 0;
  float array[HIDDEN_SIZE];
  ifstream inputfile("img_"+std::to_string(image_idx)+".txt");
  if (!inputfile.is_open()) cout<<"Error opening file" ;
  for (i = 0; i != HIDDEN_SIZE; ++i){
    inputfile >> array[i];
  }
  inputfile.close();

  cout << " Recognizing image " << image_idx << endl;
  total_start_time = sc_time_stamp();
  custom_float rgb;
  for (i = 0; i != HIDDEN_SIZE; ++i){
    feed_time = sc_time_stamp();
    rgb = (custom_float)array[i];
#ifndef NATIVE_SYSTEMC
    o_rgb.put(rgb);
#else
    o_rgb.write(rgb);
#endif
  }
}
      
    
  
void Testbench::fetch_result() {
  unsigned int i, image_idx; // for loop counter
  signal_out total;
  int total_count;
#ifndef NATIVE_SYSTEMC
	i_result.reset();
#endif
	wait(5);
	wait(1);
  for (i = 0; i != HIDDEN_SIZE; ++i){
#ifndef NATIVE_SYSTEMC
    total = i_result.get();
    latency_time = sc_time_stamp()-feed_time;      //  ns/output
    total_latency += clock_cycle( latency_time );  //  clk/output
#else
    total = i_result.read();
#endif
  }
  prediction = total;
  cout << " Prediction = " << prediction << endl;

  total_count = HIDDEN_SIZE;
	total_run_time = sc_time_stamp() - total_start_time;
  throughput = (double)total_count / clock_cycle( total_run_time );
  avg_latency = (int)total_latency/total_count ;
  sc_stop();
}

unsigned int Testbench::clock_cycle( sc_time time )
{
    sc_clock * clk_p = dynamic_cast < sc_clock * >( i_clk.get_interface() );
    sc_time clock_period = clk_p->period(); // get period from the sc_clock object.
    return ( unsigned int )( time / clock_period );

}