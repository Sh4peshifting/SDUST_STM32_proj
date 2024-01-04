# Face recognition with LBP descriptors.
# See Timo Ahonen's "Face Recognition with Local Binary Patterns".
#
# Before running the example:
# 1) Download the AT&T faces database http://www.cl.cam.ac.uk/Research/DTG/attarchive/pub/data/att_faces.zip
# 2) Exract and copy the orl_faces directory to the SD card root.


import sensor, time, image, pyb

import sensor, image, time, math
from pyb import UART
import json

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # or sensor.GRAYSCALE
sensor.set_framesize(sensor.B128X128) # or sensor.QQVGA (or others)
sensor.set_windowing((92,112))
sensor.skip_frames(10) # Let new settings take affect.
sensor.skip_frames(time = 5000) #等待5s

uart = UART(3, 115200,timeout_char=10000)
uart.init(115200, bits=8, parity=None, stop=1)

#SUB = "s1"
NUM_SUBJECTS = 1 #图像库中不同人数，一共6人
NUM_SUBJECTS_IMGS = 10 #每人有20张样本图片

# 拍摄当前人脸。
img = None
pmin = 999999
num=0

img_data = bytearray([0x0f,0x00])#串口函数打包

def min(pmin, a, s):
    global num
    if a<pmin:
        pmin=a
        num=s
    return pmin

while(True):
    img = sensor.snapshot()
    #img = image.Image("face/%s/1.pgm"%(SUB))
    d0 = img.find_lbp((0, 0, img.width(), img.height()))
    #d0为当前人脸的lbp特征
    for s in range(1, NUM_SUBJECTS+1):
        dist = 0
        for i in range(2, NUM_SUBJECTS_IMGS+1):
            img = image.Image("face/s%d/%d.pgm"%(s, i))
            d1 = img.find_lbp((0, 0, img.width(), img.height()))
            #d1为第s文件夹中的第i张图片的lbp特征
            dist += image.match_descriptor(d0, d1)#计算d0 d1即样本图像与被检测人脸的特征差异度。
        print("Average dist for subject %d: %d"%(s, dist/NUM_SUBJECTS_IMGS))
        pmin = dist/NUM_SUBJECTS_IMGS
        print(pmin)
        if(pmin < 8200):
            img_data = bytearray([0x0f,0x01])#串口函数打包
        else:
            img_data = bytearray([0x0f,0x00])#串口函数打包
        print(img_data)
    print(num) # num为当前最匹配的人的编号。
    uart.write(img_data)
