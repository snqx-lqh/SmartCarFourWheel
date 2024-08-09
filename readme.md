## 项目说明

基于STM32F103RCT6的电机控制板，开始使用的PT2470，结果发现电机输出有部分问题，后面改成TB6612设计，但是还是将PT2470的代码放在了这里。该项目使用的是标准库搭建的项目。

3D打印件 文件夹存放搭建的一个架子

Code就是主要的代码

Hardware 该文件夹存放了立创EDA导出的原理图和PCB

## 硬件设计

3D渲染图

![image-20240809113221529](F:\Project\SmartCarFourWheel\img\readme\image-20240809113221529.png)

实物图

![image-20240809113044950](F:\Project\SmartCarFourWheel\img\readme\image-20240809113044950.png)

主控：STM32F103RCT6

电机驱动芯片：TB6612

