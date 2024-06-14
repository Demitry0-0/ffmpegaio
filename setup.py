from setuptools import Extension, setup

extensions = [Extension('ffmpegaio', sources=['ffmpegaio.c'])]

setup(ext_modules=extensions)
