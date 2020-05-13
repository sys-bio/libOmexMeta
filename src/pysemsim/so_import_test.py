import ctypes
import os

wd = os.path.dirname(os.path.realpath(__file__))

print(wd)
f = os.path.join(wd, "libsemsim.so")

if not os.path.isfile(f):
    raise FileNotFoundError(f)

print(f)

lib = ctypes.CDLL(f)

# rdf_ptr = lib.RDF()
#
# lib.RDF_fromString(rdf_ptr, rdf, "rdf_xml")

# class RDF(ctypes.Structure):
    # _fields_ = [("x", c_int),
    #              ("y", c_int)]

def wrap_function(lib, funcname, restype, argtypes):
    """Simplify wrapping ctypes functions"""
    func = lib.__getattr__(funcname)
    func.restype = restype
    func.argtypes = argtypes
    return func

class Test(object):

    def __init__(self):
        self.obj = lib.rdf_new_ptr()
        self.fromString = lib.RDF_fromString
        self.fromString.argtypes = [ctypes.POINTER]
        self.fromString.restypes = []


        # self.test_initialize = self.test_library.initializetest
        # self.test_initialize.argtypes = []
        # self.test_initialize.restype = c_char_p # c_char_p is a pointer to a string
        # self.test_search = self.test_library.searchtest
        # self.test_search.restype = c_int
        # self.test_search.argtypes = [c_char_p]
        # self.m = c_char_p(self.test_initialize())

    # def search(self):
    #     return self.test_search(self.m).value
#
# r = Test()
# print r.search()



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




