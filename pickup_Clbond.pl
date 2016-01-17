#!/usr/bin/perl

#=== Cl_bondのファイルから Cl原子を含むセルを
#抽出し、  
#その原子の位置座標をランダムに決定して出力
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

$Ix_0 = 20 ; $D_Ix = 50 ;
$Iy_0 = 750 ; $D_Iy = 50 ;

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
	   && $i_y >= $Iy_0  && $i_y < $Iy_0 + $D_Iy )
	{
	    for($i = 0; $i < $z[$i_x + $N_X * $i_y]; $i++)
	    {
		$tmp_x =  ($i_x + rand(1.0) - 0.5) * $CELLSIZE ;
		$tmp_y =  ($i_y + rand(1.0) - 0.5) * $CELLSIZE ;
		print $tmp_x . "\t" . $tmp_y . "\n" ;
	    }
	}
	$i_x++ ;
    }
    else
    {
	$i_x = 0 ;
	$i_y++ ;
    }
}

