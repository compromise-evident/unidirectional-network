### Run it

```apt install g++ geany```. Open the .cpp in Geany. Hit F9 once. F5 to run.

<br>

<p align="center">
  <video src="https://github.com/user-attachments/assets/f62cdb79-e292-4151-b448-677a8ed0e7d3" controls="controls" muted="muted" style="max-width: 100%;">
  </video>
</p>

<br>

### :hocho: Gut a keyboard & sand off black coating

<p align="center">
  <img src="docs/keyboard_guts.png">
</p>

<br>

### Solder photoresistors to leads who type if shorted

<p align="center">
  <img src="docs/keyboard_photoresistors.jpg">
</p>

<br>

### Tape photoresistors to eyes of the sending machine

<p align="center">
  <img src="docs/terminal.png">
</p>

<br>

### Or 345B/s (press enter & play wav at the same time)

This method proves that modern generic photoresistors are
sensitive to at least 5,520 adjustments in brightness per second
(an opposite bit is appended to each data bit to keep
the LED brightness normalized.) The bottleneck is the LED;
it cannot become darker fast enough after each flash of light.

<p align="center">
  <img src="docs/LED/close-up.jpeg">
</p>

<p align="center">
  <img src="docs/LED/materials.jpeg">
</p>

<p align="center">
  <video src="https://github.com/compromise-evident/unidirectional-network/assets/75550631/4a9a4f20-4205-4f49-96c6-10445f4c7c2d" controls="controls" muted="muted" style="max-width: 100%;">
  </video>
</p>

<p align="center">
  <img src="docs/LED/terminal.png">
</p>

See [LED.cpp](https://github.com/compromise-evident/unidirectional-network/blob/main/docs/LED/LED.cpp). (May need to tilt photoresistor away as in video above. Use it in a dark enclosure.) <br>
<sub>*Receiving machine must have audio recording hardware at least like that of the Dell Latitude E5500 (made in 2008.) <br>
If you own a modern thousand-dollar laptop, this won't work; your mic line is always noisy, even when disabled.<sub/>

<br>

### Send files to the sending machine via truly instant NAS (no systemd)

https://github.com/compromise-evident/what-not/blob/main/truly_instant_NAS

<br>

### Send files to the sending machine via local network.

* Sending machine should have the Gnome desktop environment, unfortunately.
  Go to Settings, Sharing. Enable sharing, then enable
  "File Sharing" without password. This creates a "Public"
  folder in /home/user/ if missing.
* Sending machine should run these tools in a new folder in /home/user/Public.
* Now any machine on that network has read / write access
  to that "Public" folder. Find it in your files browser
  in "Browse Network" or "Other Locations" and keep dropping files in folder "Send".

<br>

### DIY

https://github.com/compromise-evident/what-not/blob/main/process_file_by_bits.cpp

https://github.com/compromise-evident/what-not/blob/main/presses_enter_after_you_type_n_characters.cpp

https://github.com/compromise-evident/what-not/blob/main/toggle_num_lock_and_caps_lock.cpp

https://github.com/compromise-evident/what-not/blob/main/date.cpp

<br>

### Appendix

unidirectional-network has been written about on
[HACKADAY](https://hackaday.com/2024/03/19/photoresistors-provide-air-gap-data-transfer-slowly/).
