from PIL import Image


image_path = 'House.jpg'
img = Image.open(image_path)
img.show()
width, height = img.size
print(f"Изначальный размер изображения: {width} x {height}")

sizes = (int(width / 4), int(height / 4))
img.thumbnail(size=sizes)
width, height = img.size
print(f"Изменённый размер изображения: {width} x {height}")
img.show()
img.save('House.jpg')
