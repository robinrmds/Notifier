# Notifier
Send real-time ssh and web access notifications to telegram for linux or pfsense. It is also possible to receive notifications related to DHCP, firewall and OpenVPN.

Instalation
1 - On pfSense web gui, acess te menu "Diagnostics > Command Prompt"
2 - Execute Shell Command
    pkg add https://github.com/robinrmds/Notifier/raw/main/pfSense-pkg-Notifier-0.1_3.pkg
3 - Refresh WebGui

Config - DEMO
1 - Click Add%0A
2 - Insert Telegram Chat ID \n
3 - Insert Telegram Token \n
4 - Select SSHD in "Log to Analizer" \n
5 - Insert "Accepted|error" in "Filter"\n