graph [
node [
id 0
label "readCLIF_0"
type "readCLIF"
graphics [
x -201,000000
y -1,000000
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
x -46,000000
y -10,000000
]
params [
epiCircuit "(UNKNOWN)"
mergeCircuit "(UNKNOWN)"
DispStart 3,000000
DispStop 7,000000
DispStep 1,000000
StartLine 750
StopLine 800
]
]
node [
id 2
label "writeMesh_0"
type "writeMesh"
graphics [
x 165,000000
y -14,000000
]
params [
obj_filename "/home/hendrik/projects/openlf/examples/demo.obj"
ply_filename "(UNSET)"
]
]
node [
id 3
label "writeCLIF_0"
type "writeCLIF"
graphics [
x 124,000000
y 98,000000
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
