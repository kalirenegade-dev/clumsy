#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include "iup.h"
#include "common.h"
#include "ini.h"
#include <stdbool.h>
#include "bandwidth.h"
#include "drop.h"
#include "duplicate.h"
#include "lag.h"
#include "ood.h"
#include "reset.h"
#include "tamper.h"
#include "throttle.h"
#include "disconnect.h"
#include <process.h> 

int running = 0;
int Mode = 0;
char timerbuffer[6];

void preset1_config(void);
void preset2_config(void);
void preset3_config(void);
void preset4_config(void);
void preset5_config(void);
void intToStr(int num, char* str);



typedef struct {
   const char* Keybind;
} General;

typedef struct {
    const char* PresetName;
    bool Lag_Inbound;
    bool Lag_Outbound;
    const char* Lag_Delay;
    bool Drop_Inbound;
    bool Drop_Outbound;
    const char* Drop_Chance;
    bool Disconnect_Inbound;
    bool Disconnect_Outbound;
    const char* BandwidthLimiter_QueueSize;
    const char* BandwidthLimiter_Size;
    bool BandwidthLimiter_Inbound;
    bool BandwidthLimiter_Outbound;
    const char* BandwidthLimiter_Limit;
    bool Throttle_DropThrottled;
    const char* Throttle_Timeframe;
    bool Throttle_Inbound;
    bool Throttle_Outbound;
    const char* Throttle_Chance;
    const char* Duplicate_Count;
    bool Duplicate_Inbound;
    bool Duplicate_Outbound;
    const char* Duplicate_Chance;
    bool OutOfOrder_Inbound;
    bool OutOfOrder_Outbound;
    const char* OutOfOrder_Chance;
    bool Tamper_RedoChecksum;
    bool Tamper_Inbound;
    bool Tamper_Outbound;
    const char* Tamper_Chance;
    bool SetTCPRST_Inbound;
    bool SetTCPRST_Outbound;
    const char* SetTCPRST_Chance;
} Preset1;

typedef struct {
    const char* PresetName;
    bool Lag_Inbound;
    bool Lag_Outbound;
    const char* Lag_Delay;
    bool Drop_Inbound;
    bool Drop_Outbound;
    const char* Drop_Chance;
    bool Disconnect_Inbound;
    bool Disconnect_Outbound;
    const char* BandwidthLimiter_QueueSize;
    const char* BandwidthLimiter_Size;
    bool BandwidthLimiter_Inbound;
    bool BandwidthLimiter_Outbound;
    const char* BandwidthLimiter_Limit;
    bool Throttle_DropThrottled;
    const char* Throttle_Timeframe;
    bool Throttle_Inbound;
    bool Throttle_Outbound;
    const char* Throttle_Chance;
    const char* Duplicate_Count;
    bool Duplicate_Inbound;
    bool Duplicate_Outbound;
    const char* Duplicate_Chance;
    bool OutOfOrder_Inbound;
    bool OutOfOrder_Outbound;
    const char* OutOfOrder_Chance;
    bool Tamper_RedoChecksum;
    bool Tamper_Inbound;
    bool Tamper_Outbound;
    const char* Tamper_Chance;
    bool SetTCPRST_Inbound;
    bool SetTCPRST_Outbound;
    const char* SetTCPRST_Chance;
} Preset2;

typedef struct {
    const char* PresetName;
    bool Lag_Inbound;
    bool Lag_Outbound;
    const char* Lag_Delay;
    bool Drop_Inbound;
    bool Drop_Outbound;
    const char* Drop_Chance;
    bool Disconnect_Inbound;
    bool Disconnect_Outbound;
    const char* BandwidthLimiter_QueueSize;
    const char* BandwidthLimiter_Size;
    bool BandwidthLimiter_Inbound;
    bool BandwidthLimiter_Outbound;
    const char* BandwidthLimiter_Limit;
    bool Throttle_DropThrottled;
    const char* Throttle_Timeframe;
    bool Throttle_Inbound;
    bool Throttle_Outbound;
    const char* Throttle_Chance;
    const char* Duplicate_Count;
    bool Duplicate_Inbound;
    bool Duplicate_Outbound;
    const char* Duplicate_Chance;
    bool OutOfOrder_Inbound;
    bool OutOfOrder_Outbound;
    const char* OutOfOrder_Chance;
    bool Tamper_RedoChecksum;
    bool Tamper_Inbound;
    bool Tamper_Outbound;
    const char* Tamper_Chance;
    bool SetTCPRST_Inbound;
    bool SetTCPRST_Outbound;
    const char* SetTCPRST_Chance;
} Preset3;

typedef struct {
    const char* PresetName;
    bool Lag_Inbound;
    bool Lag_Outbound;
    const char* Lag_Delay;
    bool Drop_Inbound;
    bool Drop_Outbound;
    const char* Drop_Chance;
    bool Disconnect_Inbound;
    bool Disconnect_Outbound;
    const char* BandwidthLimiter_QueueSize;
    const char* BandwidthLimiter_Size;
    bool BandwidthLimiter_Inbound;
    bool BandwidthLimiter_Outbound;
    const char* BandwidthLimiter_Limit;
    bool Throttle_DropThrottled;
    const char* Throttle_Timeframe;
    bool Throttle_Inbound;
    bool Throttle_Outbound;
    const char* Throttle_Chance;
    const char* Duplicate_Count;
    bool Duplicate_Inbound;
    bool Duplicate_Outbound;
    const char* Duplicate_Chance;
    bool OutOfOrder_Inbound;
    bool OutOfOrder_Outbound;
    const char* OutOfOrder_Chance;
    bool Tamper_RedoChecksum;
    bool Tamper_Inbound;
    bool Tamper_Outbound;
    const char* Tamper_Chance;
    bool SetTCPRST_Inbound;
    bool SetTCPRST_Outbound;
    const char* SetTCPRST_Chance;
} Preset4;

typedef struct {
    const char* PresetName;
    bool Lag_Inbound;
    bool Lag_Outbound;
    const char* Lag_Delay;
    bool Drop_Inbound;
    bool Drop_Outbound;
    const char* Drop_Chance;
    bool Disconnect_Inbound;
    bool Disconnect_Outbound;
    const char* BandwidthLimiter_QueueSize;
    const char* BandwidthLimiter_Size;
    bool BandwidthLimiter_Inbound;
    bool BandwidthLimiter_Outbound;
    const char* BandwidthLimiter_Limit;
    bool Throttle_DropThrottled;
    const char* Throttle_Timeframe;
    bool Throttle_Inbound;
    bool Throttle_Outbound;
    const char* Throttle_Chance;
    const char* Duplicate_Count;
    bool Duplicate_Inbound;
    bool Duplicate_Outbound;
    const char* Duplicate_Chance;
    bool OutOfOrder_Inbound;
    bool OutOfOrder_Outbound;
    const char* OutOfOrder_Chance;
    bool Tamper_RedoChecksum;
    bool Tamper_Inbound;
    bool Tamper_Outbound;
    const char* Tamper_Chance;
    bool SetTCPRST_Inbound;
    bool SetTCPRST_Outbound;
    const char* SetTCPRST_Chance;
} Preset5;


struct General {
    const char* Keybind;
};

General general = {
    "["
};

// Initialize Preset1 structure with default values
Preset1 preset1 = {
    .PresetName = "Preset1",
    .Lag_Inbound = false,
    .Lag_Outbound = false,
    .Lag_Delay = "0",
    .Drop_Inbound = false,
    .Drop_Outbound = false,
    .Drop_Chance = "0",
    .Disconnect_Inbound = false,
    .Disconnect_Outbound = false,
    .BandwidthLimiter_QueueSize = "0",
    .BandwidthLimiter_Size = "kb",
    .BandwidthLimiter_Inbound = false,
    .BandwidthLimiter_Outbound = false,
    .BandwidthLimiter_Limit = "0",
    .Throttle_DropThrottled = false,
    .Throttle_Timeframe = "0",
    .Throttle_Inbound = false,
    .Throttle_Outbound = false,
    .Throttle_Chance = "0",
    .Duplicate_Count = "0",
    .Duplicate_Inbound = false,
    .Duplicate_Outbound = false,
    .Duplicate_Chance = "0",
    .OutOfOrder_Inbound = false,
    .OutOfOrder_Outbound = false,
    .OutOfOrder_Chance = "0",
    .Tamper_RedoChecksum = false,
    .Tamper_Inbound = false,
    .Tamper_Outbound = false,
    .Tamper_Chance = "0",
    .SetTCPRST_Inbound = false,
    .SetTCPRST_Outbound = false,
    .SetTCPRST_Chance = "0"
};

// Initialize Preset1 structure with default values
Preset2 preset2 = {
    .PresetName = "Preset2",
    .Lag_Inbound = false,
    .Lag_Outbound = false,
    .Lag_Delay = "0",
    .Drop_Inbound = false,
    .Drop_Outbound = false,
    .Drop_Chance = "0",
    .Disconnect_Inbound = false,
    .Disconnect_Outbound = false,
    .BandwidthLimiter_QueueSize = "0",
    .BandwidthLimiter_Size = "kb",
    .BandwidthLimiter_Inbound = false,
    .BandwidthLimiter_Outbound = false,
    .BandwidthLimiter_Limit = "0",
    .Throttle_DropThrottled = false,
    .Throttle_Timeframe = "0",
    .Throttle_Inbound = false,
    .Throttle_Outbound = false,
    .Throttle_Chance = "0",
    .Duplicate_Count = "0",
    .Duplicate_Inbound = false,
    .Duplicate_Outbound = false,
    .Duplicate_Chance = "0",
    .OutOfOrder_Inbound = false,
    .OutOfOrder_Outbound = false,
    .OutOfOrder_Chance = "0",
    .Tamper_RedoChecksum = false,
    .Tamper_Inbound = false,
    .Tamper_Outbound = false,
    .Tamper_Chance = "0",
    .SetTCPRST_Inbound = false,
    .SetTCPRST_Outbound = false,
    .SetTCPRST_Chance = "0"
};

// Initialize Preset1 structure with default values
Preset3 preset3 = {
    .PresetName = "Preset3",
    .Lag_Inbound = false,
    .Lag_Outbound = false,
    .Lag_Delay = "0",
    .Drop_Inbound = false,
    .Drop_Outbound = false,
    .Drop_Chance = "0",
    .Disconnect_Inbound = false,
    .Disconnect_Outbound = false,
    .BandwidthLimiter_QueueSize = "0",
    .BandwidthLimiter_Size = "kb",
    .BandwidthLimiter_Inbound = false,
    .BandwidthLimiter_Outbound = false,
    .BandwidthLimiter_Limit = "0",
    .Throttle_DropThrottled = false,
    .Throttle_Timeframe = "0",
    .Throttle_Inbound = false,
    .Throttle_Outbound = false,
    .Throttle_Chance = "0",
    .Duplicate_Count = "0",
    .Duplicate_Inbound = false,
    .Duplicate_Outbound = false,
    .Duplicate_Chance = "0",
    .OutOfOrder_Inbound = false,
    .OutOfOrder_Outbound = false,
    .OutOfOrder_Chance = "0",
    .Tamper_RedoChecksum = false,
    .Tamper_Inbound = false,
    .Tamper_Outbound = false,
    .Tamper_Chance = "0",
    .SetTCPRST_Inbound = false,
    .SetTCPRST_Outbound = false,
    .SetTCPRST_Chance = "0"
};

// Initialize Preset1 structure with default values
Preset4 preset4 = {
    .PresetName = "Preset4",
    .Lag_Inbound = false,
    .Lag_Outbound = false,
    .Lag_Delay = "0",
    .Drop_Inbound = false,
    .Drop_Outbound = false,
    .Drop_Chance = "0",
    .Disconnect_Inbound = false,
    .Disconnect_Outbound = false,
    .BandwidthLimiter_QueueSize = "0",
    .BandwidthLimiter_Size = "kb",
    .BandwidthLimiter_Inbound = false,
    .BandwidthLimiter_Outbound = false,
    .BandwidthLimiter_Limit = "0",
    .Throttle_DropThrottled = false,
    .Throttle_Timeframe = "0",
    .Throttle_Inbound = false,
    .Throttle_Outbound = false,
    .Throttle_Chance = "0",
    .Duplicate_Count = "0",
    .Duplicate_Inbound = false,
    .Duplicate_Outbound = false,
    .Duplicate_Chance = "0",
    .OutOfOrder_Inbound = false,
    .OutOfOrder_Outbound = false,
    .OutOfOrder_Chance = "0",
    .Tamper_RedoChecksum = false,
    .Tamper_Inbound = false,
    .Tamper_Outbound = false,
    .Tamper_Chance = "0",
    .SetTCPRST_Inbound = false,
    .SetTCPRST_Outbound = false,
    .SetTCPRST_Chance = "0"
};

// Initialize Preset1 structure with default values
Preset5 preset5 = {
    .PresetName = "Preset5",
    .Lag_Inbound = false,
    .Lag_Outbound = false,
    .Lag_Delay = "0",
    .Drop_Inbound = false,
    .Drop_Outbound = false,
    .Drop_Chance = "0",
    .Disconnect_Inbound = false,
    .Disconnect_Outbound = false,
    .BandwidthLimiter_QueueSize = "0",
    .BandwidthLimiter_Size = "kb",
    .BandwidthLimiter_Inbound = false,
    .BandwidthLimiter_Outbound = false,
    .BandwidthLimiter_Limit = "0",
    .Throttle_DropThrottled = false,
    .Throttle_Timeframe = "0",
    .Throttle_Inbound = false,
    .Throttle_Outbound = false,
    .Throttle_Chance = "0",
    .Duplicate_Count = "0",
    .Duplicate_Inbound = false,
    .Duplicate_Outbound = false,
    .Duplicate_Chance = "0",
    .OutOfOrder_Inbound = false,
    .OutOfOrder_Outbound = false,
    .OutOfOrder_Chance = "0",
    .Tamper_RedoChecksum = false,
    .Tamper_Inbound = false,
    .Tamper_Outbound = false,
    .Tamper_Chance = "0",
    .SetTCPRST_Inbound = false,
    .SetTCPRST_Outbound = false,
    .SetTCPRST_Chance = "0"
};



static int handler3(void* user, const char* section, const char* name, const char* value) {
    General* generalconfig = (General*)user;
#define MATCH(s, n) (strcmp(section, s) == 0 && strcmp(name, n) == 0)

    if (MATCH("General", "Keybind")) {
        // Use _strdup if your environment requires it
        generalconfig->Keybind = _strdup(value);

        // Optionally, handle memory allocation errors
        if (generalconfig->Keybind == NULL) {
            return -1; // Indicate an error
        }
    }

    return 0; // Indicate success
}


static int handler1(void* user, const char* section, const char* name, const char* value)
{
    Preset1* pconfig1 = (Preset1*)user;

#define MATCH(s, n) (strcmp(section, s) == 0 && strcmp(name, n) == 0)

    if (MATCH("Preset1", "PresetName")) {
        pconfig1->PresetName = _strdup(value);
    }
    else if (MATCH("Preset1", "Lag_Inbound")) {
        pconfig1->Lag_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Lag_Outbound")) {
        pconfig1->Lag_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Lag_Delay")) {
        pconfig1->Lag_Delay = _strdup(value);
    }
    else if (MATCH("Preset1", "Drop_Inbound")) {
        pconfig1->Drop_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Drop_Outbound")) {
        pconfig1->Drop_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Drop_Chance")) {
        pconfig1->Drop_Chance = _strdup(value);
    }
    else if (MATCH("Preset1", "Disconnect_Inbound")) {
        pconfig1->Disconnect_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Disconnect_Outbound")) {
        pconfig1->Disconnect_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "BandwidthLimiter_QueueSize")) {
        pconfig1->BandwidthLimiter_QueueSize = _strdup(value);
    }
    else if (MATCH("Preset1", "BandwidthLimiter_Size")) {
        pconfig1->BandwidthLimiter_Size = _strdup(value);
    }
    else if (MATCH("Preset1", "BandwidthLimiter_Inbound")) {
        pconfig1->BandwidthLimiter_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "BandwidthLimiter_Outbound")) {
        pconfig1->BandwidthLimiter_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "BandwidthLimiter_Limit")) {
        pconfig1->BandwidthLimiter_Limit = _strdup(value);
    }
    else if (MATCH("Preset1", "Throttle_DropThrottled")) {
        pconfig1->Throttle_DropThrottled = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Throttle_Timeframe")) {
        pconfig1->Throttle_Timeframe = _strdup(value);
    }
    else if (MATCH("Preset1", "Throttle_Inbound")) {
        pconfig1->Throttle_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Throttle_Outbound")) {
        pconfig1->Throttle_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Throttle_Chance")) {
        pconfig1->Throttle_Chance = _strdup(value);
    }
    else if (MATCH("Preset1", "Duplicate_Count")) {
        pconfig1->Duplicate_Count = _strdup(value);
    }
    else if (MATCH("Preset1", "Duplicate_Inbound")) {
        pconfig1->Duplicate_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Duplicate_Outbound")) {
        pconfig1->Duplicate_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Duplicate_Chance")) {
        pconfig1->Duplicate_Chance = _strdup(value);
    }
    else if (MATCH("Preset1", "OutOfOrder_Inbound")) {
        pconfig1->OutOfOrder_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "OutOfOrder_Outbound")) {
        pconfig1->OutOfOrder_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "OutOfOrder_Chance")) {
        pconfig1->OutOfOrder_Chance = _strdup(value);
    }
    else if (MATCH("Preset1", "Tamper_RedoChecksum")) {
        pconfig1->Tamper_RedoChecksum = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Tamper_Inbound")) {
        pconfig1->Tamper_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Tamper_Outbound")) {
        pconfig1->Tamper_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "Tamper_Chance")) {
        pconfig1->Tamper_Chance = _strdup(value);
    }
    else if (MATCH("Preset1", "SetTCPRST_Inbound")) {
        pconfig1->SetTCPRST_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "SetTCPRST_Outbound")) {
        pconfig1->SetTCPRST_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset1", "SetTCPRST_Chance")) {
        pconfig1->SetTCPRST_Chance = _strdup(value);
    }else {
        return 0;  // unknown section/name, error
    }

    return 1;  // Success
}
static int handler2(void* user, const char* section, const char* name, const char* value)
{

    Preset2* pconfig2 = (Preset2*)user;


#define MATCH(s, n) (strcmp(section, s) == 0 && strcmp(name, n) == 0)

   if (MATCH("Preset2", "PresetName")) {
        pconfig2->PresetName = _strdup(value);
    }
    else if (MATCH("Preset2", "Lag_Inbound")) {
        pconfig2->Lag_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "Lag_Outbound")) {
        pconfig2->Lag_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "Lag_Delay")) {
        pconfig2->Lag_Delay = _strdup(value);
    }
    else if (MATCH("Preset2", "Drop_Inbound")) {
        pconfig2->Drop_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "Drop_Outbound")) {
        pconfig2->Drop_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "Drop_Chance")) {
        pconfig2->Drop_Chance = _strdup(value);
    }
    else if (MATCH("Preset2", "Disconnect_Inbound")) {
       pconfig2->Disconnect_Inbound = strcmp(value, "true") == 0;
   }
    else if (MATCH("Preset2", "Disconnect_Outbound")) {
       pconfig2->Disconnect_Outbound = strcmp(value, "true") == 0;
   }
    else if (MATCH("Preset2", "BandwidthLimiter_QueueSize")) {
        pconfig2->BandwidthLimiter_QueueSize = _strdup(value);
    }
    else if (MATCH("Preset2", "BandwidthLimiter_Size")) {
        pconfig2->BandwidthLimiter_Size = _strdup(value);
    }
    else if (MATCH("Preset2", "BandwidthLimiter_Inbound")) {
        pconfig2->BandwidthLimiter_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "BandwidthLimiter_Outbound")) {
        pconfig2->BandwidthLimiter_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "BandwidthLimiter_Limit")) {
        pconfig2->BandwidthLimiter_Limit = _strdup(value);
    }
    else if (MATCH("Preset2", "Throttle_DropThrottled")) {
        pconfig2->Throttle_DropThrottled = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "Throttle_Timeframe")) {
        pconfig2->Throttle_Timeframe = _strdup(value);
    }
    else if (MATCH("Preset2", "Throttle_Inbound")) {
        pconfig2->Throttle_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "Throttle_Outbound")) {
        pconfig2->Throttle_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "Throttle_Chance")) {
        pconfig2->Throttle_Chance = _strdup(value);
    }
    else if (MATCH("Preset2", "Duplicate_Count")) {
        pconfig2->Duplicate_Count = _strdup(value);
    }
    else if (MATCH("Preset2", "Duplicate_Inbound")) {
        pconfig2->Duplicate_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "Duplicate_Outbound")) {
        pconfig2->Duplicate_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "Duplicate_Chance")) {
        pconfig2->Duplicate_Chance = _strdup(value);
    }
    else if (MATCH("Preset2", "OutOfOrder_Inbound")) {
        pconfig2->OutOfOrder_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "OutOfOrder_Outbound")) {
        pconfig2->OutOfOrder_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "OutOfOrder_Chance")) {
        pconfig2->OutOfOrder_Chance = _strdup(value);
    }
    else if (MATCH("Preset2", "Tamper_RedoChecksum")) {
        pconfig2->Tamper_RedoChecksum = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "Tamper_Inbound")) {
        pconfig2->Tamper_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "Tamper_Outbound")) {
        pconfig2->Tamper_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "Tamper_Chance")) {
        pconfig2->Tamper_Chance = _strdup(value);
    }
    else if (MATCH("Preset2", "SetTCPRST_Inbound")) {
        pconfig2->SetTCPRST_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "SetTCPRST_Outbound")) {
        pconfig2->SetTCPRST_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset2", "SetTCPRST_Chance")) {
        pconfig2->SetTCPRST_Chance = _strdup(value);
    }
    else {
        return 0;  // unknown section/name, error
    }

    return 1;  // Success
}
static int handler4(void* user, const char* section, const char* name, const char* value)
{
    Preset3* pconfig3 = (Preset3*)user;

#define MATCH(s, n) (strcmp(section, s) == 0 && strcmp(name, n) == 0)

    if (MATCH("Preset3", "PresetName")) {
        pconfig3->PresetName = _strdup(value);
    }
    else if (MATCH("Preset3", "Lag_Inbound")) {
        pconfig3->Lag_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Lag_Outbound")) {
        pconfig3->Lag_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Lag_Delay")) {
        pconfig3->Lag_Delay = _strdup(value);
    }
    else if (MATCH("Preset3", "Drop_Inbound")) {
        pconfig3->Drop_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Drop_Outbound")) {
        pconfig3->Drop_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Drop_Chance")) {
        pconfig3->Drop_Chance = _strdup(value);
    }
    else if (MATCH("Preset3", "Disconnect_Inbound")) {
        pconfig3->Disconnect_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Disconnect_Outbound")) {
        pconfig3->Disconnect_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "BandwidthLimiter_QueueSize")) {
        pconfig3->BandwidthLimiter_QueueSize = _strdup(value);
    }
    else if (MATCH("Preset3", "BandwidthLimiter_Size")) {
        pconfig3->BandwidthLimiter_Size = _strdup(value);
    }
    else if (MATCH("Preset3", "BandwidthLimiter_Inbound")) {
        pconfig3->BandwidthLimiter_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "BandwidthLimiter_Outbound")) {
        pconfig3->BandwidthLimiter_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "BandwidthLimiter_Limit")) {
        pconfig3->BandwidthLimiter_Limit = _strdup(value);
    }
    else if (MATCH("Preset3", "Throttle_DropThrottled")) {
        pconfig3->Throttle_DropThrottled = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Throttle_Timeframe")) {
        pconfig3->Throttle_Timeframe = _strdup(value);
    }
    else if (MATCH("Preset3", "Throttle_Inbound")) {
        pconfig3->Throttle_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Throttle_Outbound")) {
        pconfig3->Throttle_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Throttle_Chance")) {
        pconfig3->Throttle_Chance = _strdup(value);
    }
    else if (MATCH("Preset3", "Duplicate_Count")) {
        pconfig3->Duplicate_Count = _strdup(value);
    }
    else if (MATCH("Preset3", "Duplicate_Inbound")) {
        pconfig3->Duplicate_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Duplicate_Outbound")) {
        pconfig3->Duplicate_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Duplicate_Chance")) {
        pconfig3->Duplicate_Chance = _strdup(value);
    }
    else if (MATCH("Preset3", "OutOfOrder_Inbound")) {
        pconfig3->OutOfOrder_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "OutOfOrder_Outbound")) {
        pconfig3->OutOfOrder_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "OutOfOrder_Chance")) {
        pconfig3->OutOfOrder_Chance = _strdup(value);
    }
    else if (MATCH("Preset3", "Tamper_RedoChecksum")) {
        pconfig3->Tamper_RedoChecksum = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Tamper_Inbound")) {
        pconfig3->Tamper_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Tamper_Outbound")) {
        pconfig3->Tamper_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "Tamper_Chance")) {
        pconfig3->Tamper_Chance = _strdup(value);
    }
    else if (MATCH("Preset3", "SetTCPRST_Inbound")) {
        pconfig3->SetTCPRST_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "SetTCPRST_Outbound")) {
        pconfig3->SetTCPRST_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset3", "SetTCPRST_Chance")) {
        pconfig3->SetTCPRST_Chance = _strdup(value);
    }
    else {
        return 0;  // unknown section/name, error
    }

    return 1;  // Success
}
static int handler5(void* user, const char* section, const char* name, const char* value)
{
    Preset4* pconfig4 = (Preset4*)user;

#define MATCH(s, n) (strcmp(section, s) == 0 && strcmp(name, n) == 0)

    if (MATCH("Preset4", "PresetName")) {
        pconfig4->PresetName = _strdup(value);
    }
    else if (MATCH("Preset4", "Lag_Inbound")) {
        pconfig4->Lag_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Lag_Outbound")) {
        pconfig4->Lag_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Lag_Delay")) {
        pconfig4->Lag_Delay = _strdup(value);
    }
    else if (MATCH("Preset4", "Drop_Inbound")) {
        pconfig4->Drop_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Drop_Outbound")) {
        pconfig4->Drop_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Drop_Chance")) {
        pconfig4->Drop_Chance = _strdup(value);
    }
    else if (MATCH("Preset4", "Disconnect_Inbound")) {
        pconfig4->Disconnect_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Disconnect_Outbound")) {
        pconfig4->Disconnect_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "BandwidthLimiter_QueueSize")) {
        pconfig4->BandwidthLimiter_QueueSize = _strdup(value);
    }
    else if (MATCH("Preset4", "BandwidthLimiter_Size")) {
        pconfig4->BandwidthLimiter_Size = _strdup(value);
    }
    else if (MATCH("Preset4", "BandwidthLimiter_Inbound")) {
        pconfig4->BandwidthLimiter_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "BandwidthLimiter_Outbound")) {
        pconfig4->BandwidthLimiter_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "BandwidthLimiter_Limit")) {
        pconfig4->BandwidthLimiter_Limit = _strdup(value);
    }
    else if (MATCH("Preset4", "Throttle_DropThrottled")) {
        pconfig4->Throttle_DropThrottled = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Throttle_Timeframe")) {
        pconfig4->Throttle_Timeframe = _strdup(value);
    }
    else if (MATCH("Preset4", "Throttle_Inbound")) {
        pconfig4->Throttle_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Throttle_Outbound")) {
        pconfig4->Throttle_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Throttle_Chance")) {
        pconfig4->Throttle_Chance = _strdup(value);
    }
    else if (MATCH("Preset4", "Duplicate_Count")) {
        pconfig4->Duplicate_Count = _strdup(value);
    }
    else if (MATCH("Preset4", "Duplicate_Inbound")) {
        pconfig4->Duplicate_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Duplicate_Outbound")) {
        pconfig4->Duplicate_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Duplicate_Chance")) {
        pconfig4->Duplicate_Chance = _strdup(value);
    }
    else if (MATCH("Preset4", "OutOfOrder_Inbound")) {
        pconfig4->OutOfOrder_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "OutOfOrder_Outbound")) {
        pconfig4->OutOfOrder_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "OutOfOrder_Chance")) {
        pconfig4->OutOfOrder_Chance = _strdup(value);
    }
    else if (MATCH("Preset4", "Tamper_RedoChecksum")) {
        pconfig4->Tamper_RedoChecksum = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Tamper_Inbound")) {
        pconfig4->Tamper_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Tamper_Outbound")) {
        pconfig4->Tamper_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "Tamper_Chance")) {
        pconfig4->Tamper_Chance = _strdup(value);
    }
    else if (MATCH("Preset4", "SetTCPRST_Inbound")) {
        pconfig4->SetTCPRST_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "SetTCPRST_Outbound")) {
        pconfig4->SetTCPRST_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset4", "SetTCPRST_Chance")) {
        pconfig4->SetTCPRST_Chance = _strdup(value);
    }
    else {
        return 0;  // unknown section/name, error
    }

    return 1;  // Success
}
static int handler6(void* user, const char* section, const char* name, const char* value)
{
    Preset5* pconfig5 = (Preset5*)user;

#define MATCH(s, n) (strcmp(section, s) == 0 && strcmp(name, n) == 0)

    if (MATCH("Preset5", "PresetName")) {
        pconfig5->PresetName = _strdup(value);
    }
    else if (MATCH("Preset5", "Lag_Inbound")) {
        pconfig5->Lag_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Lag_Outbound")) {
        pconfig5->Lag_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Lag_Delay")) {
        pconfig5->Lag_Delay = _strdup(value);
    }
    else if (MATCH("Preset5", "Drop_Inbound")) {
        pconfig5->Drop_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Drop_Outbound")) {
        pconfig5->Drop_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Drop_Chance")) {
        pconfig5->Drop_Chance = _strdup(value);
    }
    else if (MATCH("Preset5", "Disconnect_Inbound")) {
        pconfig5->Disconnect_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Disconnect_Outbound")) {
        pconfig5->Disconnect_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "BandwidthLimiter_QueueSize")) {
        pconfig5->BandwidthLimiter_QueueSize = _strdup(value);
    }
    else if (MATCH("Preset5", "BandwidthLimiter_Size")) {
        pconfig5->BandwidthLimiter_Size = _strdup(value);
    }
    else if (MATCH("Preset5", "BandwidthLimiter_Inbound")) {
        pconfig5->BandwidthLimiter_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "BandwidthLimiter_Outbound")) {
        pconfig5->BandwidthLimiter_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "BandwidthLimiter_Limit")) {
        pconfig5->BandwidthLimiter_Limit = _strdup(value);
    }
    else if (MATCH("Preset5", "Throttle_DropThrottled")) {
        pconfig5->Throttle_DropThrottled = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Throttle_Timeframe")) {
        pconfig5->Throttle_Timeframe = _strdup(value);
    }
    else if (MATCH("Preset5", "Throttle_Inbound")) {
        pconfig5->Throttle_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Throttle_Outbound")) {
        pconfig5->Throttle_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Throttle_Chance")) {
        pconfig5->Throttle_Chance = _strdup(value);
    }
    else if (MATCH("Preset5", "Duplicate_Count")) {
        pconfig5->Duplicate_Count = _strdup(value);
    }
    else if (MATCH("Preset5", "Duplicate_Inbound")) {
        pconfig5->Duplicate_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Duplicate_Outbound")) {
        pconfig5->Duplicate_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Duplicate_Chance")) {
        pconfig5->Duplicate_Chance = _strdup(value);
    }
    else if (MATCH("Preset5", "OutOfOrder_Inbound")) {
        pconfig5->OutOfOrder_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "OutOfOrder_Outbound")) {
        pconfig5->OutOfOrder_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "OutOfOrder_Chance")) {
        pconfig5->OutOfOrder_Chance = _strdup(value);
    }
    else if (MATCH("Preset5", "Tamper_RedoChecksum")) {
        pconfig5->Tamper_RedoChecksum = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Tamper_Inbound")) {
        pconfig5->Tamper_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Tamper_Outbound")) {
        pconfig5->Tamper_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "Tamper_Chance")) {
        pconfig5->Tamper_Chance = _strdup(value);
    }
    else if (MATCH("Preset5", "SetTCPRST_Inbound")) {
        pconfig5->SetTCPRST_Inbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "SetTCPRST_Outbound")) {
        pconfig5->SetTCPRST_Outbound = strcmp(value, "true") == 0;
    }
    else if (MATCH("Preset5", "SetTCPRST_Chance")) {
        pconfig5->SetTCPRST_Chance = _strdup(value);
    }
    else {
        return 0;  // unknown section/name, error
    }

    return 1;  // Success
}

// ! the order decides which module get processed first
Module* modules[MODULE_CNT] = {
    &lagModule,
    &dropModule,
    &disconnectModule,
    &bandwidthModule,
    &throttleModule,
    &dupModule,
    &oodModule,
    &tamperModule,
    &resetModule,
};

volatile short sendState = SEND_STATUS_NONE;

// global iup handlers
static Ihandle *dialog, *topFrame, * middleFrame, * lowerMiddleFrame, * bottomFrame;
static Ihandle *statusLabel;
static Ihandle* filterText, * filterButton;
static Ihandle* label1, * label2;

// Function prototype for timer callback
static int timerDelayCb(Ihandle* ih);


Ihandle* filterSelectList;
Ihandle* filterSelectList2;
Ihandle* filterSelectList3;
Ihandle* filterSelectList4;
Ihandle* filterSelectList5;

int DelayTimerValue=1000;


Ihandle* TimerLabel;

// timer to update icons
static Ihandle *stateIcon;
static Ihandle *timer;
static Ihandle *timeout = NULL;

void showStatus(const char *line);
static int uiOnDialogShow(Ihandle *ih, int state);
static int uiStopCb(Ihandle *ih);
static int uiStartCb(Ihandle *ih);
static int uiTimerCb(Ihandle *ih);
static int uiTimeoutCb(Ihandle *ih);
static int uiListSelectCb(Ihandle* ih, char* text, int item, int state);
static int uiList2SelectCb(Ihandle* ih, char* text, int item, int state);
static int uiList3SelectCb(Ihandle* ih, char* text, int item, int state);
static int uiList4SelectCb(Ihandle* ih, char* text, int item, int state);
static int uiList5SelectCb(Ihandle* ih, char* text, int item, int state);






static int uiFilterTextCb(Ihandle *ih);
static void uiSetupModule(Module *module, Ihandle *parent);

// serializing config files using a stupid custom format
#define CONFIG_FILE "config.txt"
#define CONFIG_MAX_RECORDS 64
#define CONFIG_BUF_SIZE 4096
typedef struct {
    char* filterName;
    char* filterValue;
} filterRecord;
UINT filtersSize;
filterRecord filters[CONFIG_MAX_RECORDS] = {0};
char configBuf[CONFIG_BUF_SIZE+2]; // add some padding to write \n
BOOL parameterized = 0; // parameterized flag, means reading args from command line

// loading up filters and fill in
void loadConfig() {
    char path[MSG_BUFSIZE];
    char *p;
    FILE *f;
    GetModuleFileName(NULL, path, MSG_BUFSIZE);
    LOG("Executable path: %s", path);
    p = strrchr(path, '\\');
    if (p == NULL) p = strrchr(path, '/'); // holy shit
    strcpy(p+1, CONFIG_FILE);
    LOG("Config path: %s", path);
    f = fopen(path, "r");
    if (f) {
        size_t len;
        char *current, *last;
        len = fread(configBuf, sizeof(char), CONFIG_BUF_SIZE, f);
        if (len == CONFIG_BUF_SIZE) {
            LOG("Config file is larger than %d bytes, get truncated.", CONFIG_BUF_SIZE);
        }
        // always patch in a newline at the end to ease parsing
        configBuf[len] = '\n';
        configBuf[len+1] = '\0';

        // parse out the kv pairs. isn't quite safe
        filtersSize = 0;
        last = current = configBuf;
        do {
            // eat up empty lines
EAT_SPACE:  while (isspace(*current)) { ++current; }
            if (*current == '#') {
                current = strchr(current, '\n');
                if (!current) break;
                current = current + 1;
                goto EAT_SPACE;
            }

            // now we can start
            last = current;
            current = strchr(last, ':');
            if (!current) break;
            *current = '\0';
            filters[filtersSize].filterName = last;
            current += 1;
            while (isspace(*current)) { ++current; } // eat potential space after :
            last = current;
            current = strchr(last, '\n');
            if (!current) break;
            filters[filtersSize].filterValue = last;
            *current = '\0';
            if (*(current-1) == '\r') *(current-1) = 0;
            last = current = current + 1;
            ++filtersSize;
        } while (last && last - configBuf < CONFIG_BUF_SIZE);
        LOG("Loaded %u records.", filtersSize);
    }

    if (!f || filtersSize == 0)
    {
        LOG("Failed to load from config. Fill in a simple one.");
        // config is missing or ill-formed. fill in some simple ones
        filters[filtersSize].filterName = "loopback packets";
        filters[filtersSize].filterValue = "outbound and ip.DstAddr >= 127.0.0.1 and ip.DstAddr <= 127.255.255.255";
        filtersSize = 1;
    }
}

void init(int argc, char* argv[]) {
    UINT ix;
    Ihandle* topVbox, * bottomVbox, * dialogVBox, * controlHbox;
    Ihandle* noneIcon, * doingIcon, * errorIcon;
    char* arg_value = NULL;

    // fill in config
    loadConfig();

    // iup inits
    IupOpen(&argc, &argv);

    // this is so easy to get wrong so it's pretty worth noting in the program
    statusLabel = IupLabel("NOTICE: When capturing localhost (loopback) packets, you CAN'T include inbound criteria.\n"
        "Filters like 'udp' need to be 'udp and outbound' to work. See readme for more info.");
    IupSetAttribute(statusLabel, "EXPAND", "HORIZONTAL");
    IupSetAttribute(statusLabel, "PADDING", "8x8");

    topFrame = IupFrame(
        topVbox = IupVbox(
            filterText = IupText(NULL),
            controlHbox = IupHbox(
                stateIcon = IupLabel(NULL),
                filterButton = IupButton("Start", NULL),
                IupLabel("Network:  "),
                filterSelectList2 = IupList(NULL),
                IupFill(),
                IupLabel("Presets:  "),
                filterSelectList = IupList(NULL),
                NULL
            ),
            NULL
        )
    );

    
      controlHbox = IupHbox(
          IupLabel("Function Presets:  "),
          filterSelectList3 = IupList(NULL),
          IupFill(),

          IupLabel("Trigger Mode"),
          filterSelectList4 = IupList(NULL),

          IupFill(),

          TimerLabel = IupLabel("Timer:"),
          filterSelectList5 = IupList(NULL),
        NULL
    );

     
      
      //filterSelectList5
    lowerMiddleFrame = IupFrame(
        controlHbox 
  
    );
    IupHide(filterSelectList5);
    IupHide(TimerLabel);

    // Define the keybind as a constant character string
    const char* keybind = general.Keybind;

    // Base text with placeholder for the keybind variable
    const char* baseText = "Use the key %s to toggle on/off\nThis is a modified version of clumsy to use hotkeys to toggle on/off coded by kalirenegade\nIf you like these updates and want to show your appreciation, feel free to donate with cashapp $kalirenegade";

    // Calculate the length needed for the formatted string
    int len = snprintf(NULL, 0, baseText, keybind) + 1;

  // Allocate memory for the label text
    char* labelText = (char*)malloc(len);
    if (labelText == NULL) {
        perror("Failed to allocate memory");
        // Handle the error appropriately (e.g., log it, clean up resources)
        return;  // Simply return without a value
    }

    // Construct the label text with the keybind variable
    snprintf(labelText, len, baseText, keybind);
    middleFrame = IupFrame(
        label1 = IupLabel(labelText)
      
    );


    // parse arguments and set globals *before* setting up UI.
    // arguments can be read and set after callbacks are setup
    // FIXME as Release is built as WindowedApp, stdout/stderr won't show
    LOG("argc: %d", argc);
    if (argc > 1) {
        if (!parseArgs(argc, argv)) {
            fprintf(stderr, "invalid argument count. ensure you're using options as \"--drop on\"");
            exit(-1); // fail fast.
        }
        parameterized = 1;
    }
    IupSetAttribute(label1, "ALIGNMENT", "ACENTER");    
    IupSetAttribute(topFrame, "TITLE", "Filtering");
    IupSetAttribute(topFrame, "EXPAND", "HORIZONTAL");
    IupSetAttribute(filterText, "EXPAND", "HORIZONTAL");
    IupSetCallback(filterText, "VALUECHANGED_CB", (Icallback)uiFilterTextCb);
    IupSetAttribute(filterButton, "PADDING", "8x");
    IupSetCallback(filterButton, "ACTION", uiStartCb);
    IupSetAttribute(topVbox, "NCMARGIN", "4x4");
    IupSetAttribute(topVbox, "NCGAP", "4x2");
    IupSetAttribute(controlHbox, "ALIGNMENT", "ACENTER");

    // setup state icon
    IupSetAttribute(stateIcon, "IMAGE", "none_icon");
    IupSetAttribute(stateIcon, "PADDING", "4x");

    // fill in options and setup callback
    IupSetAttribute(filterSelectList, "VISIBLECOLUMNS", "24");
    IupSetAttribute(filterSelectList, "DROPDOWN", "YES");

    IupSetAttribute(filterSelectList2, "VISIBLECOLUMNS", "15");
    IupSetAttribute(filterSelectList2, "DROPDOWN", "YES");
    IupSetAttributes(filterSelectList2, "1=(Local)_This_Device, 2=(Remote)_Shared_Devices");
    IupSetAttribute(filterSelectList2, "VALUE", "2");
    IupSetCallback(filterSelectList2, "ACTION", (Icallback)uiList2SelectCb);

    for (ix = 0; ix < filtersSize; ++ix) {
        char ixBuf[4];
        sprintf(ixBuf, "%d", ix+1); // ! staring from 1, following lua indexing
        IupStoreAttribute(filterSelectList, ixBuf, filters[ix].filterName);
    }
    IupSetAttribute(filterSelectList, "VALUE", "1");

    IupSetAttribute(filterSelectList3, "VALUE", "1");
    IupSetAttribute(filterSelectList4, "VALUE", "1");

    IupSetCallback(filterSelectList, "ACTION", (Icallback)uiListSelectCb);
    // set filter text value since the callback won't take effect before main loop starts
    IupSetAttribute(filterText, "VALUE", filters[0].filterValue);

    // functionalities frame 
    bottomFrame = IupFrame(
        bottomVbox = IupVbox(
            NULL
        )
    );
    IupSetAttribute(bottomFrame, "TITLE", "Functions");
    IupSetAttribute(bottomVbox, "NCMARGIN", "4x4");
    IupSetAttribute(bottomVbox, "NCGAP", "4x2");

    // create icons
    noneIcon = IupImage(8, 8, icon8x8);
    doingIcon = IupImage(8, 8, icon8x8);
    errorIcon = IupImage(8, 8, icon8x8);
    IupSetAttribute(noneIcon, "0", "BGCOLOR");
    IupSetAttribute(noneIcon, "1", "224 224 224");
    IupSetAttribute(doingIcon, "0", "BGCOLOR");
    IupSetAttribute(doingIcon, "1", "109 170 44");
    IupSetAttribute(errorIcon, "0", "BGCOLOR");
    IupSetAttribute(errorIcon, "1", "208 70 72");
    IupSetHandle("none_icon", noneIcon);
    IupSetHandle("doing_icon", doingIcon);
    IupSetHandle("error_icon", errorIcon);



    IupSetAttribute(label1, "EXPAND", "HORIZONTAL");
    IupSetAttribute(middleFrame, "TITLE", "Info");
    IupSetAttribute(middleFrame, "EXPAND", "HORIZONTAL");
    

    IupSetAttribute(label2, "EXPAND", "HORIZONTAL");
    IupSetAttribute(lowerMiddleFrame, "TITLE", "Extra Presets");
    IupSetAttribute(lowerMiddleFrame, "EXPAND", "HORIZONTAL");
    IupSetAttribute(filterSelectList3, "VISIBLECOLUMNS", "15");
    IupSetAttribute(filterSelectList3, "DROPDOWN", "YES");
    IupSetCallback(filterSelectList3, "ACTION", (Icallback)uiList3SelectCb);

    IupSetAttribute(filterSelectList4, "VISIBLECOLUMNS", "4");
    IupSetAttribute(filterSelectList4, "DROPDOWN", "YES");
    IupSetCallback(filterSelectList4, "ACTION", (Icallback)uiList4SelectCb);

    IupSetAttribute(filterSelectList5, "VISIBLECOLUMNS", "2");
    IupSetAttribute(filterSelectList5, "DROPDOWN", "YES");
    IupSetCallback(filterSelectList5, "ACTION", (Icallback)uiList5SelectCb);



    
    // setup module uis
    for (ix = 0; ix < MODULE_CNT; ++ix) {
        uiSetupModule(*(modules+ix), bottomVbox);
    }

    // dialog
    dialog = IupDialog(
        dialogVBox = IupVbox(
            topFrame,
            middleFrame,
            lowerMiddleFrame,
            bottomFrame,
            statusLabel,
            NULL
        )
    );

    IupSetAttribute(dialog, "TITLE", "clumsy Keybind Edition by Kalirenegade " CLUMSY_VERSION);
    IupSetAttribute(dialog, "SIZE", "480x"); // add padding manually to width
    IupSetAttribute(dialog, "RESIZE", "NO");
    IupSetCallback(dialog, "SHOW_CB", (Icallback)uiOnDialogShow);


    // global layout settings to affect childrens
    IupSetAttribute(dialogVBox, "ALIGNMENT", "ACENTER");
    IupSetAttribute(dialogVBox, "NCMARGIN", "4x4");
    IupSetAttribute(dialogVBox, "NCGAP", "4x2");

    // setup timer
    timer = IupTimer();
    IupSetAttribute(timer, "TIME", STR(ICON_UPDATE_MS));
    IupSetCallback(timer, "ACTION_CB", uiTimerCb);

    // setup timeout of program
    arg_value = IupGetGlobal("timeout");
    if(arg_value != NULL)
    {
        char valueBuf[16];
        sprintf(valueBuf, "%s000", arg_value);  // convert from seconds to milliseconds

        timeout = IupTimer();
        IupStoreAttribute(timeout, "TIME", valueBuf);
        IupSetCallback(timeout, "ACTION_CB", uiTimeoutCb);
        IupSetAttribute(timeout, "RUN", "YES");
    }
}

void startup() {
    // initialize seed
    srand((unsigned int)time(NULL));

    // kickoff event loops
    IupShowXY(dialog, IUP_CENTER, IUP_CENTER);
    IupMainLoop();
    // ! main loop won't return until program exit
}

void cleanup() {

    IupDestroy(timer);
    if (timeout) {
        IupDestroy(timeout);
    }

    IupClose();
    endTimePeriod(); // try close if not closing
}

// ui logics
void showStatus(const char *line) {
    IupStoreAttribute(statusLabel, "TITLE", line); 
}

// in fact only 32bit binary would run on 64 bit os
// if this happens pop out message box and exit
static BOOL check32RunningOn64(HWND hWnd) {
    BOOL is64ret;
    // consider IsWow64Process return value
    if (IsWow64Process(GetCurrentProcess(), &is64ret) && is64ret) {
        MessageBox(hWnd, (LPCSTR)"You're running 32bit clumsy on 64bit Windows, which wouldn't work. Please use the 64bit clumsy version.",
            (LPCSTR)"Aborting", MB_OK);
        return TRUE;
    }
    return FALSE;
}

static BOOL checkIsRunning() {
    //It will be closed and destroyed when programm terminates (according to MSDN).
    HANDLE hStartEvent = CreateEventW(NULL, FALSE, FALSE, L"Global\\CLUMSY_IS_RUNNING_EVENT_NAME");

    if (hStartEvent == NULL)
        return TRUE;

    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(hStartEvent);
        hStartEvent = NULL;
        return TRUE;
    }

    return FALSE;
}


static int uiOnDialogShow(Ihandle *ih, int state) {
    // only need to process on show
    HWND hWnd;
    BOOL exit;
    HICON icon;
    HINSTANCE hInstance;
    if (state != IUP_SHOW) return IUP_DEFAULT;
    hWnd = (HWND)IupGetAttribute(ih, "HWND");
    hInstance = GetModuleHandle(NULL);

    // set application icon
    icon = LoadIcon(hInstance, "CLUMSY_ICON");
    SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
    SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);

    exit = checkIsRunning();
    if (exit) {
        MessageBox(hWnd, (LPCSTR)"Theres' already an instance of clumsy running.",
            (LPCSTR)"Aborting", MB_OK);
        return IUP_CLOSE;
    }

#ifdef _WIN32
    exit = check32RunningOn64(hWnd);
    if (exit) {
        return IUP_CLOSE;
    }
#endif

    // try elevate and decides whether to exit
    exit = tryElevate(hWnd, parameterized);

    if (!exit && parameterized) {
        setFromParameter(filterText, "VALUE", "filter");
        LOG("is parameterized, start filtering upon execution.");
        uiStartCb(filterButton);
    }

    return exit ? IUP_CLOSE : IUP_DEFAULT;
}static int uiStartCb(Ihandle* ih) {
    if (Mode == 0) {
        running = 1;
        char buf[MSG_BUFSIZE];
        UNREFERENCED_PARAMETER(ih);
        if (divertStart(IupGetAttribute(filterText, "VALUE"), buf) == 0) {
            showStatus(buf);
            return IUP_DEFAULT;
        }

        // Successfully started
        showStatus("Started filtering. Enable functionalities to take effect.");
        IupSetAttribute(filterText, "ACTIVE", "NO");
        IupSetAttribute(filterButton, "TITLE", "Stop");
        IupSetCallback(filterButton, "ACTION", uiStopCb);
        IupSetAttribute(timer, "RUN", "NO");
        return IUP_DEFAULT;
    }
    else {
        running = 1;
        char buf[MSG_BUFSIZE];
        UNREFERENCED_PARAMETER(ih);
        if (divertStart(IupGetAttribute(filterText, "VALUE"), buf) == 0) {
            showStatus(buf);
            return IUP_DEFAULT;
        }

        // Successfully started
        showStatus("Started filtering. Enable functionalities to take effect.");
        IupSetAttribute(filterText, "ACTIVE", "NO");
        IupSetAttribute(filterButton, "TITLE", "Stop");
        IupSetCallback(filterButton, "ACTION", uiStopCb);
        IupSetAttribute(timer, "RUN", "YES");

        // Create and configure the timer
        Ihandle* delayTimer = IupTimer();
        intToStr(DelayTimerValue, timerbuffer);
        IupSetAttribute(delayTimer, "TIME", timerbuffer);
        IupSetCallback(delayTimer, "ACTION_CB", timerDelayCb);
        IupSetAttribute(delayTimer, "RUN", "YES");

        return IUP_DEFAULT;
    }
}
static int uiStopCb(Ihandle *ih) {
    running = 0;
    int ix;
    UNREFERENCED_PARAMETER(ih);
    
    // try stopping
    IupSetAttribute(filterButton, "ACTIVE", "NO");
    IupFlush(); // flush to show disabled state
    divertStop();

    IupSetAttribute(filterText, "ACTIVE", "YES");
    IupSetAttribute(filterButton, "TITLE", "Start");
    IupSetAttribute(filterButton, "ACTIVE", "YES");
    IupSetCallback(filterButton, "ACTION", uiStartCb);

    // stop timer and clean up icons
    IupSetAttribute(timer, "RUN", "NO");
    for (ix = 0; ix < MODULE_CNT; ++ix) {
        modules[ix]->processTriggered = 0; // use = here since is threads already stopped
        IupSetAttribute(modules[ix]->iconHandle, "IMAGE", "none_icon");
    }
    sendState = SEND_STATUS_NONE;
    IupSetAttribute(stateIcon, "IMAGE", "none_icon");

    showStatus("Stopped. To begin again, edit criteria and click Start.");
    return IUP_DEFAULT;
}

static int uiToggleControls(Ihandle *ih, int state) {
    Ihandle *controls = (Ihandle*)IupGetAttribute(ih, CONTROLS_HANDLE);
    short *target = (short*)IupGetAttribute(ih, SYNCED_VALUE);
    int controlsActive = IupGetInt(controls, "ACTIVE");
    if (controlsActive && !state) {
        IupSetAttribute(controls, "ACTIVE", "NO");
        InterlockedExchange16(target, I2S(state));
    } else if (!controlsActive && state) {
        IupSetAttribute(controls, "ACTIVE", "YES");
        InterlockedExchange16(target, I2S(state));
    }

    return IUP_DEFAULT;
}

static int uiTimerCb(Ihandle* ih) {
    int ix;
    UNREFERENCED_PARAMETER(ih);

    for (ix = 0; ix < MODULE_CNT; ++ix) {
        // Use Interlocked functions for thread-safe access
        short processTriggered = InterlockedExchange16(&(modules[ix]->processTriggered), 0);

        if (processTriggered) {
            IupSetAttribute(modules[ix]->iconHandle, "IMAGE", "doing_icon");
            // Set the value back to 0 atomically
            InterlockedAnd16(&(modules[ix]->processTriggered), 0);
        }
        else {
            IupSetAttribute(modules[ix]->iconHandle, "IMAGE", "none_icon");
        }
    }

    return IUP_DEFAULT;
}

static int uiTimeoutCb(Ihandle *ih) {
    UNREFERENCED_PARAMETER(ih);
    return IUP_CLOSE;
 }


static int uiListSelectCb(Ihandle* ih, char* text, int item, int state) {
    UNREFERENCED_PARAMETER(text);
    UNREFERENCED_PARAMETER(ih);
    if (state == 1) {
        IupSetAttribute(filterText, "VALUE", filters[item - 1].filterValue);
    }
    return IUP_DEFAULT;
}

static int uiList2SelectCb(Ihandle* ih, char* text, int item, int state) {
    UNREFERENCED_PARAMETER(text);
    UNREFERENCED_PARAMETER(ih);
    UNREFERENCED_PARAMETER(state);
    NetworkType = item;
 
    return IUP_DEFAULT;
}

static int uiList4SelectCb(Ihandle* ih, char* text, int item, int state) {
    UNREFERENCED_PARAMETER(text);
    UNREFERENCED_PARAMETER(ih);
    UNREFERENCED_PARAMETER(item);
    UNREFERENCED_PARAMETER(state);

    if (state == 1) {
        if (strcmp(text, "Toggle") == 0) {
            IupHide(filterSelectList5);
            IupHide(TimerLabel);
            Mode = 0;
        }
        else if (strcmp(text, "Timer") == 0) {
            IupShow(filterSelectList5);
            IupShow(TimerLabel);
            Mode = 1;
        }
    }
    return IUP_DEFAULT;
}

static int uiList5SelectCb(Ihandle* ih, char* text, int item, int state) {
    UNREFERENCED_PARAMETER(ih);
    UNREFERENCED_PARAMETER(item);
    UNREFERENCED_PARAMETER(state);

    if (state == 1) {
        int seconds = atoi(text);  // Convert the text to an integer

        if (seconds >= 1 && seconds <= 60) {
            DelayTimerValue = seconds*1000;
        }
    }

    return IUP_DEFAULT;
}

static int uiList3SelectCb(Ihandle* ih, char* text, int item, int state) {
    UNREFERENCED_PARAMETER(text);
    UNREFERENCED_PARAMETER(ih);
    UNREFERENCED_PARAMETER(item);
    UNREFERENCED_PARAMETER(state);  

    if (state == 1) {
        if (strcmp(text, preset1.PresetName) == 0) {
            //preset1
            preset1_config();
        }
        else if (strcmp(text, preset2.PresetName) == 0) {
            //preset2
            preset2_config();
        }
        else if (strcmp(text, preset3.PresetName) == 0) {
            //preset3
            preset3_config();
        }
        else if (strcmp(text, preset4.PresetName) == 0) {
            //preset4
            preset4_config();
        }
        else if (strcmp(text, preset5.PresetName) == 0) {
            //preset5
            preset5_config();
          

        }
      

    }
    return IUP_DEFAULT;
}

void preset1_config(void) {
    //lag
    if (preset1.Lag_Inbound == true) {
        Set_Lag_inboundCheckbox("ON");
    }
    else {
        Set_Lag_inboundCheckbox("OFF");
    }
    if (preset1.Lag_Outbound == true) {
        Set_Lag_outboundCheckbox("ON");
    }
    else {
        Set_Lag_outboundCheckbox("OFF");
    }
    Set_Lag_timeInput(preset1.Lag_Delay);
    //drop
    if (preset1.Drop_Inbound == true) {
        Set_Drop_inboundCheckbox("ON");
    }
    else {
        Set_Drop_inboundCheckbox("OFF");
    }
    if (preset1.Drop_Outbound == true) {
        Set_Drop_outboundCheckbox("ON");
    }
    else {
        Set_Drop_outboundCheckbox("OFF");
    }
    Set_Drop_chanceInput(preset1.Drop_Chance);
    //Disconnect
    if (preset1.Disconnect_Inbound == true) {
        Set_Disconnect_inboundCheckbox("ON");
    }
    else {
        Set_Disconnect_inboundCheckbox("OFF");
    }
    if (preset1.Disconnect_Outbound == true) {
        Set_Disconnect_outboundCheckbox("ON");
    }
    else {
        Set_Disconnect_outboundCheckbox("OFF");
    }
    //bandwidth
    if (preset1.BandwidthLimiter_Inbound == true) {
        Set_Bandwidth_inboundCheckbox("ON");
    }
    else {
        Set_Bandwidth_inboundCheckbox("OFF");
    }
    if (preset1.BandwidthLimiter_Outbound == true) {
        Set_Bandwidth_outboundCheckbox("ON");
    }
    else {
        Set_Bandwidth_outboundCheckbox("OFF");
    }
    Set_Bandwidth_bandwidthInput(preset1.BandwidthLimiter_Limit);
    Set_Bandwidth_queueSizeInput(preset1.BandwidthLimiter_QueueSize);
    Set_Bandwidth_speed(preset1.BandwidthLimiter_Size);
    //Throttle
    if (preset1.Throttle_Inbound == true) {
        Set_Throttle_inboundCheckbox("ON");
    }
    else {
        Set_Throttle_inboundCheckbox("OFF");
    }
    if (preset1.Throttle_Outbound == true) {
        Set_Throttle_outboundCheckbox("ON");
    }
    else {
        Set_Throttle_outboundCheckbox("OFF");
    }
    Set_Throttle_frameInput(preset1.Throttle_Timeframe);
    Set_Throttle_frameInpchanceInputut(preset1.Throttle_Chance);
    if (preset1.Throttle_DropThrottled == true) {
        Set_Throttle_dropThrottledCheckbox("ON");
    }
    else {
        Set_Throttle_dropThrottledCheckbox("OFF");
    }
    //Duplicate
    if (preset1.Duplicate_Inbound == true) {
        Set_Duplicate_inboundCheckbox("ON");
    }
    else {
        Set_Duplicate_inboundCheckbox("OFF");
    }
    if (preset1.Duplicate_Outbound == true) {
        Set_Duplicate_outboundCheckbox("ON");
    }
    else {
        Set_Duplicate_outboundCheckbox("OFF");
    }
    Set_Duplicate_chanceInput(preset1.Duplicate_Chance);
    Set_Duplicate_countInput(preset1.Duplicate_Count);
    //OutOfOrdfer
    if (preset1.OutOfOrder_Inbound == true) {
        Set_OutOfOrder_inboundCheckbox("ON");
    }
    else {
        Set_OutOfOrder_inboundCheckbox("OFF");
    }
    if (preset1.OutOfOrder_Outbound == true) {
        Set_OutOfOrder_outboundCheckbox("ON");
    }
    else {
        Set_OutOfOrder_outboundCheckbox("OFF");
    }
    Set_OutOfOrder_chanceInput(preset1.OutOfOrder_Chance);
    //Tamper
    if (preset1.Tamper_Inbound == true) {
        Set_Tamper_inboundCheckbox("ON");
    }
    else {
        Set_Tamper_inboundCheckbox("OFF");
    }
    if (preset1.Tamper_Outbound == true) {
        Set_Tamper_outboundCheckbox("ON");
    }
    else {
        Set_Tamper_outboundCheckbox("OFF");
    }
    Set_Tamper_chanceInput(preset1.Tamper_Chance);
    if (preset1.Tamper_RedoChecksum == true) {
        Set_Tamper_checksumCheckbox("ON");
    }
    else {
        Set_Tamper_checksumCheckbox("OFF");
    }
    //Reset
    if (preset1.SetTCPRST_Inbound == true) {
        Set_Reset_inboundCheckbox("ON");
    }
    else {
        Set_Reset_inboundCheckbox("OFF");
    }
    if (preset1.SetTCPRST_Outbound == true) {
        Set_Reset_outboundCheckbox("ON");
    }
    else {
        Set_Reset_outboundCheckbox("OFF");
    }
    Set_Reset_chanceInput(preset1.SetTCPRST_Chance);
}

void preset2_config(void) {
    //lag
    if (preset2.Lag_Inbound == true) {
        Set_Lag_inboundCheckbox("ON");
    }
    else {
        Set_Lag_inboundCheckbox("OFF");
    }
    if (preset2.Lag_Outbound == true) {
        Set_Lag_outboundCheckbox("ON");
    }
    else {
        Set_Lag_outboundCheckbox("OFF");
    }
    Set_Lag_timeInput(preset2.Lag_Delay);
    //drop
    if (preset2.Drop_Inbound == true) {
        Set_Drop_inboundCheckbox("ON");
    }
    else {
        Set_Drop_inboundCheckbox("OFF");
    }
    if (preset2.Drop_Outbound == true) {
        Set_Drop_outboundCheckbox("ON");
    }
    else {
        Set_Drop_outboundCheckbox("OFF");
    }
    Set_Drop_chanceInput(preset2.Drop_Chance);
    //Disconnect
    if (preset2.Disconnect_Inbound == true) {
        Set_Disconnect_inboundCheckbox("ON");
    }
    else {
        Set_Disconnect_inboundCheckbox("OFF");
    }
    if (preset2.Disconnect_Outbound == true) {
        Set_Disconnect_outboundCheckbox("ON");
    }
    else {
        Set_Disconnect_outboundCheckbox("OFF");
    }
    //bandwidth
    if (preset2.BandwidthLimiter_Inbound == true) {
        Set_Bandwidth_inboundCheckbox("ON");
    }
    else {
        Set_Bandwidth_inboundCheckbox("OFF");
    }
    if (preset2.BandwidthLimiter_Outbound == true) {
        Set_Bandwidth_outboundCheckbox("ON");
    }
    else {
        Set_Bandwidth_outboundCheckbox("OFF");
    }
    Set_Bandwidth_bandwidthInput(preset2.BandwidthLimiter_Limit);
    Set_Bandwidth_queueSizeInput(preset2.BandwidthLimiter_QueueSize);
    Set_Bandwidth_speed(preset2.BandwidthLimiter_Size);
    //Throttle
    if (preset2.Throttle_Inbound == true) {
        Set_Throttle_inboundCheckbox("ON");
    }
    else {
        Set_Throttle_inboundCheckbox("OFF");
    }
    if (preset2.Throttle_Outbound == true) {
        Set_Throttle_outboundCheckbox("ON");
    }
    else {
        Set_Throttle_outboundCheckbox("OFF");
    }
    Set_Throttle_frameInput(preset2.Throttle_Timeframe);
    Set_Throttle_frameInpchanceInputut(preset2.Throttle_Chance);
    if (preset2.Throttle_DropThrottled == true) {
        Set_Throttle_dropThrottledCheckbox("ON");
    }
    else {
        Set_Throttle_dropThrottledCheckbox("OFF");
    }
    //Duplicate
    if (preset2.Duplicate_Inbound == true) {
        Set_Duplicate_inboundCheckbox("ON");
    }
    else {
        Set_Duplicate_inboundCheckbox("OFF");
    }
    if (preset2.Duplicate_Outbound == true) {
        Set_Duplicate_outboundCheckbox("ON");
    }
    else {
        Set_Duplicate_outboundCheckbox("OFF");
    }
    Set_Duplicate_chanceInput(preset2.Duplicate_Chance);
    Set_Duplicate_countInput(preset2.Duplicate_Count);
    //OutOfOrdfer
    if (preset2.OutOfOrder_Inbound == true) {
        Set_OutOfOrder_inboundCheckbox("ON");
    }
    else {
        Set_OutOfOrder_inboundCheckbox("OFF");
    }
    if (preset2.OutOfOrder_Outbound == true) {
        Set_OutOfOrder_outboundCheckbox("ON");
    }
    else {
        Set_OutOfOrder_outboundCheckbox("OFF");
    }
    Set_OutOfOrder_chanceInput(preset2.OutOfOrder_Chance);
    //Tamper
    if (preset2.Tamper_Inbound == true) {
        Set_Tamper_inboundCheckbox("ON");
    }
    else {
        Set_Tamper_inboundCheckbox("OFF");
    }
    if (preset2.Tamper_Outbound == true) {
        Set_Tamper_outboundCheckbox("ON");
    }
    else {
        Set_Tamper_outboundCheckbox("OFF");
    }
    Set_Tamper_chanceInput(preset2.Tamper_Chance);
    if (preset2.Tamper_RedoChecksum == true) {
        Set_Tamper_checksumCheckbox("ON");
    }
    else {
        Set_Tamper_checksumCheckbox("OFF");
    }
    //Reset
    if (preset2.SetTCPRST_Inbound == true) {
        Set_Reset_inboundCheckbox("ON");
    }
    else {
        Set_Reset_inboundCheckbox("OFF");
    }
    if (preset2.SetTCPRST_Outbound == true) {
        Set_Reset_outboundCheckbox("ON");
    }
    else {
        Set_Reset_outboundCheckbox("OFF");
    }
    Set_Reset_chanceInput(preset2.SetTCPRST_Chance);
}
void preset3_config(void) {
    //lag
    if (preset3.Lag_Inbound == true) {
        Set_Lag_inboundCheckbox("ON");
    }
    else {
        Set_Lag_inboundCheckbox("OFF");
    }
    if (preset3.Lag_Outbound == true) {
        Set_Lag_outboundCheckbox("ON");
    }
    else {
        Set_Lag_outboundCheckbox("OFF");
    }
    Set_Lag_timeInput(preset3.Lag_Delay);
    //drop
    if (preset3.Drop_Inbound == true) {
        Set_Drop_inboundCheckbox("ON");
    }
    else {
        Set_Drop_inboundCheckbox("OFF");
    }
    if (preset3.Drop_Outbound == true) {
        Set_Drop_outboundCheckbox("ON");
    }
    else {
        Set_Drop_outboundCheckbox("OFF");
    }
    Set_Drop_chanceInput(preset3.Drop_Chance);
    //Disconnect
    if (preset3.Disconnect_Inbound == true) {
        Set_Disconnect_inboundCheckbox("ON");
    }
    else {
        Set_Disconnect_inboundCheckbox("OFF");
    }
    if (preset3.Disconnect_Outbound == true) {
        Set_Disconnect_outboundCheckbox("ON");
    }
    else {
        Set_Disconnect_outboundCheckbox("OFF");
    }
    //bandwidth
    if (preset3.BandwidthLimiter_Inbound == true) {
        Set_Bandwidth_inboundCheckbox("ON");
    }
    else {
        Set_Bandwidth_inboundCheckbox("OFF");
    }
    if (preset3.BandwidthLimiter_Outbound == true) {
        Set_Bandwidth_outboundCheckbox("ON");
    }
    else {
        Set_Bandwidth_outboundCheckbox("OFF");
    }
    Set_Bandwidth_bandwidthInput(preset3.BandwidthLimiter_Limit);
    Set_Bandwidth_queueSizeInput(preset3.BandwidthLimiter_QueueSize);
    Set_Bandwidth_speed(preset3.BandwidthLimiter_Size);
    //Throttle
    if (preset3.Throttle_Inbound == true) {
        Set_Throttle_inboundCheckbox("ON");
    }
    else {
        Set_Throttle_inboundCheckbox("OFF");
    }
    if (preset3.Throttle_Outbound == true) {
        Set_Throttle_outboundCheckbox("ON");
    }
    else {
        Set_Throttle_outboundCheckbox("OFF");
    }
    Set_Throttle_frameInput(preset3.Throttle_Timeframe);
    Set_Throttle_frameInpchanceInputut(preset3.Throttle_Chance);
    if (preset3.Throttle_DropThrottled == true) {
        Set_Throttle_dropThrottledCheckbox("ON");
    }
    else {
        Set_Throttle_dropThrottledCheckbox("OFF");
    }
    //Duplicate
    if (preset3.Duplicate_Inbound == true) {
        Set_Duplicate_inboundCheckbox("ON");
    }
    else {
        Set_Duplicate_inboundCheckbox("OFF");
    }
    if (preset3.Duplicate_Outbound == true) {
        Set_Duplicate_outboundCheckbox("ON");
    }
    else {
        Set_Duplicate_outboundCheckbox("OFF");
    }
    Set_Duplicate_chanceInput(preset3.Duplicate_Chance);
    Set_Duplicate_countInput(preset3.Duplicate_Count);
    //OutOfOrdfer
    if (preset3.OutOfOrder_Inbound == true) {
        Set_OutOfOrder_inboundCheckbox("ON");
    }
    else {
        Set_OutOfOrder_inboundCheckbox("OFF");
    }
    if (preset3.OutOfOrder_Outbound == true) {
        Set_OutOfOrder_outboundCheckbox("ON");
    }
    else {
        Set_OutOfOrder_outboundCheckbox("OFF");
    }
    Set_OutOfOrder_chanceInput(preset3.OutOfOrder_Chance);
    //Tamper
    if (preset3.Tamper_Inbound == true) {
        Set_Tamper_inboundCheckbox("ON");
    }
    else {
        Set_Tamper_inboundCheckbox("OFF");
    }
    if (preset3.Tamper_Outbound == true) {
        Set_Tamper_outboundCheckbox("ON");
    }
    else {
        Set_Tamper_outboundCheckbox("OFF");
    }
    Set_Tamper_chanceInput(preset3.Tamper_Chance);
    if (preset3.Tamper_RedoChecksum == true) {
        Set_Tamper_checksumCheckbox("ON");
    }
    else {
        Set_Tamper_checksumCheckbox("OFF");
    }
    //Reset
    if (preset3.SetTCPRST_Inbound == true) {
        Set_Reset_inboundCheckbox("ON");
    }
    else {
        Set_Reset_inboundCheckbox("OFF");
    }
    if (preset3.SetTCPRST_Outbound == true) {
        Set_Reset_outboundCheckbox("ON");
    }
    else {
        Set_Reset_outboundCheckbox("OFF");
    }
    Set_Reset_chanceInput(preset3.SetTCPRST_Chance);
}
void preset4_config(void) {
    //lag
    if (preset4.Lag_Inbound == true) {
        Set_Lag_inboundCheckbox("ON");
    }
    else {
        Set_Lag_inboundCheckbox("OFF");
    }
    if (preset4.Lag_Outbound == true) {
        Set_Lag_outboundCheckbox("ON");
    }
    else {
        Set_Lag_outboundCheckbox("OFF");
    }
    Set_Lag_timeInput(preset4.Lag_Delay);
    //drop
    if (preset4.Drop_Inbound == true) {
        Set_Drop_inboundCheckbox("ON");
    }
    else {
        Set_Drop_inboundCheckbox("OFF");
    }
    if (preset4.Drop_Outbound == true) {
        Set_Drop_outboundCheckbox("ON");
    }
    else {
        Set_Drop_outboundCheckbox("OFF");
    }
    Set_Drop_chanceInput(preset4.Drop_Chance);
    //Disconnect
    if (preset4.Disconnect_Inbound == true) {
        Set_Disconnect_inboundCheckbox("ON");
    }
    else {
        Set_Disconnect_inboundCheckbox("OFF");
    }
    if (preset4.Disconnect_Outbound == true) {
        Set_Disconnect_outboundCheckbox("ON");
    }
    else {
        Set_Disconnect_outboundCheckbox("OFF");
    }
    //bandwidth
    if (preset4.BandwidthLimiter_Inbound == true) {
        Set_Bandwidth_inboundCheckbox("ON");
    }
    else {
        Set_Bandwidth_inboundCheckbox("OFF");
    }
    if (preset4.BandwidthLimiter_Outbound == true) {
        Set_Bandwidth_outboundCheckbox("ON");
    }
    else {
        Set_Bandwidth_outboundCheckbox("OFF");
    }
    Set_Bandwidth_bandwidthInput(preset4.BandwidthLimiter_Limit);
    Set_Bandwidth_queueSizeInput(preset4.BandwidthLimiter_QueueSize);
    Set_Bandwidth_speed(preset4.BandwidthLimiter_Size);
    //Throttle
    if (preset4.Throttle_Inbound == true) {
        Set_Throttle_inboundCheckbox("ON");
    }
    else {
        Set_Throttle_inboundCheckbox("OFF");
    }
    if (preset4.Throttle_Outbound == true) {
        Set_Throttle_outboundCheckbox("ON");
    }
    else {
        Set_Throttle_outboundCheckbox("OFF");
    }
    Set_Throttle_frameInput(preset4.Throttle_Timeframe);
    Set_Throttle_frameInpchanceInputut(preset4.Throttle_Chance);
    if (preset4.Throttle_DropThrottled == true) {
        Set_Throttle_dropThrottledCheckbox("ON");
    }
    else {
        Set_Throttle_dropThrottledCheckbox("OFF");
    }
    //Duplicate
    if (preset4.Duplicate_Inbound == true) {
        Set_Duplicate_inboundCheckbox("ON");
    }
    else {
        Set_Duplicate_inboundCheckbox("OFF");
    }
    if (preset4.Duplicate_Outbound == true) {
        Set_Duplicate_outboundCheckbox("ON");
    }
    else {
        Set_Duplicate_outboundCheckbox("OFF");
    }
    Set_Duplicate_chanceInput(preset4.Duplicate_Chance);
    Set_Duplicate_countInput(preset4.Duplicate_Count);
    //OutOfOrdfer
    if (preset4.OutOfOrder_Inbound == true) {
        Set_OutOfOrder_inboundCheckbox("ON");
    }
    else {
        Set_OutOfOrder_inboundCheckbox("OFF");
    }
    if (preset4.OutOfOrder_Outbound == true) {
        Set_OutOfOrder_outboundCheckbox("ON");
    }
    else {
        Set_OutOfOrder_outboundCheckbox("OFF");
    }
    Set_OutOfOrder_chanceInput(preset4.OutOfOrder_Chance);
    //Tamper
    if (preset4.Tamper_Inbound == true) {
        Set_Tamper_inboundCheckbox("ON");
    }
    else {
        Set_Tamper_inboundCheckbox("OFF");
    }
    if (preset4.Tamper_Outbound == true) {
        Set_Tamper_outboundCheckbox("ON");
    }
    else {
        Set_Tamper_outboundCheckbox("OFF");
    }
    Set_Tamper_chanceInput(preset4.Tamper_Chance);
    if (preset4.Tamper_RedoChecksum == true) {
        Set_Tamper_checksumCheckbox("ON");
    }
    else {
        Set_Tamper_checksumCheckbox("OFF");
    }
    //Reset
    if (preset4.SetTCPRST_Inbound == true) {
        Set_Reset_inboundCheckbox("ON");
    }
    else {
        Set_Reset_inboundCheckbox("OFF");
    }
    if (preset4.SetTCPRST_Outbound == true) {
        Set_Reset_outboundCheckbox("ON");
    }
    else {
        Set_Reset_outboundCheckbox("OFF");
    }
    Set_Reset_chanceInput(preset4.SetTCPRST_Chance);
}
void preset5_config(void) {
    //lag
    if (preset5.Lag_Inbound == true) {
        Set_Lag_inboundCheckbox("ON");
    }
    else {
        Set_Lag_inboundCheckbox("OFF");
    }
    if (preset5.Lag_Outbound == true) {
        Set_Lag_outboundCheckbox("ON");
    }
    else {
        Set_Lag_outboundCheckbox("OFF");
    }
    Set_Lag_timeInput(preset5.Lag_Delay);
    //drop
    if (preset5.Drop_Inbound == true) {
        Set_Drop_inboundCheckbox("ON");
    }
    else {
        Set_Drop_inboundCheckbox("OFF");
    }
    if (preset5.Drop_Outbound == true) {
        Set_Drop_outboundCheckbox("ON");
    }
    else {
        Set_Drop_outboundCheckbox("OFF");
    }
    Set_Drop_chanceInput(preset5.Drop_Chance);
    //Disconnect
    if (preset5.Disconnect_Inbound == true) {
        Set_Disconnect_inboundCheckbox("ON");
    }
    else {
        Set_Disconnect_inboundCheckbox("OFF");
    }
    if (preset5.Disconnect_Outbound == true) {
        Set_Disconnect_outboundCheckbox("ON");
    }
    else {
        Set_Disconnect_outboundCheckbox("OFF");
    }
    //bandwidth
    if (preset5.BandwidthLimiter_Inbound == true) {
        Set_Bandwidth_inboundCheckbox("ON");
    }
    else {
        Set_Bandwidth_inboundCheckbox("OFF");
    }
    if (preset5.BandwidthLimiter_Outbound == true) {
        Set_Bandwidth_outboundCheckbox("ON");
    }
    else {
        Set_Bandwidth_outboundCheckbox("OFF");
    }
    Set_Bandwidth_bandwidthInput(preset5.BandwidthLimiter_Limit);
    Set_Bandwidth_queueSizeInput(preset5.BandwidthLimiter_QueueSize);
    Set_Bandwidth_speed(preset5.BandwidthLimiter_Size);
    //Throttle
    if (preset5.Throttle_Inbound == true) {
        Set_Throttle_inboundCheckbox("ON");
    }
    else {
        Set_Throttle_inboundCheckbox("OFF");
    }
    if (preset5.Throttle_Outbound == true) {
        Set_Throttle_outboundCheckbox("ON");
    }
    else {
        Set_Throttle_outboundCheckbox("OFF");
    }
    Set_Throttle_frameInput(preset5.Throttle_Timeframe);
    Set_Throttle_frameInpchanceInputut(preset5.Throttle_Chance);
    if (preset5.Throttle_DropThrottled == true) {
        Set_Throttle_dropThrottledCheckbox("ON");
    }
    else {
        Set_Throttle_dropThrottledCheckbox("OFF");
    }
    //Duplicate
    if (preset5.Duplicate_Inbound == true) {
        Set_Duplicate_inboundCheckbox("ON");
    }
    else {
        Set_Duplicate_inboundCheckbox("OFF");
    }
    if (preset5.Duplicate_Outbound == true) {
        Set_Duplicate_outboundCheckbox("ON");
    }
    else {
        Set_Duplicate_outboundCheckbox("OFF");
    }
    Set_Duplicate_chanceInput(preset5.Duplicate_Chance);
    Set_Duplicate_countInput(preset5.Duplicate_Count);
    //OutOfOrdfer
    if (preset5.OutOfOrder_Inbound == true) {
        Set_OutOfOrder_inboundCheckbox("ON");
    }
    else {
        Set_OutOfOrder_inboundCheckbox("OFF");
    }
    if (preset5.OutOfOrder_Outbound == true) {
        Set_OutOfOrder_outboundCheckbox("ON");
    }
    else {
        Set_OutOfOrder_outboundCheckbox("OFF");
    }
    Set_OutOfOrder_chanceInput(preset5.OutOfOrder_Chance);
    //Tamper
    if (preset5.Tamper_Inbound == true) {
        Set_Tamper_inboundCheckbox("ON");
    }
    else {
        Set_Tamper_inboundCheckbox("OFF");
    }
    if (preset5.Tamper_Outbound == true) {
        Set_Tamper_outboundCheckbox("ON");
    }
    else {
        Set_Tamper_outboundCheckbox("OFF");
    }
    Set_Tamper_chanceInput(preset5.Tamper_Chance);
    if (preset5.Tamper_RedoChecksum == true) {
        Set_Tamper_checksumCheckbox("ON");
    }
    else {
        Set_Tamper_checksumCheckbox("OFF");
    }
    //Reset
    if (preset5.SetTCPRST_Inbound == true) {
        Set_Reset_inboundCheckbox("ON");
    }
    else {
        Set_Reset_inboundCheckbox("OFF");
    }
    if (preset5.SetTCPRST_Outbound == true) {
        Set_Reset_outboundCheckbox("ON");
    }
    else {
        Set_Reset_outboundCheckbox("OFF");
    }
    Set_Reset_chanceInput(preset5.SetTCPRST_Chance);
}

static int uiFilterTextCb(Ihandle *ih)  {
    UNREFERENCED_PARAMETER(ih);
    // unselect list
    IupSetAttribute(filterSelectList, "VALUE", "0");
    return IUP_DEFAULT;
}

static void uiSetupModule(Module *module, Ihandle *parent) {
    Ihandle *groupBox, *toggle, *controls, *icon;
    groupBox = IupHbox(
        icon = IupLabel(NULL),
        toggle = IupToggle(module->displayName, NULL),
        IupFill(),
        controls = module->setupUIFunc(),
        NULL
    );
    IupSetAttribute(groupBox, "EXPAND", "HORIZONTAL");
    IupSetAttribute(groupBox, "ALIGNMENT", "ACENTER");
    IupSetAttribute(controls, "ALIGNMENT", "ACENTER");
    IupAppend(parent, groupBox);

    // set controls as attribute to toggle and enable toggle callback
    IupSetCallback(toggle, "ACTION", (Icallback)uiToggleControls);
    IupSetAttribute(toggle, CONTROLS_HANDLE, (char*)controls);
    IupSetAttribute(toggle, SYNCED_VALUE, (char*)module->enabledFlag);
    IupSetAttribute(controls, "ACTIVE", "NO"); // startup as inactive
    IupSetAttribute(controls, "NCGAP", "4"); // startup as inactive

    // set default icon
    IupSetAttribute(icon, "IMAGE", "none_icon");
    IupSetAttribute(icon, "PADDING", "4x");
    module->iconHandle = icon;

    // parameterize toggle
    if (parameterized) {
        setFromParameter(toggle, "VALUE", module->shortName);
    }
}

// Thread function
DWORD WINAPI threadFunction(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    printf("Hello from the thread!\n");
    BOOL keyToggled = FALSE; // Track the toggle state
    BOOL keyCurrentlyDown = FALSE; // Track the current key state
    while (1) {
 
        wchar_t wch;

        // Convert the first character of Keybind to wchar_t
        size_t convertedChars = 0;
        mbstowcs_s(&convertedChars, &wch, 1, general.Keybind, _TRUNCATE);
    
        if (convertedChars > 0) {
       
                mbstowcs(&wch, general.Keybind, 1);
                // Convert character to a virtual-key code using VkKeyScanW
                SHORT vkScan = VkKeyScanW(wch);

                // Extract the virtual-key code
                int vkCode = LOBYTE(vkScan);
                // Check if the key was found
                if (vkScan == -1) {
                    return 1;
                }
            BOOL isKeyDown = (GetAsyncKeyState(vkCode) & 0x8000) != 0; // 0x53 is the virtual key code for 'S' 0x5A = 'Z', 0xDB = '['

            if (isKeyDown && !keyCurrentlyDown) {
                // Key was just pressed
                keyToggled = !keyToggled; // Toggle the state
                keyCurrentlyDown = TRUE; // Set the key state to down
                printf("Key [ toggled to %s!\n", keyToggled ? "ON" : "OFF");
                if (running) {
                    uiStopCb(filterButton);
                }
                else {
                    if (Mode == 0) {
                        uiStartCb(filterButton);
                    }
                    else {
                        
                        IupSetAttribute(filterButton, "ACTIVE", "NO");
                        uiStartCb(filterButton);
                        Sleep(DelayTimerValue);
                        uiStopCb(filterButton);
                        IupSetAttribute(filterButton, "ACTIVE", "YES");
                    }
                }
            }
            else if (!isKeyDown && keyCurrentlyDown) {
                // Key was just released
                keyCurrentlyDown = FALSE; // Set the key state to up
            }
        }

        Sleep(10); // Sleep to reduce CPU usage
    }

    return 0;
}
// Callback function for the timer
static int timerDelayCb(Ihandle* ih) {
    // Call uiStopCb to stop filtering
    uiStopCb(ih);
    // Destroy the timer after use to clean up
    IupDestroy(ih);
    return IUP_DEFAULT;
}

void intToStr(int num, char* str) {
    int i = 0;
    int sign = num;
    if (num < 0) {
        num = -num;
    }
    do {
        str[i++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);
    if (sign < 0) {
        str[i++] = '-';
    }
    str[i] = '\0';
    // Reverse the string
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}
int main(int argc, char* argv[]) {

    

    if (ini_parse("presets.ini", handler1, &preset1) < 0) {
        return 1;
    }
    if (ini_parse("presets.ini", handler2, &preset2) < 0) {
        return 1;
    }
    if (ini_parse("presets.ini", handler3, &general) < 0) {
        return 1;
    }
    if (ini_parse("presets.ini", handler4, &preset3) < 0) {
        return 1;
    }
    if (ini_parse("presets.ini", handler5, &preset4) < 0) {
        return 1;
    }
    if (ini_parse("presets.ini", handler6, &preset5) < 0) {
        return 1;
    }

    LOG("Config loaded from 'presets.ini': keybind=%c\n", general.Keybind);





    LOG("Is Run As Admin: %d", IsRunAsAdmin());
    LOG("Is Elevated: %d", IsElevated());
    init(argc, argv);

    HANDLE thread;
    DWORD threadId;

    // Create a new thread
    thread = CreateThread(NULL, 0, threadFunction, NULL, 0, &threadId);
    if (thread == NULL) {
        printf("Error creating thread\n");
        return 1;
    }

    // Calculate the length needed for the attributes string
    int len = snprintf(NULL, 0, "1=%s, 2=%s, 3=%s, 4=%s, 5=%s", preset1.PresetName, preset2.PresetName, preset3.PresetName, preset4.PresetName, preset5.PresetName) + 1;
    char* attributes = (char*)malloc(len);

    // Construct the attribute string
    snprintf(attributes, len, "1=%s, 2=%s, 3=%s, 4=%s, 5=%s", preset1.PresetName, preset2.PresetName, preset3.PresetName, preset4.PresetName, preset5.PresetName);

    // Set the attributes
    IupSetAttributes(filterSelectList3, attributes);
    IupSetAttributes(filterSelectList4, "1=Toggle, 2=Timer");
    IupSetAttributes(filterSelectList5, "1=1, 2=2, 3=3, 4=4, 5=5, 6=6, 7=7, 8=8, 9=9, 10=10, 11=11, 12=12, 13=13, 14=14, 15=15, 16=16, 17=17, 18=18, 19=19, 20=20, 21=21, 22=22, 23=23, 24=24, 25=25, 26=26, 27=27, 28=28, 29=29, 30=30, 31=31, 32=32, 33=33, 34=34, 35=35, 36=36, 37=37, 38=38, 39=39, 40=40, 41=41, 42=42, 43=43, 44=44, 45=45, 46=46, 47=47, 48=48, 49=49, 50=50, 51=51, 52=52, 53=53, 54=54, 55=55, 56=56, 57=57, 58=58, 59=59, 60=60");

    IupSetAttribute(filterSelectList5, "VALUE", "1");

    preset1_config();


   // IupSetAttribute(filterSelectList3, "VALUE", "1");

    // Free the allocated memory
    free(attributes);
    startup();
    // Wait for the thread to finish
    //WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    cleanup();


    return 0;
}
