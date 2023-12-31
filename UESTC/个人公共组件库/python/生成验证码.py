from PIL import Image, ImageFilter, ImageFont, ImageDraw
import random


def rnd_random():
    return chr(random.randint(48, 57))


def rnd_color():
    return random.randint(64, 255), random.randint(64, 255), random.randint(64, 255)


def rnd_color2():
    return random.randint(32, 127), random.randint(32, 127), random.randint(32, 127)


if __name__ == '__main__':
    width = 240
    height = 60
    image = Image.new('RGB', (width, height), (255, 255, 255))
    image.save('row.jpg', 'jpeg')
    font = ImageFont.truetype('C:\Windows\Fonts\Arial.ttf', 36)
    draw = ImageDraw.Draw(image)

    for x in range(width):
        for y in range(height):
            draw.point((x, y), fill=rnd_color())

    for t in range(4):
        draw.text((60 * t + 10, 10), rnd_random(), font=font, fill=rnd_color2())

    image = image.filter(ImageFilter.BLUR)
    image.save('code.jpg', 'jpeg')
