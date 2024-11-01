from SiestaPythonFramework import *

if __name__ == "__main__":    
    macro_gen = cmake.CmakeMacroGenerator()
    macro_gen.enable_bool_option("SIESTA_ENABLE_GPU_VALIDATION")
    
    cmake.invoke_cmake_gen(macro_gen)
    pass
    