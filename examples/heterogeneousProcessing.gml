graph [
node [
id 0
label "COMP_readCLIF_0"
type "COMP_readCLIF"
graphics [
x -121.000000
y -74.000000
]
params [
filename "C:/Users/Purgy/Desktop/demo.clif"
dataset "(UNSET)"
Clif_Dataset "(UNKNOWN)"
]
]
node [
id 1
label "COMP_select_path_0"
type "COMP_select_path"
graphics [
x 18.000000
y -68.000000
]
params [
path "calibration/extrinsics/default"
ClifTree "(UNKNOWN)"
]
]
node [
id 2
label "COMP_subset_0"
type "COMP_subset"
graphics [
x 156.000000
y -55.000000
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
x 285.000000
y -105.000000
]
params [
tensorCircuit "StructureTensor_Part1"
orientationCircuit "StructureTensor_Part2"
mergeCircuit "OP_MergeDispByCoherence"
DispStart 3.000000
DispStop 7.000000
DispStep 1.000000
StartLine 0
StopLine 1080
disparity_name "default"
disparity_S_integrate 5.000000
disparity_S_pre_blur_x 0.000000
disparity_S_pre_blur_y 0.000000
orientation_S_min_coherence 0.500000
]
]
node [
id 4
label "COMP_WarpByRefDisparity_0"
type "COMP_WarpByRefDisparity"
graphics [
x 442.000000
y -48.000000
]
params [
disparity_idx 0
shifted_name "default"
]
]
node [
id 5
label "COMP_spectral2RGB_XYZ_0"
type "COMP_spectral2RGB_XYZ"
graphics [
x 644.000000
y -21.000000
]
params [
rgb_name "RGBrecon"
gamma 0.500000
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
source 2
target 4
source_pad 0
target_pad 1
]
edge [
source 4
target 5
source_pad 0
target_pad 0
]
]
