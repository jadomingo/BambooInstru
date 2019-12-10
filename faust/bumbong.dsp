import("stdfaust.lib");

declare options "[midi:on][nvoices:32]";

freq = hslider("freq",ba.midikey2hz(60),ba.midikey2hz(0),ba.midikey2hz(127),0.0001);
gate = button("gate");
gain = hslider("gain",0,0,1,0.0001);

blowPressure = hslider("blowPressure",0.3,0,1,0.001);
blowCutoff = hslider("blowCutoff",2000,ba.midikey2hz(0),ba.midikey2hz(127),0.0001);
vibratoFreq = hslider("vibratoFreq[hidden:xx]",0,0,1,0.001);
vibratoGain = hslider("vibratoGain",0,0,1,0.001);

attack = hslider("attack",0.7,0,1,0.001);
release = hslider("release",0.7,0,1,0.001);

closedToOpenEndRatio = hslider("closedToOpenEndRatio",1,0,1,0.0001);
closedEndReflectionRatio = hslider("closedEndReflectionRatio",0.95,0,1,0.0001);
closedEndDispersionRatio = hslider("closedEndDispersionRatio",0.2,0,1,0.0001);
openEndReflectionRatio = hslider("openEndReflectionRatio",.9,0,1,0.0001);
openEndDispersionRatio = hslider("openEndDispersionRatio",0.4,0,1,0.0001);

input = pm.blower(blowPressure,gain,blowCutoff,vibratoFreq,vibratoGain);

tube = pm.endChain( 
  pm.terminations(
	*(openEndReflectionRatio) : si.smooth(openEndDispersionRatio), 
	pm.chain(  pm.out : pm.openTube( pm.f2l( ba.midikey2hz( 0 ) ), ( 1 - closedToOpenEndRatio ) * pm.f2l( freq ) ) : pm.in( input * en.adsre( attack, 0, 1, release, gate ) ) : pm.openTube( pm.f2l( ba.midikey2hz( 0 ) ), closedToOpenEndRatio * pm.f2l( freq ) ) ),
	*(-closedEndReflectionRatio) : si.smooth(closedEndDispersionRatio)
  )
);

process = tube : fi.dcblocker;