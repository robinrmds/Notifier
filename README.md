<p>
<h3>Notifier</h3>
<p align="justify">&emsp;The Notifier module for pfSense and Linux is a feature that allows the user to receive real-time alerts and notifications about events occurring on their network and attempts to access the device where the feature is enabled. This initial version can be configured to send alerts through Telegram.</p>
<p>&emsp;Notifier allows you to create rules to determine which events should generate notifications and which recipients should receive them. For example, it is possible to configure Notifier to send an alert via Telegram whenever a device with a specific registered MAC previously receives a DHCP address or even connects to a certain IP.
<p align="justify">&emsp; In addition, it allows sending notifications to recipients when WEB, SSH and OpenVPN access attempts are made on the device where the Notifier is enabled.<p>
<p align="justify">&emsp; The Notifier module is a useful tool to help manage the security of your network and keep the user informed about what is happening in real time. It can be configured to meet each user's specific needs and is a valuable option for those who need quick and accurate alerts on critical device-related events.</p>
</p>
<p align="justify">
Instalation</br>
1 - On pfSense web gui, access the menu "Diagnostics > Command Prompt"</br>
2 - Execute Shell Command</br>
    pkg add https://github.com/robinrmds/Notifier/raw/main/pfSense-pkg-Notifier-0.1_3.pkg</br>
3 - Refresh WebGui</br>
</p>
<p align="justify">
Config - DEMO</br>
1 - Click in the "Services Menu"</br>
2 - Click in Notifier</br>
3 - Click Add</br>
4 - Insert Telegram Chat ID</br>
5 - Insert Telegram Token</br>
6 - Select SSHD in "Log to Analizer"</br>
7 - Insert "Accepted|error" in "Filter"</br>
</p>
<p align="justify">
Note: In order for the hostname to appear in the notifications, it is necessary to enable it in "DNS Resolver", in the General tab, enable the option "DHCP Registration".
</p>
