import asyncio
import ffmpegaio


async def ffmpeg_exec():
    loop = asyncio.get_event_loop()
    future = loop.create_future()

    res = ffmpegaio.get_result(future, "323123")
    print(res)
    print(await res)

async def main():
    await ffmpeg_exec()


if __name__ == '__main__':
    asyncio.run(main())
"""
Fatal Python error: PyThreadState_Get: the function must be called with the GIL held, but the GIL is released (the current Python thread state is NULL)
Python runtime state: initialized

"""