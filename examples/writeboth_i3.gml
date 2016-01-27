graph [
node [
id 0
label "readCLIF_0"
type "readCLIF"
graphics [
x -244.000000
y 21.000000
]
params [
filename "demo.clif"
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
StartLine 1000
StopLine 1200
disparity_S_integrate 5.000000
disparity_S_min_coherence 0.800000
disparity_S_pre_blur_x 0.000000
disparity_S_pre_blur_y 0.000000
]
]
node [
id 2
label "writeMesh_0"
type "writeMesh"
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
type "writeCLIF"
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
