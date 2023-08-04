import os, tf
from pyb import LED
from machine import UART
import utime
import seekfree
import math
import sensor, image, time

uart_num = 0

red_point_threshold = [(62, 100, -15, 127, 19, 127)]
green_point_threshold = [(89, 100, -77, -13, -67, 127)]
rectangle_threshold = [(60, 67, 6, 55, -56, -24)]

day_brightness = 1000
uart = UART(1, baudrate=115200) #串口



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
    sensor.set_auto_gain(False)
    sensor.set_auto_whitebal(False,(0,0,0))


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
            green_blobs = img.find_blobs(green_point_threshold, pixels_threshold=2, area_threshold=15, margin=1, merge=True, invert=0)
            if green_blobs:
                for blob in green_blobs:
                    green_x = blob.cx()
                    green_y = blob.cy()
                    img.draw_rectangle(blob.rect(), color=(255, 0, 0), scale=2, thickness=2)
                    break  # If you want to consider only one green blob, you can break the loop here

            red_blobs = img.find_blobs(red_point_threshold, pixels_threshold=2, area_threshold=15, margin=1, merge=True, invert=0)
            if red_blobs:
                for blob in red_blobs:
                    red_x = blob.cx()
                    red_y = blob.cy()
                    img.draw_rectangle(blob.rect(), color=(0, 255, 0), scale=2, thickness=2)
                    break  # If you want to consider only one red blob, you can break the loop here

            if green_blobs and red_blobs:

                img.draw_line(green_x, green_y, red_x, red_y, color=(0, 0, 255))
                print(green_x - red_x, green_y - red_y)



def sort_points(corners):
    # Step 1: Find the center
    center = [sum([corner[0] for corner in corners]) / 4, sum([corner[1] for corner in corners]) / 4]

    # Step 2: Sort by angle
    corners_list = list(corners)
    corners_list.sort(key=lambda point: math.atan2(point[1] - center[1], point[0] - center[0]))

    return tuple(corners_list) # convert list back to tuple after sorting



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
            for r in img.find_rects(threshold = 30000):
                img.draw_rectangle(r.rect(), color = (255, 0, 0))   # 绘制红色矩形框
                img_x=(int)(r.rect()[0]+r.rect()[2]/2)              # 图像中心的x值
                img_y=(int)(r.rect()[1]+r.rect()[3]/2)              # 图像中心的y值
                img.draw_circle(img_x, img_y, 5, color = (0, 255, 0)) # 给矩形中心绘制一个小圆 便于观察矩形中心是否识别正确
                corners = r.corners()
                sorted_corners = sort_points(corners)
                for corner in corners:
                    img.draw_circle(corner[0], corner[1], 2, color=(0, 255, 0))


                x0, y0 = sorted_corners[0]
                x1, y1 = sorted_corners[1]
                x2, y2 = sorted_corners[2]
                x3, y3 = sorted_corners[3]

                print(x0,y0,x1,y1,x2,y2,x3,y3)

                uart.write("A")  # 发送包头

                uart.write("%c" % (x0))
                uart.write("%c" % (y0))
                uart.write("%c" % (x1))
                uart.write("%c" % (y1))
                uart.write("%c" % (x2))
                uart.write("%c" % (y2))
                uart.write("%c" % (x3))
                uart.write("%c" % (y3))


                uart.write("Y")  # 发送包尾

                print(x0,y0,x1,y1,x2,y2,x3,y3)
                find_flag = 0
                break
                #img.draw_circle(r.cx(), r.cy(), 5, color=(0, 255, 0))




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
        #Tracking_point()
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
                find_rectangle()









if __name__ == '__main__':
    main()
