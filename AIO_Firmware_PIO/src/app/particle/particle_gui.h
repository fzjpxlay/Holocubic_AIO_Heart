#ifndef APP_PARTICLE_GUI_H
#define APP_PARTICLE_GUI_H

#ifdef __cplusplus
extern "C"
{
#endif


#include "lvgl.h"
#define ANIEND                      \
    while (lv_anim_count_running()) \
        lv_task_handler(); //等待动画完成

    void particle_gui_init(void);
    void particle_gui_del(void);

#ifdef __cplusplus
} /* extern "C" */
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"
    extern const lv_img_dsc_t loveIcon;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif