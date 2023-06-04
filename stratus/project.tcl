#*******************************************************************************
# Copyright 2015 Cadence Design Systems, Inc.
# All Rights Reserved.
#
#*******************************************************************************
#
# Stratus Project File
#
############################################################
# Project Parameters
############################################################
#
# Technology Libraries
#
set LIB_PATH "[get_install_path]/share/stratus/techlibs/GPDK045/gsclib045_svt_v4.4/gsclib045/timing"
set LIB_LEAF "slow_vdd1v2_basicCells.lib"
use_tech_lib    "$LIB_PATH/$LIB_LEAF"
#use_hls_lib "cynw_cm_float"


#
# Global synthesis attributes.
#
set_attr clock_period           10.0
set_attr message_detail         3 
#set_attr default_input_delay    0.1
#set_attr sched_aggressive_1 on
#set_attr unroll_loops on
#set_attr flatten_arrays all 
#set_attr timing_aggression 0
#set_attr default_protocol true

#
# Simulation Options
#
### 1. You may add your own options for C++ compilation here.
set_attr cc_options             "-DCLOCK_PERIOD=10.0 -g"
#enable_waveform_logging -vcd
set_attr end_of_sim_command "make saySimPassed"

#
# Testbench or System Level Modules
#
### 2. Add your testbench source files here.
define_system_module ../main.cpp
define_system_module ../Testbench.cpp
define_system_module ../System.cpp

#
# SC_MODULEs to be synthesized
#
### 3. Add your design source files here (to be high-level synthesized).
define_hls_module Filter ../Filter.cpp

### 4. Define your HLS configuration (arbitrary names, BASIC and DPA in this example). 
define_hls_config Filter BASIC
define_hls_config Filter DPA       --dpopt_auto=op,expr
define_hls_config Filter FLAT_UNROLL_ALL_FAST --flatten_arrays=all -post_elab_tcl {
    unroll_loops [find -loop "loop_*" ]
    constrain_latency -max_lat $HLS::ACHIEVABLE [find -loop "while_1"]
}
define_hls_config Filter FLAT_UNROLL_ALL_FAST_DPA --dpopt_auto=op,expr --flatten_arrays=all -post_elab_tcl {
    unroll_loops [find -loop "loop_*" ]
    constrain_latency -max_lat $HLS::ACHIEVABLE [find -loop "while_1"]
}
define_hls_config Filter PIPELINE -DPIPELINE -DII=2
define_hls_config Filter PIPELINE_DPA -DPIPELINE -DII=2 --dpopt_auto=op,expr


set IMAGE_DIR           ".."
set IN_FILE_NAME        "${IMAGE_DIR}/test.bmp"
set OUT_FILE_NAME				"out.bmp"

### 5. Define simulation configuration for each HLS configuration
### 5.1 The behavioral simulation (C++ only).
define_sim_config B -argv "$IN_FILE_NAME $OUT_FILE_NAME"
### 5.2 The Verilog simulation for HLS config "BASIC". 
define_sim_config V_BASIC "Filter RTL_V BASIC" -argv "$IN_FILE_NAME $OUT_FILE_NAME"
### 5.3 The Verilog simulation for HLS config "DPA". 
define_sim_config V_DPA "Filter RTL_V DPA" -argv "$IN_FILE_NAME $OUT_FILE_NAME"
### 5.4 The Verilog simulation for HLS config "FLAT_UNROLL_ALL_FAST".
define_sim_config V_FLAT_UNROLL_ALL_FAST "Filter RTL_V FLAT_UNROLL_ALL_FAST" -argv "$IN_FILE_NAME $OUT_FILE_NAME"
### 5.5 The Verilog simulation for HLS config "PIPELINE".
define_sim_config V_PIPELINE "Filter RTL_V PIPELINE" -argv "$IN_FILE_NAME $OUT_FILE_NAME"
### 5.6 The Verilog simulation for HLS config "DPO_AUTO_OP".

define_sim_config V_FLAT_UNROLL_ALL_FAST_DPA "Filter RTL_V FLAT_UNROLL_ALL_FAST_DPA" -argv "$IN_FILE_NAME $OUT_FILE_NAME"
### 5.7 The Verilog simulation for HLS config "UNROLL_ALL_FAST_DPA".
#define_sim_config V_UNROLL_ALL_FAST_DPA "Filter RTL_V UNROLL_ALL_FAST_DPA" -argv "$IN_FILE_NAME $OUT_FILE_NAME"

#foreach config [find -hls_config *] {
#	set cname [get_attr name $config]

#	define_sim_config V_${cname} "Filter RTL_V $cname"
#}

# sim_B
# sim_V_BASIC
# sim_V_DPA
# sim_V_FLAT_UNROLL_ALL_FAST
# sim_V_PIPELINE
# sim_V_DPO_AUTO_OP
# sim_V_DPO_AUTO_EXPR
# sim_V_DPO_REGION
# sim_V_FLAT_UNROLL_ALL_FAST_DPA
# sim_V_UNROLL_ALL_FAST_DPA