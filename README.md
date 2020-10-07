# Furioos UE SDK
## Requirements
Minimum requirements: Business subscription (or higher) on Furioos to use the SDK.
Then choose the app you want to use with the SDK and create a SDK link.

**Tested on Unreal Engine 4.25**

## Installation
1. Download the latest version of the Zip package.
2. Import the package in your project folder (into Plugins Folder)
3. Put the blueprint **FS_WebSocket_BP** in your scene

![Alt text](/FS_WebSocket/Resources/unreal.png)

You'll need to have the **FS_WebSocket_BP** blueprint in each scene with SDK interactions.

## Blueprint Usage

![Alt text](/FS_WebSocket/Resources/connect.png)

To connect to the websocket server, you will have to bind your event as shown in the example above.

## C++ Usage

In the zip file, you'll find an actor class example name : FSWS_Example

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

