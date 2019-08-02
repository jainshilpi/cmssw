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



energy=( 20 30 50 80 100 120 150 200 250 300 )

actualEnergy=( 20 30 49.99 79.93 99.83 119.65 149.14 197.32 243.61 287.18 )
spreadE=( 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0. 0. )

beamX=( -1.403746 -1.533473 -1.704140 -1.885550 -1.963353 -2.041249 -2.074213 -2.153069 -2.150512 -1.944331 )
beamY=( 1.125468 1.296669 1.675706 1.757273 1.606283 1.525826 1.539302 1.499916 1.500629 1.585095 ) 
beamSX=( 1.44889  1.25232 1.08042 0.871084 0.783124 0.798317 0.727934 0.61806 0.620636 0.711645 )
beamSY=( 1.57165 1.30135 1.0828  0.837924 0.732903 0.66349 0.638578 0.710955 0.720203 0.739451 )

#phi=( 3.675168 3.649887 3.637378 3.638861 3.638332 3.639313 3.640390 3.637868 3.639525 3.641401 )
#theta=( 0.011217 0.011837 0.011995 0.012064 0.012138 0.012116 0.012092 0.012148 0.012080 0.012053 )

#pid=( 11 211 2212)
#name=( "ele" "pi" "p")

pid=( 11 )
name=( "ele" )


np=${#pid[@]}
ne=${#energy[@]}

for ((ip=0; ip<$np; ip++))
do

    for ((ie=0; ie<$ne; ie++))
    do
#	beamX=$(float_eval "${beamX[$ie]}/10.0")
#	beamY=$(float_eval "${beamY[$ie]}/10.0")
#	beamSX=$(float_eval "${beamSX[$ie]}/10.0")
#	beamSY=$(float_eval "${beamSY[$ie]}/10.0")

	beamX=$(float_eval "${beamX[$ie]}")
	beamY=$(float_eval "${beamY[$ie]}")
	beamSX=$(float_eval "${beamSX[$ie]}")
	beamSY=$(float_eval "${beamSY[$ie]}")
	phi=$(float_eval "${phi[$ie]}") 
	theta=$(float_eval "${theta[$ie]}") 

	part=${pid[$ip]}
	#e=${energy[$ie]}
	e=${actualEnergy[$ie]}
	spreade=$(float_eval "${spreadE[$ie]}*${energy[$ie]}/100")
	#min=${mine[$ie]}
	#max=${maxe[$ie]}
	partname=${name[$ip]}
	echo "particle : energy "$part " "$e
	cp HGCalTBCERN170_cfg.py HGCalTBCERN170_tmp_cfg.py
	#sed s/'MINE'/${min}/g <HGCalTBCERN170_tmp_cfg.py|
	#sed s/'MAXE'/${max}/g | 
	sed s/'MEANP'/${e}/g <HGCalTBCERN170_tmp_cfg.py|
	sed s/'SIGMAP'/${spreade}/g | 
	sed s/'PID'/${part}/g |
	#sed s/'PHI'/${phi}/g |
	#sed s/'THETA'/${theta}/g |
	sed s/'BEAMX'/${beamX}/g |
	sed s/'BEAMSX'/${beamSX}/g |
	sed s/'BEAMY'/${beamY}/g |
	sed s/'BEAMSY'/${beamSY}/g  > HGCalTBCERN170_${partname}_E${energy[$ie]}_cfg.py
	rm HGCalTBCERN170_tmp_cfg.py 
    
    done
done