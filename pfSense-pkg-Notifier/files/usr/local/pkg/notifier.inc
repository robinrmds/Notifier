<?php
/*
 * cron.inc
 *
 * part of pfSense (https://www.pfsense.org)
 * Copyright (c) 2015-2022 Rubicon Communications, LLC (Netgate)
 * Copyright (c) 2008 Mark J Crane
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

require_once("pfsense-utils.inc");
require_once("services.inc");


function notifier_sync_package(array $ent) {
	global $g, $config;
	
	if ( $ent['selectlog'] === 'Disabled'){
		notifier_remove_package($ent);
	
	}else{
	
		if ( $ent['selectlog'] === 'sshd'){
			$typeLOG = "sshd";
			$pathLOG = "/var/log/auth.log";
			//$idLOG = count($config['notifier']['item'])."-".$ent['notifierid'];
			$idLOG = $ent['notifierid'];
			$B_MESSAGE="`head -\$i \$TEMPFILE |tail +\$i | awk '{print $0}'|sed 's/ /%20/g' | sed 's/\[/-/g'| sed 's/\]/-/g'`";
			$B_IP_SRC="`echo \$MESSAGE | awk -F \"%20\" '{print \$11}'`";
			$B_MAC_SRC="`arp -a | grep \$IP_SRC | awk '{print \$4}'`";
			$B_HOST_NAME="`host \$IP_SRC |awk '{print $5}'`";
			$B_COMMAND="\"\$SENDMESSAGE SERVER:`hostname`%20-%20$typeLOG%0A%0A\$MESSAGE%20|%20MAC%20Adress:\$MAC_SRC%20|%20Name:\$HOST_NAME\"";
			
		}elseif ( $ent['selectlog'] === 'web') {
			$typeLOG = "php-fpm";
			$pathLOG = "/var/log/auth.log";
			$idLOG = $ent['notifierid'];
			$B_MESSAGE="`head -\$i \$TEMPFILE |tail +\$i | awk '{print $0}'|sed 's/ /%20/g' | sed 's/\[/-/g'| sed 's/\]/-/g'`";
			$B_IP_SRC="`echo \$MESSAGE | awk -F \"%20\" '{print \$13}'`";
			$B_MAC_SRC="`arp -a | grep \$IP_SRC | awk '{print \$4}'`";
			$B_HOST_NAME="`host \$IP_SRC |awk '{print $5}'`";
			$B_COMMAND="\"\$SENDMESSAGE SERVER:`hostname`%20-%20$typeLOG%0A%0A\$MESSAGE%20|%20MAC%20Adress:\$MAC_SRC%20|%20Name:\$HOST_NAME\"";
			
		}elseif ( $ent['selectlog'] === 'dhcpd') {
			$typeLOG = "dhcpd";
			$pathLOG = "/var/log/dhcpd.log";
			$idLOG = $ent['notifierid'];
			$B_MESSAGE="`head -\$i \$TEMPFILE |tail +\$i | sed 's/ /%20/g' | sed 's/\[/-/g'| sed 's/\]/-/g'`";
			$B_IP_SRC="`echo \$MESSAGE | awk -F \"%20\" '{print \$13}'`";
			$B_MAC_SRC="`arp -a | grep \$IP_SRC | awk '{print \$4}'`";
			$B_HOST_NAME="`host \$IP_SRC |awk '{print $5}'`";
			$B_COMMAND="\"\$SENDMESSAGE SERVER:`hostname`%20-%20$typeLOG%0A%0A\$MESSAGE%20|%20MAC%20Adress:\$MAC_SRC%20|%20Name:\$HOST_NAME\"";
			
		}elseif ( $ent['selectlog'] === 'firewall') {
			$typeLOG = "filterlog";
			$pathLOG = "/var/log/filter.log";
			$idLOG = $ent['notifierid'];
			$B_MESSAGE="`head -\$i \$TEMPFILE |tail +\$i | sed 's/ /%20/g' | sed 's/\[/-/g'| sed 's/\]/-/g'`";
			$B_IP_SRC="`echo \$MESSAGE | awk -F \"%20\" '{print \$13}'`";
			$B_MAC_SRC="`arp -a | grep \$IP_SRC | awk '{print \$4}'`";
			$B_HOST_NAME="`host \$IP_SRC |awk '{print $5}'`";
			$B_COMMAND="\"\$SENDMESSAGE SERVER:`hostname`%20-%20$typeLOG%0A%0A\$MESSAGE%20|%20MAC%20Adress:\$MAC_SRC%20|%20Name:\$HOST_NAME\"";
			
		}elseif ( $ent['selectlog'] === 'openvpn') {
			$typeLOG = "openvpn";
			$pathLOG = "/var/log/openvpn.log";
			$idLOG = $ent['notifierid'];
			$B_MESSAGE="`head -\$i \$TEMPFILE |tail +\$i | sed 's/ /%20/g' | sed 's/\[/-/g'| sed 's/\]/-/g'`";
			$B_IP_SRC="`echo \$MESSAGE | awk -F \"%20\" '{print \$13}'`";
			$B_MAC_SRC="`arp -a | grep \$IP_SRC | awk '{print \$4}'`";
			$B_HOST_NAME="`host \$IP_SRC |awk '{print $5}'`";
			$B_COMMAND="\"\$SENDMESSAGE SERVER:`hostname`%20-%20$typeLOG%0A%0A\$MESSAGE%20\"";
			
		}
	
		
		$txt = "PREFIX=/usr/local/pkg/notifier\nVALUEIDLASTFILE=\$PREFIX/$idLOG/valueidlast.txt\nVALUEIDLAST=`tail -1 \$VALUEIDLASTFILE`\nTEMPFILE=\$PREFIX/$idLOG/tempFILE.txt\nNUMLINES=30\n";
		$txt = $txt . "LOGFILE=$pathLOG\nCHAT_ID=".$ent['telechatid']."\nTOKEN=".$ent['telgramtoken']."\nSENDMESSAGE=\"\$PREFIX/lib/telegram.sh \$TOKEN \$CHAT_ID\"";
		$txt = $txt . "\n[ -f \"\$PREFIX/$idLOG\" ] || mkdir \$PREFIX/$idLOG";

		$txt = $txt . "\n[ -f \"\$VALUEIDLASTFILE\" ] ||echo `date +%Y%m%d%H%M00` > \"\$VALUEIDLASTFILE\"";
		$txt = $txt . "\n[ -f \"\$TEMPFILE\" ] ||touch \"\$TEMPFILE\"";
		$txt = $txt . "\n\nwhile [ true ]; do\n\tgrep $typeLOG \$LOGFILE | grep -E \"".$ent['filterlog']."\" | tail -\$NUMLINES > \$TEMPFILE    ";
		$txt = $txt . "\n\tNUMLINHAS=`wc -l \$TEMPFILE |awk '{print $1}'`\n\tYEAR=`date +%Y`\n\tCURRENTMONTH=`date +%m`\n\ti=1\n\twhile [ \$i -le \$NUMLINHAS ]; do\n\t\tMONTH=`head -\$i \$TEMPFILE |tail +\$i | awk '{print $1}'`;"; 
		$txt = $txt . "\n\t\tVALUEIDLAST=`tail -1 \$VALUEIDLASTFILE`;";
		$txt = $txt . "\n\t\tDAY=`head -\$i \$TEMPFILE |tail +\$i | awk '{print $2}'`;";
		$txt = $txt . "\n\tif [ \$DAY -lt 10 ]";
		$txt = $txt . "\n\tthen";
		$txt = $txt . "\n\t\tDAY=0\$DAY";
		$txt = $txt . "\n\tfi";
		$txt = $txt . "\n\t\tHOUR=`head -\$i \$TEMPFILE |tail +\$i | awk '{print $3}' | awk -F\":\" '{print $1$2$3}'`;";
		$txt = $txt . "\n\t\tcase \$MONTH in";
		$txt = $txt . "\n\t\t\t'Jan')";
		$txt = $txt . "\n\t\t\tMONTH=01";
		$txt = $txt . "\n\t\t\t;;";
		$txt = $txt . "\n\t\t\t'Feb')";
		$txt = $txt . "\n\t\t\tMONTH=02";
		$txt = $txt . "\n\t\t\t;;";
		$txt = $txt . "\n\t\t\t'Mar')";
		$txt = $txt . "\n\t\t\tMONTH=03";
		$txt = $txt . "\n\t\t\t;;";
		$txt = $txt . "\n\t\t\t'Apr')";
		$txt = $txt . "\n\t\t\tMONTH=04";
		$txt = $txt . "\n\t\t\t;;";
		$txt = $txt . "\n\t\t\t'May')";
		$txt = $txt . "\n\t\t\tMONTH=05";
		$txt = $txt . "\n\t\t\t;;";
		$txt = $txt . "\n\t\t\t'Jun')";
		$txt = $txt . "\n\t\t\tMONTH=06";
		$txt = $txt . "\n\t\t\t;;";
		$txt = $txt . "\n\t\t\t'Jul')";
		$txt = $txt . "\n\t\t\tMONTH=07";
		$txt = $txt . "\n\t\t\t;;";
		$txt = $txt . "\n\t\t\t'Aug')";
		$txt = $txt . "\n\t\t\tMONTH=08";
		$txt = $txt . "\n\t\t\t;;";
		$txt = $txt . "\n\t\t\t'Sep')";
		$txt = $txt . "\n\t\t\tMONTH=09";
		$txt = $txt . "\n\t\t\t;;";
		$txt = $txt . "\n\t\t\t'Oct')";
		$txt = $txt . "\n\t\t\tMONTH=10";
		$txt = $txt . "\n\t\t\t;;";
		$txt = $txt . "\n\t\t\t'Nov')";
		$txt = $txt . "\n\t\t\tMONTH=11";
		$txt = $txt . "\n\t\t\t;;";
		$txt = $txt . "\n\t\t\t'Dec')";
		$txt = $txt . "\n\t\t\tMONTH=12";
		$txt = $txt . "\n\t\t\t;;";
		$txt = $txt . "\n\t\tesac";
		$txt = $txt . "\n\t\tVALUEID=\$YEAR\$MONTH\$DAY\$HOUR";
		$txt = $txt . "\n\t\tif [ \$VALUEID -gt \$VALUEIDLAST ] && [ \$MONTH -le \$CURRENTMONTH ]";
		$txt = $txt . "\n\t\tthen";
		//$txt = $txt . "\n\t\t\tMESSAGE=`head -\$i \$TEMPFILE |tail +\$i | awk '{print $0}'|sed 's/ /%20/g' | sed 's/\[/-/g'| sed 's/\]/-/g'`";
		$txt = $txt . "\n\t\t\tMESSAGE=$B_MESSAGE";
		$txt = $txt . "\n\t\t\tIP_SRC=$B_IP_SRC";
		$txt = $txt . "\n\t\t\tMAC_SRC=$B_MAC_SRC";
		$txt = $txt . "\n\t\t\tHOST_NAME=$B_HOST_NAME";
		//$txt = $txt . "\n\t\t\tCOMMAND=\"\$SENDMESSAGE \$MESSAGE%20|%20MAC%20Adress:\$MAC_SRC%20|%20Name:\$HOST_NAME\"";
		$txt = $txt . "\n\t\t\tCOMMAND=$B_COMMAND";
		$txt = $txt . "\n\t\t\t`\$COMMAND`";
		$txt = $txt . "\n\t\t\techo \$VALUEID > \$VALUEIDLASTFILE";
		$txt = $txt . "\n\t\telse";
		$txt = $txt . "\n\t\tfi";
		$txt = $txt . "\n\t\ti=$(( i+1 ))";
		$txt = $txt . "\n\tdone";
		$txt = $txt . "\n\tsleep 10";
		$txt = $txt . "\ndone";
		
		
		


		
		$myfile = fopen("/usr/local/pkg/notifier/$idLOG.sh", "w") or die("Unable to open file!");
		fwrite($myfile, $txt);
		fclose($myfile);
		shell_exec("chmod +x /usr/local/pkg/notifier/$idLOG.sh");
		
		shell_exec("echo \"@reboot root /usr/local/pkg/notifier/$idLOG.sh\" > /etc/cron.d/$idLOG");
		exec("/bin/sh /usr/local/pkg/notifier/$idLOG.sh > /dev/null 2>&1 &");
		
		//file_put_contents("/usr/local/pkg/notifier/notifier_DB.db","$typeLOG\t".$ent['teleChatId']."\t".$ent['telgramToken']."\t".$ent['filterLog']."\n",FILE_APPEND);
	}
	
	
}
function notifier_remove_package(array $update) {
	
	shell_exec("kill -9 `ps fax | grep ".$update['notifierid'].".sh | head -1 | awk '{print $1}'`");
	shell_exec("rm /usr/local/pkg/notifier/".$update['notifierid'].".sh");
	shell_exec("rm -Rf /usr/local/pkg/notifier/".$update['notifierid']);
	shell_exec("rm /etc/cron.d/".$update['notifierid']);
}

?>	
