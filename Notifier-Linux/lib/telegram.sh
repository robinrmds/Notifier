
 # Licensed under the Apache License, Version 2.0 (the "License");
 # you may not use this file except in compliance with the License.
 # You may obtain a copy of the License at
 #
 # http://www.apache.org/licenses/LICENSE-2.0
 #
 # Unless required by applicable law or agreed to in writing, software
 # distributed under the License is distributed on an "AS IS" BASIS,
 # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 # See the License for the specific language governing permissions and
 # limitations under the License.
#
 # Basead on  Pfsense cron package
 # Notifier package
 # Author: Robinson Stürmer
 # Contact: robin.rmds@gmail.com

TOKEN=$1 
USER=$2
SUBJECT=$3
COMMAND="curl -s  --output /dev/null -X POST ""https://api.telegram.org/bot$TOKEN/sendMessage?chat_id=$USER&text=$SUBJECT"""
`$COMMAND`
 
exit 0

