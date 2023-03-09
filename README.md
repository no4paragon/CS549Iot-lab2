# Lab 2

# Lab 2: **Highway Traffic Light**

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/400d9c32-3874-400e-a094-aba4a48ebd71/Untitled.png)

Your task is to build a simplified traffic light (TL) controller using the ESP32 board and the provided set of sensors. The TL comprises three LEDs, a buzzer, and a touch button.

Problem description:

- The TL goes from green through yellow to red, and from red through red-yellow to green. The TL remains in red for 10 seconds.
- The TL remains in yellow and red-yellow for 2 seconds.
- The TL has a touch button for pedestrians, it remains in green until the pedestrian button is pressed. The TL remains in green at least 5 seconds after the touch button has become active.
- The TL has a buzzer for visual impairment aid with two modes. When in green the buzzer must be 500 ms on and 1500 ms off; when in red the buzzer must be 250 ms on and 250 ms off. (NOTE: You can put a fingertip on the top of the buzzer to reduce the sound volume)