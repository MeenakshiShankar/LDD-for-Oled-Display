#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>


#include "oled.h"

int  I2C_Write( unsigned char *buf, unsigned int len );

static struct i2c_adapter *oled_i2c_adapter     = NULL;  // I2C Adapter Structure
static struct i2c_client  *oled_i2c_client = NULL;  // I2C Cient Structure (In our case it is OLED)

extern uint8_t iisc_logo[1024];
extern uint8_t india_logo[1024];
extern uint8_t smile_logo[1024];



/*
** Structure that has slave device id
*/
static const struct i2c_device_id oled_id[] = {
  { SLAVE_DEVICE_NAME, 0 },
  { }
};
MODULE_DEVICE_TABLE(i2c, oled_id);

/*
** I2C driver Structure that has to be added to linux
*/




static int oled_probe(struct i2c_client *client)
             
{
  SSD1306_DisplayInit();
  
  //Set cursor
  SSD1306_SetCursor(0,0);  
 // SSD1306_StartScrollHorizontal( true, 0, 2);

  //Write String to OLED
  SSD1306_String("Welcome\nTo\nEmbeTronicX\n\n");
  
  pr_info("OLED Probed!!!\n");
  
  return 0;
}


static void oled_remove(struct i2c_client *client)
{
  //Set cursor
  //SSD1306_SetCursor(2,0);
  //Write String to OLED
  SSD1306_String("ThanK YoU!!!");

  msleep(1000);

  //Set cursor
  SSD1306_SetCursor(0,0);
  //clear the display
  SSD1306_Fill(0x00);

  oled_cmd(0xAE); // Entire Display OFF

  pr_info("OLED Removed!!!\n");
  //return 0;

}


static struct i2c_driver oled_driver = {
  .driver = {
    .name   = SLAVE_DEVICE_NAME,
    .owner  = THIS_MODULE,
  },
  .probe          = oled_probe,
  .remove         = oled_remove,
  .id_table       = oled_id,
};

/*
** I2C Board Info strucutre
*/
static struct i2c_board_info oled_i2c_board_info = {
    I2C_BOARD_INFO(SLAVE_DEVICE_NAME, SSD1306_SLAVE_ADDR)
};



int I2C_Write(unsigned char *buf, unsigned int len)
{
  /*
  ** Sending Start condition, Slave address with R/W bit,
  ** ACK/NACK and Stop condtions will be handled internally.
  */
  int ret = i2c_master_send(oled_i2c_client, buf, len);

  return ret;
}



static int __init oled_driver_init(void)
{
  int ret = -1;
  oled_i2c_adapter     = i2c_get_adapter(I2C_BUS_AVAILABLE);

  if( oled_i2c_adapter != NULL )
  {
    oled_i2c_client = i2c_new_client_device(oled_i2c_adapter, &oled_i2c_board_info);

    if( oled_i2c_client != NULL )
    {
      i2c_add_driver(&oled_driver);
      ret = 0;
    }

      i2c_put_adapter(oled_i2c_adapter);
  }

  pr_info("Driver Added!!!\n");

  SSD1306_SetCursor(0,0);
  SSD1306_InvertDisplay(true);
  SSD1306_Fill(0x00);  
  oled_print_logo(iisc_logo);
  msleep(5000);
   SSD1306_Fill(0x00);  
  oled_print_logo(india_logo);
  msleep(5000);
  
   SSD1306_Fill(0x00);  
  oled_print_logo(smile_logo);
  msleep(5000);
  return ret;
}

/*
** Module Exit function
*/
static void __exit oled_driver_exit(void)
{
  i2c_unregister_device(oled_i2c_client);
  i2c_del_driver(&oled_driver);
  pr_info("Driver Removed!!!\n");
}

module_init(oled_driver_init);
module_exit(oled_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Meenakshi&Sivakrishna");
MODULE_DESCRIPTION("SSD1306 I2C Driver");
MODULE_VERSION("1.40");
