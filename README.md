<p>
<h3>Notifier</h3>
Send real-time ssh and web access notifications to telegram for linux or pfsense. It is also possible to receive notifications related to DHCP, firewall and OpenVPN.
</p>
<p>
Instalation</br>
1 - On pfSense web gui, acess te menu "Diagnostics > Command Prompt"</br>
2 - Execute Shell Command</br>
    pkg add https://github.com/robinrmds/Notifier/raw/main/pfSense-pkg-Notifier-0.1_3.pkg</br>
3 - Refresh WebGui</br>
</p>
<p>
Config - DEMO</br>
1 - Click Add</br>
2 - Insert Telegram Chat ID</br>
3 - Insert Telegram Token</br>
4 - Select SSHD in "Log to Analizer"</br>
5 - Insert "Accepted|error" in "Filter"</br>
</p>
