#!/usr/bin/python3

from setuptools import setup,find_packages

setup(
    name='viennatp',
    version='0.0.1',
    description="ViennaTestProject",
    long_description='Test Prject for CPP Python interaction',
    packages=['viennatp'], #get_active_folders(), #find_packages(),
    #packages=find_packages(),
    package_dir={'viennatp': 'ViennaTestProject'},
    #install_requires=['numpy', 'scipy', 'matplotlib'], 
    # url='https://tcl-git.iue.tuwien.ac.at/TCAD/viennatp',
)

