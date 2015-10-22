graph [
node [
id 0
label "readCLIF_0"
type "readCLIF"
params [
filename "/home/hendrik/projects/clif/examples/demo.clif"
dataset "(UNSET)"
]
]
node [
id 1
label "procEPI2D_0"
type "procEPI2D"
params [
epiCircuit "(UNKNOWN)"
mergeCircuit "(UNKNOWN)"
DispStart 3.000000
DispStop 7.000000
DispStep 1.000000
StartLine 0
StopLine 2160
]
]
node [
id 2
label "writeMesh_0"
type "writeMesh"
params [
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
