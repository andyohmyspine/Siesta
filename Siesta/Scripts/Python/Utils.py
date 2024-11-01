def turn_array_into_string(array: list[str]) -> str:
    out = str()
    for val in array:
        out += val + " "
    return out
