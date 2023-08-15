#!/usr/bin/env python

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension


mmrunner_module = Extension('_mmrunner',
                           sources=['mmrunner_wrap.cxx', 
                                    'MDAPosition.cpp',
                                    'MDAEvent.cpp',
                                    'MMRunner.cpp'],
                               swig_opts=[
        '-c++',
        '-py3',
                               ]
                           )

setup (name = 'mmrunner',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Simple swig mmrunner from docs""",
       ext_modules = [mmrunner_module],
       py_modules = ["mmrunner"],
       )