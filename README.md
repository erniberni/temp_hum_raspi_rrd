temp_hum_raspi_rrd
==================

Summary: Everything you need to build a 868 MHz wireless sensor network with collecting data in rrd databases and presenting graphical results. 
Please visit my blog http://glaskugelsehen.wordpress.com/  to get details and photos of the project.

1. A sensor based on TinyTX (http://nathan.chantrell.net/tinytx-wireless-sensor/) sends data on 868 MHz with RFM12B. The sensor in use is a DHT22 and the processor is a ATTiny84. The software of Nathan Chantrell's TinyTX was modified slightly to send also informations on uptime. For more information on the TinyTX visit the above mentioned webpage.

2. A board similar to the RFM12Pi board of OpenEnergyMonitor (http://wiki.openenergymonitor.org/index.php?title=RFM12Pi_V2) but with a Arduino mini instead of the ATMega chip. This leaves all other pins of the mini still available.  

3. RRD database on the Raspberry Pi was installed and the temperature, humidity and batterie voltage of the sensor is filled in

4. Graphical presentation off rrd data
The live data and historical data is presented with a apache/php webserver running on the RaspberryPi. The graphics are dynamically generated to prevent too many write cycles to sd flash.
