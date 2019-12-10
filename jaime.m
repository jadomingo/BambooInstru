clear; clc; close all;

%%  Take inputs
%   Take input audio file and flatten to mono

[input,fs] = audioread('source_cleaned\angklung\4c.wav');

input = sum(input,2)/2;

input = input / max(abs(input(:)));

% %%  Padding
%   Pad zeros to end of audio file

%input = [input; zeros(8*ceil(numel(input)/8) - numel(input),1)];
n = 2^nextpow2(length(input));

%%  Peak picking
%   Find first few peaks with specific minimum peak prominence 
%   and peak height

npeaks = 32;

winlen = 0.02; % seconds
overlap = 0.01;
NFFT = n;
thresh = -inf;
peak_prom = 2.8;
min_peak_distance = 8;

cutoff = fs/2;

[S,F,T,P] = spectrogram(input,blackman(round(fs*winlen)),...
    round(fs*winlen*overlap),NFFT,fs,'power','yaxis');

max_freq_spec = max(10*log10(P),[],2);
% max_freq_spec = max(mag2db(abs(S)),[],2);

[peaks,peak_locs] = findpeaks(max_freq_spec,...
    'minpeakheight',thresh,...
    'sortstr','descend',...
    'minpeakprominence',peak_prom,...
    'minpeakdistance',min_peak_distance,...
    'npeaks',npeaks);   

figure;
plot(F,max_freq_spec);
xlabel('Frequency (Hz)');
ylabel('Gain (dB)');
title('Spectrogram Gain vs Frequency - C4');

xlim([0 fs/2])
grid on;
%
hold on;
peak_freqs = F(peak_locs);
peak_freqs_cutoff = cat(2,peak_freqs(peak_freqs < cutoff),peaks(peak_freqs < cutoff));
plot(peak_freqs_cutoff(:,1),peak_freqs_cutoff(:,2),'v');
hold off;

% sort_peak_locs = sort(peak_locs);
sort_peak_locs = sort(peak_locs(peak_freqs < cutoff));
peak_locs = peak_locs(peak_freqs < cutoff);
% P = (abs(S));

%%  Temporal envelopes per partial frequency
%   Get temporal envelopes of frequency bands within `freq_width` Hz from
%   peaks
%
%   Envelopes found by taking the highest gain in the frequency band in a 
%   certain time index (i.e. with a `freq_width` of zero, only the envelope
%   of the peaks will be taken)

%   Fill buffer with magnitude data of freuency band surrounding peaks and
%   get the highest points
% limit = ceil(freq_width*((NFFT/2)+1)/(fs/2));
% buf = zeros(2*limit+1,numel(T));
freq_temporal_env = zeros(numel(sort_peak_locs),numel(T));
for i = 1:numel(sort_peak_locs)
    freq_temporal_env(i,:) = max(abs(S(sort_peak_locs(i),:)),[],1);
end

%   Plot temporal envelopes per peak partial
figure;
plot(T,10*log10(freq_temporal_env));
xlabel('Time (s)');
ylabel('Gain (dB)');
title('Gain Envelopes per Partial');
grid on;
% axis([0 numel(input)/fs -inf inf]);
xlim([0 numel(input)/fs]);

%%  Synthesize using SOS

%   Resample temporal envelopes to fit time vector
An = resample(freq_temporal_env',numel(input),numel(T))';

%   Create new time vector with the same length as input signal
Time = linspace(0,(numel(input)-1)/fs,numel(input));

%   Generate pure sines with frequecies same as picked peaks
freqs = sin(2*pi*F(sort_peak_locs)*Time);

%   Additively combine sines and normalize to highest peak
An = An / max(abs(An(:)));
out = An .* freqs;
out = sum(out,1);

%%  find start of decay and release portion

[~,peak_amp_index] = findpeaks((freq_temporal_env(1,:)),'npeaks',1,'sortstr','descend'); % gets rightmost peak

% figure;
% plot(T,freq_temporal_env(1,:));
% hold on;
% plot(T(zx),freq_temporal_env(1,zx),'x');
% hold off;

%%  Get Decay Slopes
%   Get linear slope of decay part 

%   TODO: Programatically find end of decay segment
% T_new = T(peak_amp_index:end);
% FTE_new = freq_temporal_env(:,peak_amp_index:end);

T_new = T(1:end);
FTE_new = freq_temporal_env(:,1:end);

hold on;
for i = 1: length(sort_peak_locs)
    g(i,:) = polyfit(T_new,10*log10(FTE_new(i,:)),1);
    plot(T_new,polyval(g(i,:),T_new),'--k'); 
end
hold off;
legend('f0','f1','f2','f3','Location','northeast');

%%   Fundamental frequency of recorded sample

%   Get length of digital waveguide and parameters for fractional delay
%   filter
f0 = F(peak_locs(1));
L = fs/f0;
nu = L - floor(L);

forder = 8;

%   Compute gain coefficent per peak frequency
gain = 10.^((L*g(:,1))/(20*NFFT));

%   clip gains
gain(gain>=1) = 1;

[b,~] = invfreqz([1; gain; 0],pi*[0; F(sort_peak_locs)/(fs/2) ; 1],forder,0);


% transfer function magic
den = (1-nu)*[zeros(1,round(L)),-b,0] + nu*[0,zeros(1,round(L)),-b];
den(1) = 1;

impulse = impz(1,den);

if (length(impulse) > length(input))
    exc = deconvwnr(input,impulse(1:length(input)),0);
else
    exc = deconvwnr(input,impulse,0);
end

%soundsc(filter(1,den,repmat(exc(Time>0.4431 & Time<.4521),100,1)),fs) 'source\Bumbong\Toledov2-Bumbong-Cavite\3a.wav'

figure;
[H,~] = freqz(b,1,numel(F));
plot(F,mag2db(abs(H)));
hold on;grid on;
h = stem(F,mag2db(sum(gain .* (F(:)' == F(sort_peak_locs)),1)));%axis([0 fs/2 -30 0]);
h.BaseValue = -60;
xlabel('Frequency (Hz)');
ylabel('Gain (dB)');

plot(F,mag2db(1/sqrt(2)).*[ones(1,numel(F))]);
hold off;
title('Gain of each Partial');
legend('Magnitude Resp.','Partial Gains','-3dB','Location','southeast');
%%  Synthesis
%   Digital waveguide implementation 

output = conv(exc,impulse,'full');
%%

subplot(311);plot(Time,input);axis([0 1.5 -1 1]);title('Recording');
subplot(312);plot(Time,exc);axis([0 1.5 -1 1]);title('Excitation');ylabel('Amplitude');
subplot(313);plot(0:1/fs:numel(output)/fs - 1/fs,output./max(abs(output(:))));axis([0 1.5 -1 1]);title('Synthesized');xlabel('Time (s)')

%%  COMPARE INPUT AND OUTPUT FREQUENCY SPECTRUMS

input_mag = abs(fft(input,n)/n);
output_mag = abs(fft(out,n)/n); 
subplot(211);plot(linspace(0,fs/2,n/2),mag2db(input_mag(1:n/2)));
subplot(212);plot(linspace(0,fs/2,n/2),mag2db(output_mag(1:n/2)));
subplot(211);title('Recording FFT');ylabel('Magnitude (dB)');xlabel('Frequency (Hz)');
subplot(212);title('Synthesized FFT');ylabel('Magnitude (dB)');xlabel('Frequency (Hz)');
subplot(212);xlabel('Frequency (Hz)')
subplot(211);axis([0 10000 -100 -20]);grid on;
subplot(212);axis([0 10000 -100 -20]);grid on;

%%  COMPARE INPUT AND OUTPUT WAVEFORMS


subplot(311);plot(Time,input);grid on;ylabel('Magnitude');xlabel('Time (s)');
title('Recorded vs. Synthesized Waveforms - C4');
subplot(312);plot(Time,out);grid on;ylabel('Magnitude');xlabel('Time (s)');
subplot(313);plot(Time,output);grid on;ylabel('Magnitude');xlabel('Time (s)');