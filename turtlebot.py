import os
import requests
import turtle


SPARK_URL = 'https://api.spark.io/v1/devices/{device}/{action}/'


def send(action, *args):
    device = os.environ['TURTLEBOT_SPARK_DEVICE']
    access_token = os.environ['TURTLEBOT_SPARK_TOKEN']
    method = 'POST'

    url = SPARK_URL.format(device=device, action=action)
    data = {
        'access_token': access_token,
    }
    if args:
        data['args'] = str(args[0])

    print(method, url, data)
    session = requests.session()
    response = session.request(method, url, data=data)
    print(response)
    print(response.text)

def forward(distance):
    print('forward', distance)
    turtle.forward(distance)
    send('move', distance)

def backward(distance):
    print('backward', distance)
    turtle.backward(distance)
    send('move', -distance)

def left(angle):
    print('left', angle)
    turtle.left(angle)
    send('rotate', -angle)

def right(angle):
    print('right', angle)
    turtle.right(angle)
    send('rotate', -angle)
    
def penup():
    print('penup')
    turtle.penup()
    send('penmove', 1)

def pendown():
    print('pendown')
    turtle.pendown()
    send('penmove', -1)


def almost_rectangle_test():
    forward(50)

    left(90)
    forward(50)

    penup()
    right(90)
    backward(50)

    pendown()
    left(90)
    backward(50)

