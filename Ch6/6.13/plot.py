import numpy
import cv2
import os

def save_img(img, filename):
    cv2.imwrite(filename, img)

def enlarge(img, size):
    n, m = img.shape
    new_img = numpy.zeros((n * size, m * size))
    for i in range(n):
        for j in range(m):
            for a in range(size):
                for b in range(size):
                    new_img[i * size + a][j * size + b] = img[i][j]
    return new_img

if __name__ == '__main__':
    for file in os.listdir('output'):
        img = []
        print(os.path.join('output', file))
        with open(os.path.join('output', file), "r") as fp:
            for line in fp:
                pix = []
                for c in line:
                    if c == '\n':
                        break
                    if c == '.':
                        pix.append(255)
                    else:
                        pix.append(0)
                img.append(pix)
        img = numpy.array(img)
        img = enlarge(img, 20)
        save_img(img, 'output/' + file.replace('txt', 'png'))
