import("stdfaust.lib");

declare options "[midi:on] [nvoices:16]";

//	Inputs
freq = hslider("freq",261.63,20,20000,0.01);
gate = button("gate");
gain = hslider("gain",1,0,1,0.01);
shakeFreq = hslider("shakeFreq",0,0,20,0.5);

//	Functions

trigger = ba.if(shakeFreq == 0, gate, (gate * os.osc(shakeFreq)) >= 0); 

envelope(a,r) = en.arfe(a,r-a,0,ba.impulsify(trigger)) * gain;

s0 = os.osc(1.0000*freq+000.00) * envelope(0.0495918367346939,0.326734693877551) * 0.121157477545092;
s1 = os.osc(2.0104*freq-4.8538) * envelope(0.0297959183673469 ,0.188163265306122) * 0.229344817057941;
s2 = os.osc(3.0958*freq-72.771) * envelope(0.01,0.148571428571429 ) * 0.113097970788361 ;
s3 = os.osc(4.0217*freq+492.84) * envelope(0.01,0.188163265306122) * 0.147125101459152 ;
s4 = os.osc(5.6169*freq+412.52) * envelope(0.01,0.188163265306122) * 0.0738321268768136 ;
s5 = os.osc(7.1442*freq+334.43) * envelope(0.0297959183673469,0.207959183673469) * 0.0971094555118266 ;
s6 = os.osc(7.1966*freq+530.30) * envelope(0.01,0.0891836734693878) * 0.113036477175581 ;
s7 = os.osc(7.4238*freq+1042.4) * envelope(0.01,0.128775510204082) * 0.0876133734143241 ;
s8 = os.osc(8.1804*freq+1108.6) * envelope(0.01,0.0693877551020408) * 0.0855315086548773 ;
s9 = os.osc(9.2439*freq+1417.3) * envelope(0.01,0.168367346938776) * 0.0823551486560556 ;

process = (s0+s1+s2+s3+s4+s5+s6+s7+s8+s9) * 20 ;	//	empirical, just so you can hear the output

effect =  dm.zita_light;

