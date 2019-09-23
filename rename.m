clear; clc; close all;

%%

[files,paths] = uigetfile('.wav','multiselect','on');



%%

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

    
    
    
    
  