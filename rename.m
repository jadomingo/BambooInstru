%%RENAME Renames input audio recordings based on naming convention
%   
%   Author: Jaime Domingo
clear; clc; close all;

%%  Select Files

[files,paths] = uigetfile('.wav','multiselect','on');

%%  Create new audio files

for i = 1 : numel(files)
    [input{i},fs{i}] = audioread(strcat(paths,files{i}));
    
    note = strsplit(files{i},'_s');
    
    if (note{1}(2) == '#')
        filename_new = [note{1}(3) note{1}(1) 's'];
    else
        filename_new = [note{1}(2) note{1}(1)];
    end
    
    try
        audiowrite(strcat(paths,'new\',filename_new,'.wav'),input{i},fs{i});
    catch
        i
    end
end

%%

    
    
    
    
  