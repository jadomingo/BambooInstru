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

npeaks = 8;
winlen = 0.02;
overlap = 0.01;
thresh = -inf;
peak_prom = 0;

%%  Extract peak frequencies

for i = 1 : numel(files)
    [input,fs] = audioread(strcat(paths,files{i}));
    input = sum(input,2)/2;
    n = 2^nextpow2(length(input));
    
    [peak_freqs{i}, S{i}, F{i}, T{i}, P{i}] = extract_peak_freqs(input,...
        fs, npeaks, winlen, overlap, thresh, n, peak_prom);
    
    peak_freqs{i} = round(peak_freqs{i},2);
end

%%  Generate SOS




%%  Write tables to file

path_split = strsplit(paths,'\');
table_name = strcat(path_split{end-1},'.csv');

new_files = files;
for i = 1 : numel(files)
    new_files{i} = new_files{i}(1:3);
    new_files{i}(1:2) = [new_files{i}(2) new_files{i}(1)];
    if(new_files{i}(3) == 's')
        new_files{i}(3) = '#';
    else
        new_files{i} = new_files{i}(1:2);
    end
end

for i = 1:npeaks
    varnames{i} = strcat('F',int2str(i-1));
end

table = array2table(cell2mat(peak_freqs));

rot_table = cell2table(table2cell(table)','VariableNames',varnames,'RowNames',new_files);

writetable(rot_table,strcat('freq_tables\csv\Marimba\',table_name),...
    'FileType','spreadsheet',...
    'WriteVariableNames',true,...
    'WriteRowNames',true);