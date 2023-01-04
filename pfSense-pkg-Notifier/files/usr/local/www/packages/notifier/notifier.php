<?php
/*
 * cron.php
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
require_once("guiconfig.inc");
//require_once("/usr/local/pkg/notifier/lib/notifier_config.inc");

if ($config['notifier']['item'] != null){
	$a_notifier = &$config['notifier']['item'];
} 
//$a_notifier = &$config['notifier']['item'];
//$a_notifier = &$config['notifier']['item'];
if ($_GET['act'] == "del") {
	if ($_GET['type'] == 'php') {
		if ($a_notifier[$_GET['id']]) {
			unset($a_notifier[$_GET['id']]);
			write_config(gettext("Notifier"));
			header("Location: notifier.php");
			exit;
		}
	}
}

$pgtitle = array(gettext("Services"), gettext("Notifier"), gettext("Settings"));
include("head.inc");

$tab_array = array();
$tab_array[] = array(gettext("Settings"), true, "/packages/notifier/notifier.php");
$tab_array[] = array(gettext("Add"), false, "/packages/notifier/notifier_edit.php");
display_top_tabs($tab_array);
?>



<div class="panel panel-default">
	<div class="panel-heading"><h2 class="panel-title">Notifier Actions - Minha bandeira jamais será do ódio <img src="Brasil.png"> #DEMOCRACIA</h2></div>
	<div class="panel-body">
		<div class="table-responsive">
			<form action="notifier.php" method="post" name="iform" id="iform">
			<?php
			if ($config_change == 1) {
				write_config(gettext("notifiertab edited via notifier package"));
				$config_change = 0;
			}
			?>

			<table class="table table-striped table-hover table-condensed">
				<thead>
					<tr>
						<th width="10%">Service</th>
						<th width="10%">Chat ID</th>
						<th width="60%">Token</th>
						<th width="10%">Filter</th>
						
						<th width="10%">Action
							<!--<a class="btn btn-small btn-success" href="notifier_edit.php"><i class="fa fa-plus" alt="edit"></i> Add</a>-->
						</th>
					</tr>
				</thead>
				<tbody>

	<?php
		$i = 0;
		if (count($a_notifier) > 0) {
			foreach ($a_notifier as $ent) {
	?>
					<tr>
						<td><?= htmlspecialchars($ent['selectlog']) ?></td>
						<td><?= htmlspecialchars($ent['telechatid']) ?></td>
						<td><?= htmlspecialchars($ent['telgramtoken']) ?></td>
						<td><?= htmlspecialchars($ent['filterlog']) ?></td>
						<td>
							<a href="notifier_edit.php?id=<?=$i?>"><i class="fa fa-pencil" alt="edit"></i></a>
							<a href="notifier_edit.php?dup=<?=$i?>"><i class="fa fa-clone" alt="copy"></i></a>
							<a href="notifier_edit.php?type=php&amp;act=del&amp;id=<?=$i?>"><i class="fa fa-trash" alt="delete"></i></a>
						</td>
					</tr>
	<?php
		$i++;
			}
		}
	?>
					<tr>
						<td colspan="7"></td>
						<td>
							<a class="btn btn-small btn-success" href="notifier_edit.php"><i class="fa fa-plus" alt="add"></i> Add</a>
						</td>
					</tr>
				</tbody>
			</table>
			</form>
		</div>
	</div>
</div>

<div class="infoblock">
	<?=print_info_box('The notifier package works by analyzing the log files stored in "/var/log", according to the service specified in "Log to Analyzer". It basically applies a filter using the "grep" command with the "-E" parameter. Services like SSH and web access, are in the same log file, but there is a pre-filter specifying each type of service.

<p></br>Resulting command:</p>
grep sshd /var/log/auth.log | grep -E "Accepted|error"</br>

<br>In this way, it is possible to customize the filter, obtaining the alert when the condition is met.', 'info')?>
</div>

<?php include("foot.inc"); ?>
