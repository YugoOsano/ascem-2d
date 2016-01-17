#!/usr/bin/perl

#=== Cl_bondのファイルから Cl原子を含むセルを
#抽出する。-> index を出力し、反応層の表示を行う

# (surface chlorination のplot を行う)

open(IN, $ARGV[0]);

$i_x = 0 ; # x座標用のindex
$i_y = 0 ; # y座標用のindex
$N_X = 1000 ;
$CELLSIZE = 2.718592533e-10 ;
#データサイズを小さくするために範囲を設定
# x_0, Δx, z_0, Δz : cell index で規定する

#$Ix_0 = 135 ; $D_Ix = 30 ;
#$Iy_0 = 985 ; $D_Iy = 50 ;

#$Ix_0 = 20 ; $D_Ix = 50 ;
#$Iy_0 = 750 ; $D_Iy = 50 ; 

$Ix_0 = 0 ; $D_Ix = 5000 ;
$Iy_0 = 0 ; $D_Iy = 3000 ;

while ($_ = <IN>) 
{
    # 数字を含んでいるか？
    if($_ =~ /\d/)
    {  
	$tmp = $_ ;
	chomp $tmp ;
	$z[$i_x + $N_X * $i_y] = $tmp ;
	
	#  
	if(($z[$i_x + $N_X * $i_y] % 100) & 10 >= 1
	   && $i_x >= $Ix_0  && $i_x < $Ix_0 + $D_Ix
	   && $i_y >= $Iy_0  && $i_y < $Iy_0 + $D_Iy )
	{
	    print $i_x . "\t" . $i_y . "\n" ;
	}
	$i_x++ ;
    }
    else
    {
	$i_x = 0 ;
	$i_y++ ;
    }
}
