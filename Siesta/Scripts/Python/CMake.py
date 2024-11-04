import Utils as util
from os import system

class CmakeMacroGenerator:
    def __init__(self) -> None:
        self.macros = list()
        
    def enable_bool_option(self, name: str) -> None:
        self.macros.append(f"-D{name}=ON")
        
    def __str__(self) -> str:
        return util.turn_array_into_string(self.macros)

def invoke_cmake_gen(macro_gen: CmakeMacroGenerator):
    system(f"cmake . -B.DevFiles {macro_gen}")
    
def invoke_cmake_build(config: str, macro_gen: CmakeMacroGenerator):
    system(f"cmake . -B.Packaged {macro_gen}")
    system(f"cmake --build .Packaged --config {config}")