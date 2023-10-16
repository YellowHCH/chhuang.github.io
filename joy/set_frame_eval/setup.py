from distutils.core import setup, Extension

ext_module = Extension('use_custom_frame_eval',
                    sources = ['set_frame_eval_func.c'])

setup (name = 'use_custom_frame_eval',
       ext_modules = [ext_module])
