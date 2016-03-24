graph [
node [
id 0
label "COMP_readCLIF_0"
type "COMP_readCLIF"
graphics [
x -174.000000
y -20.000000
]
params [
filename "/home/hendrik/projects/openlf/examples/demo_small.clif"
dataset "(UNSET)"
]
]
node [
id 1
label "COMP_select_path_0"
type "COMP_select_path"
graphics [
x 88.000000
y 1.000000
]
params [
path "calibration/extrinsics/default"
]
]
node [
id 2
label "COMP_subset_0"
type "COMP_subset"
graphics [
x 347.000000
y 22.000000
]
params [
subset_name "default"
scale 0.500000
]
]
node [
id 3
label "procEPI2.5D_0"
type "procEPI2.5D"
graphics [
x 600.000000
y -1.000000
]
params [
tensorCircuit "StructureTensor_Part1"
orientaionCircuit "StructureTensor_Part2"
mergeCircuit "OP_MergeDispByCoherence"
DispStart 3.000000
DispStop 7.000000
DispStep 1.000000
StartLine 0
StopLine 2160
disparity_name "default"
disparity_S_integrate 5.000000
disparity_S_pre_blur_x 0.000000
disparity_S_pre_blur_y 0.000000
orientation_S_min_coherence 0.500000
]
]
node [
id 4
label "COMP_writeCLIF_0"
type "COMP_writeCLIF"
graphics [
x 946.000000
y 9.000000
]
params [
filename "debug.clif"
dataset "(UNSET)"
]
]
node [
id 5
label "COMP_writeMesh_0"
type "COMP_writeMesh"
graphics [
x 952.000000
y 208.000000
]
params [
obj_filename "demo.obj"
ply_filename "(UNSET)"
max_depth 5000.000000
disparity_idx 0
color_idx 0
]
]
node [
id 6
label "COMP_select_path_1"
type "COMP_select_path"
graphics [
x 682.000000
y 177.000000
]
params [
path "disparity/default/data"
]
]
edge [
source 0
target 1
source_pad 0
target_pad 0
]
edge [
source 1
target 2
source_pad 0
target_pad 0
]
edge [
source 2
target 3
source_pad 0
target_pad 0
]
edge [
source 3
target 4
source_pad 0
target_pad 0
]
edge [
source 3
target 5
source_pad 0
target_pad 0
]
edge [
source 6
target 5
source_pad 0
target_pad 1
]
edge [
source 3
target 6
source_pad 0
target_pad 0
]
]
