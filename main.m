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

%%  Initialize parameters

npeaks = 200;
winlen = 0.02;
overlap = 0.01;
thresh = -inf;
peak_prom = 0;

%   Initialize empty cells
peak_locs = cell(1,numel(files));
peak_freqs = cell(1,numel(files));
peak_freqs_out = cell(1,numel(files));
S = cell(1,numel(files));
F = cell(1,numel(files));
T = cell(1,numel(files));
P = cell(1,numel(files));
mono = cell(1,numel(files));

input_length = zeros(1,numel(files));
fs = zeros(1,numel(files));

%%  Extract peak frequencies

%   Populate empty cells
for i = 1 : numel(files)
    [input,fs(i)] = audioread(strcat(paths,files{i}));
    mono{i} = sum(input,2)/2;
    n = 2^nextpow2(length(mono{i}));
    
    %   get numel for each input to be used later
    input_length(i) = length(mono{i});
    
    %   get spectrogram of each audio file
    [peak_locs{i}, S{i}, F{i}, T{i}, P{i}] = extract_peak_freqs(mono{i},...
        fs(i), npeaks, winlen, overlap, thresh, n, peak_prom);
end

%   get peak frequencies in F from the peak locations
for i = 1 : numel(files)
    peak_freqs{i} = F{i}(peak_locs{i});
    peak_freqs_out{i} = round(peak_freqs{i});
end

%%  Generate SOS

output_SOS = cell(1,numel(files));
time = linspace(0,(numel(mono{1})-1)/fs(1),numel(mono{1}));
for i = 1 : numel(files)
    temp_envs = abs(S{i});
    
    output_SOS{i} = SOS_gen(peak_locs{i},temp_envs,input_length(i),fs(i),F{i},T{i});
end

%%  Show waveform and FFT

subplot(221);
plot(time,mono{1});grid on;
title('Recording Waveform');
xlabel('Time (s)');
ylabel('Magnitude');
subplot(223);
plot(time,output_SOS{1});grid on;
title('Synthesized Waveform');
xlabel('Time (s)');
ylabel('Magnitude');

in_np2 = 2^nextpow2(numel(mono{1}));
out_np2 = 2^nextpow2(numel(output_SOS{1}));

subplot(222);
plot(linspace(-fs(1)/2,fs(1)/2,in_np2),mag2db(fftshift(abs(fft(mono{1},in_np2)/in_np2))));grid on;
title('Recording FFT');
xlabel('Frequency (Hz)');
ylabel('Magnitude (dB)');
axis([0 fs(1)/2 -inf inf]);
subplot(224);
plot(linspace(-fs(1)/2,fs(1)/2,out_np2),mag2db(fftshift(abs(fft(output_SOS{1},out_np2)/out_np2))));grid on;
title('Synthesized FFT');
xlabel('Frequency (Hz)');
ylabel('Magnitude (dB)');
axis([0 fs(1)/2 -inf inf]);

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

table = array2table(cell2mat(peak_freqs_out));

rot_table = cell2table(table2cell(table)','VariableNames',varnames,'RowNames',new_files);

writetable(rot_table,strcat('freq_tables\csv\Marimba\',table_name),...
    'FileType','spreadsheet',...
    'WriteVariableNames',true,...
    'WriteRowNames',true);