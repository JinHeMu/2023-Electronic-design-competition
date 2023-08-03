import os, tf
from pyb import LED
from machine import UART
import utime
import math
import sensor, image, time

uart_num = 0

#red_point_threshold = [(24, 100, 5, 127, -128, 127)]
#green_point_threshold = [(29, 100, -128, 1, -128, 127)]
#rectangle_threshold = [(60, 67, 6, 55, -56, -24)]


red_point_threshold = [(21, 100, 18, 127, -128, 127)]
green_point_threshold = [(36, 100, -128, 12, -128, 127)]
rectangle_threshold = [(60, 67, 6, 55, -56, -24)]


day_brightness = 100
uart = UART(2, baudrate=115200) #串口



#139,189
#236,85


corner1 = [139,189]
corner2 = [236,189]
corner3 = [236,85]
corner4 = [139,85]

#openart初始化
def openart_init():

    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.set_brightness(day_brightness)
    sensor.skip_frames(20)
    #sensor.set_auto_gain(True)
    #sensor.set_auto_whitebal(False,(0,0,0))


def find_point_red():
    recognize_flag = 1

    while recognize_flag:
        img = sensor.snapshot()
        uart_num = uart.any()  # 获取当前串口数据数量
        if uart_num != 0:
            recognize_flag = 0
            break
        else:
            for b in img.find_blobs(red_point_threshold, pixels_threshold=2, area_threshold=15, margin=1, merge=True,
                                    invert=0):
                img.draw_rectangle(b.rect(), color=(0, 255, 0), scale=2, thickness=2)

def find_point_green():
    recognize_flag = 1

    while recognize_flag:
        img = sensor.snapshot()
        uart_num = uart.any()  # 获取当前串口数据数量
        if uart_num != 0:
            recognize_flag = 0
            break
        else:
            for b in img.find_blobs(green_point_threshold, pixels_threshold=2, area_threshold=15, margin=1, merge=True,
                                    invert=0):
                img.draw_rectangle(b.rect(), color=(255, 0, 0), scale=1, thickness=2)
            for b in img.find_blobs(red_point_threshold, pixels_threshold=50, area_threshold=50, margin=1, merge=True,
                                    invert=0):
                img.draw_rectangle(b.rect(), color=(0, 255, 0), scale=1, thickness=2)



def Tracking_point():
    Tracking_point_flag = 1

    while Tracking_point_flag:
        red_x = 0
        red_y = 0
        green_x = 0
        green_y = 0
        img = sensor.snapshot()
        uart_num = uart.any()  # 获取当前串口数据数量
        if uart_num != 0:
            Tracking_point_flag = 0
            break
        else:
            green_blobs = img.find_blobs(green_point_threshold, pixels_threshold=2, area_threshold=5, margin=1, merge=True, invert=0)
            if green_blobs:
                for blob in green_blobs:
                    green_x = blob.cx()
                    green_y = blob.cy()

                    break  # If you want to consider only one green blob, you can break the loop here

            red_blobs = img.find_blobs(red_point_threshold, pixels_threshold=2, area_threshold=5, margin=1, merge=True, invert=0)
            if red_blobs:
                for blob in red_blobs:
                    red_x = blob.cx()
                    red_y = blob.cy()

                    break  # If you want to consider only one red blob, you can break the loop here

            if green_blobs and red_blobs:

                dis_x = red_x - green_x
                dis_y = red_y - green_y
                img.draw_line(green_x, green_y, red_x, red_y, color=(0, 0, 255))


                if dis_x < -64:
                    dis_x = -64
                if dis_x > 64:
                    dis_x = 64
                if dis_y < -64:
                    dis_y = -64
                if dis_y > 64:
                    dis_y = 64
                print("disx:%d,disy:%d\n" % (dis_x,dis_y))

                uart.write("A")  # 发送包头
                if(dis_x < 0):
                    uart.write("%c" % 1)
                else :
                    uart.write("%c" % 0)
                if(dis_y < 0):
                    uart.write("%c" % 1)
                else :
                    uart.write("%c" % 0)
                uart.write("%c" % (abs(dis_x)))
                uart.write("%c" % (abs(dis_y)))

                uart.write("Y")  # 发送包尾


def find_rectangle():


    find_flag = 1

    global uart_num

    while find_flag:
        uart_num = uart.any()  # 获取当前串口数据数量
        img = sensor.snapshot()

        if uart_num != 0:
            find_flag = 0
            break
        else:
            for r in img.find_rects(threshold = 20000):
                img.draw_rectangle(r.rect(), color = (255, 0, 0))   # 绘制红色矩形框
                img_x=(int)(r.rect()[0]+r.rect()[2]/2)              # 图像中心的x值
                img_y=(int)(r.rect()[1]+r.rect()[3]/2)              # 图像中心的y值
                img.draw_circle(img_x, img_y, 5, color = (0, 255, 0)) # 给矩形中心绘制一个小圆 便于观察矩形中心是否识别正确
                corners = r.corners()
                point_corners = tuple(sorted(corners))
                for corner in corners:
                    img.draw_circle(corner[0], corner[1], 5, color=(0, 255, 0))

                x0, y0 = point_corners[3]
                x1, y1 = point_corners[2]
                x2, y2 = point_corners[1]
                x3, y3 = point_corners[0]


                print(x0,y0,x1,y1,x2,y2,x3,y3)


                #img.draw_circle(r.cx(), r.cy(), 5, color=(0, 255, 0))


def find_boundary():


    find_boundary = 1

    global uart_num

    while find_boundary:
        uart_num = uart.any()  # 获取当前串口数据数量
        img = sensor.snapshot()

        if uart_num != 0:
            find_boundary = 0
            break
        else:
            # corner1 = [139,189]
            # corner2 = [236,189]
            # corner3 = [236,85]
            # corner4 = [139,85]
            for b in img.find_blobs(red_point_threshold, pixels_threshold=50, area_threshold=50, margin=1, merge=True,
                                invert=0):
                img.draw_rectangle(b.rect(), color=(0, 255, 0), scale=1, thickness=2)
            img.draw_line(corner1[0], corner1[1], corner2[0], corner2[1], color=(0, 255, 0))
            img.draw_line(corner2[0], corner2[1], corner3[0], corner3[1], color=(0, 255, 0))
            img.draw_line(corner3[0], corner3[1], corner4[0], corner4[1], color=(0, 255, 0))
            img.draw_line(corner4[0], corner4[1], corner1[0], corner1[1], color=(0, 255, 0))



def main():
    openart_init()

    while(True):
        img = sensor.snapshot()
        Tracking_point()
        #find_point_green()
        #find_point_red()
        #find_rectangle()
        #find_boundary()
        uart_num = uart.any()
        if (uart_num):
            uart_str = uart.read(uart_num).strip()
            if(uart_str.decode() == "A"):
                print("A")
                uart_num=0
                find_point_red()







if __name__ == '__main__':
    main()
