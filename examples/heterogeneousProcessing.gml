graph [
node [
id 0
label "COMP_readCLIF_0"
type "COMP_readCLIF"
graphics [
x -594.000000
y -92.000000
]
params [
filename "C:/Users/Test/Desktop/UniHD_OpenLF/20160216_camarray_acquisition/build/Release/disp.clif"
dataset "(UNSET)"
]
]
node [
id 1
label "COMP_warpToRefView_0"
type "COMP_warpToRefView"
graphics [
x 77.000000
y -47.000000
]
params [
in_group "2DTV"
out_group "warped"
refView 5
refDisp 200.000000
]
]
node [
id 2
label "COMP_2DTV_0"
type "COMP_2DTV"
graphics [
x -129.000000
y -57.000000
]
params [
iterations 1000
tau 0.012000
sigma 0.500000
delta 0.200000
iota 0.400000
phi 0.200000
alpha 0.220000
alpha_edge 0.000000
beta 0.088000
beta_edge 0.000000
initialValue 50.000000
Display 1
TVposition 5
out_group "2DTV"
in_group "merged"
]
]
node [
id 3
label "COMP_RGBrecon_0"
type "COMP_RGBrecon"
graphics [
x 272.000000
y -24.000000
]
params [
in_group_warped "warped"
out_group "RGBrecon"
gamma 0.800000
]
]
node [
id 4
label "procEPI2.5D_0"
type "procEPI2.5D"
graphics [
x -400.000000
y -72.000000
]
params [
tensorCircuit "StructureTensor_Part1"
orientaionCircuit "StructureTensor_Part2"
mergeCircuit "OP_MergeDispByCoherence"
DispStart 160.000000
DispStop 220.000000
DispStep 2.000000
StartLine 0
StopLine 486
scale 0.250000
out_group "merged"
disparity_S_integrate 1.000000
disparity_S_pre_blur_x 0.000000
disparity_S_pre_blur_y 0.000000
orientation_S_min_coherence 0.000000
]
]
node [
id 5
label "COMP_writeMesh_0"
type "COMP_writeMesh"
graphics [
x 454.000000
y -10.000000
]
params [
obj_filename "car.obj"
ply_filename "(UNSET)"
in_group_dispMap "2DTV"
in_group_colorMap "RGBrecon"
Depth_cutoff 5000.000000
dispMap_View 5
ColorMap_View 5
]
]
node [
id 6
label "COMP_writeCLIF_0"
type "COMP_writeCLIF"
graphics [
x 446.000000
y 85.000000
]
params [
filename "wow.obj"
dataset "(UNSET)"
]
]
edge [
source 2
target 1
source_pad 0
target_pad 0
]
edge [
source 4
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
edge [
source 0
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
source 3
target 6
source_pad 0
target_pad 0
]
]
