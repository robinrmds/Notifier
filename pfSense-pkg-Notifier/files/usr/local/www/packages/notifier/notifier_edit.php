<?php
/*
 
 */
require_once("config.inc");
require_once("guiconfig.inc");
require_once("/usr/local/pkg/notifier.inc");

if (!empty($_POST["cancel"])) {
	header("Location: notifier.php");
	exit;
}

if ($config['notifier']['item'] == null){
	unset($config['notifier']);
}

$a_notifier = &$config['notifier']['item'];

$id = $_GET['id'];
if (isset($_POST['id'])) {
	$id = $_POST['id'];
}

$dup = false;
if (isset($_GET['dup']) && is_numericint($_GET['dup'])) {
	$id = $_GET['dup'];
	$dup = true;
}

if ($_GET['act'] == "del") {
	if ($_GET['type'] == 'php') {
		if ($a_notifier[$_GET['id']]) {
			notifier_remove_package($a_notifier[$_GET['id']]);
			unset($a_notifier[$_GET['id']]);
			write_config(gettext("notifiertab item deleted via notifier package"));
			//notifier_sync_package($ent);
			header("Location: notifier.php");
			exit;
		}
	}
}

if (isset($id) && $a_notifier[$id]) {
	$pconfig['notifierid'] = $a_notifier[$id]['notifierid'];
	$pconfig['telechatid'] = $a_notifier[$id]['telechatid'];
	$pconfig['telgramtoken'] = $a_notifier[$id]['telgramtoken'];
	$pconfig['selectlog'] = $a_notifier[$id]['selectlog'];
	$pconfig['filterlog'] = $a_notifier[$id]['filterlog'];
	
}

if ($_POST) {
	unset($input_errors);
	$pconfig = $_POST;

	$input_errors = array();
	
	foreach ($a_notifier as $notifier_id) {
		if( $a_notifier[$id]['notifierid'] == trim($_POST['selectlog']).trim($_POST['telechatid']) && $a_notifier[$id]['filterlog'] == trim($_POST['filterlog'])){
			$input_errors[] = gettext("Service is already enabled for the specified chatid" /*. "{trim($_POST['selectlog']). - .trim($_POST['telechatid'])}"*/);
		}
	}

	if (!$input_errors) {

		$ent = array();
		$ent['notifierid'] = count($config['notifier']['item'])."-".trim($_POST['selectlog']).trim($_POST['telechatid']);
		$ent['telechatid'] = trim($_POST['telechatid']);
		$ent['telgramtoken'] = trim($_POST['telgramtoken']);
		$ent['selectlog'] = trim($_POST['selectlog']);
		$ent['filterlog'] = trim($_POST['filterlog']);
		

		if (isset($id) && $a_notifier[$id] && !$dup) {
			// update
			
			notifier_remove_package($a_notifier[$_GET['id']]);
			$a_notifier[$id] = $ent;
		} else {
			// add
			$a_notifier[] = $ent;
		}

		write_config(gettext("notifiertab edited via notifier package"));
		notifier_sync_package($ent);

		header("Location: notifier.php");
		exit;
	}
}


if (empty($id)) {
	$pgtitle = array(gettext("Services"), gettext("Notifier"), gettext("Add"));
} else {
	$pgtitle = array(gettext("Services"), gettext("Notifier"), gettext("Edit"));
}
include("head.inc");

if ($input_errors) {
	print_input_errors($input_errors);
}

$tab_array = array();
$tab_array[] = array(gettext("Settings"), false, "/packages/notifier/notifier.php");
if (empty($id)) {
	$tab_array[] = array(gettext("Add"), true, "/packages/notifier/notifier_edit.php");
} else {
	$tab_array[] = array(gettext("Edit"), true, "/packages/notifier/notifier_edit.php");
}
display_top_tabs($tab_array);

$form = new Form;
$section = new Form_Section('Add A notifier Log ');

$section->addInput(new Form_Input(
	'telechatid',
	'Telegram Chat ID',
	'text',
	$pconfig['telechatid']
))->setHelp('Set Telegram Chat ID', '<br/>');

$section->addInput(new Form_Input(
	'telgramtoken',
	'Telegram Token',
	'text',
	$pconfig['telgramtoken']
))->setHelp("Set Telegram Token.");

$section->addInput(new Form_Select(   
	'selectlog',
	'Log to Analizer',
	$pconfig['selectlog'],
	array('Disabled' => 'Disabled','sshd' => 'SSHD >> /var/log/auth.log', 'web' => 'Web Login >> /var/log/auth.log', 'dhcpd' => 'DHCP >> /var/log/dhcpd.log','firewall' => 'Firewall  >> /var/log/filter.log','openvpn' => 'OpenVpn >> /var/log/openvpn.log')
))->setHelp("Choose a log type to send the notification.");

$section->addInput(new Form_Input(
	'filterlog',
	'Filter',
	'text',
	$pconfig['filterlog']
))->setHelp("Set the filter log with parameter to grep -E. Ex: grep -E \"filter1|filter2\" file.txt
			<p></br>For SSH login attempts, use the following filter:</br><li>&emsp;Accepted|error</li></p>
			<p></br>For WEB login attempts, use the following filter:</br><li>&emsp;Successful|error</li></p>
			<p></br>Note: It is allowed to use any word in the log of the respective selected service. When the word is found, the notification is sent.</p>");
				


$form->add($section);

$btncncl = new Form_Button(
    'cancel',
    'Cancel'
);
 
$btncncl->removeClass('btn-primary')->addClass('btn-danger');
 
$form->addGlobal($btncncl);

print $form;

?>
<div class="infoblock">
	<?=print_info_box('The notifier package works by analyzing the log files stored in "/var/log", according to the service specified in "Log to Analyzer". It basically applies a filter using the "grep" command with the "-E" parameter. Services like SSH and web access, are in the same log file, but there is a pre-filter specifying each type of service.

<p></br>Resulting command:</p>
grep sshd /var/log/auth.log | grep -E "Accepted|error"</br>

<br>In this way, it is possible to customize the filter, obtaining the alert when the condition is met.', 'info')?>
</div>

<?php include("foot.inc"); ?>
