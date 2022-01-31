cmake_minimum_required(VERSION 3.2)

# We don't use the C++ compiler, so don't let project()
# test for it in case the platform doesn't have one
project(FFT-WASM-Module VERSION 1.0.0 LANGUAGES C)
# Primary tool for this project
add_library(fft_module STATIC
    matlab/getFreqRep_data.c matlab/getFreqRep_data.h
    matlab/getFreqRep_initialize.c matlab/getFreqRep_initialize.h
    matlab/getFreqRep_terminate.c matlab/getFreqRep_terminate.h
    matlab/getFreqRep_types.h
    matlab/getFreqRep.c matlab/getFreqRep.h
    matlab/rtwtypes.h
    matlab/tmwtypes.h
    matlab/FFTImplementationCallback.c
    matlab/FFTImplementationCallback.h
)
