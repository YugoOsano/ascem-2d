#!/usr/bin/perl

# Gnuplot �Ő������� table �t�@�C�����ASigmaplot �Ŏg�p�ł���悤�ɂ���
# 
#  �P�@�R�����g�s�̍폜
#�@�Q�@x,y ���W�ɃZ���T�C�Y���|����

# usage : ./table2sigma_with_cellsize.pl [file name]  > [new file]

# compare strings
#http://tohoho.wakusei.ne.jp/wwwperl1.htm#CompStrOperand

$CELLSIZE = 2.718592533e-1  ; #(nm)

open(IN , $ARGV[0])|| die("$!") ;

while($xx = <IN>)  
{
  # $xx��#�Ŏn�܂��Ă��Ȃ����H�i�R�����g�s���폜�j
  if($xx !~ /^\#/)
    {
      if($xx =~ /\d/) #--���l���܂�ł��邩�H
        {
          @tmp = split(/\s/, $xx);
          chomp $tmp[2] ; # -- split ����������͉��s���܂�ł���
          
	  #== ��������open space 
	  if($CELLSIZE * $tmp[0] > 1.0 || 
	     $CELLSIZE * $tmp[1] < 1.0e2 )
	  {
	      print $CELLSIZE * $tmp[0] . "\t" .
		  ( $CELLSIZE * $tmp[1] - 2.7 ) . "\t" .
		  $tmp[2] . "\n";
	  }
        }
      else
        {
          print $xx ;
        }
    }
}

close(IN) ;


