# Furioos UE SDK
## Requirements
Minimum requirements: Business subscription (or higher) on Furioos to use the SDK.
Then choose the app you want to use with the SDK and create a SDK link.
**Unreal Engine 4.25++**

## Installation
1. Download the latest version of the Zip package.
2. Import the package in your project folder (into Plugins Folder)
3. Put the blueprint **FS_WebSocket_BP** in your scene

You'll need to have the **FS_WebSocket_BP** prefab in each scene with SDK interactions.

## Blueprint Usage
![ScreenShot](Resources/connect.PNG)

## Properties
#### debug: Boolean
Enable the local debug mode. Show messages in Output Log.

## Events
#### static OnOpen()
Bind an event that will be called when the application is connected to the Furioos streaming server and ready to communicate.

#### OnData(string data, byte[] rawData)
Bind an event that will be called everytime data is received.
- `string data`: The parsed data
- `byte[] rawData`: The raw data. Convert that data to JSON and parsed it by yourself to handle other types of data transfert. (float, int, etc...)

#### OnError(ErrorEventArgs events)
Bind an event that will be called each time an error is fired.
- `ErrorEventArgs events`

#### OnClose(CloseEventArgs events)
Bind an event that will be called when the connection with Furioos streaming server is closed.
- `callback: Function`: Implement your code.

## Methods
#### static FSSocket.Connect()
You can call this function to connect your application to the Furioos Streaming Server.
**As the script is a MonoBehavior script you don't need to call it at start.
Use this function to reconnect when you get an error or if the connection get close.**

#### static FSSocket.Send<T>(T data)
Send data to the JS client.
- `T data`: The data to send