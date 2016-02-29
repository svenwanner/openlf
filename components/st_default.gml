graph [
type "DefaultStructureTensor"
node [
id 0
label "OP_Scharr_0"
type "OP_Scharr"
graphics [
x -143.000000
y -42.000000
]
]
node [
id 1
label "OP_Tensor2x2_0"
type "OP_Tensor2x2"
graphics [
x 22.000000
y -2.000000
]
]
node [
id 2
label "OP_AverageChannels_0"
type "OP_AverageChannels"
graphics [
x 228.000000
y -32.000000
]
]
node [
id 3
label "OP_AverageChannels_1"
type "OP_AverageChannels"
graphics [
x 228.000000
y 48.000000
]
]
node [
id 4
label "OP_AverageChannels_2"
type "OP_AverageChannels"
graphics [
x 219.000000
y 130.000000
]
]
node [
id 5
label "OP_Gauss_1"
type "OP_Gauss"
graphics [
x 450.000000
y -18.000000
]
params [
x_blur 5.000000
y_blur 5.000000
]
]
node [
id 6
label "OP_Gauss_2"
type "OP_Gauss"
graphics [
x 455.000000
y 74.000000
]
params [
x_blur 5.000000
y_blur 5.000000
]
]
node [
id 7
label "OP_Gauss_3"
type "OP_Gauss"
graphics [
x 452.000000
y 172.000000
]
params [
x_blur 5.000000
y_blur 5.000000
]
]
node [
id 8
label "OP_Tensor2Orientation_0"
type "OP_Tensor2Orientation"
graphics [
x 658.000000
y -13.000000
]
params [
min_coherence 0.500000
input_disparity 0.000000
]
]
node [
id 9
label "OP_Gauss_0"
type "OP_Gauss"
graphics [
x -497.640288
y -38.000000
]
params [
x_blur 0.000000
y_blur 0.000000
]
]
node [
id 10
label "OP_dx_0"
type "OP_dx"
graphics [
x -323.000000
y -32.000000
]
]
edge [
source 10
target 0
source_pad 0
target_pad 0
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
source_pad 1
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
source_pad 1
target_pad 0
]
edge [
source 1
target 4
source_pad 2
target_pad 0
]
edge [
source 2
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
edge [
source 4
target 7
source_pad 0
target_pad 0
]
edge [
source 5
target 8
source_pad 0
target_pad 0
]
edge [
source 6
target 8
source_pad 0
target_pad 1
]
edge [
source 7
target 8
source_pad 0
target_pad 2
]
edge [
source 9
target 10
source_pad 0
target_pad 0
]
outputedge [
source 8
source_pad 0
target_pad 0
]
outputedge [
source 8
source_pad 1
target_pad 1
]
inputedge [
target 9
source_pad 0
target_pad 0
]
alias [
label "integrate"
component 5
parameter 0
]
alias [
label "integrate"
component 5
parameter 1
]
alias [
label "integrate"
component 6
parameter 0
]
alias [
label "integrate"
component 6
parameter 1
]
alias [
label "integrate"
component 7
parameter 0
]
alias [
label "integrate"
component 7
parameter 1
]
alias [
label "input_disparity"
component 8
parameter 1
]
alias [
label "min_coherence"
component 8
parameter 0
]
alias [
label "pre_blur_x"
component 9
parameter 0
]
alias [
label "pre_blur_y"
component 9
parameter 1
]
]
