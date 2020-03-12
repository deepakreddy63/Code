#!/usr/bin/env python3

## To experiment with canny edge detection
## 01/16/2020
import cv2
import numpy as np

image = cv2.imread('/home/deepak/CARLA/sc_old/Images/savedImage384.jpg')

print(np.array(image).shape)
cv2.imshow("Image0", image)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

gray = cv2.bilateralFilter(gray, 11, 17, 17)
edged = cv2.Canny(gray, 30, 200)
cv2.imshow("Image1", edged)
cv2.waitKey(0)

