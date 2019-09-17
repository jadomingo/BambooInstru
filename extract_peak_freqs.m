function [peak_freqs, F, T, P] = extract_peak_freqs(input, fs, npeaks, winlen, overlap, thresh, NFFT)
%EXTRACT_PEAK_FREQS  Function returns top npeaks frequencies from input
%      
%
%   Author: Jaime Domingo
peak_prom = 10;

[~,F,T,P] = spectrogram(input,blackman(round(fs*winlen)),...
    round(fs*winlen*overlap),NFFT,fs,'power','yaxis');

max_freq_spec = max(10*log10(P),[],2);

[~,peak_locs] = findpeaks(max_freq_spec,...
    'minpeakprominence',peak_prom,...
    'minpeakheight',thresh,...
    'sortstr','descend',...
    'npeaks',npeaks);

peak_locs = sort(peak_locs);

peak_freqs = F(peak_locs);

end