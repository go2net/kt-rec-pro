/*


*/
#include "device.h"
#include "uart.h"

extern DECODER_MSG _xdata *dec_msg;
extern u8 _xdata decode_buffer[];
extern u8 given_device;
extern u8 given_file_method;
extern u16 break_point_filenum;
extern u8 _xdata win_buffer[512];
//extern u8 _code one_table[];
extern void stop_decode(void);
extern FSAPIMSG _pdata fs_msg;
extern FIL xdata fat_ptr1;

#if 0
extern DISK_MUSIC_POINT _idata	disk_mus_point[];
#else
extern xd_u16 sd_music_bp,usb_music_bp;
#endif

u8 _bdata device_online;			    ///<设备在线标记
sbit sdmmc_connect = device_online^0;   ///<SD卡在线状态标记寄存器；1:在线 0：不在线
sbit udisk_connect = device_online^1;   ///<USB MASS storage在线状态标记寄存器；1:在线 0：不在线
sbit pc_connect = device_online^4;      ///<PC在线状态标记寄存器；1:在线 0：不在线
u8 device_active;                       ///<当前在线活动设备
u8 const _code file_type[] = "MP1MP2MP3WMAWAV";  ///<解码文件格式
#if 0

#if VIRTUAL_ENABLE
u8 _code  device_tab[4] = 
{
    DEVICE_SDMMC0,
    DEVICE_SDMMC0_REC,
    DEVICE_UDISK,
    DEVICE_UDISK_REC,
};
#else
u8 _code  device_tab[2] = 
{
    DEVICE_SDMMC0,
    DEVICE_UDISK,
};
#endif
u8 get_device_cnt(u8 dev)
{
    u8 i;
    for(i = 0;i < sizeof(device_tab);i++)
    {
        if(dev == device_tab[i])
        {
            return i;
        }
    }
    return 0;
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief   检测当前活动的设备
   @param   无
   @return  0：当前活动的设备不在线：其他：当前活动的设备
   @note    u8 device_check(void)
*/
/*----------------------------------------------------------------------------*/
u8 device_check(void)
{
    device_online = get_device_online_status();
    return device_active & device_online;
}


/*----------------------------------------------------------------------------*/
/**@brief   设备初始化
   @param   无
   @return  0：找到有效谁而；其他：没有找到有效设备
   @note    u8 device_init(void)
*/
/*----------------------------------------------------------------------------*/
u8 device_init(void)
{
    u8 sector_sizeof512 = 1;
    device_check();
    if (device_active & device_online)  ///<当前需要活动的设备在线
    {
        disp_port(MENU_SCAN_DISK);

        stop_decode();
//        deg_str("device init\n");
        fs_fun_init();

        if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
        {
            if (init_sd())                  ///<sd 卡鉴定
            {
                f_init(win_buffer, (u16)sdmmc_read, 1);//get_usb_device_pkt_size());    ///<鉴定成功后 初始化文件系统参数
            }
            else
            {
				return 0xff;                       ///<鉴定失败
            }

        }

        else if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
        {
            if (usb_host_emuerate_devcie(win_buffer))     ///<USB MASS STORAGE 枚举
            {
                sector_sizeof512 = get_usb_device_pkt_size();
                f_init(win_buffer, (u16)read_usb, sector_sizeof512);      ///<枚举成功后 初始化文件系统参数
            }
            else
            {
                return 0xff;             ///<枚举失败
            }
        }

    }
    else
    {
        return 0xff;
    }

//    deg_str("fat init\n");
    //if (!f_mount())                                      ///<文件系统初始化
    if (!f_mount_bsp(sector_sizeof512))
    {
        
        if((RECODE_INIT == encode_status))
        {
             if(0 == f_write_init(device_active & (~VIRTUAL_DEVICE)))  //初始化写设备的数据
             {
                 return 0xfd;
             }
             else
             {
                 return 0;
             }
        }
        fs_ext_setting(file_type);
        {
            u16 break_point;
            //get_rec_mem_info();
            if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
            {
                //break_point = disk_mus_point[0 + encode_cnt].id0;
                break_point =sd_music_bp;
            }
            else if ((device_active & (~VIRTUAL_DEVICE) ) == DEVICE_UDISK)
            {
               // break_point = disk_mus_point[1 + encode_cnt].id0;
                break_point =usb_music_bp;               
            }
            	break_point_filenum = fs_scan_disk(break_point);
    		encode_fristfile = fs_msg_rec.firstfilenum;	  //录音文件总数
            	encode_filenum = fs_msg_rec.fileTotalInDir;	  //录音文件夹的第一个文件号
            //if (break_point_filenum)
            {
                //break_point_filenum = filenum_phy_logic(break_point_filenum);
            }
        }
		     




#if VIRTUAL_ENABLE
        logic_fileTotal = fs_msg.fileTotal - encode_filenum;          ///音乐文件总数

        if(device_active & VIRTUAL_DEVICE)
        {
            logic_fileTotal = encode_filenum;	//录音文件总数
        }
#else
        logic_fileTotal = fs_msg.fileTotal;
#endif
        
		
        if(0 == logic_fileTotal)//if (fs_msg.fileTotal == 0)
        {
            return 0xfe;
        }

        return 0;
    }
    else
    {
        return 0xff;	//无有效设备
    }
}
/*----------------------------------------------------------------------------*/
/**@brief    查找指定的设备或自动查找下一个有效设备
   @param    select : 1：查找SD设备；2：查找USB mass storage设备; 0x81:查找上一个设备；0x82:查找下一个设备;其它：无效
   @return   0：成功查找到一个设备；1:指定的设备没有找到；2：只有一个设备，查找上一个设备或下一个设备无效;3:找到设备，但初始化不成功;4：无在线设备
   @note     u8 find_device(u8 select)
*/
/*----------------------------------------------------------------------------*/


u8 find_device(u8 select)
{
    //u8 i;
    //u8 cnt;
	
    device_check();

    //i = one_table[device_online & 0x0f];

    if ((device_online&0x03) == 0)				//无设备
    {
        device_active = 0;
        return NO_DEV_ONLINE;
    }
    if((select == DEVICE_AUTO_PREV)||(select == DEVICE_AUTO_NEXT))		//查找上一个设备
    {
//        if ((i == 1) && (device_active & device_online))			//当前设备已经选中
//            return ONLY_ONE_DEVICE;
#if 1
	   if(device_active==DEVICE_UDISK){
		device_active = DEVICE_SDMMC0;
	   }
	   else if(device_active==DEVICE_SDMMC0){
		device_active = DEVICE_UDISK;
	   }
	   else{
		device_active=0;
	   }

          if ((device_active & device_online) == 0){
        	device_active = 0;
        	return NO_EFFECTIVE_DEV;				//无有效可以使用的设备
          }	

          if (!device_init())             //找到有效设备
                return FIND_DEV_OK;
			
#else
        for (i = 0;i < MAX_DEVICE;i++)
        {
            cnt = get_device_cnt(device_active);
            
            if(0 == cnt)
            {
               cnt = (MAX_DEVICE-1);
            }
            else
            {
                cnt--;
            }
            device_active = device_tab[cnt];	   //用查表的方法来找下一个设备


            if ((device_active & device_online) == 0)
                continue;

            if (!device_init())             //找到有效设备
                return FIND_DEV_OK;
        }
        device_active = 0;
        return NO_EFFECTIVE_DEV;				//无有效可以使用的设备
#endif
    }
#if 0	
    else if (select == DEVICE_AUTO_NEXT)    //查找下一个设备
    {
#if 1

#else
        for (i = 0;i < MAX_DEVICE;i++)
        {
            cnt = get_device_cnt(device_active);  
            cnt++;
            if(cnt > (MAX_DEVICE-1))
            {
               cnt = 0;
            }
            device_active = device_tab[cnt];		//用查表的方法来找下一个设备
//            if ((device_active > MAX_PLAY_DEVICE) || (device_active == 0))
//                device_active = DEVICE_UDISK;


            if ((device_active  & device_online) == 0)
            {
                continue;
            }
            if (!device_init())             //找到有效设备
            {
                return FIND_DEV_OK;
            }

        }

        device_active = 0;
        return NO_EFFECTIVE_DEV;							//无有效可以使用的设备
#endif        
    }
#endif	
    else
    {
        if (select & device_online)
        {

            device_active = select;
            if (!device_init())
                return FIND_DEV_OK;
            else
            {
                device_active = 0;
                return DEV_INIT_ERR;
            }
        }
        else
            return NO_DEFINE_DEV;
    }

     	return NO_EFFECTIVE_DEV;				//无有效可以使用的设备

}
/*----------------------------------------------------------------------------*/
/**@brief   记录文件ID0，ID1信息到EEPROM
   @param   无
   @return  无
   @note    void write_file_info(u8)
*/
/*----------------------------------------------------------------------------*/
#if 1
void write_file_info(u8 cmd)
{
    u16 id;
    //u8 i;
//    u8 encode_cnt;
//    u8 mem_addr;
    if(0 == cmd)
    {
        id = 0;
    }
    else
    {
        id = read_file_id(&fat_ptr1);
    }

    write_info(MEM_ACTIVE_DEV, device_active);

   // get_rec_mem_info();
    if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
    {

#if 1
	sd_music_bp = id;
	write_info(MEM_SD_PLAYPOINT_ID0,(((u8 *)(&sd_music_bp))[0]));
	write_info(MEM_SD_PLAYPOINT_ID0+1,(((u8 *)(&sd_music_bp))[1]));
#else
        disk_mus_point[0+encode_cnt].id0 = id;
        disk_mus_point[0+encode_cnt].id1 = 0;
        disk_mus_point[0+encode_cnt].id2 = 0;
        for (i = 9;i != (-1);i--)
        {
            write_info(MEM_SD_PLAYPOINT_ID0+i+mem_addr,((u8 *)(&(disk_mus_point[0+encode_cnt].id0)))[i]);
        }
#endif
    }
    else if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
    {
#if 1
	usb_music_bp = id;
	write_info(MEM_USB_PLAYPOINT_ID0,(((u8 *)(&usb_music_bp))[0]));
	write_info(MEM_USB_PLAYPOINT_ID0+1,(((u8 *)(&usb_music_bp))[1]));
#else    
        disk_mus_point[1 + encode_cnt].id0 = id;
        disk_mus_point[1 + encode_cnt].id1 = 0;
        disk_mus_point[1 + encode_cnt].id2 = 0;
        for (i = 9;i != (-1);i--)
        {
            write_info(MEM_USB_PLAYPOINT_ID0+i+mem_addr,((u8 *)(&(disk_mus_point[1 + encode_cnt].id0)))[i]);
        }
#endif
		
    }
}

#endif



