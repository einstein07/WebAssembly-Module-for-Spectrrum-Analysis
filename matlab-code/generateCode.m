%% Script for generating C source code from MATLAB code

% clear the codegen directory
status = rmdir("codegen\", 's');

% create a config object, and specify various properties:
coderConfig = coder.config('lib'); % the MATLAB code can be seen as a library
coderConfig.TargetLang = 'C'; % let's use C 
coderConfig.GenCodeOnly = true; % only need the source code
coderConfig.Toolchain = 'Automatically locate an installed toolchain'; % this can be to specify an existing

% specify template argument types, so MATLAB knows what data types to use
% in the compiled code:
% since we will be reading in the file data as int16, just create an array
% of int16 values, so coder can optimize code knowing that the input will
% be int16 values (this will map to the short type in C)
templateInput = ones(1, 100000, 'int16');

codegen -report -config coderConfig getFreqRep.m -args templateInput

% the code generations creates various build files in
% "codegen/lib/getFreqRep". Let's use Matlab's packNGo function to create a
% zip file that contains all the necessary headers and source code from the
% build. This will produce a "getFreqRep.zip" file
buildInfoFile = fullfile('./codegen/lib/getFreqRep/', 'buildInfo.mat');
packNGo(buildInfoFile);

% let's take this zip archive, and unzip it to "../c-code/src/matlab/".
unzip("getFreqRep.zip", "../c-code/src/matlab/");