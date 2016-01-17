#!/usr/local/bin/gnuplot -persist
#
#    
#    	G N U P L O T
#    	Version 4.0 patchlevel 0
#    	last modified Thu Apr 15 14:44:22 CEST 2004
#    	System: Linux 2.4.18-3
#    
#    	Copyright (C) 1986 - 1993, 1998, 2004
#    	Thomas Williams, Colin Kelley and many others
#    
#    	This is gnuplot version 4.0.  Please refer to the documentation
#    	for command syntax changes.  The old syntax will be accepted
#    	throughout the 4.0 series, but all save files use the new syntax.
#    
#    	Type `help` to access the on-line reference manual.
#    	The gnuplot FAQ is available from
#    		http://www.gnuplot.info/faq/
#    
#    	Send comments and requests for help to
#    		<gnuplot-info@lists.sourceforge.net>
#    	Send bugs, suggestions and mods to
#    		<gnuplot-bugs@lists.sourceforge.net>
#    
# set terminal x11 
# set output
unset clip points
set clip one
unset clip two
set bar 1.000000
set border 31 lt -1 lw 1.000
set xdata
set ydata
set zdata
set x2data
set y2data
set timefmt x "%d/%m/%y\n%H:%M"
set timefmt y "%d/%m/%y\n%H:%M"
set timefmt z "%d/%m/%y\n%H:%M"
set timefmt x2 "%d/%m/%y\n%H:%M"
set timefmt y2 "%d/%m/%y\n%H:%M"
set timefmt cb "%d/%m/%y\n%H:%M"
set boxwidth
set style fill empty border
set dummy x,y
set format x "%g"
set format y "%g"
set format x2 "%g"
set format y2 "%g"
set format z "%g"
set format cb "% g"
set angles radians
unset grid
set key title ""
set key right top Right noreverse enhanced box linetype -2 linewidth 1.000 samplen 4 spacing 1 width 0 height 0 autotitles
unset label
unset arrow
unset style line
unset style arrow
unset logscale
set offsets 0, 0, 0, 0
set pointsize 1
set encoding default
unset polar
unset parametric
unset decimalsign
set view 0, 0, 1, 1
set samples 100, 100
set isosamples 10, 10
unset surface
set contour base
set clabel '%8.3g'
set mapping cartesian
set datafile separator whitespace
unset hidden3d
set cntrparam order 4
set cntrparam linear
set cntrparam levels discrete 5
set cntrparam points 5
set size ratio 1 1,1
set origin 0,0
set style data points
set style function lines
set xzeroaxis lt -2 lw 1.000
set yzeroaxis lt -2 lw 1.000
set x2zeroaxis lt -2 lw 1.000
set y2zeroaxis lt -2 lw 1.000
set tics in
set ticslevel 0.5
set mxtics default
set mytics default
set mztics default
set mx2tics default
set my2tics default
set mcbtics default
set xtics border mirror norotate autofreq 
set ytics border mirror norotate autofreq 
set ztics border nomirror norotate autofreq 
set nox2tics
set noy2tics
set cbtics border mirror norotate autofreq 
set title "" 0.000000,0.000000  font ""
set timestamp "" bottom norotate 0.000000,0.000000  ""
set rrange [ * : * ] noreverse nowriteback  # (currently [0.00000:10.0000] )
set trange [ * : * ] noreverse nowriteback  # (currently [-5.00000:5.00000] )
set urange [ * : * ] noreverse nowriteback  # (currently [-5.00000:5.00000] )
set vrange [ * : * ] noreverse nowriteback  # (currently [-5.00000:5.00000] )
set xlabel "" 0.000000,0.000000  font ""
set x2label "" 0.000000,0.000000  font ""
set xrange [ * : * ] noreverse nowriteback  # (currently [-10.0000:10.0000] )
set x2range [ * : * ] noreverse nowriteback  # (currently [-10.0000:10.0000] )
set ylabel "" 0.000000,0.000000  font ""
set y2label "" 0.000000,0.000000  font ""
set yrange [ * : * ] reverse nowriteback  # (currently [-10.0000:10.0000] )
set y2range [ * : * ] noreverse nowriteback  # (currently [-10.0000:10.0000] )
set zlabel "" 0.000000,0.000000  font ""
set zrange [ * : * ] noreverse nowriteback  # (currently [-10.0000:10.0000] )
set cblabel "" 0.000000,0.000000  font ""
set cbrange [ * : * ] noreverse nowriteback  # (currently [-10.0000:10.0000] )
set zero 1e-08
set lmargin -1
set bmargin -1
set rmargin -1
set tmargin -1
set locale "C"
set pm3d scansautomatic flush begin noftriangles nohidden3d implicit corners2color mean
unset pm3d
set palette positive nops_allcF maxcolors 0 gamma 1.5 color model RGB 
set palette rgbformulae 7, 5, 15
set colorbox default
set colorbox vertical origin 0.9,0.2 size 0.1,0.63 bdefault
set loadpath 
set fontpath 
set fit noerrorvariables
incident_particle_counter = 0

set t table 

set o 'table0.dat'
splot 'Si_matrix0.dat' w l
set o 'table1.dat'
splot 'Si_matrix28528.dat' w l
set o 'table2.dat'
splot 'Si_matrix57056.dat' w l
set o 'table3.dat'
splot 'Si_matrix85584.dat' w l
set o 'table4.dat'
splot 'Si_matrix114112.dat' w l
set o 'table5.dat'
splot 'Si_matrix142640.dat' w l
set o 'table6.dat'
splot 'Si_matrix171168.dat' w l
set o 'table7.dat'
splot 'Si_matrix199696.dat' w l
set o 'table8.dat'
splot 'Si_matrix228224.dat' w l
set o 'table9.dat'
splot 'Si_matrix256752.dat' w l
set o 'table10.dat'
splot 'Si_matrix285280.dat' w l
set o 'table11.dat'
splot 'Si_matrix313808.dat' w l
set o 'table12.dat'
splot 'Si_matrix342336.dat' w l
set o 'table13.dat'
splot 'Si_matrix370864.dat' w l
set o 'table14.dat'
splot 'Si_matrix399392.dat' w l
set o 'table15.dat'
splot 'Si_matrix427920.dat' w l
set o 'table16.dat'
splot 'Si_matrix456448.dat' w l
set o 'table17.dat'
splot 'Si_matrix484976.dat' w l
set o 'table18.dat'
splot 'Si_matrix513504.dat' w l
set o 'table19.dat'
splot 'Si_matrix542032.dat' w l
set o 'table20.dat'
splot 'Si_matrix570560.dat' w l
set o 'table21.dat'
splot 'Si_matrix599088.dat' w l
set o 'table22.dat'
splot 'Si_matrix627616.dat' w l
set o 'table23.dat'
splot 'Si_matrix656144.dat' w l
set o 'table24.dat'
splot 'Si_matrix684672.dat' w l
set o 'table25.dat'
splot 'Si_matrix713200.dat' w l
set o 'table26.dat'
splot 'Si_matrix741728.dat' w l
set o 'table27.dat'
splot 'Si_matrix770256.dat' w l
set o 'table28.dat'
splot 'Si_matrix798784.dat' w l
set o 'table29.dat'
splot 'Si_matrix827312.dat' w l
set o 'table30.dat'
splot 'Si_matrix855840.dat' w l
set o 'table31.dat'
splot 'Si_matrix884368.dat' w l
set o 'table32.dat'
splot 'Si_matrix912896.dat' w l
set o 'table33.dat'
splot 'Si_matrix941424.dat' w l
set o 'table34.dat'
splot 'Si_matrix969952.dat' w l
set o 'table35.dat'
splot 'Si_matrix998480.dat' w l
set o 'table36.dat'
splot 'Si_matrix1027008.dat' w l
set o 'table37.dat'
splot 'Si_matrix1055536.dat' w l
set o 'table38.dat'
splot 'Si_matrix1084064.dat' w l
set o 'table39.dat'
splot 'Si_matrix1112592.dat' w l
set o 'table40.dat'
splot 'Si_matrix1141120.dat' w l
set o 'table41.dat'
splot 'Si_matrix1169648.dat' w l
set o 'table42.dat'
splot 'Si_matrix1198176.dat' w l
set o 'table43.dat'
splot 'Si_matrix1226704.dat' w l
set o 'table44.dat'
splot 'Si_matrix1255232.dat' w l
set o 'table45.dat'
splot 'Si_matrix1283760.dat' w l
set o 'table46.dat'
splot 'Si_matrix1312288.dat' w l
set o 'table47.dat'
splot 'Si_matrix1340816.dat' w l
set o 'table48.dat'
splot 'Si_matrix1369344.dat' w l
set o 'table49.dat'
splot 'Si_matrix1397872.dat' w l
set o 'table50.dat'
splot 'Si_matrix1426400.dat' w l
set o 'table51.dat'
splot 'Si_matrix1454928.dat' w l
set o 'table52.dat'
splot 'Si_matrix1483456.dat' w l
set o 'table53.dat'
splot 'Si_matrix1511984.dat' w l
set o 'table54.dat'
splot 'Si_matrix1540512.dat' w l
set o 'table55.dat'
splot 'Si_matrix1569040.dat' w l
set o 'table56.dat'
splot 'Si_matrix1597568.dat' w l
set o 'table57.dat'
splot 'Si_matrix1626096.dat' w l
set o 'table58.dat'
splot 'Si_matrix1654624.dat' w l
set o 'table59.dat'
splot 'Si_matrix1683152.dat' w l
set o 'table60.dat'
splot 'Si_matrix1711680.dat' w l
set o 'table61.dat'
splot 'Si_matrix1740208.dat' w l
set o 'table62.dat'
splot 'Si_matrix1768736.dat' w l
set o 'table63.dat'
splot 'Si_matrix1797264.dat' w l
set o 'table64.dat'
splot 'Si_matrix1825792.dat' w l
set o 'table65.dat'
splot 'Si_matrix1854320.dat' w l
set o 'table66.dat'
splot 'Si_matrix1882848.dat' w l
set o 'table67.dat'
splot 'Si_matrix1911376.dat' w l
set o 'table68.dat'
splot 'Si_matrix1939904.dat' w l
set o 'table69.dat'
splot 'Si_matrix1968432.dat' w l
set o 'table70.dat'
splot 'Si_matrix1996960.dat' w l
set o 'table71.dat'
splot 'Si_matrix2025488.dat' w l
set o 'table72.dat'
splot 'Si_matrix2054016.dat' w l
set o 'table73.dat'
splot 'Si_matrix2082544.dat' w l
set o 'table74.dat'
splot 'Si_matrix2111072.dat' w l
set o 'table75.dat'
splot 'Si_matrix2139600.dat' w l
set o 'table76.dat'
splot 'Si_matrix2168128.dat' w l
set o 'table77.dat'
splot 'Si_matrix2196656.dat' w l
set o 'table78.dat'
splot 'Si_matrix2225184.dat' w l
set o 'table79.dat'
splot 'Si_matrix2253712.dat' w l
set o 'table80.dat'
splot 'Si_matrix2282240.dat' w l
set o 'table81.dat'
splot 'Si_matrix2310768.dat' w l
set o 'table82.dat'
splot 'Si_matrix2339296.dat' w l
set o 'table83.dat'
splot 'Si_matrix2367824.dat' w l
set o 'table84.dat'
splot 'Si_matrix2396352.dat' w l
set o 'table85.dat'
splot 'Si_matrix2424880.dat' w l
set o 'table86.dat'
splot 'Si_matrix2453408.dat' w l
set o 'table87.dat'
splot 'Si_matrix2481936.dat' w l
set o 'table88.dat'
splot 'Si_matrix2510464.dat' w l
set o 'table89.dat'
splot 'Si_matrix2538992.dat' w l
set o 'table90.dat'
splot 'Si_matrix2567520.dat' w l
set o 'table91.dat'
splot 'Si_matrix2596048.dat' w l
set o 'table92.dat'
splot 'Si_matrix2624576.dat' w l
set o 'table93.dat'
splot 'Si_matrix2653104.dat' w l
set o 'table94.dat'
splot 'Si_matrix2681632.dat' w l
set o 'table95.dat'
splot 'Si_matrix2710160.dat' w l
set o 'table96.dat'
splot 'Si_matrix2738688.dat' w l
set o 'table97.dat'
splot 'Si_matrix2767216.dat' w l
set o 'table98.dat'
splot 'Si_matrix2795744.dat' w l
set o 'table99.dat'
splot 'Si_matrix2824272.dat' w l
set o 'table100.dat'
splot 'Si_matrix2852800.dat' w l



set o
set t x11



#    EOF
