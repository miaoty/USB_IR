#ifndef _LIBIRCMD_H_
#define _LIBIRCMD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#define DLLEXPORT __declspec(dllexport)
#include <windows.h>
#elif defined(linux) || defined(unix)
#define DLLEXPORT
#include <unistd.h>
#endif


	/**
	* @brief Error type in libircmd library
	*/
	typedef enum {
		/** Function excute success */
		IRCMD_SUCCESS = 0,
		/** Transfer command error */
		IRCMD_TRANSFER_ERROR = -1,
		/** Invalid parameter */
		IRCMD_ERROR_PARAM = -2,
		/** Vdcmd's length is too long */
		IRCMD_VDCMD_TOO_LONG = -3,
		/** Unsupported command */
		IRCMD_UNSUPPORTED_CMD = -4,
		/** I2c transfer fail */
		IRCMD_I2C_TRANSFER_FAIL = -5,
		/** I2c device open fail */
		IRCMD_I2C_DEVICE_OPEN_FAIL = -6,
		/** I2c device open fail */
		IRCMD_CMD_EXECUTE_FAIL = -7
	}IrcmdError_t;


	/**
	 * @brief Restore defaut config types
	 */
	enum vdcmd_driver_type
	{
		/// send command by USB
		VDCMD_USB_VDCMD = 0,
		/// send command by I2C_USB
		VDCMD_I2C_USB_VDCMD,
		/// send command by I2C(linux with i2c port only)
		VDCMD_I2C_VDCMD,
		/// send command by UART
		VDCMD_UART_VDCMD
	};

	/**
	* @brief Log level definition in libircmd library
	*/
	typedef enum {
		IRCMD_LOG_DEBUG = 0,		///< print debug and error infomation
		IRCMD_LOG_ERROR = 1,		///< only print error infomation
		IRCMD_LOG_NO_PRINT = 2,	///< don't print debug and error infomation
	}ircmd_log_level_t;

	/**
	 * @brief Restore or save config types for applications development
	 */
	enum basic_prop_cfg
	{
		/// all config
		BASIC_CFG_ALL = 0,
		/// algorithm parameters config
		BASIC_CFG_ALGORITHM_PARAM = 1,
	};


	/**
	 * @brief parameters set or get status types
	 */
	enum get_set_type
	{
		///set params status
		SET_PARAMS_STA = 0,
		///get params status
		GET_PARAMS_STA
	};


	/**
	 * @brief Device id types for applications development
	 */
	enum basic_device_id_types
	{
		/// project infomation, 100 bytes
		BASIC_DEV_INFO_PROJECT_INFO = 0,
		/// get product number, 100 bytes
		BASIC_DEV_INFO_GET_PN,
		/// get serial number, 100 bytes
		BASIC_DEV_INFO_GET_SN
	};


	/**
	 * @brief Y16 mode source types for applications development
	 */
	enum basic_y16_isp_stream_src_types
	{
		BASIC_Y16_MODE_YUV = 0,
		/// temperature mode source
		BASIC_Y16_MODE_TEMPERATURE,
		/// ir sensor mode source
		BASIC_Y16_MODE_IR,
		BASIC_Y16_MODE_KBC,
		BASIC_Y16_MODE_SNR,
		BASIC_Y16_MODE_DDE,

	};


	/**
	 * @brief Preview order yuv types
	 */
	enum preview_yuv_types
	{
		UYVY = 0,
		VYUY = 1,
		YUYV = 2,
		YVYU = 3,
	};


	/**
* @brief Interface and output Types
*/
	enum interface_format_types
	{
		DVP_MODE = 0,
		USB_MODE = 1,
		BT1120_MODE = 2,
		BT656_SENSOR_MODE = 3,
		BT656_STD720_EACHLINE_MODE = 4,
		BT656_STD720_INTERLEAVED_MODE = 5,
		VOSPI_MODE
	};

	/**
	* @brief Image output format
	*/
	enum image_output_format
	{
		SINGLE_IMAGE_OR_TEMP = 0,
		FRAME_COMPOSITE_DATE
	};


	/**
* @brief Restore defaut config types for depth development
*/
	enum adv_prop_cfg
	{
		/// tpd config
		ADV_CFG_TPD = 0,
		/// dead pixel config
		ADV_CFG_DEAD_PIXEL = 1,
	};


	enum isp_param_module {
		CDC = 0,
		HBC = 1,
		SDPC = 2,
		VBC = 3,
		TNR = 4,
		DUMMY = 5,
		RMVCOVER = 6,
		TPD = 7,
		SNR_GAUSS = 8,
		SNR_BP = 9,
		DDPC = 10,
		FOCUS = 11,
		AGC = 12,
		DDE = 13,
		GAMMA = 14,
		MIRROR_AND_FLIP = 15,
		KBC = 16,
		OOC = 17
	};


	/**
	* @brief Ktbt recalculate point index
	*/
	enum tpd_ktbt_recal_point_idx
	{
		/// the first point
		TPD_KTBT_RECAL_P1 = 0,
		/// the second point
		TPD_KTBT_RECAL_P2 = 1
	};

	typedef struct _IrcmdHandle_t IrcmdHandle_t;

	/**
* @brief Line struct
*/
	typedef struct {
		/// preview path 0/1
		uint8_t path;
		/// preview source 0:sensor 1:fix pattern
		uint8_t source;
		/// preview width
		uint16_t width;
		/// preview height
		uint16_t height;
		/// preview fps
		uint8_t fps;
		/**
		 * preview mode
		 * 0: VOC_DVP_MODE
		 * 1: VOC_ESAV_SMPTE296_MODE
		 * 2: VOC_HSYNC_PAL_MODE
		 * 3: VOC_ESAV_625LINE_MODE
		 * 4: VOC_ESAV_525LINE_MODE
		 * 5: VOC_COMPOSITE_PAL_MODE
		 * 6: VOC_COMPOSITE_NTSC_MODE
		 * 7: Square PAL mode
		 * 8: VOSPI_MODE
		 * 9: VOC_COMPOSITE_PAL_EXT_DAC_MODE
		 */
		uint8_t mode;
	}PreviewStartParam_t;

	/**
	 * @brief Point struct, start from 1
	 */
	typedef struct {
		/// x position
		uint16_t x;
		/// y position
		uint16_t y;
	}IrcmdPoint_t;


	/**
	 * @brief Line struct, start from 1
	 */
	typedef struct {
		/// start point's position
		IrcmdPoint_t start_point;
		/// end point's position
		IrcmdPoint_t end_point;
	}IrcmdLine_t;


	/**
	 * @brief Rectangle struct, start from 1
	 */
	typedef struct {
		/// start point's position
		IrcmdPoint_t start_point;
		/// end point's position
		IrcmdPoint_t end_point;
	}IrcmdRect_t;


	/**
	 * @brief Maximum and minimum temperature information struct of the frame
	 */
	typedef struct
	{
		/// maximum temperature value
		uint16_t max_temp;
		/// minimum temperature value
		uint16_t min_temp;
		/// maximum temperature point's position
		IrcmdPoint_t max_temp_point;
		/// minimum temperature point's position
		IrcmdPoint_t min_temp_point;
	}FrameTempInfo_t;

	/**
	 * @brief Maximum and minimum temperature information struct
	 */
	typedef struct
	{
		/// maximum temperature value
		uint16_t max_temp;
		/// minimum temperature value
		uint16_t min_temp;
		/// maximum temperature point's position
		IrcmdPoint_t max_temp_point;
		/// minimum temperature point's position
		IrcmdPoint_t min_temp_point;
	}MaxMinTempInfo_t;





	/**
	 * @brief Temperature information struct, including average, maximum,
	 * and minimum temperature value.
	 */
	typedef struct
	{
		/// average temperature value
		uint16_t ave_temp;
		/// maximum temperature value
		uint16_t max_temp;
		/// minimum temperature value
		uint16_t min_temp;
	}TpdTempInfoValue_t;


	/**
	 * @brief Temperature information struct of a line or a rectangle.
	 */
	typedef struct
	{
		/// the temperature information
		TpdTempInfoValue_t temp_info_value;
		/// maximum temperature's point position
		IrcmdPoint_t max_temp_point;
		/// minimum temperature's point position
		IrcmdPoint_t min_temp_point;
	}TpdLineRectTempInfo_t;


	typedef struct {
		uint8_t bySdpcDeadPixEn;     //盲元功能使能
		uint8_t bySdpRpEn;           //新增盲元写入盲元表使能
		uint8_t bySdpcDeadPixType;   //盲元类型（勿改）
		uint8_t bySdpcInterpolationTh; //盲元替换时的插值阈值
		uint8_t bySdpcMedianFilterEn;  //中值滤波使能
	}SdpcParma_t;


	typedef struct {
		uint8_t byBpEn;          //新增单点盲元检测使能
		uint8_t byBpOptEn;		//新增连续盲元检测使能
		int16_t swBpMaxTshd;    //新增单点盲元最大值的算法裕度
		int16_t swBpMinTshd;    //新增单点盲元最小值的算法裕度
		int16_t swBpMaxOptTshd; //新增连续盲元最大值的算法裕度
		int16_t swBpMinOptTshd; //新增连续盲元最小值的算法裕度
		int8_t sbyBpRpMaxOffset; //新增单点盲元最大值的算法偏移
		int8_t sbyBpRpMinOffset; //新增单点盲元最小值的算法偏移
		int8_t sbyBpRpMaxOptOffset;//新增连续盲元最大值的算法偏移
		int8_t sbyBpRpMinOptOffset;//新增连续盲元最小值的算法偏移
	}DdpcParma_t;

	/**
	 * @brief Get libircmd library's version
	 *
	 * @return version's string
	 */
	DLLEXPORT const char* ircmd_version(void);


	/**
	 * @brief Register log print via log_level
	 *
	 * @param[in] log_level debug information level
	 *
	 */
	DLLEXPORT void ircmd_log_register(ircmd_log_level_t log_level);


	/**
	 * @brief Create and initialize ircmd's handle
	 *
	 * @param driver_handle driver's handle
	 * @param driver_type driver's type
	 *
	 * @return IrcmdHandle_t struct pointer
	 */
	DLLEXPORT IrcmdHandle_t* ircmd_create_handle(void* driver_handle, enum vdcmd_driver_type driver_type);


	/**
	 * @brief Delete and release ircmd's handle
	 *
	 * @param handle ircmd's handle
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t ircmd_delete_handle(IrcmdHandle_t* handle);


	/**
	 * @brief Get device infomation via id_type for applications development
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] id_type the device's id type for applications development
	 * @param[out] id_content[100] the device's infomation data
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_get_device_info(IrcmdHandle_t* handle, enum basic_device_id_types basic_id_type, uint8_t* id_content);


	/**
	 * @brief Update the firmware
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] data firmware data
	 * @param[in] data_size firmware data size
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_update_fw(IrcmdHandle_t* handle, uint8_t* data, int data_size);


	/**
	 * @brief Restore defaut parameters for applications development
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] default_cfg_type default config type for applications development
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_restore_default_cfg(IrcmdHandle_t* handle, enum basic_prop_cfg default_cfg_type);



	/**
	 * @brief Save config to flash for applications development
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] flash_cfg_type flash config type for applications development
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_flash_config_save(IrcmdHandle_t* handle, enum basic_prop_cfg flash_cfg_type);


	/**
	 * @brief Switch to y16 mode
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] src_type y16 mode source type
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_y16_preview(IrcmdHandle_t* handle, enum basic_y16_isp_stream_src_types src_type);


	/**
	* @brief Set preview yuv types
	*
	* @param[in] handle ircmd's handle
	* @param[in] preview_yuv_types pveview yuv types.UYVY = 0,VYUY = 1,YUYV = 2,YVYU = 3.
	*
	* @return see IrcmdError_t
	*/
	DLLEXPORT IrcmdError_t basic_preview_yuv_format_set(IrcmdHandle_t* handle, enum preview_yuv_types preview_yuv_type);


	/**
	 * @brief Start preview via command for applications development
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] interface_format_type interface and format types
	 * @param[in] output_format image output format
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_preview_mode_select(IrcmdHandle_t* handle, enum interface_format_types interface_format_type, \
		enum image_output_format output_format);


	/**
	 * @brief Zoom up from the center
	 *
	 * @param[in] handle ircmd's handle
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_zoom_center_up(IrcmdHandle_t* handle);


	/**
	 * @brief Zoom down from the center
	 *
	 * @param[in] handle ircmd's handle
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_zoom_center_down(IrcmdHandle_t* handle);


	/**
	 * @brief Set or get property page's image parameters mirror or flip status.
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] set_get_sta image's parameter set or get types
	 * @param[in/out] value  Mirror flip status. 0:no mirror/flip,1:only mirror the frame,2:only flip the frame,3:mirror and flip the frame
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_image_mirror_flip(IrcmdHandle_t* handle, enum get_set_type set_get_sta, uint16_t* value);


	/**
	 * @brief Set or get property page's image parameters DDE str level.
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] set_get_sta image's parameter set or get types
	 * @param[in/out] value DDE(digital detail enhance) level.Range:0-100.
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_image_params_dde(IrcmdHandle_t* handle, enum get_set_type set_get_sta, uint16_t* value);

	/**
	 * @brief Set or get property page's image parameters Brightness level.
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] set_get_sta image's parameter set or get types
	 * @param[in/out] value Brightness level. range:0-255
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_image_params_brightness(IrcmdHandle_t* handle, enum get_set_type set_get_sta, uint16_t* value);

	/**
	 * @brief Set or get property page's image parameters Contrast level.
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] set_get_sta image's parameter set or get types
	 * @param[in/out] value Contrast level. range:0-255
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_image_params_contrast(IrcmdHandle_t* handle, enum get_set_type set_get_sta, uint16_t* value);


	/**
	 * @brief Set or get property page's auto shutter switch
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] set_get_sta parameter set or get types
	 * @param[in/out] value Auto shutter update switch. 0:OFF, 1:ON
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_auto_shutter_onoff(IrcmdHandle_t* handle, enum get_set_type set_get_sta, uint16_t* value);

	/**
	  * @brief Set or get auto shutter minimun interval,to prevent updates too frequently
	  *
	  * @param[in] handle ircmd's handle
	  * @param[in] set_get_sta parameter set or get types
	  * @param[in/out] value shutter minimun interval.range:5-655
	  *
	  * @return see IrcmdError_t
	  */
	DLLEXPORT IrcmdError_t basic_auto_shutter_min_interval(IrcmdHandle_t* handle, enum get_set_type set_get_sta, uint16_t* value);

	/**
	  * @brief Set or get auto shutter maximun interval,shutter updates automatically at this time.
	  *
	  * @param[in] handle ircmd's handle
	  * @param[in] set_get_sta parameter set or get types
	  * @param[in/out] value shutter maximun interval.range:5-655
	  *
	  * @return see IrcmdError_t
	  */
	DLLEXPORT IrcmdError_t basic_auto_shutter_max_interval(IrcmdHandle_t* handle, enum get_set_type set_get_sta, uint16_t* value);

	/**
	  * @brief Set or get temp's threshold to trigger B update in auto shutter.
	  * Do B update according to the temperature difference between latest update.
	  *
	  * @param[in] handle ircmd's handle
	  * @param[in] set_get_sta parameter set or get types
	  * @param[in/out] value unit:cnt(36cnt~=1c), range:0-65535
	  *
	  * @return see IrcmdError_t
	  */
	DLLEXPORT IrcmdError_t basic_auto_shutter_vtemp_threshold(IrcmdHandle_t* handle, enum get_set_type set_get_sta, uint16_t* value);


	/**
	* @brief Update shutter
	*
	* @param[in] handle ircmd's handle
	*
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_shutter_update(IrcmdHandle_t* handle);

	/**
	  * @brief Set or get pseudo color types.
	  *
	  * @param[in] handle ircmd's handle
	  * @param[in] set_get_sta parameter set or get types
	  * @param[in/out] value pseudo color types.
	  *
	  * @return see IrcmdError_t
	  */
	DLLEXPORT IrcmdError_t basic_pseudo_color(IrcmdHandle_t* handle, enum get_set_type set_get_sta, uint16_t* value);


	/**
	 * @brief Get the point temperature information with normal mode.default index=0.Unit:1/16 K
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] point_pos point's position
	 * @param[out] point_temp_value the temperature information of the point
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_tpd_get_point_temp_info(IrcmdHandle_t* handle, IrcmdPoint_t point_pos, uint16_t* point_temp_value);


	/**
	 * @brief Get the line temperature information with normal mode.default index=0..Unit:1/16 K
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] line_pos line's position
	 * @param[out] line_temp_info the temperature information of the line
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_tpd_get_line_temp_info(IrcmdHandle_t* handle, IrcmdLine_t line_pos, TpdLineRectTempInfo_t* line_temp_info);


	/**
	 * @brief Get the rectangle temperature information with normal mode.default index=0..Unit:1/16 K
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] rect_pos rectangle's position
	 * @param[out] rect_temp_info the temperature information of the rectangle
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_tpd_get_rect_temp_info(IrcmdHandle_t* handle, IrcmdRect_t rect_pos, TpdLineRectTempInfo_t* rect_temp_info);


	/**
	 * @brief Get the maximum and minimum temperature information of the frame.Unit:1/16 K
	 *
	 * @param[in] handle ircmd's handle
	 * @param[out] max_min_temp_info the maximum and minimum temperature information of the frame
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_tpd_get_frame_temp_info(IrcmdHandle_t* handle, FrameTempInfo_t* frame_temp_info);


	/**
	 * @brief Set or get property page's tpd parameters
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] set_get_sta parameter set or get types
	 * @param[in] value Gain select. 0:low gain, 1:high gain
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t basic_prop_tpd_sel_gain(IrcmdHandle_t* handle, enum get_set_type set_get_sta, uint16_t* value);



	/**
 * @brief Set or get property page's image parameters AGC level.
 *
 * @param[in] handle ircmd's handle
 * @param[in] set_get_sta image's parameter set or get types
 * @param[in/out] value AGC(Auto Gain Control) level.Range:0-100.
 *
 * @return see IrcmdError_t
 */
	DLLEXPORT IrcmdError_t adv_image_params_agc_mode(IrcmdHandle_t* handle, enum get_set_type set_get_sta, uint16_t* value);


	/**
	 * @brief clear the rmcover data from flash.
	 *
	 * @param[in] handle ircmd's handle
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t adv_rmcover_clear_data(IrcmdHandle_t* handle);


	/**
	 * @brief auto calibrate dead pixel and save to flash in firmware.
	 *
	 * @param[in] handle ircmd's handle
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t adv_dpc_auto_calc(IrcmdHandle_t* handle);


	/**
	 * @brief Add dead pixel point temporarily, need to use basic_flash_config_save to save in flash.
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] position position of the point.Axis start from 1.
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t adv_dpc_add_point(IrcmdHandle_t* handle, IrcmdPoint_t position);


	/**
	 * @brief Remove dead pixel point temporarily, need to use adv_dpc_save to save in flash.
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] position position of the point.Axis start from 1.
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t adv_dpc_remove_point(IrcmdHandle_t* handle, IrcmdPoint_t position);


	/**
	 * @brief Save config dead pixel to flash in firmware
	 *
	 * @param[in] handle ircmd's handle
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t adv_dpc_save(IrcmdHandle_t* handle);


	/**
	 * @brief clear dead pixel data from flash.
	 *
	 * @param[in] handle ircmd's handle
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t adv_dpc_clear_data(IrcmdHandle_t* handle);


	/**
	 * @brief Recalculate the kt_bt by 1 point's temperature
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] temp the target black body's temperature. units:K(integer)
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t adv_tpd_ktbt_recal_1point(IrcmdHandle_t* handle, uint16_t temp);


	/**
	 * @brief Recalculate the kt_bt by 2 points' temperature.First set point1(low temp),then set point2(high temp).
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] point_idx point index
	 * @param[in] temp the target black body's temperature. units:K(integer)
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t adv_tpd_ktbt_recal_2point(IrcmdHandle_t* handle, enum tpd_ktbt_recal_point_idx point_idx, \
		uint16_t temp);


	/**
	 * @brief Restore property page's defaut parameters for deep developmenta.
	 *
	 * @param[in] handle ircmd's handle
	 * @param[in] adv_default_cfg_type default config type for deep development
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t adv_restore_default_cfg(IrcmdHandle_t* handle, enum adv_prop_cfg default_cfg_type);


	/**
	 * @brief Read data from ISP chip with SPI communication about error log
	 *
	 * @param[in] handle ircmd's handle
	 * @param[out] pbyData the data read from memory about error log
	 *
	 * @return see IrcmdError_t
	 */
	DLLEXPORT IrcmdError_t adv_read_error_log(IrcmdHandle_t* handle, uint8_t* pbyData);


#ifdef __cplusplus
}
#endif

#endif


