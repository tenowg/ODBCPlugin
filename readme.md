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
