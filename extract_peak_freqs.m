function [peak_locs, S, F, T, P] = extract_peak_freqs(input, fs,...
    npeaks, winlen, overlap, thresh, NFFT, peak_prom)
%EXTRACT_PEAK_FREQS  Returns list of peak frequencies from an input signal
%   
%   Returns the complex double FFT and the power spectrum for each frame,
%   and vectors for the time and frequency axes.
%
%   Author: Jaime Domingo

[S,F,T,P] = spectrogram(input,blackman(round(fs*winlen)),...
    round(fs*winlen*overlap),NFFT,fs,'power','yaxis');

max_freq_spec = max(abs(S),[],2);

[~,peak_locs] = findpeaks(max_freq_spec,...
    'minpeakheight',thresh,...
    'sortstr','descend',...
    'minpeakprominence',peak_prom,...
    'minpeakdistance',100,...
    'npeaks',npeaks);

peak_locs = sort(peak_locs);

end