from PIL import Image, ImageDraw
from math import sin, cos, pi

def rotate_image(angle):
    # Load image:
    input_image = Image.open("test.png")
    input_pixels = input_image.load()

    # Create output image
    output_image = Image.new("RGB", input_image.size)
    draw = ImageDraw.Draw(output_image)

    center_x = input_image.width / 2
    center_y = input_image.height / 2

    # Copy pixels
    for x in range(input_image.width):
        for y in range(input_image.height):
            # Compute coordinate in input image
            xp = int((x - center_x) * cos(angle) - (y - center_y) * sin(angle) + center_x)
            yp = int((x - center_x) * sin(angle) + (y - center_y) * cos(angle) + center_y)
            if 0 <= xp < input_image.width and 0 <= yp < input_image.height:
                draw.point((x, y), input_pixels[xp, yp])

    return output_image

import tkinter
from tkinter import *
from PIL import Image, ImageTk

root = Tk()

# Create a photoimage object of the image in the path
pil_img = rotate_image(-90)
test = ImageTk.PhotoImage(pil_img)

label1 = tkinter.Label(image=test)
label1.image = test

# Position image
label1.place(x=50, y=50)
mainloop()
