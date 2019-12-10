function [peak_locs, S, F, T, P] = extract_peak_freqs(input, fs,...
    npeaks, winlen, overlap, thresh, NFFT, peak_prom, peak_dist)
%EXTRACT_PEAK_FREQS  Returns list of peak frequencies from an input signal
%   
%   Returns the complex double FFT and the power spectrum for each frame,
%   and vectors for the time and frequency axes.
%
%   Author: Jaime Domingo

[S,F,T,P] = spectrogram(input,blackman(round(fs*winlen)),...
    round(fs*winlen*overlap),NFFT,fs,'power','yaxis');

% max_freq_spec = max(abs(S),[],2);
max_freq_spec = max(10*log10(P),[],2);

[~,peak_locs] = findpeaks(max_freq_spec,...
    'minpeakheight',thresh,...
    'sortstr','descend',...
    'minpeakprominence',peak_prom,...
    'minpeakdistance',peak_dist,...
    'npeaks',npeaks);

peak_locs = sort(peak_locs);

end