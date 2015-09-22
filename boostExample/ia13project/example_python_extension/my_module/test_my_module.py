import _my_module

import numpy



img = numpy.random.rand(4,3)

ret = _my_module.imageLoop(numpy.require(img,dtype=numpy.float32))

print img,'\n',ret