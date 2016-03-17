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
filename ""
dataset "(UNSET)"
]
]
node [
id 1
label "procEPI2D_0"
type "procEPI2D"
graphics [
x -449.000000
y -79.000000
]
params [
epiCircuit "DefaultStructureTensor"
mergeCircuit "OP_MergeDispByCoherence"
DispStart 6.000000
DispStop 7.000000
DispStep 1.000000
StartLine 0
StopLine 520
scale 1.000000
out_group "disparity"
disparity_S_integrate 1.000000
disparity_S_min_coherence 0.500000
disparity_S_pre_blur_x 0.300000
disparity_S_pre_blur_y 0.300000
]
]
node [
id 2
label "COMP_writeCLIF_0"
type "COMP_writeCLIF"
graphics [
x 402.000000
y -26.000000
]
params [
filename ""
dataset "(UNSET)"
]
]
node [
id 3
label "COMP_mergeDispMaps_0"
type "COMP_mergeDispMaps"
graphics [
x -301.000000
y -59.000000
]
params [
in_group "disparity"
out_group "merged"
refView 10
StartView 0
EndView 20
]
]
node [
id 4
label "COMP_warpToRefView_0"
type "COMP_warpToRefView"
graphics [
x 55.000000
y -48.000000
]
params [
in_group "2DTV"
out_group "warped"
refView 10
]
]
node [
id 5
label "COMP_2DTV_0"
type "COMP_2DTV"
graphics [
x -110.000000
y -64.000000
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
initialValue 0.000000
Display 1
TVposition 10
out_group "2DTV"
in_group "merged"
]
]
node [
id 6
label "COMP_RGBrecon_0"
type "COMP_RGBrecon"
graphics [
x 258.000000
y -36.000000
]
params [
in_group_warped "warped"
out_group "RGBrecon"
]
]
edge [
source 0
target 1
source_pad 0
target_pad 0
]
edge [
source 6
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
source 5
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
source 4
target 6
source_pad 0
target_pad 0
]
]
