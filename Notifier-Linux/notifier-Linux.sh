#!/bin/bash
#Autor: Robinson Stürmer
#Contact: robin.rmds@gmail.com

PREFIX=/opt/notifier
VALUEIDLASTFILE=$PREFIX/ssh/valueidlast.txt
VALUEIDLAST=`tail -1 $VALUEIDLASTFILE`
TEMPFILE=$PREFIX/ssh/tempFILE.txt
NUMLINES=30
LOGFILE=/var/log/auth.log
CHAT_ID=
TOKEN=
SENDMESSAGE="$PREFIX/lib/telegram.sh $TOKEN $CHAT_ID"
[ -f "$PREFIX/1-sshd657637586" ] || mkdir $PREFIX/1-sshd657637586
[ -f "$VALUEIDLASTFILE" ] ||echo `date +%Y%m%d%H%M00` > "$VALUEIDLASTFILE"
[ -f "$TEMPFILE" ] ||touch "$TEMPFILE"

while [ true ]; do
	grep sshd $LOGFILE | grep -E "Accepted|error" | tail -$NUMLINES > $TEMPFILE    
	NUMLINHAS=`wc -l $TEMPFILE |awk '{print $1}'`
	YEAR=`date +%Y`
	CURRENTMONTH=`date +%m`
	i=1
	while [ $i -le $NUMLINHAS ]; do
		MONTH=`head -$i $TEMPFILE |tail +$i | awk '{print $1}'`;
		VALUEIDLAST=`tail -1 $VALUEIDLASTFILE`;
		DAY=`head -$i $TEMPFILE |tail +$i | awk '{print $2}'`;
	if [ $DAY -lt 10 ]
	then
		DAY=0$DAY
	fi
		HOUR=`head -$i $TEMPFILE |tail +$i | awk '{print $3}' | awk -F":" '{print $1$2$3}'`;
		case $MONTH in
			'Jan')
			MONTH=01
			;;
			'Feb')
			MONTH=02
			;;
			'Mar')
			MONTH=03
			;;
			'Apr')
			MONTH=04
			;;
			'May')
			MONTH=05
			;;
			'Jun')
			MONTH=06
			;;
			'Jul')
			MONTH=07
			;;
			'Aug')
			MONTH=08
			;;
			'Sep')
			MONTH=09
			;;
			'Oct')
			MONTH=10
			;;
			'Nov')
			MONTH=11
			;;
			'Dec')
			MONTH=12
			;;
		esac
		
		VALUEID=$YEAR$MONTH$DAY$HOUR
		
		if [ $VALUEID -gt $VALUEIDLAST ] && [ $MONTH -le $CURRENTMONTH ]
		then
			MESSAGE=`head -$i $TEMPFILE |tail +$i | awk '{print $0}'|sed 's/ /%20/g' | sed 's/\[/-/g'| sed 's/\]/-/g'`
			IP_SRC=`echo $MESSAGE | awk -F "%20" '{print $11}'`
			MAC_SRC=`arp -a | grep $IP_SRC | awk '{print $4}'`
			HOST_NAME=`host $IP_SRC |awk '{print $5}'`
			COMMAND="$SENDMESSAGE SERVER:`cat /etc/hosts | awk '{print $1}' | tail -n 1`%20-%20SSHD%0A%0A$MESSAGE%20|%20MAC%20Adress:$MAC_SRC%20|%20Name:$HOST_NAME"
			`$COMMAND`
			echo $VALUEID > $VALUEIDLASTFILE
		else
		fi
		i=$(( i+1 ))
	done
	sleep 10
done
