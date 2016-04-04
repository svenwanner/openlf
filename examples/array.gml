graph [
node [
id 0
label "COMP_camarray_0"
type "COMP_camarray"
graphics [
x 122.000000
y -411.000000
]
params [
camera_config "/home/hendrik/projects/openlf/basler_ace2500_8bit_runtime5_4_linux.mcf"
exposures "10,10,10,50,50,50,100,100,100,1,1"
]
]
node [
id 1
label "COMP_writeCLIF_0"
type "COMP_writeCLIF"
graphics [
x 362.000000
y -405.000000
]
params [
filename "test.clif"
dataset "(UNSET)"
]
]
edge [
source 0
target 1
source_pad 0
target_pad 0
]
]
