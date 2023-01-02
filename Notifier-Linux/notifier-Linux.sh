PREFIX=/opt/notifier
VALUEIDLASTFILE=$PREFIX/sshd/valueidlast.txt
VALUEIDLAST=`tail -1 $VALUEIDLASTFILE`
TEMPFILE=$PREFIX/sshd/tempSSHD.txt
NUMLINES=100
LOGFILE=/var/log/auth.log
CHAT_ID=
TOKEN=
SENDMESSAGE="$PREFIX/lib/telegram.sh $TOKEN $CHAT_ID"
[ -f "$PREFIX/sshd" ] || mkdir $PREFIX/sshd
[ -f "$VALUEIDLASTFILE" ] ||echo "1" > "$VALUEIDLASTFILE"
[ -f "$TEMPFILE" ] ||touch "$TEMPFILE"

while [ true ]; do
	grep sshd $LOGFILE | grep -E "Accepted|error" | tail -$NUMLINES > $TEMPFILE    
	NUMLINHAS=`wc -l $TEMPFILE |awk '{print $1}'`
	YEAR=`date +%Y`
	i=1
	while [ $i -le $NUMLINHAS ]; do
		MONTH=`head -$i $TEMPFILE |tail +$i | awk '{print $1}'`;
		VALUEIDLAST=`tail -1 $VALUEIDLASTFILE`;
		DAY=`head -$i $TEMPFILE |tail +$i | awk '{print $2}'`;
	if [ $DAY -le 10 ]
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
		if [ $VALUEID -gt $VALUEIDLAST ]
			then
			MESSAGE=`head -$i $TEMPFILE |tail +$i | awk '{print $0}'|sed 's/ /%20/g' | sed 's/\[/-/g'| sed 's/\]/-/g'`
			COMMAND="$SENDMESSAGE $MESSAGE"
			`$COMMAND`
			echo $VALUEID > $VALUEIDLASTFILE
		else
		fi
		i=$(( i+1 ))
	done
	sleep 10
done
