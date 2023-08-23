#!./python3.9

import ctypes

mpost = ctypes.cdll.LoadLibrary('./Debug/libMPOST_Linux.so')

mpost.CreateAcceptor()
mpost.RunLoop()

# Other documents an links
## Python code
# https://github.com/PyramidTechnologies/Python-RS-232/blob/master/host.py#L185
# https://stackoverflow.com/questions/52403928/mei-cash-validator-programming-with-python

## Video links
# https://www.youtube.com/watch?v=l4IrCwFUXfc
# https://www.youtube.com/watch?v=AZYfosDKm2o