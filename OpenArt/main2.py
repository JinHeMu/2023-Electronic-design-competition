import os, tf
from pyb import LED
from machine import UART
import utime
import seekfree
import math
import sensor, image, time


uart = UART(2, baudrate=115200) # 串口

lcd = seekfree.LCD180(2)#显示屏
lcd.full()

#晚上阈值（需要调试！！！）
card_threshold = [(28, 100, -128, 127, -128, 127)]#色块检测阈值
day_brightness = 50

card_w = 80
card_h = 80


def openart_init():
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.set_brightness(day_brightness)
    sensor.skip_frames(20)
    sensor.set_auto_gain(False)
    sensor.set_auto_whitebal(False, (0, 0, 0))




#如果使用色块
#如果使用目标检测

# 判断一个卡片是否为新卡片
def is_new_card(card_center, last_card_center):
    # 设置阈值
    threshold = 20

    # 如果这是第一次检测到卡片，那么就认为这是一个新的卡片
    if last_card_center is None:
        return True

    # 检查卡片的位置是否与上一次检测到的卡片的位置足够接近
    dx = card_center[0] - last_card_center[0]
    dy = card_center[1] - last_card_center[1]
    distance = (dx**2 + dy**2)**0.5

    # 如果足够接近，那么就认为这不是一个新的卡片
    if distance < threshold:
        return False

    # 如果不足够接近，那么就认为这是一个新的卡片
    return True




# 存储最近一次检测到的卡片的位置
last_card_center = None

def object_detect():
    global last_card_center  # 用 global 关键字来在函数内部访问全局变量
    detect_flag = 1

    while detect_flag:
        uart_num = uart.any()  # 获取当前串口数据数量
        img = sensor.snapshot()
        lcd.show_image(img, 320, 240, zoom=2)
        if uart_num != 0:
            detect_flag = 0
            break
        else:
            for b in img.find_blobs(card_threshold, pixels_threshold=400, area_threshold=400, margin=1, merge=True,
                                    invert=0):
                #if b.w() < card_w and b.h() < card_h:  # 判断色块的大小，来确定是否是卡片参数需要调整
                    # 得到卡片的中心点坐标
                card_center = (b.cx(), b.cy())

                # 判断这个卡片是否为新卡片
                if is_new_card(card_center, last_card_center):
                    # 如果是新卡片，将它的位置存储为最新的位置
                    last_card_center = card_center

                    # 发送数据
                    uart.write("C")
                    uart.write("%c" % 1)  # 找到卡片发送1
                    uart.write("D")
                    print("find new card!!!")
                    lcd.show_image(img, 160, 120, zoom=0)
                    detect_flag = 0
                    break
                else:
                    continue





def picture_correct():

    dis_X = 0
    dis_Y = 0
    distance = 0
    correct_flag = 1

    global uart_num

    while correct_flag:
        uart_num = uart.any()  # 获取当前串口数据数量
        img = sensor.snapshot()

        if uart_num != 0:
            correct_flag = 0
            break
        else:
            closest_distance = float('inf')
            closest_blob = None

            for b in img.find_blobs(card_threshold, pixels_threshold=400, area_threshold=400, margin=1, merge=True,
                                     invert=0):
                corners = b.min_corners()
                point_corners = tuple(sorted(corners))
                for corner in corners:
                    img.draw_circle(corner[0], corner[1], 5, color=(0, 255, 0))
                x0, y0 = point_corners[3]
                x1, y1 = point_corners[2]
                x3, y3 = point_corners[0]

                len1 = (x0 - x1) ** 2 + (y0 - y1) ** 2
                len2 = (x1 - x3) ** 2 + (y1 - y3) ** 2

                if x1 == x0:
                    q = 0
                else:
                    q = math.atan((x1 - x0) / (y1 - y0))

                q = int(q * 60)

                img.draw_circle(b.cx(), b.cy(), 5, color=(0, 255, 0))
                dis_X = b.cx() - 166
                dis_Y = b.cy() - 174#（可能需要调试，测试一下是否在中心位置）

                if dis_X < -64:
                    dis_X = -64
                if dis_X > 64:
                    dis_X = 64
                if dis_Y < -64:
                    dis_Y = -64
                if dis_Y > 64:
                    dis_Y = 64

                distance = math.sqrt((dis_X ** 2) + (dis_Y ** 2))

                # 更新最近的色块
                blob_center = (b.cx(), b.cy())
                current_distance = math.sqrt((blob_center[0] - 160) ** 2 + (blob_center[1] - 200) ** 2)
                if current_distance < closest_distance:
                    closest_distance = current_distance
                    closest_blob = b

            # 绘制最近色块的标记或线条
            if closest_blob is not None:
                img.draw_circle(closest_blob.cx(), closest_blob.cy(), 5, color=(0, 255, 0))
                img.draw_line(160, 240, closest_blob.cx(), closest_blob.cy(), color=(255, 0, 0))
                img.draw_string(10, 10, "closest distance: {}".format(closest_distance), (255, 0, 0))
                lcd.show_image(img, 160, 120, zoom=0)
                print("disx:%d , disy:%d, angle:%d" % (dis_X, -dis_Y, q))
                uart.write("C")
                uart.write("%c" % dis_X)
                uart.write("%c" % -dis_Y)
                if distance < 5 :
                    uart.write("%c" % 1)
                    correct_flag = 0
                else:
                    uart.write("%c" % 0)
                uart.write("D")
            else:
                lcd.show_image(img, 320, 240, zoom=2)
                continue










def main():
    openart_init()



    while True:
        img = sensor.snapshot()
        #object_detect()
        picture_correct()

        uart_num = uart.any()  # 鑾峰彇褰撳墠涓插彛鏁版嵁鏁伴噺
        if uart_num:
            uart_str = uart.read(uart_num).strip()  # 璇诲彇涓插彛鏁版嵁
            print(uart_str.decode())
            if uart_str.decode() == "F":
                print("F")
                uart_num = 0
                object_detect()
            elif(uart_str.decode() == "B"):
                print("B")
                uart_num=0
                picture_correct()

        else:
            lcd.show_image(img, 320, 240, zoom=2)

if __name__ == '__main__':
    main()
