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
filename "/home/hendrik/projects/clif/examples/demo.clif"
dataset "(UNSET)"
]
]
node [
id 1
label "procEPI2D_0"
type "procEPI2D"
graphics [
x -21.000000
y 31.000000
]
params [
epiCircuit "(UNKNOWN)"
mergeCircuit "(UNKNOWN)"
DispStart 3.000000
DispStop 7.000000
DispStep 1.000000
StartLine 300
StopLine 600
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
obj_filename "/home/hendrik/projects/openlf/examples/demo.obj"
ply_filename "/home/hendrik/projects/openlf/examples/demo.ply"
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
filename "/home/hendrik/projects/openlf/examples/disparity.clif"
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
