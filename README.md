## HLS accelerator PEs - Handwritten digits recognition

## Usage
1. Clone file to ./ee6470 folder (Git Bash)
```properties
git clone https://github.com/wine10001/EE6470_final_project_Q1.git NN
```
2. Source the setup file
```properties
source /usr/cadtool/user_setup/01-cadence_license_set.cshset
source /usr/cad/cadence/cic_setup/stratus.cshrc
source /usr/cadtool/user_setup/03-xcelium.csh
```
3. Go to stratus directory
```properties
cd NN/stratus
```
4. Run SystemC-based behavioural simulation
```properties
make sim_B
```
5. Run HLS synthesis and Verilog simulation (BASIC)
```properties
make sim_V_BASIC
```

6. Run HLS synthesis and Verilog simulation (DPA)
```properties
make sim_V_DPA
```
7. Run HLS synthesis and Verilog simulation (FLAT_UNROLL_ALL_FAST)
```properties
make sim_V_FLAT_UNROLL_ALL_FAST
```
8. Run HLS synthesis and Verilog simulation (FLAT_UNROLL_ALL_FAST_DPA)
```properties
make sim_V_FLAT_UNROLL_ALL_FAST_DPA
```
9. Run HLS synthesis and Verilog simulation (PIPELINE)
```properties
make sim_V_PIPELINE
```
10. Run HLS synthesis and Verilog simulation (PIPELINE_DPA)
```properties
make sim_V_PIPELINE_DPA
```

