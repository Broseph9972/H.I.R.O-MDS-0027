# H.I.R.O-MDS-0027
a music video faithful mp3 player based on the H.I.R.O from good kid Music videos. built for Hack club fallout in about 2 weeks. My favorite Hardware project yet
---
<p align="center">
<img width="420" height="595" alt="A5 - 1 (2)" src="https://github.com/user-attachments/assets/7f929a32-c703-42aa-b72f-917fcbccfb31" />
<img width="585" height="780" alt="image" src="https://github.com/user-attachments/assets/95b70bfb-2dd5-4de5-b6da-58a889d61db2" />
</p>

I unironically listened to almost exclusively good kid while making this project.

---
## Why?
I've always loved good kid, and i was bored at night watching some of their music videos, and saw a scene of the H.I.R.O taken apart with a soldering iron,[^1] and realised, i could probably make that.
I cant explain how to use it yet, as i have not built it yet, but it should go something like select a song or playlist, and itll play said song or playlist. (duh)
This is my first project where i'm not very concerned about budget, as it isnt completely practical, it just needs to look as close as possible to the original. I did get rid of the arms and legs because it would make it annoying to use imho.


# Assembly

## Read through this before starting just for understanding.

  1. Solder Parts Onto the PCB. As there are many SMD Components and small capacitors, reflow soldering is recommended. Use long header pins for the screen DO NOT SOLDER THE SCREEN TO THE PCB YET.
  2. If any Through Hole parts poke into the case, like the speaker, use pliers or something to take them off. there should be indents in the case for them though.
  3. Place the PCB Onto the Main Casing. If it dosent fit, just sand the part until it does.
  4. Screw In the screen to the 4 square brackets on the main casing with M3x14 Screws.
  5. Solder the Screen Connector pins to the screen. (if gpio are short, im so sorry but i would just desolder and use jumper wires.)
  6. Plug in the battery to the JST Connector. Slide it wherever it fits, i reccomend under the screen. any lipo battery should work.
  7. (vid isnt accurate) Slide the buttons into place so that the lip dosent allow it to get pushed out.
  8. Place the Lid on Top, Turn the main casing over, and screw in 3 M3x14 Screws.
  9. (Optional) Paint it! it looks so much cooler Painted. I highly reccomend this.

### Assembly Video (its really bad)
https://github.com/user-attachments/assets/d8cce7da-2541-4a06-ba8f-5a0993665533

# Usage
The H.I.R.O has 3 inputs.
1. Button 1
2. Button 2
3. Clicky Knob

Spin the knob to cycle through the options on the screen. Click the knob to select.
Button 1 is for skipping to the next song. Hold to skip past 10s at a time in a specific song.
Button 2 is for rewinding. Click once to go to the last song. click twice to restart the song. Hold to go back 10s at a time in the song. 
# Setup
  1. Flash the Firmware for the MP3 Using arduino IDE or whichever ide you prefer
  2. Insert MicroSD Card With Music on it in Mp3 (or FLAC?) Format.
  3. Play your Music!

<p align="center">
  <img width="220" alt="image" src="https://github.com/user-attachments/assets/07dba6d8-bd7b-4430-a1e3-d626a203aa2f" />
  <img width="220" alt="image" src="https://github.com/user-attachments/assets/46cd8b47-4472-474c-b198-8e87837316af" />
  <img width="220" alt="image" src="https://github.com/user-attachments/assets/7827c1a9-077a-45b3-a236-c7bfe48a18dc" />
</p>


# Bill of Materials

| Name | Qty | Reference(s) | Price (USD) | Comments | Link |
|------|-----|--------------|-------------|----------|------|
| Seeed XIAO ESP32-S3 Plus | 1 | U1 | $7.59 | Main MCU module. SMD footprint (castellated). Source direct from Seeed for genuine part. | [Link](https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32S3-Plus-p-6361.html) |
| PCM5102A DAC (TSSOP-20) | 1 | U2 | $1.11 | Bare IC from LCSC (C107671). I2S DAC driving the 3.5mm headphone jack. | [Link](https://www.lcsc.com/product-detail/C107671.html) |
| MAX98357A Class-D Amplifier (TQFN-16) | 1 | U3 | $2.00 | Bare TQFN-16 3x3mm IC — NOT a breakout module. Check LCSC / DigiKey / Mouser for current price. | [Link](https://octopart.com/max98357aete+t-maxim+integrated-33346832) |
| CVS-1708 Speaker | 1 | LS1 | $4.02 | 8Ω 200mW 1.2kHz–20kHz. Same Sky (formerly CUI). DigiKey. | [Link](https://www.digikey.com/en/products/detail/same-sky-formerly-cui-devices/CVS-1708/2791829) |
| Hirose DM3AT-SF-PEJM5 microSD Slot | 1 | J1 | $1.53 | Push-push with card detect. LCSC (C114218). | [Link](https://www.lcsc.com/product-detail/SD-Card-Connectors_HRS-Hirose-DM3AT-SF-PEJM5_C114218.html) |
| CUI SJ-3523-SMT-TR 3.5mm Audio Jack | 1 | J2 | $0.88 | Horizontal SMT stereo TRS jack. DigiKey. | [Link](https://www.digikey.com/en/products/detail/cui-devices/SJ-3523-SMT-TR/281297) |
| 1×8 Pin Header 2.54mm (through-hole) | 1 | J3 | $7.99 | Screen connector for Waveshare LCD. Must use long header pins (see assembly notes). | [Link](https://www.amazon.com/whiteeeen-Break-Away-Header-Straight-Connector/dp/B0B75RKMD2) |
| JST PH S2B-PH-K 2-pin Connector | 1 | J4 | $0.11 | Battery connector. 2.0mm pitch horizontal SMT. | [Link](https://www.digikey.com/en/products/detail/jst-sales-america-inc/S2B-PH-K-S/926626) |
| Omron B3U-3100P-B Side Push Button | 2 | S1 / S2 | $1.17 | SMD side-actuated tactile. DigiKey. ×2 units needed. | [Link](https://www.digikey.com/en/products/detail/omron-electronics-inc-emc-div/B3U-3100P-B/1811780) |
| EC11 Right-Angle Rotary Encoder (w/ switch) | 1 | SW1 | $4.07 | Push-switch + encoder. Right-angle EC11. | [Link](https://www.aliexpress.us/item/3256809185234399.html) |
| Capacitor 10µF 0603 | 4 | C1 / C4 / C5 / C6 | $0.01 | X5R or X7R ceramic decoupling. Order from LCSC. | [Link](https://www.lcsc.com/search?q=10uF+0603) |
| Capacitor 100nF 0603 | 2 | C2 / C3 | $0.01 | X7R ceramic decoupling. Order from LCSC. | [Link](https://www.lcsc.com/search?q=100nF+0603) |
| Resistor 1MΩ 0603 | 1 | R1 | $0.01 | 1% tolerance preferred. Order from LCSC. | [Link](https://www.lcsc.com/search?q=1M+0603+resistor) |
| Waveshare 2.4in LCD Module | 1 | — | $18.99 | 240×320 SPI (ILI9341). Connects to J3 header. Closest size match to original H.I.R.O screen. | [Link](https://www.amazon.com/Waveshare-2-4inch-Display-Resolution-Interface/dp/B08H24H7KX) |
| LiPo Battery 3.7V | 1 | — | $9.99 | Any single-cell LiPo with JST PH 2.0mm connector. Slides under screen in case. 500mAh+ recommended. | [Link](https://www.amazon.com/Battery-Rechargeable-Lithium-Polymer-Connector/dp/B07S84SBV3) |
| M3×14 Socket Head Cap Screws | 7 | — | $6.99 | 4× screen brackets + 3× lid. Stainless steel A2. | [Link](https://a.co/d/00dNH8NP) |
| 3D Printed Main Casing | 1 | — | $0.10 | Print from Cad/ directory. Sand if needed for PCB fit (see assembly notes). | [Link](https://github.com/Broseph9972/H.I.R.O-MDS-0027/tree/main/Cad) |
| 3D Printed Lid | 1 | — | $0.10 | Print from Cad/ directory. 3× M3×14 screw holes. | [Link](https://github.com/Broseph9972/H.I.R.O-MDS-0027/tree/main/Cad) |
| Custom PCB (H.I.R.O) | 1 | — | $7.50 | Fabricate from Pcb/ gerbers. JLCPCB / PCBWay / OSH Park. | [Link](https://github.com/Broseph9972/H.I.R.O-MDS-0027/tree/main/Pcb) |
| Paint (optional) | 1 | — | $0 | Spray paint or acrylic. | — |

[^1]:From [Eastside](https://www.youtube.com/watch?v=-kVTMlbAywQ) 
