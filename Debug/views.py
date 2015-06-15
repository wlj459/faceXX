# -*- coding: utf-8 -*-

import json
import requests
from StringIO import StringIO
from PIL import Image
import os


url = str(raw_input("Please enter an url for your photo:"))  # 待处理图片url
url2 = str(raw_input("Please enter an url for your model:"))  # 模板图片url
url3 = str(raw_input("Please enter an url for your model2"))  # 抹掉表情的模板图片url
r = requests.get(url=url)
image = Image.open(StringIO(r.content))
detection = 'http://apicn.faceplusplus.com/v2/detection/detect?api_key=9541192d36509866997b794b00f40d78&api_secret=eYpecBbIb3mXm-xjIGt5vTT9ZARgoFme&url={url}&attribute=glass,pose,gender,age,race,smiling'.format(url=url2)
result = requests.get(url=detection)
result = json.loads(result.text)
face = result["face"][0]
height = float((face["position"]["mouth_left"]["y"]-face["position"]["eye_left"]["y"])*result["img_height"])
width = float((face["position"]["mouth_right"]["x"]-face["position"]["mouth_left"]["x"])*result["img_width"])
real_height = result["img_height"]
result = image.result(url=url, model_width=width, model_height=height, real_height=real_height)

command = "test1.exe"
os.system(command)
result = Image.open("11.jpg")
img1 = Image.open(StringIO(requests.get(url=url3).content)).paste(result, None, result)
img1.save('123.jpg')

def result(self, url, model_width, model_height, real_height):
    """
    识别人脸并切割五官
    :return: 切割结果 img
    """
    detection = 'http://apicn.faceplusplus.com/v2/detection/detect?api_key=9541192d36509866997b794b00f40d78&api_secret=eYpecBbIb3mXm-xjIGt5vTT9ZARgoFme&url={url}&attribute=glass,pose,gender,age,race,smiling'.format(url=url)
    result = requests.get(url=detection)
    result = json.loads(result.text)f
    height = result["img_height"]
    width = result["img_width"]
    face = result["face"][0]
    face_id = face["face_id"]
    resize_time = float((face["position"]["mouth_right"]["x"]-face["position"]["mouth_left"]["x"])*width)/model_width
    resize_time2 = float((face["position"]["mouth_left"]["y"]-face["position"]["eye_left"]["y"])*height)/model_height
    photo_url = 'http://apicn.faceplusplus.com/v2/detection/landmark?api_key=9541192d36509866997b794b00f40d78&api_secret=eYpecBbIb3mXm-xjIGt5vTT9ZARgoFme&face_id={face_id}&type=83p'.format(face_id=face_id)
    r = requests.get(photo_url)
    r = json.loads(r.text)
    landmarks = r["result"][0]["landmark"]
    high = landmarks["mouth_lower_lip_bottom"]["y"]+2
    low = 100
    right = 0
    left = 100
    for k in landmarks.keys():
        if landmarks[k]["x"] > right:
            right = landmarks[k]["x"]
        if landmarks[k]["x"] < left:
            left = landmarks[k]["x"]
        if landmarks[k]["y"] < low:
            low = landmarks[k]["y"]
    # print left, low, right, high
    # region = (int(left*width/100), 0, int((right-left)*width/100), int(height))
    region = (int(left*width/100), int(low*height/100), int(right*width/100), int(high*height/100))
    # print region
    img = self._image.crop(region)
    img = img.resize(((float(img.size[0]*resize_time)/float(img.size[1]*resize_time2))*real_height, real_height), Image.ANTIALIAS)
    img.save('1.jpg')
    return img
