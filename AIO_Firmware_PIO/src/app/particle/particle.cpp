#include "particle.h"
#include "sys/app_controller.h"
#include "common.h"
#include <stdint.h>
#include <stdlib.h>
#include "../idea_anim/ui_animation.h"

#define particle_APP_NAME "Love"

// 由于tft屏幕刷新太慢，现在是先开辟一块屏幕分辨率大小的空间作为一张需要显示的图像，
// 所有的绘图操作在虚拟的空间上，绘制图像，最后调用tft的图像显示功能显示图像

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 240

uint8_t *screenBuf = NULL;

/*这两个函数都只是对图像进行操作，不是对屏幕*/
static void screen_clear(uint16_t color);                            //清屏函数声明
static void screen_draw_pixel(int32_t x, int32_t y, uint16_t color); //描点函数声明
/**********************************/

static void gfx_draw_pixel(int x, int y, unsigned int rgb) //指定GUI库的描点函数
{
    screen_draw_pixel(x, y, rgb);
}

struct EXTERNAL_GFX_OP
{
    void (*draw_pixel)(int x, int y, unsigned int rgb);
    void (*fill_rect)(int x0, int y0, int x1, int y1, unsigned int rgb);
} gfx_op;

void screen_clear(uint16_t color)
{
    int32_t i = 0;
    int32_t j = 0;

    for (i = 0; i < SCREEN_HEIGHT; ++i)
    {
        for (j = 0; j < SCREEN_WIDTH; ++j)
        {
            screenBuf[i * SCREEN_WIDTH + j] = color;
        }
    }
}

void screen_draw_pixel(int32_t x, int32_t y, uint16_t color) //指定GUI库的描点函数
{
    if ((x >= SCREEN_WIDTH) || (y >= SCREEN_HEIGHT))
        return;
    if ((x < 0) || (y < 0))
        return;
    screenBuf[y * SCREEN_WIDTH + x] = color;
}

static int particle_init(AppController *sys)
{
    screenBuf = (uint8_t *)malloc(SCREEN_HEIGHT * SCREEN_WIDTH); //动态分配一块屏幕分辨率大小的空间

    if (screenBuf == NULL)
        Serial.println("screen_buf: error");
    else
    {
        Serial.println("screen_buf: OK");
    }
    // Link your LCD driver & start UI:
    gfx_op.draw_pixel = gfx_draw_pixel;                       //指定GuiLite库的描点函数
    gfx_op.fill_rect = NULL;                                  // gfx_fill_rect;
    create_uiForParticle(NULL, SCREEN_WIDTH, SCREEN_HEIGHT, 2, &gfx_op); // ui初始化
    screen_clear(0x0000);
    return 0;
}



static void particle_process(AppController *sys,const ImuAction *action) 
{
    lv_scr_load_anim_t anim_type = LV_SCR_LOAD_ANIM_NONE;

    if (RETURN == action->active)
    {
        sys->app_exit();
        return;
    }

    float accXinc = 0;
    float accYinc = 0;
    switch (action->active)
    {
    case TURN_LEFT:
        accXinc = -80;
        accYinc = 0;
        break;
    case TURN_RIGHT:
        accXinc = 80;
        accYinc = 0;
        break;
    case UP:
        accXinc = 0;
        accYinc = -80;
        break;
    case DOWN:
        accXinc = 0;
        accYinc = 80;
        break;
    default:
        accXinc = 0;
        accYinc = 0;
        break;
    }

    //清屏，以黑色作为背景
    screen_clear(0x0000);                                          //增加清除旧显存的代码
    ui_updateForParticle(accXinc,accYinc);                                             // ui更新//最终所有的特效调用都在这里面
    tft->pushImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, screenBuf); //显示图像
    delay(2);                                                     //改变这个延时函数就能改变特效播放的快慢
}

static void particle_background_task(AppController *sys,
                                 const ImuAction *act_info)
{
    // 本函数为后台任务，主控制器会间隔一分钟调用此函数
    // 本函数尽量只调用"常驻数据",其他变量可能会因为生命周期的缘故已经释放
}

static int particle_exit_callback(void *param)
{
    if (NULL != screenBuf)
    {
        free(screenBuf);
        screenBuf = NULL;
    }
    return 0;
}

static void particle_message_handle(const char *from, const char *to,
                                APP_MESSAGE_TYPE type, void *message,
                                void *ext_info)
{
}

APP_OBJ particle_app = {particle_APP_NAME, &loveIcon, "", particle_init,
                    particle_process, particle_background_task, particle_exit_callback,
                    particle_message_handle};