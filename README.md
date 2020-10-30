# Furioos UE SDK

This repository is in Beta, we do not provide support for it.

## Requirements
Minimum requirements: Business subscription (or higher) on Furioos to use the SDK.
Then choose the app you want to use with the SDK and create a SDK link.

**Tested on Unreal Engine 4.25.3 and 4.26-preview**

## Installation
1. Download the latest version of the Zip package.
2. Create a folder named "Plugins" in your project folder.
3. Extract the "FS_WebSocket" into Plugins Folder.
4. Launch your Unreal project (if your version of UE is different from 4.25.3, you will need a development IDE installed to compile the plugin again).
5. Put the blueprint **FS_WebSocket_BP** in your scene

![Alt text](/FS_WebSocket/Resources/unreal.png)

You'll need to have the **FS_WebSocket_BP** blueprint in each scene with SDK interactions.

## General Usage

When the plugin is installed and enabled, you will find a scene example with Blueprint and C++ class in LexelExample (to see the folders :)

![Alt text](/FS_WebSocket/Resources/display_pluginsfolders.PNG)

## Blueprint Usage

![Alt text](/FS_WebSocket/Resources/connect.png)

To connect to the websocket server, you will have to bind your event as shown in the example above.

## C++ Usage

### Events

#### FSOnConnectComplete()
Bind an event that will be called when the application is connected and signed in to the Furioos streaming server and ready to communicate.

#### FSOnReceiveData(FSstring data)
Bind an event that will be called everytime data is received.

- `FString data`: The parsed data

#### FSOnConnectError(FString error)
Bind an event that will be called each time an error is fired.

- `FString error`

#### FSOnClosed()
Bind an event that will be called when the connection with Furioos streaming server is closed.

### Methods

#### void Connect()
You can call this function to connect your application to the Furioos Streaming Server.

#### void SendSDKMessage(FString& data)
Send data to the JS client

- `FString data`: The data to send