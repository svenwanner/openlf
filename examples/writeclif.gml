graph [
node [
id 0
label "readCLIF_0"
type "readCLIF"
graphics [
x -232,000000
y 26,000000
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
x -61,000000
y 25,000000
]
params [
epiCircuit "(UNKNOWN)"
mergeCircuit "(UNKNOWN)"
DispStart 3,000000
DispStop 7,000000
DispStep 1,000000
]
]
node [
id 2
label "writeCLIF_0"
type "writeCLIF"
graphics [
x 104,000000
y 44,000000
]
params [
filename "/home/hendrik/projects/openlf/examples/linked.clif"
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
source 1
target 2
source_pad 0
target_pad 0
]
]
