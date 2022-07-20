#include "cmd.h"
uint16_t prevalue=3;

extern IruvcHandle_t* iruvc_handle1;
//command selection
void command_sel(StreamFrameInfo_t* handle, int cmd_type)
{
	int rst = 0;
	uint8_t id_data[100] = { 0 };
	uint16_t temp_data = 0;
	IrcmdPoint_t point_1 = { 320,256 };
	IrcmdRect_t rect1 = { 100, 100, 300, 300 };
	TpdLineRectTempInfo_t rect1_temp_info = { 0 };
	IrcmdPoint_t point_pos = { 100,100 };
	uint16_t point_temp_value = 0;
	uint16_t value=0;
	uint8_t* pbyData = NULL;
	FILE* fp = NULL;

	switch (cmd_type)
	{
	case 0:
		basic_get_device_info(handle->ircmd_handle, BASIC_DEV_INFO_GET_PN, id_data);
		printf("get device PN:");
		for (int j = 0; j < 8; j++)
		{
			printf("0x%x ", id_data[j]);
		}
		printf("\n");
		break;
	case 1:
		basic_get_device_info(handle->ircmd_handle, BASIC_DEV_INFO_PROJECT_INFO, id_data);
		printf("get device fw version:");
		for (int j = 0; j < 4; j++)
		{
			printf("0x%x ", id_data[j]);
		}
		printf("\n");
		break;
	case 2:
		basic_restore_default_cfg(handle->ircmd_handle, BASIC_CFG_ALGORITHM_PARAM);
		printf("restore default proper page config\n");
		break;
	case 3:
		basic_flash_config_save(handle->ircmd_handle, BASIC_CFG_ALL);
		printf("spi config save all\n");
		break;
	case 4:
		basic_y16_preview(handle->ircmd_handle, BASIC_Y16_MODE_YUV);
		printf("y16 preview mode YUV\n");
		break;
	case 5:
		basic_preview_yuv_format_set(handle->ircmd_handle, YUYV);
		printf("preview yuv format set:YUYV\n");
		break;
	case 51:
		basic_preview_mode_select(handle->ircmd_handle, USB_MODE,SINGLE_IMAGE_OR_TEMP);
		printf("preview mode set:USB_mode\n");
		break;
	case 6:
		rst = basic_zoom_center_up(handle->ircmd_handle);
		printf("zoom_center_up\n");
		break;
	case 7:
		rst = basic_zoom_center_down(handle->ircmd_handle);
		printf("zoom_center_down\n");		
		break;
	case 8:
		value = 3;
		basic_image_mirror_flip(handle->ircmd_handle, SET_PARAMS_STA, &value);
		printf("image_mirror_flip\n");
		break;
	case 9:
		basic_auto_shutter_onoff(handle->ircmd_handle, GET_PARAMS_STA, &value);
		printf("auto_shutter_onoff\n");
		printf("value =%d\n", value);
		break;
	case 10:
		value = 6;
		basic_auto_shutter_min_interval(handle->ircmd_handle, GET_PARAMS_STA, &value);
		printf("auto_shutter_min_interval\n");
		printf("value =%d\n", value);
		break;
	case 11:
		value = 15;
		basic_auto_shutter_vtemp_threshold(handle->ircmd_handle, SET_PARAMS_STA, &value);
		printf("basic_auto_shutter_vtemp_threshold\n");
		break;
	case 12:
		value = 3;
		basic_pseudo_color(handle->ircmd_handle, SET_PARAMS_STA, &value);
		printf("pseudo color set:3\n");
		printf("input <301> to close\n");
		break;
	case 13:
		basic_tpd_get_point_temp_info(handle->ircmd_handle, point_pos, &point_temp_value);
		printf("tpd_get_point_temp_info:%.2f\n", (point_temp_value / 16 - 273.15));
		break;
	case 14:
		basic_tpd_get_rect_temp_info(handle->ircmd_handle, rect1, &rect1_temp_info);
		printf("tpd_get_rect_temp_info:min(%d,%d):%.2f, max(%d,%d):%.2f\n", \
			rect1_temp_info.min_temp_point.x, rect1_temp_info.min_temp_point.y, \
			(rect1_temp_info.temp_info_value.min_temp / 16 - 273.15), \
			rect1_temp_info.max_temp_point.x, rect1_temp_info.max_temp_point.y, \
			(rect1_temp_info.temp_info_value.max_temp / 16 - 273.15));
		break;
	case 15:
		value = 4;
		basic_image_params_dde(handle->ircmd_handle, SET_PARAMS_STA, &value);
		printf("basic_image_params_dde\n");
		break;
	case 16:
		value = 1;
		basic_prop_tpd_sel_gain(handle->ircmd_handle, SET_PARAMS_STA, &value);
		printf("basic_prop_tpd_sel_gain\n");
		break;
	case 17:
		adv_image_params_agc_mode(handle->ircmd_handle, GET_PARAMS_STA, &value);
		printf("advanced_image_params_agc_mode\n");
		printf("value =%d\n", value);
		break;
	case 18:
		value = 200;
		basic_image_params_brightness(handle->ircmd_handle, SET_PARAMS_STA, &value);
		printf("basic_image_params_brightness\n");
		break;
	case 19:
		adv_restore_default_cfg(handle->ircmd_handle, ADV_CFG_TPD);
		printf("restore default tpd config\n");
		break;
	case 20:
		adv_rmcover_clear_data(handle->ircmd_handle);
		printf("clear rmcover data\n");
		break;
	case 21:
		pbyData = (uint8_t*)malloc(8192);
		adv_read_error_log(handle->ircmd_handle, pbyData);
		printf("read fw error log\n");
		fp = fopen("aim_image.bin", "wb");
		fwrite(pbyData, 1, 8192, fp);
		fclose(fp);
		break;
	case 22:
		adv_dpc_save(handle->ircmd_handle);
		printf("dpc save\n");
		break;
	case 23:
		adv_dpc_auto_calc(handle->ircmd_handle);
		printf("dpc auto calc\n");
		break;
	case 301:
		ir_camera_close(iruvc_handle1);
		printf("ir_camera_close\n");
		break;
	default:
		break;
	}
}

//command thread function
void* cmd_function(void* threadarg)
{
	command_sel(((StreamFrameInfo_t*)threadarg), 12);
	int cmd = 0;
	while (cmd != 999)
	{
		scanf("%d", &cmd);
		command_sel(((StreamFrameInfo_t*)threadarg), cmd);
	}
	printf("cmd thread exit!!\n");
	return NULL;
}
