#!/usr/bin/perl

#=== Si_matrix�Υե����뤫�� solid �Υ����
#��Ф���  i_x    i_y    FLAG(10)
#���¤٤ƽ���

open(IN, $ARGV[0]);

$i_x = 0 ; # x��ɸ�Ѥ�index
$i_y = 0 ; # y��ɸ�Ѥ�index
$N_X = 1000 ;
$CELLSIZE = 2.718592533e-10 ;
#�ǡ����������򾮤������뤿����ϰϤ�����
# x_0, ��x, z_0, ��z : cell index �ǵ��ꤹ��

#$Ix_0 = 135 ; $D_Ix = 30 ;
#$Iy_0 = 985 ; $D_Iy = 50 ;

$Ix_0 = 20 ; $D_Ix = 50 ;
$Iy_0 = 750 ; $D_Iy = 50 ;

#$DEPTH_RANGE = 3.0e-7 ; # 1.0 ; #

while ($_ = <IN>) 
{
    # ������ޤ�Ǥ��뤫��
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

