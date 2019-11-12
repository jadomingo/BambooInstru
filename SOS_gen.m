function output = SOS_gen(peak_locs,temp_envs,input_length,fs,F,T)
%SOS_GEN  Generates audio waveform using SOS Synthesis
%   
%   Takes arrays of input frequencies and temporal envelopes as input.
%   Temporal envelopes should either be from the PSD or the magnitude of
%   the STFT.
%
%   Generates pure sine tones using the input frequencies and applies the
%   temporal envelope to each before adding.
%
%   Author: Jaime Domingo

%   Extract envelope 
for i = 1 : numel(peak_locs)
    freq_temp_env(i,:) = max(temp_envs(peak_locs(i),:),[],1);
end

%   Resample temporal envelopes to fit time vector
An = resample(freq_temp_env',input_length,numel(T))';

%   Create new time vector with the same length as input signal
Time = linspace(0,(input_length-1)/fs,input_length);

%   Generate pure sines with frequecies same as picked peaks
freqs = sin(2*pi*F(peak_locs)*Time);

%   Additively combine sines and normalize to highest peak
output = An .* freqs;
output = sum(output,1)/numel(peak_locs);
% output = output/max(abs(output(:)));

end