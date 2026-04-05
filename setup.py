from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "sistema_recomendacao_py", 
        [
            "wrapper.cpp", 
            "moduloBusca.cpp", 
            "moduloListaCompras.cpp", 
            "moduloRecomendacao.cpp", 
            "moduloSimilaridade.cpp"
        ],
    ),
]

setup(
    name="sistema_recomendacao_py",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)