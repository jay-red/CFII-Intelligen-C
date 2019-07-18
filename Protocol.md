# ColorfightII Protocol Version 2

## Clientbound

Every packet that comes from the server is serialized in JSON, and can come from one of two channels:
`game_channel` or `action_channel`. The `game_channel` is the primary interest, because messages received
from the `action_channel` only provide information regarding bot actions.

Packets from the `game_channel` have the following fields:

|Field    |Meaning|
|---------|-------|
|error    |Any errors in the game state|
|game_map |<a href="#celldata">Cell Data</a>|
|info     |<a href="#roomdata">Room Data</a>|
|turn     |Current turn of game|
|users    |<a href="#userdata">User Data</a>|

<a name="celldata" href="#celldata"><h3>Cell Data</h3></a>

`game_map` has two fields, `data` and `headers`. `data` is a multi-dimensional array. In actuality, it is
a three-dimensional array which holds 30x30x10 elements, but each 10-element array technically represents a
single cell. Each element in the cell array represents a piece of information. The headers for each element can be
found in `headers`, which is a one-dimensional, 10-element array of strings.

These are the headers for cell data:

|index|Header|
|-----|------|
|0    |attack_cost|
|1    |force_field|
|2    |building|
|3    |gold|
|4    |energy|
|5    |owner|
|6    |position|
|7    |natural_gold|
|8    |natural_energy|
|9    |natural_cost|

<a name="roomdata" href="#roomdata"><h3>Room Data</h3></a>

<a name="userdata" href="#userdata"><h3>Cell Data</h3></a>

## Serverbound

All packets sent from the client have an `action`. Currently we have `register` and `command`.

### Login Action
This is the first packet sent.

|Field    |Meaning|
|---------|-------|
|action   |Identifies packet as registration|
|username |Bot username|
|password |Bot password|
|join-key |Room password|

### Command Action
|Field    |Meaning|
|---------|-------|
|action   |Identifies packet as command|
|cmd_list |A list of command strings|

The first character of strings in `cmd_list` identifies the type of command.

|Type Indentifier|Meaning|
|----------------|-------|
|a               |<a href="#attackcmd">Attack</a>|
|b               |<a href="#buildcmd">Build</a>|
|u               |<a href="#upgradecmd">Upgrade</a>|

<a name="attackcmd" href="#attackcmd"><h4>Attack Command</h4></a>

<a name="buildcmd" href="#buildcmd"><h4>Build Command</h4></a>

<a name="upgradecmd" href="#upgradecmd"><h4>Upgrade Command</h4></a>
