# -*- coding: UTF-8 -*-
import numpy as np
import cv2
import os

Const_Image_Format = [".jpg",".jpeg",".bmp",".png"]
fileList = [""]
img_rgb = cv2.imread('a.png')
img_gray = cv2.cvtColor(img_rgb, cv2.COLOR_BGR2GRAY)
dirr = "/root/Desktop"
for s in os.listdir(dirr):
            newDir = os.path.join(dirr,s)
            if os.path.isfile(newDir):
                if newDir and(os.path.splitext(newDir)[1] in Const_Image_Format):
                    fileList.append(newDir)
print fileList 
for k in fileList:
    template = cv2.imread(k,0)

w, h = template.shape[::-1]
res = cv2.matchTemplate(img_gray,template,cv2.TM_CCOEFF_NORMED)
print res
threshold = 0.8

loc = np.where( res >= threshold)
for pt in zip(*loc[::-1]):
    cv2.rectangle(img_rgb, pt, (pt[0] + w, pt[1] + h), (0,0,255), 2)
cv2.imwrite('res.png',img_rgb)
