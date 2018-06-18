/*
 * Copyright (c) 2011-2018 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * DO NOT EDIT - This file is generated automatically
 */

/*
 * IMPORTANT:  This file is for system that supports STA mode ONLY.
 */
#include "cfg_priv.h"

/**
 * cfg_get_string() - return string conversion of HE WNI CFG
 * @cfg_id: Config ID.
 *
 * This utility function helps log string conversion of WNI config ID.
 *
 * Return: string conversion of the HE WNI config ID, if match found;
 *	"Invalid" otherwise.
 */
const char *cfg_get_string(uint16_t cfg_id)
{
	switch (cfg_id) {
	default:
		break;
	CASE_RETURN_STRING(WNI_CFG_STA_ID);
	CASE_RETURN_STRING(WNI_CFG_CFP_PERIOD);
	CASE_RETURN_STRING(WNI_CFG_CFP_MAX_DURATION);
	CASE_RETURN_STRING(WNI_CFG_SSID);
	CASE_RETURN_STRING(WNI_CFG_BEACON_INTERVAL);
	CASE_RETURN_STRING(WNI_CFG_DTIM_PERIOD);
	CASE_RETURN_STRING(WNI_CFG_WEP_DEFAULT_KEY_1);
	CASE_RETURN_STRING(WNI_CFG_WEP_DEFAULT_KEY_2);
	CASE_RETURN_STRING(WNI_CFG_WEP_DEFAULT_KEY_3);
	CASE_RETURN_STRING(WNI_CFG_WEP_DEFAULT_KEY_4);
	CASE_RETURN_STRING(WNI_CFG_WEP_DEFAULT_KEYID);
	CASE_RETURN_STRING(WNI_CFG_RTS_THRESHOLD);
	CASE_RETURN_STRING(WNI_CFG_FRAGMENTATION_THRESHOLD);
	CASE_RETURN_STRING(WNI_CFG_ACTIVE_MAXIMUM_CHANNEL_TIME);
	CASE_RETURN_STRING(WNI_CFG_PASSIVE_MINIMUM_CHANNEL_TIME);
	CASE_RETURN_STRING(WNI_CFG_PASSIVE_MAXIMUM_CHANNEL_TIME);
	CASE_RETURN_STRING(WNI_CFG_JOIN_FAILURE_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_AUTHENTICATE_FAILURE_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_AUTHENTICATE_RSP_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_ASSOCIATION_FAILURE_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_REASSOCIATION_FAILURE_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_PS_DATA_INACTIVITY_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_SUPPORTED_RATES_11B);
	CASE_RETURN_STRING(WNI_CFG_SUPPORTED_RATES_11A);
	CASE_RETURN_STRING(WNI_CFG_DOT11_MODE);
	CASE_RETURN_STRING(WNI_CFG_OPERATIONAL_RATE_SET);
	CASE_RETURN_STRING(WNI_CFG_EXTENDED_OPERATIONAL_RATE_SET);
	CASE_RETURN_STRING(WNI_CFG_LISTEN_INTERVAL);
	CASE_RETURN_STRING(WNI_CFG_VALID_CHANNEL_LIST);
	CASE_RETURN_STRING(WNI_CFG_APSD_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_SHARED_KEY_AUTH_ENABLE);
	CASE_RETURN_STRING(WNI_CFG_OPEN_SYSTEM_AUTH_ENABLE);
	CASE_RETURN_STRING(WNI_CFG_AUTHENTICATION_TYPE);
	CASE_RETURN_STRING(WNI_CFG_PRIVACY_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_SHORT_PREAMBLE);
	CASE_RETURN_STRING(WNI_CFG_ACCEPT_SHORT_SLOT_ASSOC_ONLY);
	CASE_RETURN_STRING(WNI_CFG_QOS_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_HCF_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_RSN_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_MAX_NUM_PRE_AUTH);
	CASE_RETURN_STRING(WNI_CFG_HEART_BEAT_THRESHOLD);
	CASE_RETURN_STRING(WNI_CFG_PROBE_AFTER_HB_FAIL_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_MANUFACTURER_NAME);
	CASE_RETURN_STRING(WNI_CFG_MODEL_NUMBER);
	CASE_RETURN_STRING(WNI_CFG_MODEL_NAME);
	CASE_RETURN_STRING(WNI_CFG_MANUFACTURER_PRODUCT_NAME);
	CASE_RETURN_STRING(WNI_CFG_MANUFACTURER_PRODUCT_VERSION);
	CASE_RETURN_STRING(WNI_CFG_11D_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_MAX_TX_POWER_2_4);
	CASE_RETURN_STRING(WNI_CFG_MAX_TX_POWER_5);
	CASE_RETURN_STRING(WNI_CFG_CURRENT_TX_POWER_LEVEL);
	CASE_RETURN_STRING(WNI_CFG_NEW_BSS_FOUND_IND);
	CASE_RETURN_STRING(WNI_CFG_COUNTRY_CODE);
	CASE_RETURN_STRING(WNI_CFG_11H_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_WT_CNF_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_OLBC_DETECT_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_PROTECTION_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_11G_PROTECTION_ALWAYS);
	CASE_RETURN_STRING(WNI_CFG_FORCE_POLICY_PROTECTION);
	CASE_RETURN_STRING(WNI_CFG_11G_SHORT_PREAMBLE_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_11G_SHORT_SLOT_TIME_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_11G_ONLY_POLICY);
	CASE_RETURN_STRING(WNI_CFG_WME_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_ADDTS_RSP_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_MAX_SP_LENGTH);
	CASE_RETURN_STRING(WNI_CFG_WSM_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_EDCA_PROFILE);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ANI_ACBK_LOCAL);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ANI_ACBE_LOCAL);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ANI_ACVI_LOCAL);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ANI_ACVO_LOCAL);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ANI_ACBK);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ANI_ACBE);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ANI_ACVI);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ANI_ACVO);
	CASE_RETURN_STRING(WNI_CFG_EDCA_WME_ACBK_LOCAL);
	CASE_RETURN_STRING(WNI_CFG_EDCA_WME_ACBE_LOCAL);
	CASE_RETURN_STRING(WNI_CFG_EDCA_WME_ACVI_LOCAL);
	CASE_RETURN_STRING(WNI_CFG_EDCA_WME_ACVO_LOCAL);
	CASE_RETURN_STRING(WNI_CFG_EDCA_WME_ACBK);
	CASE_RETURN_STRING(WNI_CFG_EDCA_WME_ACBE);
	CASE_RETURN_STRING(WNI_CFG_EDCA_WME_ACVI);
	CASE_RETURN_STRING(WNI_CFG_EDCA_WME_ACVO);
	CASE_RETURN_STRING(WNI_CFG_LOCAL_POWER_CONSTRAINT);
	CASE_RETURN_STRING(WNI_CFG_ADMIT_POLICY);
	CASE_RETURN_STRING(WNI_CFG_ADMIT_BWFACTOR);
	CASE_RETURN_STRING(WNI_CFG_CHANNEL_BONDING_MODE);
	CASE_RETURN_STRING(WNI_CFG_SCAN_CONTROL_LIST);
	CASE_RETURN_STRING(WNI_CFG_BLOCK_ACK_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_HT_CAP_INFO);
	CASE_RETURN_STRING(WNI_CFG_HT_AMPDU_PARAMS);
	CASE_RETURN_STRING(WNI_CFG_SUPPORTED_MCS_SET);
	CASE_RETURN_STRING(WNI_CFG_EXT_HT_CAP_INFO);
	CASE_RETURN_STRING(WNI_CFG_TX_BF_CAP);
	CASE_RETURN_STRING(WNI_CFG_AS_CAP);
	CASE_RETURN_STRING(WNI_CFG_HT_INFO_FIELD1);
	CASE_RETURN_STRING(WNI_CFG_HT_INFO_FIELD2);
	CASE_RETURN_STRING(WNI_CFG_HT_INFO_FIELD3);
	CASE_RETURN_STRING(WNI_CFG_BASIC_MCS_SET);
	CASE_RETURN_STRING(WNI_CFG_CURRENT_MCS_SET);
	CASE_RETURN_STRING(WNI_CFG_VHT_MAX_MPDU_LENGTH);
	CASE_RETURN_STRING(WNI_CFG_VHT_SUPPORTED_CHAN_WIDTH_SET);
	CASE_RETURN_STRING(WNI_CFG_VHT_LDPC_CODING_CAP);
	CASE_RETURN_STRING(WNI_CFG_VHT_SHORT_GI_80MHZ);
	CASE_RETURN_STRING(WNI_CFG_VHT_SHORT_GI_160_AND_80_PLUS_80MHZ);
	CASE_RETURN_STRING(WNI_CFG_VHT_TXSTBC);
	CASE_RETURN_STRING(WNI_CFG_VHT_RXSTBC);
	CASE_RETURN_STRING(WNI_CFG_VHT_SU_BEAMFORMER_CAP);
	CASE_RETURN_STRING(WNI_CFG_VHT_SU_BEAMFORMEE_CAP);
	CASE_RETURN_STRING(WNI_CFG_VHT_CSN_BEAMFORMEE_ANT_SUPPORTED);
	CASE_RETURN_STRING(WNI_CFG_VHT_NUM_SOUNDING_DIMENSIONS);
	CASE_RETURN_STRING(WNI_CFG_VHT_MU_BEAMFORMER_CAP);
	CASE_RETURN_STRING(WNI_CFG_VHT_MU_BEAMFORMEE_CAP);
	CASE_RETURN_STRING(WNI_CFG_VHT_TXOP_PS);
	CASE_RETURN_STRING(WNI_CFG_VHT_HTC_VHTC_CAP);
	CASE_RETURN_STRING(WNI_CFG_VHT_AMPDU_LEN_EXPONENT);
	CASE_RETURN_STRING(WNI_CFG_VHT_LINK_ADAPTATION_CAP);
	CASE_RETURN_STRING(WNI_CFG_VHT_RX_ANT_PATTERN);
	CASE_RETURN_STRING(WNI_CFG_VHT_TX_ANT_PATTERN);
	CASE_RETURN_STRING(WNI_CFG_VHT_RX_MCS_MAP);
	CASE_RETURN_STRING(WNI_CFG_VHT_TX_MCS_MAP);
	CASE_RETURN_STRING(WNI_CFG_VHT_RX_HIGHEST_SUPPORTED_DATA_RATE);
	CASE_RETURN_STRING(WNI_CFG_VHT_TX_HIGHEST_SUPPORTED_DATA_RATE);
	CASE_RETURN_STRING(WNI_CFG_VHT_BASIC_MCS_SET);
	CASE_RETURN_STRING(WNI_CFG_VHT_MU_MIMO_CAP_STA_COUNT);
	CASE_RETURN_STRING(WNI_CFG_VHT_SS_UNDER_UTIL);
	CASE_RETURN_STRING(WNI_CFG_VHT_40MHZ_UTILIZATION);
	CASE_RETURN_STRING(WNI_CFG_VHT_80MHZ_UTILIZATION);
	CASE_RETURN_STRING(WNI_CFG_VHT_160MHZ_UTILIZATION);
	CASE_RETURN_STRING(WNI_CFG_MPDU_DENSITY);
	CASE_RETURN_STRING(WNI_CFG_MAX_RX_AMPDU_FACTOR);
	CASE_RETURN_STRING(WNI_CFG_MAX_PS_POLL);
	CASE_RETURN_STRING(WNI_CFG_WOWLAN_UCAST_PATTERN_FILTER_ENABLE);
	CASE_RETURN_STRING(WNI_CFG_WOWLAN_CHANNEL_SWITCH_ENABLE);
	CASE_RETURN_STRING(WNI_CFG_WOWLAN_DEAUTH_ENABLE);
	CASE_RETURN_STRING(WNI_CFG_WOWLAN_DISASSOC_ENABLE);
	CASE_RETURN_STRING(WNI_CFG_WOWLAN_MAX_MISSED_BEACON);
	CASE_RETURN_STRING(WNI_CFG_WOWLAN_MAX_SLEEP_PERIOD);
	CASE_RETURN_STRING(WNI_CFG_IBSS_AUTO_BSSID);
	CASE_RETURN_STRING(WNI_CFG_WPS_ENABLE);
	CASE_RETURN_STRING(WNI_CFG_WPS_STATE);
	CASE_RETURN_STRING(WNI_CFG_WPS_VERSION);
	CASE_RETURN_STRING(WNI_CFG_WPS_CFG_METHOD);
	CASE_RETURN_STRING(WNI_CFG_WPS_UUID);
	CASE_RETURN_STRING(WNI_CFG_WPS_PRIMARY_DEVICE_CATEGORY);
	CASE_RETURN_STRING(WNI_CFG_WPS_PIMARY_DEVICE_OUI);
	CASE_RETURN_STRING(WNI_CFG_WPS_DEVICE_SUB_CATEGORY);
	CASE_RETURN_STRING(WNI_CFG_WPS_DEVICE_PASSWORD_ID);
	CASE_RETURN_STRING(WNI_CFG_SINGLE_TID_RC);
	CASE_RETURN_STRING(WNI_CFG_TELE_BCN_WAKEUP_EN);
	CASE_RETURN_STRING(WNI_CFG_TELE_BCN_MAX_LI);
	CASE_RETURN_STRING(WNI_CFG_INFRA_STA_KEEP_ALIVE_PERIOD);
	CASE_RETURN_STRING(WNI_CFG_ASSOC_STA_LIMIT);
	CASE_RETURN_STRING(WNI_CFG_ENABLE_LTE_COEX);
	CASE_RETURN_STRING(WNI_CFG_AP_KEEP_ALIVE_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_GO_KEEP_ALIVE_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_ENABLE_MC_ADDR_LIST);
	CASE_RETURN_STRING(WNI_CFG_ENABLE_MCC_ADAPTIVE_SCHED);
	CASE_RETURN_STRING(WNI_CFG_DISABLE_LDPC_WITH_TXBF_AP);
	CASE_RETURN_STRING(WNI_CFG_AP_LINK_MONITOR_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_TDLS_QOS_WMM_UAPSD_MASK);
	CASE_RETURN_STRING(WNI_CFG_TDLS_BUF_STA_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_TDLS_PUAPSD_INACT_TIME);
	CASE_RETURN_STRING(WNI_CFG_TDLS_RX_FRAME_THRESHOLD);
	CASE_RETURN_STRING(WNI_CFG_PMF_SA_QUERY_MAX_RETRIES);
	CASE_RETURN_STRING(WNI_CFG_PMF_SA_QUERY_RETRY_INTERVAL);
	CASE_RETURN_STRING(WNI_CFG_GO_LINK_MONITOR_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_RMC_ACTION_PERIOD_FREQUENCY);
	CASE_RETURN_STRING(WNI_CFG_CURRENT_RSSI);
	CASE_RETURN_STRING(WNI_CFG_RTT3_ENABLE);
	CASE_RETURN_STRING(WNI_CFG_DEBUG_P2P_REMAIN_ON_CHANNEL);
	CASE_RETURN_STRING(WNI_CFG_TDLS_OFF_CHANNEL_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_IBSS_ATIM_WIN_SIZE);
	CASE_RETURN_STRING(WNI_CFG_DFS_MASTER_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_VHT_ENABLE_TXBF_20MHZ);
	CASE_RETURN_STRING(WNI_CFG_TDLS_WMM_MODE_ENABLED);
	CASE_RETURN_STRING(WNI_CFG_OBSS_HT40_SCAN_PASSIVE_DWELL_TIME);
	CASE_RETURN_STRING(WNI_CFG_OBSS_HT40_SCAN_ACTIVE_DWELL_TIME);
	CASE_RETURN_STRING(WNI_CFG_OBSS_HT40_SCAN_WIDTH_TRIGGER_INTERVAL);
	CASE_RETURN_STRING(WNI_CFG_OBSS_HT40_SCAN_PASSIVE_TOTAL_PER_CHANNEL);
	CASE_RETURN_STRING(WNI_CFG_OBSS_HT40_SCAN_ACTIVE_TOTAL_PER_CHANNEL);
	CASE_RETURN_STRING(WNI_CFG_OBSS_HT40_WIDTH_CH_TRANSITION_DELAY);
	CASE_RETURN_STRING(WNI_CFG_OBSS_HT40_SCAN_ACTIVITY_THRESHOLD);
	CASE_RETURN_STRING(WNI_CFG_TGT_GTX_USR_CFG);
	CASE_RETURN_STRING(WNI_CFG_MAX_HT_MCS_TX_DATA);
	CASE_RETURN_STRING(WNI_CFG_DISABLE_ABG_RATE_FOR_TX_DATA);
	CASE_RETURN_STRING(WNI_CFG_RATE_FOR_TX_MGMT);
	CASE_RETURN_STRING(WNI_CFG_HE_CONTROL);
	CASE_RETURN_STRING(WNI_CFG_HE_TWT_REQUESTOR);
	CASE_RETURN_STRING(WNI_CFG_HE_TWT_RESPONDER);
	CASE_RETURN_STRING(WNI_CFG_HE_FRAGMENTATION);
	CASE_RETURN_STRING(WNI_CFG_HE_MAX_FRAG_MSDU);
	CASE_RETURN_STRING(WNI_CFG_HE_MIN_FRAG_SIZE);
	CASE_RETURN_STRING(WNI_CFG_HE_TRIG_PAD);
	CASE_RETURN_STRING(WNI_CFG_HE_MTID_AGGR);
	CASE_RETURN_STRING(WNI_CFG_HE_LINK_ADAPTATION);
	CASE_RETURN_STRING(WNI_CFG_HE_ALL_ACK);
	CASE_RETURN_STRING(WNI_CFG_HE_UL_MU_RSP_SCHEDULING);
	CASE_RETURN_STRING(WNI_CFG_HE_BUFFER_STATUS_RPT);
	CASE_RETURN_STRING(WNI_CFG_HE_BCAST_TWT);
	CASE_RETURN_STRING(WNI_CFG_HE_BA_32BIT);
	CASE_RETURN_STRING(WNI_CFG_HE_MU_CASCADING);
	CASE_RETURN_STRING(WNI_CFG_HE_MULTI_TID);
	CASE_RETURN_STRING(WNI_CFG_HE_DL_MU_BA);
	CASE_RETURN_STRING(WNI_CFG_HE_OMI);
	CASE_RETURN_STRING(WNI_CFG_HE_OFDMA_RA);
	CASE_RETURN_STRING(WNI_CFG_HE_MAX_AMPDU_LEN);
	CASE_RETURN_STRING(WNI_CFG_HE_AMSDU_FRAG);
	CASE_RETURN_STRING(WNI_CFG_HE_FLEX_TWT_SCHED);
	CASE_RETURN_STRING(WNI_CFG_HE_RX_CTRL);
	CASE_RETURN_STRING(WNI_CFG_HE_BSRP_AMPDU_AGGR);
	CASE_RETURN_STRING(WNI_CFG_HE_QTP);
	CASE_RETURN_STRING(WNI_CFG_HE_A_BQR);
	CASE_RETURN_STRING(WNI_CFG_HE_SR_RESPONDER);
	CASE_RETURN_STRING(WNI_CFG_HE_NDP_FEEDBACK_SUPP);
	CASE_RETURN_STRING(WNI_CFG_HE_OPS_SUPP);
	CASE_RETURN_STRING(WNI_CFG_HE_DUAL_BAND);
	CASE_RETURN_STRING(WNI_CFG_HE_CHAN_WIDTH);
	CASE_RETURN_STRING(WNI_CFG_HE_RX_PREAM_PUNC);
	CASE_RETURN_STRING(WNI_CFG_HE_CLASS_OF_DEVICE);
	CASE_RETURN_STRING(WNI_CFG_HE_LDPC);
	CASE_RETURN_STRING(WNI_CFG_HE_LTF_PPDU);
	CASE_RETURN_STRING(WNI_CFG_HE_LTF_NDP);
	CASE_RETURN_STRING(WNI_CFG_HE_TX_STBC_LT80);
	CASE_RETURN_STRING(WNI_CFG_HE_RX_STBC_LT80);
	CASE_RETURN_STRING(WNI_CFG_HE_DOPPLER);
	CASE_RETURN_STRING(WNI_CFG_HE_UL_MUMIMO);
	CASE_RETURN_STRING(WNI_CFG_HE_DCM_TX);
	CASE_RETURN_STRING(WNI_CFG_HE_DCM_RX);
	CASE_RETURN_STRING(WNI_CFG_HE_MU_PPDU);
	CASE_RETURN_STRING(WNI_CFG_HE_SU_BEAMFORMER);
	CASE_RETURN_STRING(WNI_CFG_HE_SU_BEAMFORMEE);
	CASE_RETURN_STRING(WNI_CFG_HE_MU_BEAMFORMER);
	CASE_RETURN_STRING(WNI_CFG_HE_BFEE_STS_LT80);
	CASE_RETURN_STRING(WNI_CFG_HE_BFEE_STS_GT80);
	CASE_RETURN_STRING(WNI_CFG_HE_NUM_SOUND_LT80);
	CASE_RETURN_STRING(WNI_CFG_HE_NUM_SOUND_GT80);
	CASE_RETURN_STRING(WNI_CFG_HE_SU_FEED_TONE16);
	CASE_RETURN_STRING(WNI_CFG_HE_MU_FEED_TONE16);
	CASE_RETURN_STRING(WNI_CFG_HE_CODEBOOK_SU);
	CASE_RETURN_STRING(WNI_CFG_HE_CODEBOOK_MU);
	CASE_RETURN_STRING(WNI_CFG_HE_BFRM_FEED);
	CASE_RETURN_STRING(WNI_CFG_HE_ER_SU_PPDU);
	CASE_RETURN_STRING(WNI_CFG_HE_DL_PART_BW);
	CASE_RETURN_STRING(WNI_CFG_HE_PPET_PRESENT);
	CASE_RETURN_STRING(WNI_CFG_HE_SRP);
	CASE_RETURN_STRING(WNI_CFG_HE_POWER_BOOST);
	CASE_RETURN_STRING(WNI_CFG_HE_4x_LTF_GI);
	CASE_RETURN_STRING(WNI_CFG_HE_MAX_NC);
	CASE_RETURN_STRING(WNI_CFG_HE_TX_STBC_GT80);
	CASE_RETURN_STRING(WNI_CFG_HE_RX_STBC_GT80);
	CASE_RETURN_STRING(WNI_CFG_HE_ER_4x_LTF_GI);
	CASE_RETURN_STRING(WNI_CFG_HE_RX_MCS_MAP_LT_80);
	CASE_RETURN_STRING(WNI_CFG_HE_TX_MCS_MAP_LT_80);
	CASE_RETURN_STRING(WNI_CFG_HE_RX_MCS_MAP_160);
	CASE_RETURN_STRING(WNI_CFG_HE_TX_MCS_MAP_160);
	CASE_RETURN_STRING(WNI_CFG_HE_RX_MCS_MAP_80_80);
	CASE_RETURN_STRING(WNI_CFG_HE_TX_MCS_MAP_80_80);
	CASE_RETURN_STRING(WNI_CFG_HE_PPET_2G);
	CASE_RETURN_STRING(WNI_CFG_HE_PPET_5G);
	CASE_RETURN_STRING(WNI_CFG_HE_OPS_BSS_COLOR);
	CASE_RETURN_STRING(WNI_CFG_HE_OPS_DEFAULT_PE);
	CASE_RETURN_STRING(WNI_CFG_HE_OPS_TWT_REQUIRED);
	CASE_RETURN_STRING(WNI_CFG_HE_OPS_RTS_THRESHOLD);
	CASE_RETURN_STRING(WNI_CFG_HE_OPS_PARTIAL_BSS_COL);
	CASE_RETURN_STRING(WNI_CFG_HE_OPS_VHT_OPER_PRESENT);
	CASE_RETURN_STRING(WNI_CFG_HE_OPS_MBSSID_AP);
	CASE_RETURN_STRING(WNI_CFG_HE_OPS_TX_BSSID_IND);
	CASE_RETURN_STRING(WNI_CFG_HE_OPS_BSS_COL_DISABLED);
	CASE_RETURN_STRING(WNI_CFG_HE_OPS_BASIC_MCS_NSS);
	CASE_RETURN_STRING(WNI_CFG_PS_WOW_DATA_INACTIVITY_TIMEOUT);
	CASE_RETURN_STRING(WNI_CFG_HE_STA_OBSSPD);
	CASE_RETURN_STRING(WNI_CFG_SAP_MAX_MCS_DATA);
	CASE_RETURN_STRING(WNI_CFG_RATE_FOR_TX_MGMT_2G);
	CASE_RETURN_STRING(WNI_CFG_RATE_FOR_TX_MGMT_5G);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ETSI_ACBK_LOCAL);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ETSI_ACBE_LOCAL);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ETSI_ACVI_LOCAL);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ETSI_ACVO_LOCAL);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ETSI_ACBK);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ETSI_ACBE);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ETSI_ACVI);
	CASE_RETURN_STRING(WNI_CFG_EDCA_ETSI_ACVO);
	CASE_RETURN_STRING(WNI_CFG_OBSS_DETECTION_OFFLOAD);
	CASE_RETURN_STRING(WNI_CFG_OBSS_COLOR_COLLISION_OFFLOAD);
	CASE_RETURN_STRING(WNI_CFG_TWT_REQUESTOR);
	CASE_RETURN_STRING(WNI_CFG_TWT_RESPONDER);
	CASE_RETURN_STRING(WNI_CFG_BCAST_TWT);
	}

	return "invalid";
}
