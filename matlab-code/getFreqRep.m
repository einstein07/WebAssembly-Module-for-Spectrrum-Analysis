function [mag, phase] = getFreqRep(x) %codegen
%GETFREQREP Computes the fft of a given signal.
%   [Y] = GETFREQREP(X) computes the fast fourier transform of a real 
%   signal. X is an M-by-1 vector. Y is an M-by-1 vector that contains the 
%   results of the fft operation on X.

mag = zeros(size(x), 'double');
phase = zeros(size(x), 'double');
y = fftshift(fft(x));
mag = abs(y);
phase = phase(y);

end