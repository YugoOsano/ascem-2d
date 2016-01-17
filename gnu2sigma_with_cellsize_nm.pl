#!/usr/bin/perl

# Gnuplot で生成した table ファイルを、Sigmaplot で使用できるようにする
# 
#  １　コメント行の削除
#　２　x,y 座標にセルサイズを掛ける

# usage : ./table2sigma_with_cellsize.pl [file name]  > [new file]

# compare strings
#http://tohoho.wakusei.ne.jp/wwwperl1.htm#CompStrOperand

$CELLSIZE = 2.718592533e-1  ; #(nm)

open(IN , $ARGV[0])|| die("$!") ;

while($xx = <IN>)  
{
  # $xxが#で始まっていないか？（コメント行を削除）
  if($xx !~ /^\#/)
    {
      if($xx =~ /\d/) #--数値を含んでいるか？
        {
          @tmp = split(/\s/, $xx);
          chomp $tmp[2] ; # -- split した文字列は改行を含んでいる
          
	  #== かたがわopen space 
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


