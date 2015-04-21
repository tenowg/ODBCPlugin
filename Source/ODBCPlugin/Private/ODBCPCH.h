#pragma once

#include "CoreUObject.h"
#include "Engine.h"
#include "ModuleManager.h"
#include "Internationalization.h"

#include <sql.h>
#include <sqltypes.h>

// SQLext needs some windows types use AllowWindowsPlatformTypes wrapper
#include "AllowWindowsPlatformTypes.h"
#include <sqlext.h>
#include "HideWindowsPlatformTypes.h"

DECLARE_LOG_CATEGORY_EXTERN(ModuleLog, Log, All)

#include "IODBCPlugin.h"
#include "ODBCPluginClasses.h"


