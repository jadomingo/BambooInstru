import("stdfaust.lib");

declare options "[midi:on] [nvoices:16]";

freq = hslider("freq",261.63,20,20000,0.01);
gate = button("gate");
gain = hslider("gain",1,0,1,0.01);
cutoff = hslider("cutoff",10000,20,20000,0.01);

attack = hslider("attack",0.0001,0.0001,1,0.001);
release = hslider("release",0.1,0.0001,1,0.001);

envelope = hgroup("envelope",attack,release);

s0 = os.osc(1.0000*freq+000.000) * 0.286681191169015 * en.are(0.0693877551020408,0.7 - 1/ma.SR,ba.impulsify(gate));
s1 = os.osc(3.4110*freq+136.010) * 0.460816360571665 * en.are(1/ma.SR,0.7 - 1/ma.SR,ba.impulsify(gate)); 
s2 = os.osc(6.8330*freq+556.580) * 0.146127080409017 * en.are(1/ma.SR,0.7 - 1/ma.SR,ba.impulsify(gate));
s3 = os.osc(9.9394*freq+1174.10) * 0.0677642101711803 * en.are(1/ma.SR,0.7 - 1/ma.SR,ba.impulsify(gate));
s4 = os.osc(18.098*freq+572.160) * 0.0268084193520404 * en.are(1/ma.SR,0.7 - 1/ma.SR,ba.impulsify(gate));
s5 = os.osc(18.268*freq+2210.10) * 0.011802738327082 * en.are(1/ma.SR,0.7 - 1/ma.SR,ba.impulsify(gate));

sines = s0,s1,s2,s3,s4,s5 :> / (6);

process = sines * gain;
			