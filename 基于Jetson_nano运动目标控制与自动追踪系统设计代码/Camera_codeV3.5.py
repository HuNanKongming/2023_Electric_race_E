# -*- coding: UTF-8 -*-
import cv2
import numpy as np
import serial
import time
scaled_path = []  # 在循环之外定义 scaled_path
print("2024_Electronic_E Program")
# print("NVIDIA Jetson Nano Developer Kit")
serial_port = serial.Serial(
    port="/dev/ttyTHS1",
    baudrate=115200,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
)
time.sleep(1)

def extract_path(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)#灰度化,首先，将输入的彩色图像转换为灰度图像。这是因为灰度图像只包含亮度信息，而不包含颜色信息，使得后续处理更加简单。
    # cv2.imshow('gray', gray)
    _, threshold = cv2.threshold(gray, 20, 255, cv2.THRESH_BINARY_INV)#阈值化,使用固定阈值将灰度图像二值化，将像素值高于阈值的设置为白色（255），低于阈值的设置为黑色（0）。这样可以将图像中的路径与背景分离出来。
    # cv2.imshow('threshold', threshold)
    kernel = np.ones((5, 5), np.uint8)#闭运算,对二值图像进行闭运算，这个操作可以填充路径中的小空洞，并消除路径中的细小断裂。
    closing = cv2.morphologyEx(threshold, cv2.MORPH_CLOSE, kernel, iterations=3)
    # cv2.imshow('closing', closing)
    kernel = np.ones((3, 3), np.uint8)
    erosion = cv2.erode(closing, kernel, iterations=1)#腐蚀,对闭运算后的图像进行腐蚀操作，这有助于去除图像中的噪声，并使得路径的边缘更加平滑。
    # cv2.imshow('erosion', erosion)
    contours, hierarchy = cv2.findContours(erosion, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)#轮廓检测使用轮廓检测算法找到图像中的所有外部轮廓。这些轮廓将代表路径的形状。
    if len(contours) > 0:#选择最大轮廓如果找到了轮廓，则选择最大的轮廓作为路径的表示。这个最大轮廓通常是路径所在的主要区域。
        contours = sorted(contours, key=cv2.contourArea, reverse=True)
        max_contour = contours[0]
        second_max_contour = contours[1] if len(contours) > 1 else None
        image_height, image_width = image.shape[:2]
        x, y, w, h = cv2.boundingRect(max_contour)
        if x == 0 or y == 0 or x + w == image_width or y + h == image_height:
            if second_max_contour is not None:
                max_contour = second_max_contour
            else:
                return None
        epsilon = 0.01 * cv2.arcLength(max_contour, True)#轮廓近似,对最大轮廓进行多边形近似，以减少轮廓中的顶点数量。这有助于降低后续处理的复杂度。
        approx_contour = cv2.approxPolyDP(max_contour, epsilon, True)
        path = []#提取路径点,将近似后的轮廓顶点坐标提取出来，组成路径点的列表。
        for point in approx_contour:#返回路径
            path.append(tuple(point[0]))
        return path
        return None
# 这个函数的作用是对输入的点集进行插值，以获得更密集的点集。
def interpolate_points(points):
    interpolated_points = []
    for i in range(len(points)):#循环遍历点集：这个循环用于遍历输入的点集中的每一个点。
        start_point = points[i]
        end_point = points[(i + 1) % len(points)]
        dx = end_point[0] - start_point[0]
        dy = end_point[1] - start_point[1]
        distance = 3
        for j in range(distance):
            x = start_point[0] + int(dx * j / distance)
            y = start_point[1] + int(dy * j / distance)
            interpolated_points.append((x, y))
    return interpolated_points
# 这个函数是用来检测图像中的红色和绿色激光点。
def detect_lasers(image):
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)#将图像转换为 HSV 色彩空间（色相、饱和度、亮度）：这个步骤将图像从 BGR（蓝、绿、红）色彩空间转换为 HSV 色彩空间，其中红色和绿色更容易被分离。
    lower_red = np.array([126, 0, 170])#定义红色和绿色的阈值范围：
    upper_red = np.array([255, 255, 255])
    lower_green = np.array([60, 11, 238])
    upper_green = np.array([95, 255, 255])
    mask_red = cv2.inRange(hsv, lower_red, upper_red)#通过应用阈值获得红色和绿色激光的掩模：这些操作根据定义的阈值范围，将图像中符合条件的像素设置为白色，不符合条件的像素设置为黑色。
    mask_green = cv2.inRange(hsv, lower_green, upper_green)
    kernel = np.ones((5, 5), np.uint8)#使用形态学操作（闭运算）来去除图像中的噪声：
    mask_red = cv2.morphologyEx(mask_red, cv2.MORPH_CLOSE, kernel)
    mask_green = cv2.morphologyEx(mask_green, cv2.MORPH_CLOSE, kernel)
    cv2.imshow('mask_red', mask_red)
    cv2.imshow('mask_green', mask_green)
    contours_red, _ = cv2.findContours(mask_red, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)#找到红色和绿色激光点的轮廓：
    contours_green, _ = cv2.findContours(mask_green, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    red_laser_coords = None
    green_laser_coords = None
    max_area_red = 0
    for contour in contours_red:#计算轮廓的面积并找到最大面积的轮廓，从而确定激光点的位置：
        area = cv2.contourArea(contour)
        if area > max_area_red:
            max_area_red = area
            M = cv2.moments(contour)
            if M["m00"] != 0:
                cX = int(M["m10"] / M["m00"])
                cY = int(M["m01"] / M["m00"])
                red_laser_coords = (cX, cY)
    max_area_green = 0
    for contour in contours_green:
        area = cv2.contourArea(contour)
        if area > max_area_green:
            max_area_green = area
            M = cv2.moments(contour)
            if M["m00"] != 0:
                cX = int(M["m10"] / M["m00"])
                cY = int(M["m01"] / M["m00"])
                green_laser_coords = (cX, cY)
    return red_laser_coords, green_laser_coords#返回红色和绿色激光点的坐标：

frame = cv2.VideoCapture(0)
# 设置摄像头分辨率（这里设置为 640x480）
frame.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
frame.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
start_time = time.time()  # 记录开始时间
frame_count = 0  # 初始化帧计数器
mode = 0
data_array2 = []  # 初始化一个空列表
while frame.isOpened():
    ret,img = frame.read()
    if not ret:#如果无法读取下一帧，则退出循环。
        break
    image_height, image_width = img.shape[:2]
    # 计算感兴趣区域的左上角和右下角坐标
    roi_size = min(image_height, image_width) // 2  # 使用图像的最小尺寸的一半作为感兴趣区域的大小
    x = (image_width - roi_size) // 2  # 感兴趣区域左上角的 x 坐标
    y = (image_height - roi_size) // 2  # 感兴趣区域左上角的 y 坐标
    # 截取感兴趣区域
    roi = img[y:y + roi_size, x:x + roi_size]
    # cv2.imshow('roi', roi)
    # 在感兴趣区域绘制一个方框
    img_copy = img.copy()
    cv2.rectangle(img_copy, (x, y), (x + roi_size, y + roi_size), (0, 255, 0), 2)
    # cv2.imshow('img_raw', img_copy)
    # 接下来进行路径提取的代码...
    path = extract_path(roi)  # 使用 extract_path() 函数从图像中提取路径。如果成功提取了路径，则返回路径的坐标。
    canvas = np.zeros_like(roi)  # 创建一个与输入图像相同大小的黑色画布
    result = cv2.addWeighted(roi, 0.7, canvas, 0.3, 0)
    if path is not None:  # 检查是否成功提取了路径。
        long_path = interpolate_points(scaled_path)  # 使用 interpolate_points() 函数对缩放后的路径进行插值，以获得更多的路径点
        if mode == 1:
            for point in path:  # 对提取的路径中的每个点进行迭代。#在循环内部，你将路径中的最左侧点、最右侧点、中间点以及路径的中心点进行了计算，并将它们用于缩放路径。
                leftmost = min(path, key=lambda x: x[0])
                rightmost = max(path, key=lambda x: x[0])
                middle_x = int((leftmost[0] + rightmost[0]) / 2)
                middle_y = int((leftmost[1] + rightmost[1]) / 2)
                middle_point = (middle_x, middle_y)
                center_x = int(sum([point[0] for point in path]) / len(path))
                center_y = int(sum([point[1] for point in path]) / len(path))
                center_point = (center_x, center_y)
                cv2.circle(canvas, center_point, 5, (0, 255, 0), -1)
                scale_factor = 0.94
                scaled_path = []  # 确保在每次处理新帧时清空scaled_path，这样您就不会在每个新帧中保留之前帧的路径点。
                data_array2_str = ""
                for point in path:  # 存储了缩放后的路径点。
                    scaled_x = int(center_x + scale_factor * (point[0] - center_x))
                    scaled_y = int(center_y + scale_factor * (point[1] - center_y))
                    scaled_path.append((scaled_x, scaled_y))
                    result = cv2.addWeighted(roi, 0.7, canvas, 0.3, 0)
                    cv2.drawContours(result, [np.array(scaled_path)], -1, (0, 255, 0), 2)# 将路径绘制在图像上
                    data_array = []
                    data_array2 = []  # 初始化一个空列表
                    for point in long_path:  # 在内部循环中，你生成了路径点的数据，用于后续处理。
                        cv2.circle(result, point, 5, (0, 0, 255), -1)
                        ZB_num = 0
                        time2 = 0
                        for coordinate in long_path:
                            x = str(coordinate[0]).zfill(3)
                            y = str(coordinate[1]).zfill(3)
                            num = str(ZB_num).zfill(2)
                            time2 += 1
                            ZB_num = ZB_num + 1
                            data = f"${num},{x},{y}@"
                            cv2.putText(result, num, (coordinate[0] - 10, coordinate[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
                            if time2 <= 12:
                                data_array2.append([x, y])
                                data_array.append(data)
                        data_array2_str = "#{},{},{},{},{},{},{},{},$".format(data_array2[0][0],data_array2[0][1],data_array2[3][0],data_array2[3][1],data_array2[6][0],data_array2[6][1],data_array2[9][0],data_array2[9][1])
            print(data_array2_str)
            serial_port.write(data_array2_str.encode())
            data_array_unique = sorted(
                set(data_array))  # data_array 是一个存储数据的列表，set(data_array) 将列表转换为集合，这样可以去除重复的元素，然后 sorted() 函数对去除重复元素后的集合进行排序，最终得到一个按升序排列的唯一值列表 data_array_unique。这样做的目的是确保数据在进行进一步处理之前是唯一的，并且以有序的方式出现。
            print("黑色胶布坐标:",end='')
            print(data_array_unique)
            # 清空原始数组
            data_array = []
            # 显示图像Q
        if mode == 2:
            red_coords, green_coords = detect_lasers(roi)
            # 处理红激光点
            if red_coords is not None:
                cX, cY = red_coords
                # cv2.circle(roi, (cX, cY), 7, (0, 0, 255), -1)
                cv2.putText(result, "Red Laser", (cX - 20, cY - 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
                R_x = str(red_coords[0]).zfill(3)
                R_y = str(red_coords[1]).zfill(3)
                #print("R_x={},R_y={}".format(R_x, R_y))
                cv2.circle(result, (int(R_x), int(R_y)), 3, (0, 0, 255), -1)
                R_data = f"#{R_x},{R_y},)"
                serial_port.write(R_data.encode())
                print(R_data)
            # 处理绿激光点
        if mode == 3:
            red_coords, green_coords = detect_lasers(roi)
            # 处理红激光点
            if red_coords is not None:
                cX, cY = red_coords
                cv2.putText(result, "Red Laser", (cX - 20, cY - 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
                R_x = str(red_coords[0]).zfill(3)
                R_y = str(red_coords[1]).zfill(3)
                cv2.circle(result, (int(R_x), int(R_y)), 3, (0, 0, 255), -1)
                R_data = f"#{R_x},{R_y},)"
                serial_port.write(R_data.encode())
                print(R_data)
            if green_coords is not None:
                cX, cY = green_coords
                cv2.putText(result, "Green Laser", (cX - 20, cY - 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
                G_x = str(green_coords[0]).zfill(3)
                G_y = str(green_coords[1]).zfill(3)
                cv2.circle(result, (int(G_x), int(G_y)), 3, (0, 255, 0), -1)
                G_data = f"#{G_x},{G_y},G"
                print(G_data)
                serial_port.write(G_data.encode())
    frame_count += 1
    fps = 1 / (time.time() - start_time)
    start_time = time.time()
    cv2.putText(result, f"FPS: {fps:.2f}", (10, 25), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 0), 2)
    cv2.imshow('roi', roi)
    cv2.imshow('result', result)
    if serial_port.inWaiting() > 0:
        data = serial_port.read()
        if data == b'0':
            mode = 0
        elif data == b'1':
            mode = 1
        elif data == b'2':
            mode = 2
        elif data == b'3':
            mode = 3
        print(data)
        print(mode)
        serial_port.write(bytes([mode]))  # 将mode转换为字节并发送
    key = cv2.waitKey(1) & 0xFF
    if key == ord('1'):
        mode = 1
        print("Key 1 pressed")
    elif key == ord('2'):
        mode = 2
        print("Key 2 pressed")
    elif key == ord('3'):
        mode = 3
        print("Key 3 pressed")
    elif key == ord('q'):
        break
serial_port.close()
frame.release()
cv2.destroyAllWindows()
