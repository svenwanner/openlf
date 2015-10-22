graph [
node [
id 0
label "readCLIF_0"
type "readCLIF"
graphics [
x -142.000000
y 27.000000
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
x 64.000000
y 40.000000
]
params [
epiCircuit "(UNKNOWN)"
mergeCircuit "(UNKNOWN)"
DispStart 3.000000
DispStop 7.000000
DispStep 1.000000
StartLine 500
StopLine 600
]
]
node [
id 2
label "writeMesh_0"
type "writeMesh"
graphics [
x 257.000000
y 76.000000
]
params [
obj_filename "demo.obj"
ply_filename "(UNSET)"
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
