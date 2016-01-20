graph [
node [
id 0
label "readCLIF_0"
type "readCLIF"
graphics [
x -246.000000
y 21.000000
]
params [
filename "/home/hendrik/data/hci/circular/Blender Dataset/work_twoplanets/img.clif"
dataset "(UNSET)"
]
]
node [
id 1
label "procEPI2D_0"
type "procEPI2D"
graphics [
x -76.000000
y 34.000000
]
params [
epiCircuit "DefaultCircularStructureTensor"
mergeCircuit "OP_MergeDispByCoherence"
DispStart 0.000000
DispStop 0.000000
DispStep 1.000000
StartLine 100
StopLine 700
disparity_S_integrate 20.000000
disparity_S_min_coherence 0.500000
disparity_S_pre_blur_x 0.000000
disparity_S_pre_blur_y 0.000000
]
]
node [
id 2
label "writeMesh_0"
type "writeMesh"
graphics [
x 112.000000
y 142.000000
]
params [
obj_filename "(UNSET)"
ply_filename "/home/hendrik/data/hci/circular/Blender Dataset/work_twoplanets/mesh.ply"
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
]
