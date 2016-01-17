#!/usr/bin/perl

#=== Cl_bond�Υե����뤫�� Cl���Ҥ�ޤॻ���
#��Ф���  
#���θ��Ҥΰ��ֺ�ɸ�������˷��ꤷ�ƽ���
# (surface chlorination ��plot ��Ԥ�)

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

