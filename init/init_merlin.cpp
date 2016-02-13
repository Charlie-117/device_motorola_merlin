/*
   Copyright (c) 2016, The CyanogenMod Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm.h"

static void setMsim(void);

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char platform[PROP_VALUE_MAX];
    char radio[PROP_VALUE_MAX];
    char sku[PROP_VALUE_MAX];
    char carrier[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    FILE *fp;
    int rc;

    UNUSED(msm_id);
    UNUSED(msm_ver);
    UNUSED(board_type);

    rc = property_get("ro.board.platform", platform);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    property_get("ro.boot.radio", radio);
    property_get("ro.boot.hardware.sku", sku);
    property_get("ro.boot.carrier", carrier);

    property_set("ro.product.model", sku);

    if (ISMATCH(sku, "XT1556") || ISMATCH(radio, "0xTODO")) {
        setMsim();
        property_set("ro.product.device", "merlin");
        property_set("ro.build.description", "TODO");
        property_set("ro.build.fingerprint", "TODO");
        property_set("ro.build.product", "merlin");
        property_set("ro.gsm.data_retry_config", "TODO");
        property_set("ro.mot.build.customerid", "TODO");
        property_set("persist.radio.mot_ecc_custid", "TODO");
        property_set("persist.radio.mot_ecc_enabled", "TODO");
        property_set("persist.radio.process_sups_ind", "TODO");
    }
    else if (ISMATCH(sku, "XT1557") || ISMATCH(radio, "0x9")) {
        setMsim();
        property_set("ro.product.device", "merlin");
        property_set("ro.build.description", "merlin_retasia-user 6.0 MPD24.65-22 23 release-keys");
        property_set("ro.build.fingerprint", "motorola/merlin_retasia/merlin:6.0/MPD24.65-22/23:user/release-keys");
        property_set("ro.build.product", "merlin");
        property_set("ro.mot.build.customerid", "retasia");
        property_set("persist.radio.mot_ecc_custid", "common");
        property_set("persist.radio.mot_ecc_enabled", "1");
    }

    property_get("ro.product.device", device);
    strlcpy(devicename, device, sizeof(devicename));
    INFO("Found radio id: %s data %s setting build properties for %s device\n", radio, sku, devicename);
}

static void setMsim(void)
{
    property_set("persist.radio.force_get_pref", "1");
    property_set("persist.radio.multisim.config", "dsds");
    property_set("persist.radio.plmn_name_cmp", "1");
    property_set("ro.telephony.ril.config", "simactivation");
}