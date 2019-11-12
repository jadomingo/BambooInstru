function output = angklung_delay(input,mag,time,fs)

delay_num = zeros(1,round(fs*time));
delay_num(1) = 1;
delay_num(end) = mag;

output = filter(delay_num,1,input);
end