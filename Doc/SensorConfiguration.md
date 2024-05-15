# Sensor Configuration

|                         | Type       | Mode                                    | Option                                       |
| ----------------------- | ---------- | --------------------------------------- | -------------------------------------------- |
| Raw                     | 0 (ANALOG) | 0                                       | (2<<8)&(2<<12)                               |
| MB-Linefollower         | 0 (ANALOG) | 0                                       | 0x2222                                       |
| NXT-Light               | 0 (ANALOG) | 0                                       | (0x7<<8) //light off<br/>(0xF<<8) //light on |
| EV3-Color               | 1 (UART)   | 0 (LIGHT)<br/>1 (AMBIENT)<br/>2 (COLOR) | 0                                            |
| EV3-Gyro                | 1 (UART)   | 0 (ANGLE)<br/>1 (RATE)                  | 0                                            |
| EV3-Infrared            | 1 (UART)   | 0                                       | 0                                            |
| EV3-Ultrasonic          | 1 (UART)   | 0                                       | 0                                            |
| NXT-Ultrasonic          | 2 (I2C)    | 0                                       | 0                                            |
| MB-Ultrasonic           | 3 (TOF)    | 0                                       | 0                                            |
| EV3-Touch<br/>NXT-Touch | 4 (TOUCH)  | 0                                       | 0                                            |
