import SiestaPythonFramework as siesta
import CMake as cmake

if __name__ == "__main__":    
    macro_gen = cmake.CmakeMacroGenerator()
    macro_gen.enable_bool_option("SIESTA_BUILD_DIST")
    
    cmake.invoke_cmake_build("MinSizeRel", macro_gen)
    pass