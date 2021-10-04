

from PIL import Image

img = Image.open("./sourceImg.jpg") #could be modified to allow for file-as-arg

count = 0 #keeping it simple

rows = 8
cols = 8

w = 600 # width and height of desired frames. Usually measured from source img
h = 600

x_offset = 0 # x/y coordinates of starting pixel. Useful for centring/ off-centring image
y_offset = 0

margin = 10 # margin around each frame. Can be used to 'zoom' in/out


for i in range(rows):
	for e in range(cols):
		count+=1

		x = e * w + x_offset
		y = i * h + y_offset

		crop = img.crop((x-margin, y-margin, x+w+margin, y+h+margin))

		if(count <= (rows*cols)):
			crop.save("./export/frame"+str(count).zfill(3)+".jpg")

