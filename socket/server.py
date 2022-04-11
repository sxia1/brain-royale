import asyncio
import websockets
import json

async def respond(websocket):
    async for message in websocket:
        responseEvent = {'type': 'message', 'data': 'This is a response from the server'}
        await websocket.send(json.dumps(responseEvent))
        print(json.loads(message))

async def main():
    async with websockets.serve(respond, "localhost", 8000):
        await asyncio.Future()  # run forever

asyncio.run(main())