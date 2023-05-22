#include "particle_gui.h"
#include <stdio.h>
#include "lvgl.h"

static lv_style_t *particle_scr = NULL;
static lv_obj_t *clockLabel_1 = NULL, *clockLabel_2 = NULL;
static lv_style_t default_style;
static lv_style_t name_style;
static lv_style_t time_style;
static lv_style_t chFont_style;
static lv_obj_t *chart, *txtLabel;
static lv_style_t numberSmall_style;
static lv_style_t numberBig_style;

void particle_gui_init(void) // style init
{
    if (particle_scr == lv_scr_act())
        return;
    particle_scr = lv_obj_create(NULL);

    lv_style_init(&default_style); // 背景
    lv_style_set_bg_color(&default_style, lv_color_hex(0x000000));
    lv_obj_add_style(particle_scr, &default_style, LV_STATE_DEFAULT);
}


void particle_gui_del(void)
{
    if (NULL != particle_scr)
    {
        lv_obj_clean(particle_scr);
        particle_scr = NULL;
    }
    // 手动清除样式，防止内存泄漏
    // lv_style_reset(&default_style);
}