%% Script for generating C source code from MATLAB code

% clear the codegen directory
status = rmdir("codegen\", 's');

% create a config object, and specify various properties:
coderConfig = coder.config('lib'); % the MATLAB code can be seen as a library
coderConfig.TargetLang = 'C'; % let's use C 
coderConfig.GenerateMakefile = true; % want the make file, to easily compile
coderConfig.GenCodeOnly = true; % only need the source code
coderConfig.Toolchain = 'Automatically locate an installed toolchain'; % this can be to specify an existing

% specify template argument types, so MATLAB knows what data types to use
% in the compiled code.
% since we will be reading in the file data as int16, just create an array
% of int16 values, so coder can optimize code knowing that the input will
% be int16 values (this will map to the short type in C)
templateInput = ones(1, 100000, 'int16');

codegen -report -config coderConfig getFreqRep.m -args templateInput