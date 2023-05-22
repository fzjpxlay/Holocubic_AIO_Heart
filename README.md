# HoloCubic_AIO_Heart

原作者的项目链接 https://github.com/peng-zhihui/HoloCubic
本项目基于的代码 https://github.com/ClimbSnail/HoloCubic_AIO

增加了番茄时钟功能以及一个动态的心的APP

番茄时钟APP项目链接 https://github.com/kylefjl/HoloCubic_AIO_TOMATO
动态的心的灵感来源 https://openprocessing.org/sketch/1906399

## 代码说明

动态的心的APP文件夹在/src/app/particle内，
动态的心的实时演算代码在/src/app/idea_anim/ui_animation.cpp内, 第588行到674行
主要实现方法是在心形范围外添加一个向内的力，力的大小由到心形的距离决定
心形的范围由极坐标下的心形函数计算得到，具体公式为：
$$R^2=1/1-abs(cos(/theta))*sin(/theta)$$