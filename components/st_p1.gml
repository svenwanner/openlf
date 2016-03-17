graph [
label "StructureTensor_Max"
type "StructureTensor_Part1"
node [
id 0
label "OP_Scharr_0"
type "OP_Scharr"
graphics [
x -210.000000
y -128.000000
]
]
node [
id 1
label "OP_Tensor2x2_0"
type "OP_Tensor2x2"
graphics [
x -67.000000
y -102.000000
]
]
node [
id 2
label "OP_AverageChannels_0"
type "OP_AverageChannels"
graphics [
x 204.000000
y -186.000000
]
]
node [
id 3
label "OP_AverageChannels_1"
type "OP_AverageChannels"
graphics [
x 210.000000
y -83.000000
]
]
node [
id 4
label "OP_AverageChannels_2"
type "OP_AverageChannels"
graphics [
x 216.000000
y 33.000000
]
]
node [
id 5
label "OP_Gauss_1"
type "OP_Gauss"
graphics [
x 432.000000
y -171.000000
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
x 435.000000
y -70.000000
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
x 441.000000
y 48.000000
]
params [
x_blur 5.000000
y_blur 5.000000
]
]
node [
id 8
label "OP_Gauss_0"
type "OP_Gauss"
graphics [
x -647.640288
y -299.000000
]
params [
x_blur 0.000000
y_blur 0.000000
]
]
node [
id 9
label "OP_Scharr_1"
type "OP_Scharr"
graphics [
x -481.000000
y -295.000000
]
]
node [
id 10
label "OP_Scharr_2"
type "OP_Scharr"
graphics [
x -343.000000
y -220.000000
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
source 8
target 9
source_pad 0
target_pad 0
]
edge [
source 9
target 10
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
target 8
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
component 8
parameter 0
]
alias [
label "pre_blur_y"
component 8
parameter 1
]
]
