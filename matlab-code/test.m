%GETFREQREP Computes the fft of a given signal.
%   Detailed explanation goes here
dataFileName = 'data.bin';
L = 1000;
Fs = 3125000;
% Load test data 
fileID = fopen(dataFileName);
iq = fread(fileID, [L*2, 1], 'int16');
% Make signal a real signal by removing the quadrature parts
real_part = iq(1:2:end);

% Next, calculate the frequency axis, which is defined by the sampling rate
F_axis = (Fs/2)*linspace(0,1,L);

[Y, Y_SHIFTED] = getFreqRep(real_part);
display (Y_SHIFTED);
% Plot the signal
figure(2);
plot(F_axis, abs(Y_SHIFTED));
title('Magnitude FFT of signal');
xlabel('Frequency (Hz)');
ylabel('Magnitude');
