/*
  MIT License

  Copyright (c) 2017 M5Stack

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
/*
*******************************************************************************
* Copyright (c) 2022 by M5Stack
*                  Equipped with M5Core sample source code
*                          配套  M5Core 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/gray
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/gray
*
* Describe: Button_Two.  双按键
* Date: 2021/8/9
******************************************** ***********************************
  Please connect to Port B(36、26),Read the button status of BUTTON Unit and
display it on the screen 请连接端口B(36、26),读取按键的状态并在显示屏上显示 if
you don't have M5GO BOTTOM, you need change the pinMode and the digitalRead to
22、21, But you will not be able to use any I2C operations. 如果你没有M5GO
BOTTOM，你需要改变pinMode和digitalRead到22,21,但是你将不能使用任何I2C操作.
*/

#include <M5Stack.h>
#define SIZE  6

int buttons[SIZE];
int cur_values[SIZE];
int last_values[SIZE];

void setupMslHandInterface(int *pin_list){
  M5.begin();        // Init M5Stack.  初始化M5Stack
  M5.Power.begin();  // Init power  初始化电源模块
  for(int i=0; i< SIZE; i++){
    pinMode(pin_list[i], INPUT);  // set pin mode to input.设置引脚模式为输入模式
  }
  M5.Lcd.setTextColor(
                      YELLOW);  // Set the font color to yellow.  设置字体颜色为黄色
  M5.Lcd.setTextSize(2);  // Setting the Font size.  设置字号大小
  M5.Lcd.setCursor(
                   80, 0);  // Set the cursor position to (80,0).  将光标位置设置为(80,0)
  M5.Lcd.println("MSL HAND INTERFACE");
  M5.Lcd.setTextColor(WHITE);
}

void readMslHandInterface(int *pin_list){
  for(int i=0; i< SIZE; i++){
    cur_values[i] = digitalRead(pin_list[i]);
    buttons[i] = cur_values[i];
  }
}

void displayMslHandInterface() {
  M5.Lcd.setCursor(20, 25);
  M5.Lcd.print("Btn. 1 2 3 4 5 6");
  M5.Lcd.setCursor(0, 45);
  M5.Lcd.print("Value: ");

  for (int i =0; i < SIZE; i++){
    if(cur_values[i] != last_values[i]){
      M5.Lcd.fillRect(20*(i+1)+ 100, 45, 25, 40,
                    BLACK);  // Draw a black rectangle 75 by 85 at (85,45).
    // 在(85,45)处绘制宽75,高85的黑色矩形
      if (cur_values[i] == 0) {
        M5.Lcd.setCursor(25*(i+1)+ 100, 45);
        M5.Lcd.print("0");  // display the statusn
      } else {
        M5.Lcd.setCursor(25*(i+1)+ 100, 45);
        M5.Lcd.print("1");  // display the status
      }
      last_values[i] = cur_values[i];
    }
  }
}
