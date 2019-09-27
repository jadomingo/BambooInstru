%%MAIN Generates a spreadsheet with a list of peak frequencies.
%
%   Generates an .xlsx spreadsheet containing the list of peak frequencies
%   from the group of files that were selected.
%
%   Assumes the input files follow a specific naming convention.
%
%   Author: Jaime Domingo

clear; clc; close all;

%%  Take inputs
%   Take input audio file and flatten to mono

[files,paths] = uigetfile('.wav','multiselect','on');

%%  Set parameters

npeaks = 16;
winlen = 0.02;
overlap = 0.01;
thresh = -inf;
peak_prom = 1;

%%  Extract peak frequencies

for i = 1 : numel(files)
    [input,fs] = audioread(strcat(paths,files{i}));
    input = sum(input,2)/2;
    n = 2^nextpow2(length(input));
    
    [peak_freqs{i}, S{i}, F{i}, T{i}, P{i}] = extract_peak_freqs(input, fs, npeaks, winlen, overlap, thresh, n, peak_prom);
end

%%  Create Table

path_split = strsplit(paths,'\');
table_name = strcat(path_split{end-2},'.xlsx');

for i = 1 : numel(files)
    new_files{i} = strcat('Note_',files{i}(1:end-4));
end

table = array2table(cell2mat(peak_freqs),'VariableNames',new_files);

writetable(table,strcat('freq_tables\',table_name),'Sheet',1);