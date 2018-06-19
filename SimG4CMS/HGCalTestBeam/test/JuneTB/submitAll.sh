#!/bin/bash 

float_scale=3
function float_eval()
{
    local stat=0
    local result=0.0
    if [[ $# -gt 0 ]]; then
        result=$(echo "scale=$float_scale; $*" | bc -q 2>/dev/null)
        stat=$?
        if [[ $stat -eq 0  &&  -z "$result" ]]; then stat=1; fi
    fi
    echo $result
    return $stat
}


energy=( 100 150 200 250 300 )
mine=( 99.99 149.99 199.99 249.99 299.99 ) 
maxe=( 100.01 150.01 200.01 250.01 300.01 )
beamX=( -2.53 -2.19 1.85  3.97 -2.20 )
beamY=( -6.46 -5.25 -5.32 -5.07  -4.58 )
beamSX=( 8.44 7.47 6.55 6.80 6.89 )
beamSY=( 7.32 6.45 6.33 6.01 5.82 )
pid=( 11 211 2212)
name=( "ele" "pi" "p")


np=${#pid[@]}
ne=${#energy[@]}

for ((ip=0; ip<$np; ip++))
do
    if [ $ip -eq 0 ]
	then
	beamX=( -3.23 -3.23 -3.23 -3.23 -3.23 )
	beamY=( -4.91 -4.91 -4.91 -4.91 -4.91 )
	beamSX=( 6.64 6.64 6.64 6.64 6.64 )
	beamSY=( 3.86 3.86 3.86 3.86 3.86 )
    fi

    if [ $ip -eq 1 ]
	then
	beamX=( -2.53 -2.19 1.85 3.97 -2.20 )
	beamY=( -6.46 -5.25 -5.32 -5.07 -4.58 )
	beamSX=( 8.44 7.47 6.55 6.80 6.89 )
	beamSY=( 7.32 6.45 6.33 6.01 5.82 )
    fi

    if [ $ip -eq 2 ]
	then
	beamX=( -2.53 -2.19 1.85 3.97 -2.20 )
	beamY=( -6.46 -5.25 -5.32 -5.07 -4.58 )
	beamSX=( 8.44 7.47 6.55 6.80 6.89 )
	beamSY=( 7.32 6.45 6.33 6.01 5.82 )
    fi
    

#    beamX=$beamX
#    beamY=$beamY
#    beamSX=$beamSX
#    beamSY=$beamSY

    for ((ie=0; ie<$ne; ie++))
    do
	beamX=$(float_eval "${beamX[$ie]}/10.0")
	beamY=$(float_eval "${beamY[$ie]}/10.0")
	beamSX=$(float_eval "${beamSX[$ie]}/10.0")
	beamSY=$(float_eval "${beamSY[$ie]}/10.0")
	
	part=${pid[$ip]}
	e=${energy[$ie]}
	min=${mine[$ie]}
	max=${maxe[$ie]}
	partname=${name[$ip]}
	echo "particle : energy "$part " "$e
	cp HGCalTBCERN170_cfg.py HGCalTBCERN170_tmp_cfg.py
	sed s/'MINE'/${min}/g <HGCalTBCERN170_tmp_cfg.py|
	sed s/'MAXE'/${max}/g | 
	sed s/'PID'/${part}/g |
	sed s/'BEAMX'/${beamX}/g |
	sed s/'BEAMSX'/${beamSX}/g |
	sed s/'BEAMY'/${beamY}/g |
	sed s/'BEAMSY'/${beamSY}/g  > HGCalTBCERN170_${partname}_E${e}_cfg.py
	rm HGCalTBCERN170_tmp_cfg.py 
    
    done
done