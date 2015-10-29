graph [
node [
id 0
label "readCLIF_0"
type "readCLIF"
graphics [
x -171.000000
y 14.000000
]
params [
filename "/home/hendrik/projects/clif/examples/alldata_calib.clif"
dataset "(UNSET)"
]
]
node [
id 1
label "writeCLIF_0"
type "writeCLIF"
graphics [
x 133.000000
y 51.000000
]
params [
filename "/home/hendrik/projects/openlf/examples/disparity.clif"
dataset "(UNSET)"
]
]
node [
id 2
label "procEPI2D_0"
type "procEPI2D"
graphics [
x -24.000000
y 39.000000
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
edge [
source 2
target 1
source_pad 0
target_pad 0
]
edge [
source 0
target 2
source_pad 0
target_pad 0
]
]
