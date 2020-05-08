import os, glob, ctypes

wd = os.path.dirname(__file__)
f = os.path.join(wd, "libsemsim.so")


lib = ctypes.cdll.LibraryLoader(f)


# class RDF:
#     def __init__(self):
#         lib.RDF.argtypes = [ctypes.c_void_p]
#         lib.RDF.restype = ctypes.c_void_p
#
# RDF()

# class Foo(object):
#     def __init__(self, val):
#         lib.Foo_new.argtypes = [ctypes.c_int]
#         lib.Foo_new.restype = ctypes.c_void_p
#         lib.Foo_bar.argtypes = [ctypes.c_void_p]
#         lib.Foo_bar.restype = ctypes.c_void_p
#         lib.Foo_foobar.argtypes = [ctypes.c_void_p, ctypes.c_int]
#         lib.Foo_foobar.restype = ctypes.c_int
#         self.obj = lib.Foo_new(val)
#
#     def bar(self):
#         lib.Foo_bar(self.obj)
#
#     def foobar(self, val):




