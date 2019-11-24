function den = DWG_gen(peak_locs,temp_envs,forder,fs,F,T,NFFT)
%DWG_gen  Generates audio waveform using Digital Waveguide Synthesis
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
freq_temporal_env = zeros(numel(peak_locs),numel(T));
for i = 1:numel(peak_locs)
    freq_temporal_env(i,:) = max(abs(temp_envs(peak_locs(i),:)),[],1);
end

%   Find start of decay portion

[~,peak_amp_index] = findpeaks((freq_temporal_env(1,:)),'npeaks',1,'sortstr','descend'); % gets rightmost peak

%  Get Decay Slopes

T_new = T(peak_amp_index:end);
FTE_new = freq_temporal_env(:,peak_amp_index:end);

for i = 1: length(peak_locs)
    g(i,:) = polyfit(T_new,mag2db(FTE_new(i,:)),1);
end

%   Get length of digital waveguide and parameters for fractional delay
%   filter
f0 = F(peak_locs(1));
L = fs/f0;
delta = L - floor(L);
eta = (1-delta)/(delta+1);

%   Compute gain coefficent per peak frequency
gain = 10.^((L*g(:,1))/(20*NFFT));

[b,~] = invfreqz([0 ; gain; 0],pi*[0; F(peak_locs)/(fs/2); 1],forder,0);

%   pseudo-inverse filter

den = [1,zeros(1,round(L)),-b];
% den = den(1:5000);%   truncate

end