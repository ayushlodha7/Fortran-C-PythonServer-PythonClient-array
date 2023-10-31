import requests
import numpy as np

response = requests.get("http://149.159.235.155:8080/retrieve_array")
array_from_fortran = np.frombuffer(response.content, dtype=np.float32)

print(f"Array from Fortran client: {array_from_fortran}")
