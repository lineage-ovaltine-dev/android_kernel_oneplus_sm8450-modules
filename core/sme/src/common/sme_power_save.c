/*
 * Copyright (c) 2015-2018 The Linux Foundation. All rights reserved.
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

#include "sme_power_save.h"
#include "sme_power_save_api.h"
#include <sir_common.h>
#include <ani_global.h>
#include <utils_api.h>
#include "sme_trace.h"
#include "qdf_mem.h"
#include "qdf_types.h"
#include "wma.h"
#include "wma_internal.h"
#include "wmm_apsd.h"
#include "cfg_api.h"
#include "csr_inside_api.h"

/**
 * sme_post_ps_msg_to_wma(): post message to WMA.
 * @type: type
 * @body: body pointer
 *
 * Return: QDF_STATUS
 */
static QDF_STATUS sme_post_ps_msg_to_wma(uint16_t type, void *body)
{
	struct scheduler_msg msg = {0};

	msg.type = type;
	msg.reserved = 0;
	msg.bodyptr = body;
	msg.bodyval = 0;

	if (QDF_STATUS_SUCCESS != scheduler_post_msg(
				QDF_MODULE_ID_WMA, &msg)) {
		QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_ERROR,
				"%s: Posting message %d failed",
				__func__, type);
		qdf_mem_free(body);
		return QDF_STATUS_E_FAILURE;
	}
	return QDF_STATUS_SUCCESS;
}

/**
 * sme_ps_enable_uapsd_req_params(): enables UASPD req params
 * @mac_ctx: global mac context
 * @session_id: session id
 *
 * Return: QDF_STATUS
 */
static void sme_ps_fill_uapsd_req_params(tpAniSirGlobal mac_ctx,
		tUapsd_Params *uapsdParams, uint32_t session_id,
		enum ps_state *ps_state)
{

	uint8_t uapsd_delivery_mask = 0;
	uint8_t uapsd_trigger_mask = 0;
	struct ps_global_info *ps_global_info = &mac_ctx->sme.ps_global_info;
	struct ps_params *ps_param = &ps_global_info->ps_params[session_id];

	uapsd_delivery_mask =
		ps_param->uapsd_per_ac_bit_mask |
		ps_param->uapsd_per_ac_delivery_enable_mask;

	uapsd_trigger_mask =
		ps_param->uapsd_per_ac_bit_mask |
		ps_param->uapsd_per_ac_trigger_enable_mask;

	uapsdParams->bkDeliveryEnabled =
		LIM_UAPSD_GET(ACBK, uapsd_delivery_mask);

	uapsdParams->beDeliveryEnabled =
		LIM_UAPSD_GET(ACBE, uapsd_delivery_mask);

	uapsdParams->viDeliveryEnabled =
		LIM_UAPSD_GET(ACVI, uapsd_delivery_mask);

	uapsdParams->voDeliveryEnabled =
		LIM_UAPSD_GET(ACVO, uapsd_delivery_mask);

	uapsdParams->bkTriggerEnabled =
		LIM_UAPSD_GET(ACBK, uapsd_trigger_mask);

	uapsdParams->beTriggerEnabled =
		LIM_UAPSD_GET(ACBE, uapsd_trigger_mask);

	uapsdParams->viTriggerEnabled =
		LIM_UAPSD_GET(ACVI, uapsd_trigger_mask);

	uapsdParams->voTriggerEnabled =
		LIM_UAPSD_GET(ACVO, uapsd_trigger_mask);
	if (ps_param->ps_state != FULL_POWER_MODE) {
		uapsdParams->enable_ps = true;
		*ps_state = UAPSD_MODE;
	} else {
		uapsdParams->enable_ps = false;
		*ps_state = FULL_POWER_MODE;
	}
}

static void sme_set_ps_state(tpAniSirGlobal mac_ctx,
		uint32_t session_id, enum ps_state ps_state)
{
	struct ps_global_info *ps_global_info = &mac_ctx->sme.ps_global_info;
	struct ps_params *ps_param = &ps_global_info->ps_params[session_id];

	ps_param->ps_state = ps_state;
}

static void sme_get_ps_state(tpAniSirGlobal mac_ctx,
		uint32_t session_id, enum ps_state *ps_state)
{
	struct ps_global_info *ps_global_info = &mac_ctx->sme.ps_global_info;
	struct ps_params *ps_param = &ps_global_info->ps_params[session_id];
	*ps_state = ps_param->ps_state;
}
/**
 * sme_ps_enable_ps_req_params(): enables power save req params
 * @mac_ctx: global mac context
 * @session_id: session id
 *
 * Return: QDF_STATUS
 */
static QDF_STATUS sme_ps_enable_ps_req_params(tpAniSirGlobal mac_ctx,
		uint32_t session_id)
{
	struct sEnablePsParams *enable_ps_req_params;
	QDF_STATUS status = QDF_STATUS_SUCCESS;
	struct ps_global_info *ps_global_info = &mac_ctx->sme.ps_global_info;
	struct ps_params *ps_param = &ps_global_info->ps_params[session_id];
	enum ps_state ps_state;

	enable_ps_req_params =  qdf_mem_malloc(sizeof(*enable_ps_req_params));
	if (NULL == enable_ps_req_params) {
		sme_err("Memory allocation failed for enable_ps_req_params");
		return QDF_STATUS_E_NOMEM;
	}
	if (ps_param->uapsd_per_ac_bit_mask) {
		enable_ps_req_params->psSetting = eSIR_ADDON_ENABLE_UAPSD;
		sme_ps_fill_uapsd_req_params(mac_ctx,
				&enable_ps_req_params->uapsdParams,
				session_id, &ps_state);
		ps_state = UAPSD_MODE;
		enable_ps_req_params->uapsdParams.enable_ps = true;
	} else {
		enable_ps_req_params->psSetting = eSIR_ADDON_NOTHING;
		ps_state = LEGACY_POWER_SAVE_MODE;
	}
	enable_ps_req_params->sessionid = session_id;

	status = sme_post_ps_msg_to_wma(WMA_ENTER_PS_REQ, enable_ps_req_params);
	if (!QDF_IS_STATUS_SUCCESS(status))
		return QDF_STATUS_E_FAILURE;
	QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_DEBUG,
		FL("Message WMA_ENTER_PS_REQ Successfully sent to WMA"));
	ps_param->ps_state = ps_state;
	return QDF_STATUS_SUCCESS;
}

/**
 * sme_ps_disable_ps_req_params(): Disable power save req params
 * @mac_ctx: global mac context
 * @session_id: session id
 *
 * Return: QDF_STATUS
 */
static QDF_STATUS sme_ps_disable_ps_req_params(tpAniSirGlobal mac_ctx,
		uint32_t session_id)
{
	struct  sDisablePsParams *disable_ps_req_params;
	QDF_STATUS status = QDF_STATUS_SUCCESS;

	disable_ps_req_params = qdf_mem_malloc(sizeof(*disable_ps_req_params));
	if (NULL == disable_ps_req_params) {
		sme_err("Memory allocation failed for sDisablePsParams");
		return QDF_STATUS_E_NOMEM;
	}

	disable_ps_req_params->psSetting = eSIR_ADDON_NOTHING;
	disable_ps_req_params->sessionid = session_id;

	status = sme_post_ps_msg_to_wma(WMA_EXIT_PS_REQ, disable_ps_req_params);
	if (!QDF_IS_STATUS_SUCCESS(status))
		return QDF_STATUS_E_FAILURE;
	QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_DEBUG,
			FL("Message WMA_EXIT_PS_REQ Successfully sent to WMA"));
	sme_set_ps_state(mac_ctx, session_id, FULL_POWER_MODE);
	return QDF_STATUS_SUCCESS;
}

/**
 * sme_ps_enable_uapsd_req_params(): enables UASPD req params
 * @mac_ctx: global mac context
 * @session_id: session id
 *
 * Return: QDF_STATUS
 */
static QDF_STATUS sme_ps_enable_uapsd_req_params(tpAniSirGlobal mac_ctx,
		uint32_t session_id)
{

	struct sEnableUapsdParams *enable_uapsd_req_params;
	QDF_STATUS status = QDF_STATUS_SUCCESS;
	enum ps_state ps_state;

	enable_uapsd_req_params =
		qdf_mem_malloc(sizeof(*enable_uapsd_req_params));
	if (NULL == enable_uapsd_req_params) {
		sme_err("Memory allocation failed for enable_uapsd_req_params");
		return QDF_STATUS_E_NOMEM;
	}

	sme_ps_fill_uapsd_req_params(mac_ctx,
			&enable_uapsd_req_params->uapsdParams,
			session_id, &ps_state);
	enable_uapsd_req_params->sessionid = session_id;

	status = sme_post_ps_msg_to_wma(WMA_ENABLE_UAPSD_REQ,
					enable_uapsd_req_params);
	if (!QDF_IS_STATUS_SUCCESS(status))
		return QDF_STATUS_E_FAILURE;

	QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_DEBUG,
		    FL("Msg WMA_ENABLE_UAPSD_REQ Successfully sent to WMA"));
	sme_set_ps_state(mac_ctx, session_id, ps_state);
	return QDF_STATUS_SUCCESS;
}

/**
 * sme_ps_disable_uapsd_req_params(): disables UASPD req params
 * @mac_ctx: global mac context
 * @session_id: session id
 *
 * Return: QDF_STATUS
 */
static QDF_STATUS sme_ps_disable_uapsd_req_params(tpAniSirGlobal mac_ctx,
		uint32_t session_id)
{
	struct sDisableUapsdParams *disable_uapsd_req_params;
	QDF_STATUS status = QDF_STATUS_SUCCESS;
	enum ps_state ps_state;

	sme_get_ps_state(mac_ctx, session_id, &ps_state);
	if (ps_state != UAPSD_MODE) {
		sme_err("UAPSD is already disabled");
		return QDF_STATUS_SUCCESS;
	}
	disable_uapsd_req_params =
		qdf_mem_malloc(sizeof(*disable_uapsd_req_params));
	if (NULL == disable_uapsd_req_params) {
		sme_err("Mem alloc failed for disable_uapsd_req_params");
		return QDF_STATUS_E_NOMEM;
	}

	disable_uapsd_req_params->sessionid = session_id;
	status = sme_post_ps_msg_to_wma(WMA_DISABLE_UAPSD_REQ,
					disable_uapsd_req_params);
	if (!QDF_IS_STATUS_SUCCESS(status))
		return QDF_STATUS_E_FAILURE;

	QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_DEBUG,
		FL("Message WMA_DISABLE_UAPSD_REQ Successfully sent to WMA"));
	sme_set_ps_state(mac_ctx, session_id, LEGACY_POWER_SAVE_MODE);
	return QDF_STATUS_SUCCESS;
}

/**
 * sme_ps_process_command(): Sme process power save messages
 *			and pass messages to WMA.
 * @mac_ctx: global mac context
 * @session_id: session id
 * sme_ps_cmd: power save message
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_ps_process_command(tpAniSirGlobal mac_ctx, uint32_t session_id,
		enum sme_ps_cmd command)
{
	QDF_STATUS status = QDF_STATUS_SUCCESS;

	if (!CSR_IS_SESSION_VALID(mac_ctx, session_id)) {
		sme_err("Invalid Session_id: %d", session_id);
		return QDF_STATUS_E_INVAL;
	}
	QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_DEBUG,
			FL("Power Save command %d"), command);
	switch (command) {
	case SME_PS_ENABLE:
		status = sme_ps_enable_ps_req_params(mac_ctx, session_id);
		break;
	case SME_PS_DISABLE:
		status = sme_ps_disable_ps_req_params(mac_ctx, session_id);
		break;
	case SME_PS_UAPSD_ENABLE:
		status = sme_ps_enable_uapsd_req_params(mac_ctx, session_id);
		break;
	case SME_PS_UAPSD_DISABLE:
		status = sme_ps_disable_uapsd_req_params(mac_ctx, session_id);
		break;
	default:
		sme_err("Invalid command type: %d", command);
		status = QDF_STATUS_E_FAILURE;
		break;
	}
	if (status != QDF_STATUS_SUCCESS) {
		QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_ERROR,
			FL("Not able to enter in PS, Command: %d"), command);
	}
	return status;
}

/**
 * sme_enable_sta_ps_check(): Checks if it is ok to enable power save or not.
 * @mac_ctx: global mac context
 * @session_id: session id
 * @command: power save cmd of type enum sme_ps_cmd
 *
 *Pre Condition for enabling sta mode power save
 *1) Sta Mode Ps should be enabled in ini file.
 *2) Session should be in infra mode and in connected state.
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_enable_sta_ps_check(tpAniSirGlobal mac_ctx, uint32_t session_id)
{
	struct ps_global_info *ps_global_info = &mac_ctx->sme.ps_global_info;

	QDF_BUG(session_id < CSR_ROAM_SESSION_MAX);
	if (session_id >= CSR_ROAM_SESSION_MAX)
		return QDF_STATUS_E_INVAL;

	/* Check if Sta Ps is enabled. */
	if (!ps_global_info->ps_enabled) {
		sme_debug("Cannot initiate PS. PS is disabled in ini");
		return QDF_STATUS_E_FAILURE;
	}

	/* Check whether the given session is Infra and in Connected State
	 * also if command is power save disable  there is not need to check
	 * for connected state as firmware can handle this
	 */
	if (!csr_is_conn_state_connected_infra(mac_ctx, session_id)) {
		sme_debug("STA not infra/connected state Session_id: %d",
			  session_id);
		return QDF_STATUS_E_FAILURE;
	}

	return QDF_STATUS_SUCCESS;
}

/**
 * sme_ps_enable_disable(): function to enable/disable PS.
 * @hal_ctx: global hal_handle
 * @session_id: session id
 * sme_ps_cmd: power save message
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_ps_enable_disable(tHalHandle hal_ctx, uint32_t session_id,
		enum sme_ps_cmd command)
{
	QDF_STATUS status = QDF_STATUS_E_FAILURE;
	tpAniSirGlobal mac_ctx = PMAC_STRUCT(hal_ctx);

	status =  sme_enable_sta_ps_check(mac_ctx, session_id);
	if (status != QDF_STATUS_SUCCESS)
		return status;
	status = sme_ps_process_command(mac_ctx, session_id, command);
	return status;
}

QDF_STATUS sme_ps_timer_flush_sync(tHalHandle hal, uint8_t session_id)
{
	QDF_STATUS status;
	tpAniSirGlobal mac_ctx = PMAC_STRUCT(hal);
	struct ps_params *ps_parm;
	enum ps_state ps_state;
	QDF_TIMER_STATE tstate;
	struct sEnablePsParams *req;
	t_wma_handle *wma;

	QDF_BUG(session_id < CSR_ROAM_SESSION_MAX);
	if (session_id >= CSR_ROAM_SESSION_MAX)
		return QDF_STATUS_E_INVAL;

	status = sme_enable_sta_ps_check(mac_ctx, session_id);
	if (QDF_IS_STATUS_ERROR(status)) {
		sme_debug("Power save not allowed for vdev id %d", session_id);
		return QDF_STATUS_SUCCESS;
	}

	ps_parm = &mac_ctx->sme.ps_global_info.ps_params[session_id];
	tstate = qdf_mc_timer_get_current_state(&ps_parm->auto_ps_enable_timer);
	if (tstate != QDF_TIMER_STATE_RUNNING)
		return QDF_STATUS_SUCCESS;

	sme_debug("flushing powersave enable for vdev %u", session_id);

	qdf_mc_timer_stop(&ps_parm->auto_ps_enable_timer);

	wma = cds_get_context(QDF_MODULE_ID_WMA);
	if (!wma) {
		sme_err("wma is null");
		return QDF_STATUS_E_INVAL;
	}

	req = qdf_mem_malloc(sizeof(*req));
	if (!req) {
		sme_err("out of memory");
		return QDF_STATUS_E_NOMEM;
	}

	if (ps_parm->uapsd_per_ac_bit_mask) {
		req->psSetting = eSIR_ADDON_ENABLE_UAPSD;
		sme_ps_fill_uapsd_req_params(mac_ctx, &req->uapsdParams,
					     session_id, &ps_state);
		ps_state = UAPSD_MODE;
		req->uapsdParams.enable_ps = true;
	} else {
		req->psSetting = eSIR_ADDON_NOTHING;
		ps_state = LEGACY_POWER_SAVE_MODE;
	}
	req->sessionid = session_id;

	wma_enable_sta_ps_mode(wma, req);
	qdf_mem_free(req);

	ps_parm->ps_state = ps_state;

	return QDF_STATUS_SUCCESS;
}

/**
 * sme_ps_uapsd_enable(): function to enable UAPSD.
 * @hal_ctx: global hal_handle
 * @session_id: session id
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_ps_uapsd_enable(tHalHandle hal_ctx, uint32_t session_id)
{

	QDF_STATUS status = QDF_STATUS_E_FAILURE;
	tpAniSirGlobal mac_ctx = PMAC_STRUCT(hal_ctx);

	status =  sme_enable_sta_ps_check(mac_ctx, session_id);
	if (status != QDF_STATUS_SUCCESS)
		return status;
	status = sme_ps_process_command(mac_ctx, session_id,
			SME_PS_UAPSD_ENABLE);
	if (status == QDF_STATUS_SUCCESS)
		sme_offload_qos_process_into_uapsd_mode(mac_ctx, session_id);

	return status;
}

/**
 * sme_ps_uapsd_disable(): function to disable UAPSD.
 * @hal_ctx: global hal_handle
 * @session_id: session id
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_ps_uapsd_disable(tHalHandle hal_ctx, uint32_t session_id)
{

	QDF_STATUS status = QDF_STATUS_E_FAILURE;
	tpAniSirGlobal mac_ctx = PMAC_STRUCT(hal_ctx);

	status = sme_enable_sta_ps_check(mac_ctx, session_id);
	if (status != QDF_STATUS_SUCCESS)
		return status;
	status = sme_ps_process_command(mac_ctx, session_id,
			SME_PS_UAPSD_DISABLE);
	if (status == QDF_STATUS_SUCCESS)
		sme_offload_qos_process_out_of_uapsd_mode(mac_ctx, session_id);

	return status;
}

/**
 * sme_set_tspec_uapsd_mask_per_session(): set tspec UAPSD mask per session
 * @mac_ctx: global mac context
 * @ts_info: tspec info.
 * @session_id: session id
 *
 * Return: QDF_STATUS
 */
void sme_set_tspec_uapsd_mask_per_session(tpAniSirGlobal mac_ctx,
		tSirMacTSInfo *ts_info,
		uint8_t session_id)
{
	uint8_t user_prio = (uint8_t) ts_info->traffic.userPrio;
	uint16_t direction = ts_info->traffic.direction;
	uint8_t ac = upToAc(user_prio);
	struct ps_global_info *ps_global_info = &mac_ctx->sme.ps_global_info;
	struct ps_params *ps_param = &ps_global_info->ps_params[session_id];

	sme_err("Set UAPSD mask for AC: %d dir: %d action: %d",
		ac, direction, ts_info->traffic.psb);

	/* Converting AC to appropriate Uapsd Bit Mask
	 * AC_BE(0) --> UAPSD_BITOFFSET_ACVO(3)
	 * AC_BK(1) --> UAPSD_BITOFFSET_ACVO(2)
	 * AC_VI(2) --> UAPSD_BITOFFSET_ACVO(1)
	 * AC_VO(3) --> UAPSD_BITOFFSET_ACVO(0)
	 */
	ac = ((~ac) & 0x3);
	if (ts_info->traffic.psb) {
		ps_param->uapsd_per_ac_bit_mask |= (1 << ac);
		if (direction == SIR_MAC_DIRECTION_UPLINK)
			ps_param->uapsd_per_ac_trigger_enable_mask |=
				(1 << ac);
		else if (direction == SIR_MAC_DIRECTION_DNLINK)
			ps_param->uapsd_per_ac_delivery_enable_mask |=
				(1 << ac);
		else if (direction == SIR_MAC_DIRECTION_BIDIR) {
			ps_param->uapsd_per_ac_trigger_enable_mask |=
				(1 << ac);
			ps_param->uapsd_per_ac_delivery_enable_mask |=
				(1 << ac);
		}
	} else {
		ps_param->uapsd_per_ac_bit_mask &= ~(1 << ac);
		if (direction == SIR_MAC_DIRECTION_UPLINK)
			ps_param->uapsd_per_ac_trigger_enable_mask &=
				~(1 << ac);
		else if (direction == SIR_MAC_DIRECTION_DNLINK)
			ps_param->uapsd_per_ac_delivery_enable_mask &=
				~(1 << ac);
		else if (direction == SIR_MAC_DIRECTION_BIDIR) {
			ps_param->uapsd_per_ac_trigger_enable_mask &=
				~(1 << ac);
			ps_param->uapsd_per_ac_delivery_enable_mask &=
				~(1 << ac);
		}
	}

	/*
	 * ADDTS success, so AC is now admitted. We shall now use the default
	 * EDCA parameters as advertised by AP and send the updated EDCA params
	 * to HAL.
	 */
	if (direction == SIR_MAC_DIRECTION_UPLINK) {
		ps_param->ac_admit_mask[SIR_MAC_DIRECTION_UPLINK] |=
			(1 << ac);
	} else if (direction == SIR_MAC_DIRECTION_DNLINK) {
		ps_param->ac_admit_mask[SIR_MAC_DIRECTION_DNLINK] |=
			(1 << ac);
	} else if (direction == SIR_MAC_DIRECTION_BIDIR) {
		ps_param->ac_admit_mask[SIR_MAC_DIRECTION_UPLINK] |=
			(1 << ac);
		ps_param->ac_admit_mask[SIR_MAC_DIRECTION_DNLINK] |=
			(1 << ac);
	}

	sme_debug("New ps_param->uapsd_per_ac_trigger_enable_mask: 0x%x",
		ps_param->uapsd_per_ac_trigger_enable_mask);
	sme_debug("New  ps_param->uapsd_per_ac_delivery_enable_mask: 0x%x",
		ps_param->uapsd_per_ac_delivery_enable_mask);
	sme_debug("New ps_param->ac_admit_mask[SIR_MAC_DIRECTION_UPLINK]: 0x%x",
		ps_param->ac_admit_mask[SIR_MAC_DIRECTION_UPLINK]);
}

/**
 * sme_ps_start_uapsd(): function to start UAPSD.
 * @hal_ctx: global hal_handle
 * @session_id: session id
 *
 * Return: QDF_STATUS
 */
QDF_STATUS sme_ps_start_uapsd(tHalHandle hal_ctx, uint32_t session_id)
{
	QDF_STATUS status = QDF_STATUS_E_FAILURE;

	status = sme_ps_uapsd_enable(hal_ctx, session_id);
	return status;
}

/**
 * sme_set_ps_host_offload(): Set the host offload feature.
 * @hal_ctx - The handle returned by mac_open.
 * @request - Pointer to the offload request.
 *
 * Return QDF_STATUS
 *            QDF_STATUS_E_FAILURE  Cannot set the offload.
 *            QDF_STATUS_SUCCESS  Request accepted.
 */
QDF_STATUS sme_set_ps_host_offload(tHalHandle hal_ctx,
		tpSirHostOffloadReq request,
		uint8_t session_id)
{
	tpSirHostOffloadReq request_buf;
	struct scheduler_msg msg = {0};
	tpAniSirGlobal mac_ctx = PMAC_STRUCT(hal_ctx);
	struct csr_roam_session *session = CSR_GET_SESSION(mac_ctx, session_id);

	QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_DEBUG,
			"%s: IP address = %d.%d.%d.%d", __func__,
			request->params.hostIpv4Addr[0],
			request->params.hostIpv4Addr[1],
			request->params.hostIpv4Addr[2],
			request->params.hostIpv4Addr[3]);

	if (NULL == session) {
		QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_ERROR,
				"%s: SESSION not Found", __func__);
		return QDF_STATUS_E_FAILURE;
	}

	request_buf = qdf_mem_malloc(sizeof(tSirHostOffloadReq));
	if (NULL == request_buf) {
		QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_ERROR,
		   FL("Not able to allocate memory for host offload request"));
		return QDF_STATUS_E_NOMEM;
	}

	qdf_copy_macaddr(&request->bssid, &session->connectedProfile.bssid);

	qdf_mem_copy(request_buf, request, sizeof(tSirHostOffloadReq));

	msg.type = WMA_SET_HOST_OFFLOAD;
	msg.reserved = 0;
	msg.bodyptr = request_buf;
	MTRACE(qdf_trace(QDF_MODULE_ID_SME, TRACE_CODE_SME_TX_WMA_MSG,
			 session_id, msg.type));
	if (QDF_STATUS_SUCCESS !=
			scheduler_post_msg(QDF_MODULE_ID_WMA, &msg)) {
		QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_ERROR,
		      FL("Not able to post WMA_SET_HOST_OFFLOAD msg to WMA"));
		qdf_mem_free(request_buf);
		return QDF_STATUS_E_FAILURE;
	}

	return QDF_STATUS_SUCCESS;
}

#ifdef WLAN_NS_OFFLOAD
/**
 * sme_set_ps_ns_offload(): Set the host offload feature.
 * @hal_ctx - The handle returned by mac_open.
 * @request - Pointer to the offload request.
 *
 * Return QDF_STATUS
 *		QDF_STATUS_E_FAILURE  Cannot set the offload.
 *		QDF_STATUS_SUCCESS  Request accepted.
 */
QDF_STATUS sme_set_ps_ns_offload(tHalHandle hal_ctx,
		tpSirHostOffloadReq request,
		uint8_t session_id)
{
	tpAniSirGlobal mac_ctx = PMAC_STRUCT(hal_ctx);
	tpSirHostOffloadReq request_buf;
	struct scheduler_msg msg = {0};
	struct csr_roam_session *session = CSR_GET_SESSION(mac_ctx, session_id);

	if (NULL == session) {
		sme_err("Session not found");
		return QDF_STATUS_E_FAILURE;
	}

	qdf_copy_macaddr(&request->bssid, &session->connectedProfile.bssid);

	request_buf = qdf_mem_malloc(sizeof(*request_buf));
	if (NULL == request_buf) {
		QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_ERROR,
			"Not able to allocate memory for NS offload request");
		return QDF_STATUS_E_NOMEM;
	}
	*request_buf = *request;

	msg.type = WMA_SET_NS_OFFLOAD;
	msg.reserved = 0;
	msg.bodyptr = request_buf;
	MTRACE(qdf_trace(QDF_MODULE_ID_SME, TRACE_CODE_SME_TX_WMA_MSG,
			 session_id, msg.type));
	if (QDF_STATUS_SUCCESS !=
			scheduler_post_msg(QDF_MODULE_ID_WMA, &msg)) {
		QDF_TRACE(QDF_MODULE_ID_SME, QDF_TRACE_LEVEL_ERROR,
			"Not able to post SIR_HAL_SET_HOST_OFFLOAD message to HAL");
		qdf_mem_free(request_buf);
		return QDF_STATUS_E_FAILURE;
	}

	return QDF_STATUS_SUCCESS;
}

#endif /* WLAN_NS_OFFLOAD */
/**
 * sme_post_pe_message
 *
 * FUNCTION:
 * Post a message to the pmm message queue
 *
 * LOGIC:
 *
 * ASSUMPTIONS:
 *
 * NOTE:
 *
 * @param msg pointer to message
 * @return None
 */

QDF_STATUS sme_post_pe_message(tpAniSirGlobal mac_ctx,
			       struct scheduler_msg *msg)
{
	QDF_STATUS qdf_status;

	qdf_status = scheduler_post_msg(QDF_MODULE_ID_PE,
					 msg);
	if (!QDF_IS_STATUS_SUCCESS(qdf_status)) {
		sme_err("scheduler_post_msg failed with status: %d",
			qdf_status);
		return QDF_STATUS_E_FAILURE;
	}

	return QDF_STATUS_SUCCESS;
}

QDF_STATUS sme_ps_enable_auto_ps_timer(tHalHandle hal_ctx,
	uint32_t session_id, uint32_t timeout)
{
	tpAniSirGlobal mac_ctx = PMAC_STRUCT(hal_ctx);
	struct ps_global_info *ps_global_info = &mac_ctx->sme.ps_global_info;
	struct ps_params *ps_param = &ps_global_info->ps_params[session_id];
	QDF_STATUS qdf_status;

	if (!timeout) {
		sme_debug("auto_ps_timer called with timeout 0; ignore");
		return QDF_STATUS_SUCCESS;
	}

	sme_info("Start auto_ps_timer for %d ms", timeout);

	qdf_status = qdf_mc_timer_start(&ps_param->auto_ps_enable_timer,
		timeout);
	if (!QDF_IS_STATUS_SUCCESS(qdf_status)) {
		if (QDF_STATUS_E_ALREADY == qdf_status) {
			/* Consider this ok since the timer is already started*/
			sme_warn("auto_ps_timer is already started");
		} else {
			sme_err("Cannot start auto_ps_timer");
			return QDF_STATUS_E_FAILURE;
		}
	}
	return QDF_STATUS_SUCCESS;
}

QDF_STATUS sme_ps_disable_auto_ps_timer(tHalHandle hal_ctx,
		uint32_t session_id)
{
	tpAniSirGlobal mac_ctx = PMAC_STRUCT(hal_ctx);
	struct ps_global_info *ps_global_info = &mac_ctx->sme.ps_global_info;
	struct ps_params *ps_param = &ps_global_info->ps_params[session_id];
	/*
	 * Stop the auto ps entry timer if runnin
	 */
	if (QDF_TIMER_STATE_RUNNING ==
			qdf_mc_timer_get_current_state(
				&ps_param->auto_ps_enable_timer)) {
		sme_info("Stop auto_ps_enable_timer Timer for session ID: %d",
				session_id);
		qdf_mc_timer_stop(&ps_param->auto_ps_enable_timer);
	}
	return QDF_STATUS_SUCCESS;
}


QDF_STATUS sme_ps_open(tHalHandle hal_ctx)
{

	uint32_t i;

	for (i = 0; i < MAX_SME_SESSIONS; i++) {
		if (QDF_STATUS_SUCCESS != sme_ps_open_per_session(hal_ctx, i)) {
			sme_err("PMC Init Failed for session: %d", i);
			return QDF_STATUS_E_FAILURE;
		}
	}
	return QDF_STATUS_SUCCESS;
}


QDF_STATUS sme_ps_open_per_session(tHalHandle hal_ctx, uint32_t session_id)
{
	tpAniSirGlobal mac_ctx = PMAC_STRUCT(hal_ctx);
	struct ps_global_info *ps_global_info = &mac_ctx->sme.ps_global_info;
	struct ps_params *ps_param = &ps_global_info->ps_params[session_id];

	ps_param->session_id = session_id;
	ps_param->mac_ctx = mac_ctx;
	/* Allocate a timer to enable ps automatically */
	if (!QDF_IS_STATUS_SUCCESS(qdf_mc_timer_init(
					&ps_param->auto_ps_enable_timer,
					QDF_TIMER_TYPE_SW,
					sme_auto_ps_entry_timer_expired,
					ps_param)))     {
		sme_err("Cannot allocate timer for auto ps entry");
		return QDF_STATUS_E_FAILURE;
	}
	return QDF_STATUS_SUCCESS;

}

void sme_auto_ps_entry_timer_expired(void *data)
{
	struct ps_params *ps_params = (struct ps_params *)data;
	tpAniSirGlobal mac_ctx;
	uint32_t session_id;
	QDF_STATUS status;

	if (!ps_params) {
		sme_err("ps_params is NULL");
		return;
	}
	mac_ctx = (tpAniSirGlobal)ps_params->mac_ctx;
	if (!mac_ctx) {
		sme_err("mac_ctx is NULL");
		return;
	}
	session_id = ps_params->session_id;
	sme_debug("auto_ps_timer expired, enabling powersave");

	status = sme_enable_sta_ps_check(mac_ctx, session_id);
	if (QDF_STATUS_SUCCESS == status)
		sme_ps_enable_disable((tHalHandle)mac_ctx, session_id,
				SME_PS_ENABLE);
}

QDF_STATUS sme_ps_close(tHalHandle hal_ctx)
{
	uint32_t i;

	for (i = 0; i < CSR_ROAM_SESSION_MAX; i++)
		sme_ps_close_per_session(hal_ctx, i);

	return QDF_STATUS_SUCCESS;
}

QDF_STATUS sme_ps_close_per_session(tHalHandle hal_ctx, uint32_t session_id)
{

	tpAniSirGlobal mac_ctx = PMAC_STRUCT(hal_ctx);
	struct ps_global_info *ps_global_info = &mac_ctx->sme.ps_global_info;
	struct ps_params *ps_param = &ps_global_info->ps_params[session_id];
	QDF_STATUS qdf_status = QDF_STATUS_SUCCESS;

	/*
	 * Stop the auto ps entry timer if running
	 */
	if (QDF_TIMER_STATE_RUNNING ==
			qdf_mc_timer_get_current_state(
				&ps_param->auto_ps_enable_timer))
		qdf_mc_timer_stop(&ps_param->auto_ps_enable_timer);

	qdf_status =
		qdf_mc_timer_destroy(&ps_param->auto_ps_enable_timer);
	if (!QDF_IS_STATUS_SUCCESS(qdf_status))
		sme_err("Cannot deallocate suto PS timer");
	return qdf_status;
}

bool sme_is_auto_ps_timer_running(tHalHandle hal_ctx,
		uint32_t session_id)
{
	tpAniSirGlobal mac_ctx = PMAC_STRUCT(hal_ctx);
	struct ps_global_info *ps_global_info = &mac_ctx->sme.ps_global_info;
	struct ps_params *ps_param = &ps_global_info->ps_params[session_id];
	bool status = false;
	/*
	 * Check if the auto ps entry timer if running
	 */
	if (QDF_TIMER_STATE_RUNNING ==
			qdf_mc_timer_get_current_state(
				&ps_param->auto_ps_enable_timer))
		status = true;

	return status;
}

