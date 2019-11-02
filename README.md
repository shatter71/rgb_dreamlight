# rgb_dreamclock
Arduino code for operating RGB Dreamclock using a microphone as input

https://www.thingiverse.com/thing:3641479

I modified the case top and bottom to accommodate adding an electret microphone amplifier and a female barrel jack for power to the original design. All hardware is inside the case (Arduino Nano, a capacitor, a resistor, the microphone, and wiring. Used hot glue to hold everything together and M3-0.5 x 6mm cap screws to secure the base.

I also used a quick disconnect plug for power to the Nano so I can program it from USB if I need to while keeping the LED matrix powered.

I am including the code I wrote to control the LEDs. I wrote in about a half dozen variations for how the matrix will light up. My code isn't commented very well but there isn't much there so shouldn't be difficult to figure out. Also has some code in it from Adafruit to measure sound levels.

https://youtu.be/5rBIQpBkwkU

SOURCE CODE:
https://pastebin.com/E13bxYhh
Audio to A1 and LED data to D3

PARTS:

    Electret Microphone Amplifier - MAX4466 with Adjustable Gain
    https://www.adafruit.com/product/1063
    3A 12v For DC Power Supply Jack Socket Female Panel Mount Connector 5.5mm 2.1mm Plug Adapter 2 Terminal Types 5.5*2.1
    https://www.aliexpress.com/item/10Pcs-3A-12v-For-DC-Power-Supply-Jack-Socket-Female-Panel-Mount-Connector-5-5mm-2/32883658107.html
    1000uF 25V Radial Electrolytic Capacitor 10 x 17mm 105°C
    https://www.banggood.com/20pcs-1000uF-25V-Radial-Electrolytic-Capacitor-10-x-17mm-105C-p-1022623.html
    Through-Hole Resistors - 470 ohm 5% 1/4W
    https://www.adafruit.com/product/2781
    2-pin JST SM Plug + Receptacle Cable Set
    https://www.adafruit.com/product/2880
    M3-0.5 x 6mm cap screws
    https://www.homedepot.com/p/Everbilt-M3-0-5-x-6-mm-Zinc-Plated-Plain-Metric-Socket-Cap-Screw-3-Piece-per-Bag-803168/204808021
    Arduino Nano
    https://www.aliexpress.com/item/Newest-1-pcs-Nano-V3-0-ATmega328P-Module-Board-Free-Mini-USB-Cable-for-Arduino-Compatible/32961269354.html
    8x8 RGB LED matrix
    https://www.banggood.com/CJMCU-64-Bit-WS2812-5050-RGB-LED-Driver-Development-Board-p-981678.html
