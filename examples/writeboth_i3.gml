graph [
node [
id 0
label "readCLIF_0"
type "COMP_readCLIF"
graphics [
x -244.000000
y 21.000000
]
params [
filename "demo_small.clif"
dataset "(UNSET)"
]
]
node [
id 1
label "procEPI2D.5_0"
type "procEPI2.5D"
graphics [
x -21.000000
y 31.000000
]
params [
tensorCircuit "StructureTensor_Part1"
DispStart 3.000000
DispStop 7.000000
DispStep 2.000000
#StartLine 0
#StopLine 1080
disparity_S_integrate 3.5
disparity_S_min_coherence 0.8
disparity_S_pre_blur_x 0.0
disparity_S_pre_blur_y 0.0
]
]
node [
id 2
label "writeMesh_0"
type "COMP_writeMesh"
graphics [
x 171.000000
y 8.000000
]
params [
obj_filename "demo_i3.obj"
ply_filename "demo_i3.ply"
]
]
node [
id 3
label "writeCLIF_0"
type "COMP_writeCLIF"
graphics [
x 189.000000
y 122.000000
]
params [
filename "disparity.clif"
dataset "(UNSET)"
]
]
edge [
source 0
target 1
source_pad 0
target_pad 0
]
edge [
source 0
target 1
source_pad 0
target_pad 1
]
edge [
source 1
target 2
source_pad 0
target_pad 0
]
edge [
source 1
target 3
source_pad 0
target_pad 0
]
]
