# Data Acquisition
This project is a collection of code for use by UCLA's Formula SAE Data Acquisition team.
Using a series of breakout sensors and Arduinos, we can create an inexpensive data logger that displays and/or records sensor information collected.

## Parts
![alt text](https://cdn.sparkfun.com//assets/parts/8/2/5/6/11858-01.jpg "Copernicus II DIP")
![alt text](https://cdn.sparkfun.com//assets/parts/1/0/5/3/3/13284-02.jpg "LSM9DS1 Breakout")
![alt text](https://cdn.sparkfun.com//assets/parts/1/1/2/6/7/13743-01.jpg "microSD Breakout")

This code was created specifically for the [Copernicus II DIP](https://www.sparkfun.com/products/11858 "Copernicus II Breakout"),  the [LSM9DS1 IMU](https://www.sparkfun.com/products/13284 "LMS9DS1 Breakout"), and the [Level Shifting microSD](https://www.sparkfun.com/products/13743 "Level Shifter microSD Breakout") from Sparkfun Electronics. As a prerequisite, the [LSM9DS1 library](https://github.com/kms-uzuki/Data-Acquisition/tree/master/Libraries/SparkFun_LSM9DS1_Arduino_Library-master) and the [TinyGPS++ library](https://github.com/kms-uzuki/Data-Acquisition/tree/master/Libraries/TinyGPSPlus-master) should both be downloaded.

## Examples
![alt text](https://user-images.githubusercontent.com/33558268/66520067-50ed3a00-ea9d-11e9-969b-f9d5e404ecee.png "Example accelerometer data")

By taking a series of moving averages we can roughly estimate the vehicle's x-axis acceleration profile. This needs to be optimized further, as the refresh rate is not quite high enough to accurately profile full-throttle vibrations at zero speed.

![alt text](https://user-images.githubusercontent.com/33558268/66525288-dd055e80-eaa9-11e9-8b18-e69833222bbb.png "Example GPS data") 

The GPS is hard-limited to 1Hz refresh rate, but the unobstructed velocity accuracy is to 0.06 m/s. 
