import ctypes 


bibl = ctypes.CDLL('./bibl.so')

bibl.init_alg.restype = ctypes.c_void_p
bibl.init_alg.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_double, ctypes.POINTER(ctypes.c_double), ctypes.c_int, ctypes.c_int, ctypes.c_double, ctypes.c_double, ctypes.c_double]

bibl.del_alg.restype = ctypes.c_void_p
bibl.del_alg.argtypes = [ctypes.c_void_p]

bibl.init_crm.restype = ctypes.c_void_p
bibl.init_crm.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double , ctypes.c_int, ctypes.c_int]

bibl.del_crm.restype = ctypes.c_void_p
bibl.del_crm.argtypes = [ctypes.c_void_p]

bibl.stepHybridAlgorithm.restype = ctypes.POINTER(ctypes.POINTER(ctypes.c_void_p))
bibl.stepHybridAlgorithm.argtypes = [ctypes.c_void_p]

bibl.chromosome_genes.restype = ctypes.POINTER(ctypes.c_double)
bibl.chromosome_genes.argtypes = [ctypes.c_void_p]

bibl.chromosome_esteem.restype = ctypes.c_double
bibl.chromosome_esteem.argtypes = [ctypes.c_void_p]

bibl.chromosome_len.restype = ctypes.c_int 
bibl.chromosome_len.argtypes = [ctypes.c_void_p]

class Algorithm:
    def __init__(self, count_individs, count_steps, probMutation, mass_coefs_polynom, iteration, criterion, left, right):
        leng =len(mass_coefs_polynom)
        c_array = (ctypes.c_double*leng)(*mass_coefs_polynom)
        self.obj = bibl.init_alg(count_individs, count_steps, probMutation, c_array, leng, iteration, criterion, left, right)
        self.nestor = []
        self.current_iteration = 0
    def __del__(self):
        bibl.del_alg(self.obj)
    def step(self):
        ans = []
        est = []
        vec = bibl.stepHybridAlgorithm(self.obj)
        for i in range(3):
            est.append(bibl.chromosome_esteem(vec[i]))
            tmp = bibl.chromosome_genes(vec[i])
            size = bibl.chromosome_len(vec[i])
            genome = [tmp[i] for i in range(size)]
            ans.append(genome)
        return ans, est
    

