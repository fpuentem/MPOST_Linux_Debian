#!./python3.9

import ctypes

mpost = ctypes.cdll.LoadLibrary('./Debug/libMPOST_Linux.so')

mpost.CreateAcceptor()
mpost.RunLoop()
