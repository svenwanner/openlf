graph [
type "StructureTensor_Part1"
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
label "OP_Scharr_1"
type "OP_Scharr"
graphics [
x -304.589928
y -41.129496
]
]
node [
id 9
label "OP_Gauss_0"
type "OP_Gauss"
graphics [
x -451.640288
y -40.000000
]
params [
x_blur 0.000000
y_blur 0.000000
]
]
edge [
source 8
target 0
source_pad 1
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
source 9
target 8
source_pad 0
target_pad 0
]
outputedge [
source 5
source_pad 0
target_pad 0
]
outputedge [
source 6
source_pad 0
target_pad 1
]
outputedge [
source 7
source_pad 0
target_pad 2
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
