# PiLo
An interface for connecting a raspberry pi to the parallax Activity Board 360
Please navigate to [Tutorial.pdf](https://github.com/torencaldwell/PiLo/blob/master/Tutorial.pdf) for hardware and library setup

Python2.x/3.x version by [hdmifish](https://github.com/hdmifish) available. 

Usage: 
```python
from PiLo import PiLo

p = PiLo()

p.sendCommand(1,100,100) #will spin the wheels at 100 ticks/second indefinitely
p.sendCommand(1, 0, 0) #stop
```
