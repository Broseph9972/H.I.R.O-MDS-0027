# H.I.R.O-MDS-0027
a music video faithful mp3 player based on the H.I.R.O from good kid Music videos. built for Hack club fallout in about (time) weeks.
---
<img width="727" height="626" alt="image" src="https://github.com/user-attachments/assets/70cbf5b6-5c69-4fd9-96f8-85359d3c164d" />
I unironically listened to almost exclusively good kid while making this project.

---
I've always loved good kid, and i was bored at night watching some of their music videos, and saw a scene of the H.I.R.O taken apart with a soldering iron,[^1] and realised, i could probably make that.
I cant explain how to use it yet, as i have not built it yet, but it should go something like select a song or playlist, and itll play said song or playlist. (duh)
This is my first project where i'm not very concerned about budget, as it isnt completely practical, it just needs to look as close as possible to the original. I did get rid of the arms and legs because it would make it annoying to use imho.

---
#Assembly
##Read through this before starting just for understanding.

  1. Solder Parts Onto the PCB. As there are many SMD Components and small capacitors, reflow soldering is recommended. Use long header pins for the screen DO NOT SOLDER THE SCREEN TO THE PCB YET.
  2. If any Through Hole parts poke into the case, like the speaker, use pliers or something to take them off. there should be indents in the case for them though.
  3. Place the PCB Onto the Main Casing. If it dosent fit, just sand the part until it does.
  4. Screw In the screen to the 4 square brackets on the main casing with M3x14 Screws.
  5. Solder the Screen Connector pins to the screen. (if gpio are short, im so sorry but i would just desolder and use jumper wires.)
  6. Plug in the battery to the JST Connector. Slide it wherever it fits, i reccomend under the screen. any lipo battery should work.
  7. Joe when you figure out how buttons work, do button assembly here
  8. If joe made a propeller thingy put that here
  9. Place the Lid on Top, Turn the main casing over, and screw in 3 M3x14 Screws.
  10. (Optional) Paint it! it looks so much cooler Painted. I highly reccomend this.
#Setup
  1. Flash the Firmware for the MP3 Player (joe show how to do that later)
  2. Insert MicroSD Card With Music on it in Mp3 (or FLAC?) Format.
  3. Play your Music!

add render later from fusion.

the H.I.R.O. uses
- [A 2.4" Screen from waveshare](https://www.waveshare.com/2.4inch-LCD-Module.htm), Closest fitting to the size in the videos.
- Side Push buttons
- PCM5102A (Audio jack stuff)
- A 3.5mm Jack
- A Really fancy MicroSD card slot
- M3 Screws
- Battery
- 3d Printed enclosure (my first really good cad design
- A cusom PCB to hold all components.
- Some paint (optional)
[^1]:From [Eastside](https://www.youtube.com/watch?v=-kVTMlbAywQ)
