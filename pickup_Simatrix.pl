#!/usr/bin/perl

#=== Si_matrixのファイルから solid のセルを
#抽出し、  i_x    i_y    FLAG(10)
#と並べて出力

open(IN, $ARGV[0]);

$i_x = 0 ; # x座標用のindex
$i_y = 0 ; # y座標用のindex
$N_X = 1000 ;
$CELLSIZE = 2.718592533e-10 ;
#データサイズを小さくするために範囲を設定
# x_0, Δx, z_0, Δz : cell index で規定する

#$Ix_0 = 135 ; $D_Ix = 30 ;
#$Iy_0 = 985 ; $D_Iy = 50 ;

$Ix_0 = 20 ; $D_Ix = 50 ;
$Iy_0 = 750 ; $D_Iy = 50 ;

#$DEPTH_RANGE = 3.0e-7 ; # 1.0 ; #

while ($_ = <IN>) 
{
    # 数字を含んでいるか？
    if($_ =~ /\d/)
    {
	$tmp = $_ ;
	chomp $tmp ;
	$z[$i_x + $N_X * $i_y] = $tmp ;
	
	#  
	if($z[$i_x + $N_X * $i_y] > 0 
	   && $i_x >= $Ix_0  && $i_x < $Ix_0 + $D_Ix
	   && $i_y >= $Iy_0  && $i_y < $Iy_0 + $D_Iy)
	{
	    print  $i_x * $CELLSIZE . "\t" . 
		$i_y * $CELLSIZE . "\t" . 
	    	$z[$i_x + $N_X * $i_y] . "\n" ;
	}
	$i_x++ ;
    }
    else
    {
	$i_x = 0 ;
	$i_y++ ;
    }
}

