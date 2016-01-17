#!/usr/bin/perl

# set o 'table[index].dat'
# splot '----[number].dat' w l
# という文字列を生成する

# ./splot_generate.pl [header 部分] [interval] [times]

#print "splot " ;

for($i=0; $i < $ARGV[2] ; $i++)
{
    print "set o \'table" . $i . ".dat\'\n" ;
    print "splot \'" . $ARGV[0] . $ARGV[1] * $i . "\.dat\' w l\n" ;
} 

print "\n" ;

