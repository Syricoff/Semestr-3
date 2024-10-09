from PIL import Image, ImageDraw, ImageFont

# Создание пустого изображения
width, height = 400, 300
image = Image.new("RGB", (width, height), "white")
draw = ImageDraw.Draw(image)

# Рисование крыши
roof = [(150, 100), (250, 100), (200, 50)]
draw.polygon(roof, fill="red")

# Рисование фасада
draw.rectangle([150, 100, 250, 200], fill="blue")

# Рисование забора
draw.rectangle([100, 200, 150, 250], fill="brown")
draw.rectangle([250, 200, 300, 250], fill="brown")

# Добавление надписи
font = ImageFont.load_default()
text = "HOUSE"

# Получение размеров текста
text_width, text_height = draw.textbbox((0, 0), text, font=font)[2:]

# Поворот текста на 180 градусов
text_image = Image.new("RGB", (text_width, text_height), "white")
text_draw = ImageDraw.Draw(text_image)
text_draw.text((0, 0), text, fill="black", font=font)

# Поворот текста
text_image = text_image.rotate(180, expand=True)

# Вставка текста на изображение
image.paste(text_image, (width // 2 - text_image.width // 2, 20))

# Сохранение изображения
image.save("house.png")
image.show()
