clear; clc; close all;

%%  Take inputs
%   Take input audio file and flatten to mono

[input,fs] = audioread('source\Bumbong\OrigCalabig-Bumbong\3a.wav');
input = sum(input,2)/2;
input = input/max(abs(input(:)));

%%  Padding
%   Pad zeros to end of audio file

%input = [input; zeros(8*ceil(numel(input)/8) - numel(input),1)];
n = 2^nextpow2(length(input));

%%  Peak picking
%   Find first few peaks with specific minimum peak prominence 
%   and peak height

winlen = 0.02; % seconds
overlap = 0.01;
NFFT = n;
npeaks = 8;
thresh = -120;
peak_prom = 0;
% freq_width = 512;


[S,F,T,P] = spectrogram(input,blackman(round(fs*winlen)),...
    round(fs*winlen*overlap),NFFT,fs,'power','yaxis');

max_freq_spec = max(10*log10(P),[],2);
% max_freq_spec = max(mag2db(abs(S)),[],2);

[peaks,peak_locs] = findpeaks(max_freq_spec,...
    'minpeakheight',thresh,...
    'sortstr','descend',...
    'minpeakprominence',peak_prom,...
    'npeaks',npeaks);   

figure;
plot(F,max_freq_spec);
xlabel('Frequency (Hz)');
ylabel('Gain (dB)');
title('Spectrogram Gain vs Frequency - C4');

axis([0 fs/2 -inf inf]);
grid on;
%
hold on;
plot(F(peak_locs),peaks,'v');
hold off;

peak_locs = sort(peak_locs); % determines if fundamental frequency is first peak or highest peak

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
freq_temporal_env = zeros(numel(peak_locs),numel(T));
for i = 1:numel(peak_locs)
%     if (F(peak_locs(i)) > limit)
%         if (F(peak_locs(i)) + limit <= fs/2)
%             buf = P(peak_locs(i)-limit:peak_locs(i)+limit,:);
%         else
%             buf = P(peak_locs(i)-limit:end,:);
%         end
%     else
%         if (F(peak_locs(i)) + limit <= fs/2)
%             buf = P(1:peak_locs(i)+limit,:);
%         else     
%             buf = P(1:end,:);
%         end
%     end
    freq_temporal_env(i,:) = max(P(peak_locs(i),:),[],1);
end

%   Plot temporal envelopes per peak partial
figure;
plot(T,10*log10(freq_temporal_env));
xlabel('Time (s)');
ylabel('Gain (dB)');
title('Gain Envelopes per Partial');
legend('f0','f1','f2','f3','f4','f5','f6','f7','Location','northeast');
grid on;
axis([0 numel(input)/fs -inf inf]);

%%  Synthesize using SOS

%   Resample temporal envelopes to fit time vector
An = resample(freq_temporal_env',numel(input),numel(T))';

%   Create new time vector with the same length as input signal
Time = linspace(0,(numel(input)-1)/fs,numel(input));

%   Generate pure sines with frequecies same as picked peaks
freqs = sin(2*pi*F(peak_locs)*Time);

%   Additively combine sines and normalize to highest peak
out = An .* freqs;
out = sum(out,1);
out = out./max(abs(out(:)));

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
T_new = T(peak_amp_index:end);
FTE_new = freq_temporal_env(:,peak_amp_index:end);

hold on;
for i = 1: length(peak_locs)
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
delta = L - floor(L);
eta = (1-delta)/(delta+1);

forder = 32 + 1;

%   Compute gain coefficent per peak frequency
gain = 10.^((L*g(:,1))/(20*NFFT));

% [b,a] = invfreqz([0; gain; 0],[0; F(peak_locs)/(fs/2); 1],1,0);
b = fir2(forder,[0; F(peak_locs)/(fs/2); 1],[0; gain; 0]);

%   TODO: Fix pseudo-inverse filter
% exc = filter([1 zeros(1,floor(L)-1)],1+[b zeros(1,floor(L))],input);

exc = filter(1+[b zeros(1,floor(L))],[1 zeros(1,floor(L)-1)],input);

exc = exc./max(abs(exc(:)));

figure;
[H,~] = freqz(b,1,numel(F));
plot(F,10*log10(abs(H)));
hold on;grid on;
h = stem(F,10*log10(sum(gain .* (F(:)' == F(peak_locs)),1)));%axis([0 fs/2 -30 0]);
h.BaseValue = -60;
xlabel('Frequency (Hz)');
ylabel('Gain (dB)');

plot(F,mag2db(1/sqrt(2)).*[ones(1,numel(F))]);
hold off;
title('Gain of each Partial');
legend('Magnitude Resp.','Partial Gains','-3dB','Location','southeast');
%%  Synthesis
%   Digital waveguide implementation 

frac_delay = 0;
forward_delay = zeros(1,floor(L));
loopfilt = zeros(1,numel(b));
output = zeros(1,numel(exc));

for i = 1 : numel(exc)                
        in_forward_delay = exc(i)-sum(b.*loopfilt);
        in_frac_delay = forward_delay(end) - eta*frac_delay;
        in_loopfilt = frac_delay+eta*frac_delay;
        in_output = frac_delay+eta*frac_delay;
        
        forward_delay = circshift(forward_delay,1);
        forward_delay(1) = in_forward_delay;
        output = circshift(output,-1);
        output(end) = in_output;
        frac_delay = in_frac_delay;
        loopfilt = circshift(loopfilt,1);
        loopfilt(1) = in_loopfilt;
end
output = output./max(abs(output(:)));

%%

subplot(311);plot(Time,input);axis([0 1.5 -1 1]);title('Recording');
subplot(312);plot(Time,exc);axis([0 1.5 -1 1]);title('Excitation');ylabel('Amplitude');
subplot(313);plot(Time,output./max(abs(output(:))));axis([0 1.5 -1 1]);title('Synthesized');xlabel('Time (s)')

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


subplot(211);plot(Time,input);grid on;ylabel('Magnitude');xlabel('Time (s)');
title('Recorded vs. Synthesized Waveforms - C4');
subplot(212);plot(Time,out);grid on;ylabel('Magnitude');xlabel('Time (s)');
