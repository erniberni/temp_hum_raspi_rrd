<?php
if ( $_GET["time"] == "d" ) {
	$start="-86400"; }
elseif ( $_GET["time"] == "w" ) {
	$start="-604800"; }
elseif ( $_GET["time"] == "m" ) {
	$start="-2592000"; }
if ( $_GET["typ"] == "temp" ) {
	$sensor=$_GET["sensor"];
	$title='DingFabrik Köln';
	$vert_label='Temperatur [C]';
	$def_a='/home/pi/rrd/sensor'.$sensor.'.rrd';
	$label1='#'.$sensor;
	header("Content-type:image/png");
	print `/usr/bin/rrdtool graph - \
	--start="$start" --end="now" \
	--title="$title" --base=1000 --height=240 --width=500 \
	--alt-autoscale --alt-y-grid COMMENT:"$label1" \
	--slope-mode --font TITLE:12: \
	--font AXIS:8: --font LEGEND:10: --font UNIT:8: \
	--vertical-label="$vert_label" \
	DEF:temp="$def_a":temp:AVERAGE \
	CDEF:realtemp=temp,100,\/ \
	LINE1:realtemp#ff0000:Temperatur GPRINT:realtemp:MAX:"max\:%5.1lf" \
	GPRINT:realtemp:MIN:"min\:%5.1lf" GPRINT:realtemp:AVERAGE:"avg\:%5.1lf" \
	GPRINT:realtemp:LAST:"last\:%5.1lf"`;
	}
else if ( $_GET["typ"] == "hum" ) {
	$sensor=$_GET["sensor"];
	$title='DingFabrik Köln';
	$vert_label='Feuchte [%]';
	$def_a='/home/pi/rrd/sensor'.$sensor.'.rrd';
	$label1='#'.$sensor;
	header("Content-type:image/png");
	print `/usr/bin/rrdtool graph - \
	--start="$start" --end="now" \
	--title="$title" --base=1000 --height=240 --width=500 \
	--alt-autoscale --alt-y-grid COMMENT:"$label1" \
	--slope-mode --font TITLE:12: \
	--font AXIS:8: --font LEGEND:10: --font UNIT:8: \
	--vertical-label="$vert_label" \
	DEF:hum="$def_a":hum:AVERAGE \
	CDEF:realhum=hum,100,\/ \
	LINE1:realhum#ff0000:Feuchte GPRINT:realhum:MAX:"max\:%5.1lf" \
	GPRINT:realhum:MIN:"min\:%5.1lf" GPRINT:realhum:AVERAGE:"avg\:%5.1lf" \
	GPRINT:realhum:LAST:"last\:%5.1lf"`;
	}
else if ( $_GET["typ"] == "batt" ) {
	$sensor=$_GET["sensor"];
	$title='DingFabrik Köln';
	$vert_label='Batterie [mV]';
	$def_a='/home/pi/rrd/sensor'.$sensor.'.rrd';
	$label1='#'.$sensor;
	header("Content-type:image/png");
	print `/usr/bin/rrdtool graph - \
	--start="$start" --end="now" \
	--title="$title" --base=1000 --height=240 --width=500 \
	--alt-autoscale --alt-y-grid COMMENT:"$label1" \
	--slope-mode --font TITLE:12: \
	--font AXIS:8: --font LEGEND:10: --font UNIT:8: \
	--vertical-label="$vert_label" \
	DEF:batt="$def_a":batt:AVERAGE \
	LINE1:batt#ff0000:Batterie GPRINT:batt:MAX:"max\:%5.0lf" \
	GPRINT:batt:MIN:"min\:%5.0lf" GPRINT:batt:AVERAGE:"avg\:%5.0lf" \
	GPRINT:batt:LAST:"last\:%5.0lf"`;
	}
else  {
	header("Content-type:image/png");
	print `cat /var/www/smilee.png`;
	}
?>



