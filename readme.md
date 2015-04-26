### ODBC Blueprint Plugin for UE4
An easy to use Blueprint option for handling simple database calls (with ODBC Drivers) in UE4 (Unreal Engine 4)

### What does ODBCPlugin do?
#### Connections
ODBCPlugin manages ODBC Connections, current implementation is not error proof. This is a work in progress.

#### SQL Queries
ODBCPlugin will generate simple SQL queries using Blueprints via Structs, Functions and Arrays.. As well as a few Macros thrown in for fun.

#### Async?
Yes, Currently Async options are available, but uses the polling method over the notification method. Future plans to include an option to use the notification method with Events.

### Examples
#### Connection Creation
![Connection Creation](https://copy.com/BKOsOnW2Dsr8sOOS)  
This connects to the database though ODBC, this can be run at Begin Play on any entity that needs to connect to a database.

#### Where Clause Blueprint
![WhereClause Example](https://copy.com/s4bYOK2u6vRz00gV)  
This would produce something similar to: WHERE ([testing].[text] = test AND [testing].[integer] = 0)

### For Further Usage Information View the Wiki

### Contribute
#### Improve and Learn
This plugin is written with the intent to learn C++, and to create a functional Database connection manager/query builder/exector for UE4. Please, if you look through my code, and you see a place where an improvement can be made PLEASE feel free to comment on the code by opening an Issue, make a pull request with full comments explaning why so that I (and anyone else) reading this code can learn and improve.
#### Donate
I am more interested in coding than graphics/art, but I am working on a game (which hopefully this plugin will be used in) and would love to buy some assets, have assets created. If you feel like donating to this cause please donate either:

* Bitcoin: ADDRESS HERE SOON
* Paypal: Link here SOON
* CoinBase: Link here SOON

Thanks for reading.
