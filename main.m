clear; clc; close all;

%%  Take inputs
%   Take input audio file and flatten to mono

[files,paths] = uigetfile('.wav','multiselect','on');

%%
npeaks = 6;
winlen = 0.03;
overlap = 0;
thresh = -60;
peak_prom = 10;
%%
for i = 1 : numel(files)
    [input,fs] = audioread(strcat(paths,files{i}));
    input = sum(input,2)/2;
    n = 2^nextpow2(length(input));
    
    [peak_freqs{i}, F{i}, T{i}, P{i}] = extract_peak_freqs(input, fs, npeaks, winlen, overlap, thresh, n);
end